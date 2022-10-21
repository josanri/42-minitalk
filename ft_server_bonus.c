/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_server_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josesanc <josesanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 10:23:03 by josesanc          #+#    #+#             */
/*   Updated: 2022/10/12 11:57:21 by josesanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk_bonus.h"

static void	ft_putnbr_rec(int n)
{
	char	towrite;

	if (n != 0)
	{
		if (n < 0)
			towrite = '0' - (n % 10);
		else
			towrite = '0' + (n % 10);
		ft_putnbr_rec(n / 10);
		write(1, &towrite, 1);
	}
}

static void	ft_putnbr_server(int n)
{
	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (n < 0)
		write(1, "-", 1);
	ft_putnbr_rec(n);
}

void	ft_signal_handler_server(int signalNum, siginfo_t *info, void *ucontext)
{
	static char		c = 0;
	static int		i = 7;

	(void) ucontext;
	if (signalNum == SIGUSR2)
		c = c | (1 << i);
	i--;
	if (i < 0)
	{
		i = 7;
		if (c != 0)
		{
			if (write(1, &c, 1) < 1)
				exit(1);
			c = 0;
		}
		else
		{
			if (kill(info->si_pid, SIGUSR2) == -1)
				exit(1);
			return ;
		}
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		exit(1);
}

int	main(void)
{
	struct sigaction	sig;

	sigemptyset(&sig.sa_mask);
	sig.sa_flags = SA_SIGINFO | SA_RESTART | SA_NODEFER;
	sig.sa_sigaction = ft_signal_handler_server;
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	write(1, "\033[0;33mServer PID:\033[0;37m", 25);
	ft_putnbr_server(getpid());
	write(1, "\n", 1);
	while (1)
	{
		pause();
	}
	return (0);
}
