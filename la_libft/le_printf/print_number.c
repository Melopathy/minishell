/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_number.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:04:45 by anlamber          #+#    #+#             */
/*   Updated: 2025/04/07 14:05:04 by anlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_number(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		print_char('-');
		len++;
		n = -n;
	}
	if (n >= 10)
	{
		len += print_number(n / 10);
	}
	len += print_char((n % 10) + '0');
	return (len);
}
