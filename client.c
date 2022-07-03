/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaren <rmaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:44:49 by rmaren            #+#    #+#             */
/*   Updated: 2022/01/22 15:36:21 by rmaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	for_exit(void)
{
	write(1, "Message can't be send\n", 22);
	exit (0);
}

void	send_msg(int server_id, char *str, t_mini *g_mini)
{
	g_mini->i = -1;
	while (str[++g_mini->i])
	{
		g_mini->byte = 128;
		while (g_mini->byte)
		{
			if (g_mini->byte & str[g_mini->i])
			{
				if (kill(server_id, SIGUSR1) == -1)
					for_exit();
			}
			else
			{
				if (kill(server_id, SIGUSR2) == -1)
					for_exit();
			}
			g_mini->byte /= 2;
			pause();
			usleep(50);
		}
	}
}

void	received(int sig)
{
	static unsigned long	count;

	if (sig == SIGUSR1)
		++count;
	else
	{
		write (1, "\033[01;03;07;38;05;24;48;05;181mRecieved: \033[0m", 44);
		ft_putnbr_fd(count / 8 - 1, 1);
		write (1, "\n", 1);
		exit (0);
	}
}

int	main(int argc, char **argv)
{
	int					server_id;
	struct sigaction	sig_act;
	int					i;
	t_mini				g_mini;

	server_id = ft_atoi(argv[1]);
	sig_act.sa_handler = received;
	sig_act.sa_flags = SA_SIGINFO;
	if (argc != 3)
	{
		write (1, "Invalid number of parameters\n", 29);
		exit(1);
	}
	if (sigaction(SIGUSR1, &sig_act, NULL) == -1
		|| sigaction(SIGUSR2, &sig_act, NULL) == -1)
		write (2, "SIGERROR!\n", 10);
	send_msg(server_id, argv[2], &g_mini);
	send_msg(server_id, "\n", &g_mini);
	i = -1;
	while (++i < 8)
	{
		kill(server_id, SIGUSR2);
		pause();
		usleep(50);
	}
}
