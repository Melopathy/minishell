/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:06:21 by anlamber          #+#    #+#             */
/*   Updated: 2025/04/07 14:06:37 by anlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(unsigned long n, int uppercase)
{
	int		len;
	char	*base;

	len = 0;
	if (uppercase)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
	{
		len += print_hex(n / 16, uppercase);
	}
	len += print_char(base[n % 16]);
	return (len);
}
