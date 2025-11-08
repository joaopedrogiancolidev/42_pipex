/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_filter.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:54:57 by jgiancol          #+#    #+#             */
/*   Updated: 2025/08/15 00:00:04 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	filter_specifier(char specifier, va_list args)
{
	if (specifier == 'c')
		return (print_c(args));
	else if (specifier == 's')
		return (print_s(args));
	else if (specifier == 'p')
		return (print_p(args));
	else if (specifier == 'd')
		return (print_d(args));
	else if (specifier == 'i')
		return (print_i(args));
	else if (specifier == 'u')
		return (print_u(args));
	else if (specifier == 'x')
		return (print_x(args));
	else if (specifier == 'X')
		return (print_x_upper(args));
	else if (specifier == '%')
		return (ft_putchar('%'));
	return (0);
}
