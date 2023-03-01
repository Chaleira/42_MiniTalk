/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chales <chales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 13:39:03 by chales            #+#    #+#             */
/*   Updated: 2023/03/01 20:31:22 by chales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include "libft/libft.h"

void	handler(int signal)
{
	static int		bit;
	static char		c;

	if (!signal)
		exit(EXIT_FAILURE);
	if (signal == SIGUSR1)
		c |= 1 << bit;
	else
		c |= 0 << bit;
	if (bit == 7)
	{
		write(1, &c, 1);
		c = 0;
		bit = 0;
		bit--;
	}
	bit++;
	usleep(100);
}

int	main(void)
{
	pid_t						pid;
	static struct	sigaction	sa;

	pid = getpid();
	ft_printf("PID : %d\n", pid);
	sa.sa_handler = &handler;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
