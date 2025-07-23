/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_string.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 14:04:18 by anlamber          #+#    #+#             */
/*   Updated: 2025/04/07 14:04:34 by anlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_string(const char *s)
{
	int	len;

	len = 0;
	if (!s)
		return (len += print_string("(null)"));
	while (*s)
		len += write(1, s++, 1);
	return (len);
}
