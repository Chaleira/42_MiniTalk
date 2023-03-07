/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:39:03 by chales            #+#    #+#             */
/*   Updated: 2023/03/07 18:49:41 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "libft/libft.h"

void	handler(int signal, siginfo_t *info, void *context);

static char	*g_string;

void	s_error(void)
{
	ft_printf("Error!\n");
	exit(EXIT_FAILURE);
}

int	client(int signal, siginfo_t *info, int *bit, void *s)
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
		s = 0;
	}
	return (client_pid);
}

void	createstring(int signal, siginfo_t *info, void *context)
{
	static int			bit;
	static int			count;
	struct sigaction	sa;

	(void)context;
	client(signal, info, &bit, &count);
	if (signal == SIGUSR1)
		count |= 1 << bit;
	else
		count |= 0 << bit;
	bit++;
	if (bit == 32)
	{
		g_string = ft_calloc(count + 1, sizeof(char));
		if (!g_string)
			return ;
		sa.sa_sigaction = handler;
		sa.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR1, &sa, 0);
		sigaction(SIGUSR2, &sa, 0);
		bit = 0;
		count = 0;
	}
	else
		kill(info->si_pid, SIGUSR2);
}

void	handler(int signal, siginfo_t *info, void *context)
{
	static int			bit;
	static int			i;
	struct sigaction	sa;

	(void)context;
	client(signal, info, &bit, g_string);
	if (signal == SIGUSR1)
		g_string[i] |= 1 << bit;
	else
		g_string[i] |= 0 << bit;
	bit++;
	if (bit == 8)
	{
		if (g_string[i] == '\0')
		{
			ft_putstr(g_string);
			free(g_string);
			if (kill(info->si_pid, SIGUSR1) == -1)
				s_error();
			sa.sa_sigaction = createstring;
			sa.sa_flags = SA_SIGINFO;
			sigaction(SIGUSR1, &sa, 0);
			sigaction(SIGUSR2, &sa, 0);
			i = -1;
		}
		bit = 0;
		i++;
	}
	else
		kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	sa;

	pid = getpid();
	ft_printf("PID : %d\n", pid);
	sa.sa_sigaction = createstring;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	while (1)
		pause();
	return (0);
}

// asbdcasbdcasbdcasbdcasbdcasbdcasbdcasbdcasbdcasbda