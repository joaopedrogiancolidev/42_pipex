/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:53:52 by jgiancol          #+#    #+#             */
/*   Updated: 2025/08/15 00:00:37 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *print, ...)
{
	va_list	args;
	int		i;
	int		count;

	va_start(args, print);
	i = 0;
	count = 0;
	while (print[i])
	{
		if (print[i] == '%' && print[i + 1] != '\0')
		{
			i++;
			count += filter_specifier(print[i], args);
		}
		else
		{
			count += ft_putchar(print[i]);
		}
		i++;
	}
	va_end(args);
	return (count);
}
