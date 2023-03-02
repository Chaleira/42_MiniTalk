/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chales <chales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:39:03 by chales            #+#    #+#             */
/*   Updated: 2023/03/02 16:12:26 by chales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

void	s_error(void)
{
	ft_printf("Error!\n");
	exit(EXIT_FAILURE);
}

int	client(int signal, siginfo_t *info, int *bit, char *c)
{
	static int	current_pid;
	static int	client_pid;

	if (!signal)
		s_error();
	if (!client_pid)
		client_pid = info->si_pid;
	current_pid = info->si_pid;
	if (client_pid != current_pid)
	{
		client_pid = current_pid;
		*bit = 0;
		*c = 0;
	}
	return (client_pid);
}

void	handler(int signal, siginfo_t *info, void *context)
{
	static int		bit;
	static char		c;
	int				client_pid;

	(void)context;
	client_pid = client(signal, info, &bit, &c);
	if (signal == SIGUSR1)
		c |= 1 << bit;
	else
		c |= 0 << bit;
	bit++;
	if (bit == 8)
	{
		write(1, &c, 1);
		if (c == '\0')
		{
			if (kill(client_pid, SIGUSR1) == -1)
				s_error();
			c = 0;
		}
		c = 0;
		bit = 0;
	}
	usleep(200);
	kill(client_pid, SIGUSR2);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	ft_printf("PID : %d\n", pid);
	sa.sa_sigaction = handler;
	while (1)
	{
		sigaction(SIGUSR1, &sa, 0);
		sigaction(SIGUSR2, &sa, 0);
		pause();
	}
	return (0);
}
