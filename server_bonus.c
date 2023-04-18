/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 18:20:13 by plopes-c          #+#    #+#             */
/*   Updated: 2023/04/18 17:44:04 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "libft/libft.h"

typedef struct s_var
{
	char				*string;
	int					len;
}				t_var;

static t_var			g_var;

void	handler(int signal, siginfo_t *info, void *context);
void	createstring(int signal, siginfo_t *info, void *context);

void	set_handler(void (*handler)(int signal, siginfo_t *info, void *context))
{
	static struct sigaction	sa;

	sa.sa_sigaction = handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, 0);
	sigaction(SIGUSR2, &sa, 0);
}

void	createstring(int signal, siginfo_t *info, void *context)
{
	static int	bit;
	static int	count;

	(void)context;
	if (signal == SIGUSR1)
		count |= 1 << bit;
	bit++;
	if (bit == 32)
	{
		g_var.string = ft_calloc((count + 1), sizeof(char));
		if (!g_var.string)
		{
			write(1, "Error!Malloc\n", 13);
			exit(EXIT_FAILURE);
		}
		set_handler(handler);
		g_var.len = count;
		bit = 0;
		count = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

void	handler(int signal, siginfo_t *info, void *context)
{
	static int	bit;
	static int	i;

	(void)context;
	if (signal == SIGUSR1)
		g_var.string[i] |= 1 << bit;
	bit++;
	if (bit == 8)
	{
		i++;
		if (i == g_var.len)
		{
			write(1, g_var.string, g_var.len);
			free(g_var.string);
			set_handler(createstring);
			kill(info->si_pid, SIGUSR1);
			i = 0;
		}
		bit = 0;
	}
	kill(info->si_pid, SIGUSR2);
}

int	main(void)
{
	pid_t	pid;

	pid = getpid();
	ft_printf("PID : %d\n", pid);
	set_handler(createstring);
	while (1)
		pause();
	return (0);
}
