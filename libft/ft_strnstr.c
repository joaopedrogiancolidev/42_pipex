/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/26 21:24:13 by jgiancol          #+#    #+#             */
/*   Updated: 2025/07/26 21:59:46 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t n)
{
	size_t	little_len;
	size_t	i;
	size_t	j;

	little_len = ft_strlen(little);
	if (big == little || little_len == 0)
		return ((char *)big);
	i = 0;
	while (i < n && big[i] != '\0')
	{
		j = 0;
		while (big[i + j] != '\0' && little[j] != '\0'
			&& (i + j) < n && big[i + j] == little[j])
		{
			j++;
			if ((j == n && j == little_len) || j == little_len)
				return ((char *)(big + i));
		}
		i++;
	}
	return (0);
}
