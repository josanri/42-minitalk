/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: josesanc <josesanc@student.42malaga.com>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 10:50:40 by josesanc          #+#    #+#             */
/*   Updated: 2022/10/12 10:54:55 by josesanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_minitalk.h"

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

void	ft_putnbr(int n)
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
