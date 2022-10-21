/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_client.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josesanc <josesanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:25:07 by josesanc          #+#    #+#             */
/*   Updated: 2022/10/12 12:16:13 by josesanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"
#include <stdio.h>

int	g_mutex;

static int	ft_atoi(const char *str)
{
	int		res;
	int		negative;
	size_t	cont;

	res = 0;
	negative = 0;
	cont = 0;
	while ((str[cont] >= 9 && str[cont] <= 13) || str[cont] == ' ')
		cont++;
	if (str[cont] == '+' || str[cont] == '-')
		if (str[cont++] == '-')
			negative = 1;
	while (str[cont] >= '0' && str[cont] <= '9')
	{
		if (negative)
			res = (res * 10) - (str[cont] - '0');
		else
			res = (res * 10) + (str[cont] - '0');
		cont++;
	}
	return (res);
}

void	ft_signal_handler_client(int signalNum)
{
	static int	cont = 0;

	if (signalNum == SIGUSR1)
		cont++;
	else if (signalNum == SIGUSR2)
	{
		write(1, "OK: ", 2);
		ft_putnbr(cont + 1);
		write(1, "\n", 1);
		exit(0);
	}
	g_mutex = 1;
}

void	ft_sending(pid_t	server_pid, char str)
{
	int	position;

	position = 7;
	while (position >= 0)
	{
		g_mutex = 0;
		if (str & (1 << position--))
		{
			if (kill(server_pid, SIGUSR2) == -1)
				exit(1);
		}
		else
		{
			if (kill(server_pid, SIGUSR1) == -1)
				exit(1);
		}
		while (g_mutex == 0)
			usleep(1);
	}
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	int					i;
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	sig.sa_handler = ft_signal_handler_client;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	if (argc != 3)
		return (write(1, "Should have two arguments\n", 26), -1);
	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		return (write(1, "The PID is not valid\n", 21), -1);
	i = 0;
	while (argv[2][i] != 0)
	{
		ft_sending(server_pid, argv[2][i]);
		i++;
	}
	ft_sending(server_pid, 0);
	return (0);
}
