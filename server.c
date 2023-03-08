/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: plopes-c <plopes-c@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:39:03 by chales            #+#    #+#             */
/*   Updated: 2023/03/08 20:44:11 by plopes-c         ###   ########.fr       */
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
	int					client_pid;
}				t_var;

static t_var			g_var;

void	handler(int signal, siginfo_t *info, void *context);
void	createstring(int signal, siginfo_t *info, void *context);

void	set_handler(void (*handler)(int signal, siginfo_t *info, void *context))
{
	g_var.sa.sa_sigaction = handler;
	g_var.sa.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &g_var.sa, 0);
	sigaction(SIGUSR2, &g_var.sa, 0);
}

int	client(int signal, siginfo_t *info)
{
	static int	current_pid;

	if (!signal)
	{
		write(1, "Error!Sig\n", 10);
		exit(EXIT_FAILURE);
	}
	if (!g_var.client_pid)
		g_var.client_pid = info->si_pid;
	current_pid = info->si_pid;
	if (g_var.client_pid != current_pid)
	{
		kill(current_pid, SIGUSR2);
		g_var.client_pid = 0;
		return (0);
	}
	return (1);
}

void	createstring(int signal, siginfo_t *info, void *context)
{
	static int			bit;
	static int			count;

	(void)context;
	(void)info;
	if (signal == SIGUSR1)
		count |= 1 << bit;
	else
		count |= 0 << bit;
	bit++;
	if (bit == 32)
	{
		g_var.g_string = ft_calloc((count + 1), sizeof(char));
		if (!g_var.g_string)
		{
			free(g_var.g_string);
			write(1, "Error!Malloc\n", 13);
			exit(EXIT_FAILURE);
		}
		set_handler(handler);
		bit = 0;
		g_var.len = count;
		count = 0;
	}
}

void	handler(int signal, siginfo_t *info, void *context)
{
	static int	bit;

	(void)context;
	if (!client(signal, info))
		return ;
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
			g_var.client_pid = 0;
			set_handler(createstring);
			kill(info->si_pid, SIGUSR1);
			g_var.i = 0;
			bit = 0;
			return ;
		}
		bit = 0;
		g_var.i++;
	}
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