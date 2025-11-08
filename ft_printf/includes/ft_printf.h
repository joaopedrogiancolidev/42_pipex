/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/14 19:58:46 by jgiancol          #+#    #+#             */
/*   Updated: 2025/08/19 15:50:34 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdlib.h>
# include <stddef.h>
# include <unistd.h>

int	ft_printf(const char *format, ...);
int	filter_specifier(char specifier, va_list args);

int	ft_putchar(char c);
int	ft_putstr(char *str);
int	ft_putnbr(int nb);
int	ft_putnbr_un(unsigned int n);
int	ft_puthex(unsigned long n, const char *base);

int	print_c(va_list args);
int	print_s(va_list args);
int	print_p(va_list args);
int	print_d(va_list args);
int	print_i(va_list args);
int	print_u(va_list args);
int	print_x(va_list args);
int	print_x_upper(va_list args);

#endif