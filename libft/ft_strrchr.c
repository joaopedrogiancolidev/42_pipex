/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:07:43 by jgiancol          #+#    #+#             */
/*   Updated: 2025/07/28 13:37:29 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char		ch;
	const char	*p;

	ch = (char)c;
	p = (char *)s + ft_strlen(s);
	if (!ch)
		return ((char *)p);
	while (p >= s)
	{
		if (*p == ch)
			return ((char *)p);
		p--;
	}
	return (NULL);
}
