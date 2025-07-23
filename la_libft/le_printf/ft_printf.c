/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anlamber <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 16:22:47 by anlamber          #+#    #+#             */
/*   Updated: 2025/04/02 16:25:50 by anlamber         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
   %c : character
   %s : string
   %p : pointer in hexadecimal format
   %d : signed decimal
   %i : signed decimal
   %u : unsigned decimal
   %x : hexadecimal (lowercase)
   %X : hexadecimal (uppercase)
   %% : percent sign
*/
// cspdiuxX%

#include "ft_printf.h"

int	handle_format(const char *format, int *i, va_list args)
{
	int	count;

	count = 0;
	if (format[*i] == 'c')
		count += print_char(va_arg(args, int));
	else if (format[*i] == 's')
		count += print_string(va_arg(args, const char *));
	else if (format[*i] == 'p')
		count += print_pointer(va_arg(args, void *));
	else if (format[*i] == 'd' || format[*i] == 'i')
		count += print_number(va_arg(args, int));
	else if (format[*i] == 'u')
		count += print_unsigned(va_arg(args, unsigned int));
	else if (format[*i] == 'x')
		count += print_hex(va_arg(args, unsigned int), 0);
	else if (format[*i] == 'X')
		count += print_hex(va_arg(args, unsigned int), 1);
	else if (format[*i] == '%')
		count += print_char('%');
	(*i)++;
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		i;
	int		count;
	va_list	args;

	i = 0;
	count = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i++;
			count += handle_format(format, &i, args);
		}
		else
		{
			print_char(format[i]);
			i++;
			count++;
		}
	}
	va_end(args);
	return (count);
}

/*int main(void)
{

	ft_printf("Test 1: %c\n",'c');
	ft_printf("Test 2: %s\n","sadf");
	ft_printf("Test 3: %p\n", 6);
	ft_printf("Test 4: %d\n", -42);
	ft_printf("Test 4: %d\n", 42);
	ft_printf("Test 4: %d\n", -1);
	ft_printf("Test 4: %d\n", -200000);
	ft_printf("Test 5: %i\n", 2100000000);
	ft_printf("Test 6: %u\n", 4200000000);
	ft_printf("Test 7: %x\n", 255);
	ft_printf("Test 8: %X\n", 255);
}*/
