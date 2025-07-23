/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:05:20 by anlamber          #+#    #+#             */
/*   Updated: 2025/04/07 14:05:35 by anlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_unsigned(unsigned int n)
{
	int	len;

	len = 0;
	if (n >= 10)
	{
		len += print_unsigned(n / 10);
	}
	len += print_char((n % 10) + '0');
	return (len);
}
