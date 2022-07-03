/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaren <rmaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:44:45 by rmaren            #+#    #+#             */
/*   Updated: 2022/01/22 15:36:35 by rmaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_mini	g_mini;

void	print_that_resived(int sig, siginfo_t *siginfo, void *oact)
{
	static int		i;

	(void)oact;
	if (sig == SIGUSR1)
		g_mini.chars_code += g_mini.full_byte;
	g_mini.full_byte /= 2;
	if (++i == 8)
	{
		if (!g_mini.chars_code)
		{
			kill(siginfo->si_pid, SIGUSR2);
			g_mini.full_byte = 128;
			i = 0;
			return ;
		}
		write(1, &g_mini.chars_code, 1);
		g_mini.full_byte = 128;
		g_mini.chars_code = 0;
		i = 0;
	}
	usleep(150);
	kill(siginfo->si_pid, SIGUSR1);
}

int	main(void)
{
	pid_t				server_id;
	struct sigaction	sig_act;

	g_mini.full_byte = 128;
	g_mini.chars_code = 0;
	server_id = getpid();
	write(1, "\033[01;03;07;38;05;24;48;05;181mいらっしゃいませ！！！サーバーのPID: ", 83);
	ft_putnbr_fd(server_id, 1);
	write(1, "\033[0m\n", 5);
	sig_act.sa_sigaction = print_that_resived;
	sig_act.sa_flags = SA_SIGINFO;
	if (sigaction(SIGUSR1, &sig_act, NULL) == -1
		|| sigaction(SIGUSR2, &sig_act, NULL) == -1)
		write (2, "SIGERROR!\n", 10);
	while (1)
		pause();
	return (0);
}
