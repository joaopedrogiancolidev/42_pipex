/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specifier_nbrs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 23:58:39 by jgiancol          #+#    #+#             */
/*   Updated: 2025/08/14 23:58:40 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_p(va_list args)
{
	void			*ptr;
	int				count;

	ptr = va_arg(args, void *);
	if (!ptr)
		return (ft_putstr("(nil)"));
	count = 0;
	count += ft_putstr("0x");
	count += ft_puthex((unsigned long)ptr, "0123456789abcdef");
	return (count);
}

int	print_u(va_list args)
{
	unsigned int	n;

	n = va_arg(args, unsigned int);
	return (ft_putnbr_un(n));
}

int	print_x(va_list args)
{
	unsigned int	n;

	n = va_arg(args, unsigned int);
	return (ft_puthex(n, "0123456789abcdef"));
}

int	print_x_upper(va_list args)
{
	unsigned int	n;

	n = va_arg(args, unsigned int);
	return (ft_puthex(n, "0123456789ABCDEF"));
}
