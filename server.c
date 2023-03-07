/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:39:03 by chales            #+#    #+#             */
/*   Updated: 2023/03/07 20:38:41 by plopes-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include "libft/libft.h"

typedef struct s_var
{
	char				*g_string;
	int					len;
	int					i;
	struct sigaction	sa;
}				t_var;

static t_var			g_var;

void	handler(int signal, siginfo_t *info, void *context);

void	set_handler(void (*handler)(int signal, siginfo_t *info, void *context))
{
	g_var.sa.sa_sigaction = handler;
	g_var.sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &g_var.sa, 0);
	sigaction(SIGUSR2, &g_var.sa, 0);
}

void	client(int signal, siginfo_t *info, int *bit, void *s)
{
	static int	current_pid;
	static int	client_pid;

	if (!signal)
	{
		write(1, "Error!\n", 7);
		exit(EXIT_FAILURE);
	}
	if (!client_pid)
		client_pid = info->si_pid;
	current_pid = info->si_pid;
	if (client_pid != current_pid)
	{
		client_pid = current_pid;
		*bit = 0;
		s = 0;
	}
}

void	createstring(int signal, siginfo_t *info, void *context)
{
	static int			bit;
	static int			count;

	(void)context;
	client(signal, info, &bit, &count);
	if (signal == SIGUSR1)
		count |= 1 << bit;
	else
		count |= 0 << bit;
	bit++;
	if (bit == 32)
	{
		g_var.g_string = ft_calloc(count + 1, sizeof(char));
		if (!g_var.g_string)
			return ;
		set_handler(handler);
		bit = 0;
		g_var.len = count;
		count = 0;
	}
	else
		kill(info->si_pid, SIGUSR2);
}

void	handler(int signal, siginfo_t *info, void *context)
{
	static int	bit;

	(void)context;
	client(signal, info, &bit, g_var.g_string);
	if (signal == SIGUSR1)
		g_var.g_string[g_var.i] |= 1 << bit;
	else
		g_var.g_string[g_var.i] |= 0 << bit;
	bit++;
	if (bit == 8)
	{
		if (g_var.g_string[g_var.i] == '\0')
		{
			write(1, g_var.g_string, g_var.len);
			free(g_var.g_string);
			kill(info->si_pid, SIGUSR1);
			set_handler(createstring);
			g_var.i = -1;
		}
		bit = 0;
		g_var.i++;
	}
	else
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

// asbdcasbdcasbdcasbdcasbdcasbdcasbdcasbdcasbdcasbda