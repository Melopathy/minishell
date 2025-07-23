/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:05:55 by anlamber          #+#    #+#             */
/*   Updated: 2025/04/07 14:06:12 by anlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_pointer(void *p)
{
	int				len;
	unsigned long	address;

	if (!p)
		return (print_string("(nil)"));
	len = 0;
	len += print_string("0x");
	address = (unsigned long)p;
	len += print_hex(address, 0);
	return (len);
}
