/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 20:22:05 by jgiancol          #+#    #+#             */
/*   Updated: 2025/07/26 20:45:14 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	char	*dest_end;

	dest_len = ft_strlen(dest);
	src_len = ft_strlen(src);
	dest_end = dest + dest_len;
	if (size <= dest_len)
		return (size + src_len);
	size -= dest_len;
	while (*src && --size)
		*dest_end++ = *src++;
	*dest_end = '\0';
	return (dest_len + src_len);
}
