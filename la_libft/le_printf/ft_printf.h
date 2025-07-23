/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:21:46 by anlamber          #+#    #+#             */
/*   Updated: 2025/04/02 16:22:20 by anlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int	print_char(char c);
int	print_string(const char *s);
int	print_number(long n);
int	print_unsigned(unsigned int n);
int	print_hex(unsigned long n, int uppercase);
int	print_pointer(void *p);
int	ft_printf(const char *format, ...);

#endif
