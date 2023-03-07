/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:20:41 by chales            #+#    #+#             */
/*   Updated: 2023/03/07 20:32:31 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "libft/libft.h"

void	error_msg(void)
{
	write(1, "Error!\n", 7);
	exit(EXIT_FAILURE);
}

void	confirm_receive(int signal, siginfo_t *info, void *context)
{
	static int	sent;

	(void)context;
	(void)info;
	if (signal == SIGUSR1)
	{
		write(1, "Success, message sent!\n", 23);
		exit(EXIT_SUCCESS);
	}
	if (signal == SIGUSR2)
		sent++;
}

void	sender(char c, pid_t pid)
{
	int				i;

	i = 0;
	while (i <= 7)
	{
		if (c & (1 << i))
		{
			if (kill(pid, SIGUSR1) == -1)
				error_msg();
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				error_msg();
		}
		i++;
		usleep(100);
	}
	usleep(150);
}

void	send_count(int count, pid_t pid)
{
	int	i;

	i = 0;
	while (i <= 31)
	{
		if (count & (1 << i))
		{
			if (kill(pid, SIGUSR1) == -1)
				error_msg();
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				error_msg();
		}
		i++;
		usleep(100);
	}
	usleep(150);
}

int	main(int ac, char	*av[])
{
	pid_t				server_pid;
	int					count;
	struct sigaction	sa;

	count = 0;
	if (ac != 3)
	{
		ft_putstr("Usage : ./client <pid> <msg>\n");
		exit(EXIT_FAILURE);
	}
	sa.sa_sigaction = confirm_receive;
	sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
	server_pid = ft_atoi(av[1]);
	send_count(ft_strlen(av[2]), server_pid);
	while (av[2] && av[2][count] != '\0')
	{
		sender(av[2][count], server_pid);
		++count;
	}
	sender('\0', server_pid);
}
