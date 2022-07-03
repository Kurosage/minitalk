/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmaren <rmaren@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/18 13:44:56 by rmaren            #+#    #+#             */
/*   Updated: 2022/01/20 15:22:48 by rmaren           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <unistd.h>
# include <wchar.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_mini
{
	int				full_byte;
	unsigned char	chars_code;
	int				i;
	uint8_t			byte;
}	t_mini;

int		ft_atoi(char *str);
void	ft_putnbr_fd(int n, int fd);
void	ft_putchar_fd(char c, int fd);
void	for_exit(void);
void	send_msg(int server_id, char *str, t_mini *g_mini);
void	received(int sig);
void	print_that_resived(int sig, siginfo_t *siginfo, void *oact);
#endif