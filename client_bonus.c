/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:31:48 by arohmann          #+#    #+#             */
/*   Updated: 2021/10/19 11:01:15 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_send_bits(pid_t pid, char *str)
{
	int	i;
	int	bit;
	int	bytes;

	i = 0;
	bytes = 0;
	while (str[i])
	{
		bit = 1;
		while (bit < 256)
		{
			usleep(80);
			if ((str[i] & bit) == bit)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			bit *= 2;
			pause();
		}
		bytes++;
		i++;
	}
	ft_putstr_fd("Bytes send and received ", 0);
	ft_putnbr_fd(bytes, 0);
}

void	sig_handler(int signum)
{
	signum = 0;
}

int	main(int argc, char **argv)
{
	if (argc == 3 && (ft_atoi(argv[1]) != 0))
	{
		signal(SIGUSR1, sig_handler);
		ft_send_bits(ft_atoi(argv[1]), argv[2]);
	}
	else
		write(1, "Wrong input! Try: ./client [PID] [Message]\n", 44);
	return (0);
}
