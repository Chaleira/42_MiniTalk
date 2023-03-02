/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chales <chales@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/27 12:20:41 by chales            #+#    #+#             */
/*   Updated: 2023/03/02 17:58:09 by chales           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>
#include "libft/libft.h"

void	s_error(void)
{
	ft_printf("Error!\n");
	exit(EXIT_FAILURE);
}

void	confirm_receive(int signal)
{
	static int	sent;

	if (signal == SIGUSR1)
	{
		ft_printf("Success, message sent!\n");
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
				s_error();
		}
		else
		{
			if (kill(pid, SIGUSR2) == -1)
				s_error();
		}
		i++;
		usleep(500);
	}
}

int	main(int ac, char	*av[])
{
	pid_t	server_pid;
	int		count;

	if (ac == 3)
	{
		signal(SIGUSR1, confirm_receive);
		signal(SIGUSR2, confirm_receive);
		server_pid = ft_atoi(av[1]);
		count = 0;
		while (av[2] && av[2][count] != '\0')
		{
			sender(av[2][count], server_pid);
			++count;
		}
		sender('\0', server_pid);
	}
	else
	{
		ft_printf("Usage : ./client <pid> <msg>\n");
		exit(EXIT_FAILURE);
	}
}
