/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arohmann <arohmann@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 10:32:57 by arohmann          #+#    #+#             */
/*   Updated: 2021/10/19 10:33:01 by arohmann         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	ft_send_bits(pid_t pid, char *str)
{
	int	i;
	int	bit;

	i = 0;
	while (str[i])
	{
		bit = 1;
		while (bit < 256)
		{
			if ((str[i] & bit) == bit)
				kill(pid, SIGUSR2);
			else
				kill(pid, SIGUSR1);
			bit *= 2;
			usleep(37);
		}
		i++;
	}
	if (str[i] == '\0')
		write(1, "Everything done.", 17);
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;

	if (argc == 3)
	{
		ft_send_bits(ft_atoi(argv[1]), argv[2]);
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
	}
	else
		write(1, "Wrong input! Try: ./client [PID] [Message]\n", 44);
	return (0);
}
