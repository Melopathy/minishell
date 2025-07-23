/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 11:37:18 by anlamber          #+#    #+#             */
/*   Updated: 2025/04/02 12:42:20 by anlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t					i;
	unsigned char			*ptr;
	const unsigned char		*source;

	source = (const unsigned char *)src;
	ptr = (unsigned char *)dest;
	if (dest < src)
	{
		i = 0;
		while (i < n)
		{
			ptr[i] = source[i];
			i++;
		}
	}
	else
	{
		i = n;
		while (i > 0)
		{
			i--;
			ptr[i] = source[i];
		}
	}
	return (dest);
}
