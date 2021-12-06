/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:29:14 by arohmann          #+#    #+#             */
/*   Updated: 2021/10/19 11:00:34 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int	signum, siginfo_t *info, void *context)
{
	static int	i = 0;
	static int	bit = 1;

	(void)context;
	(void)info;
	if (signum == SIGUSR2)
		i = i + bit;
	bit = bit * 2;
	if (bit > 128)
	{
		write(1, &i, 1);
		bit = 1;
		i = 0;
	}
	usleep(50);
	kill(info->si_pid, SIGUSR1);
}

/*
**	The main function of "server"
**	sigaction() will receive the signals from "client"
**	getpid() will output the process ID of the server
**	an endless loop waiting for the clients signals starts
*/
int	main(void)
{
	struct sigaction	sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = sig_handler;
	write(1, "Server PID: ", 13);
	ft_putnbr_fd(getpid(), 0);
	write(1, "\n", 1);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
