/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgiancol <jgiancol@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/21 17:31:53 by jgiancol          #+#    #+#             */
/*   Updated: 2025/09/25 21:03:14 by jgiancol         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_words(char const *s, char c)
{
	char	*str;
	int		count_words;
	int		delimiter_checker;

	str = (char *)s;
	count_words = 0;
	delimiter_checker = 1;
	while (*str != '\0')
	{
		if (*str == c)
			delimiter_checker = 1;
		else if (delimiter_checker == 1)
		{
			delimiter_checker = 0;
			count_words++;
		}
		str++;
	}
	return (count_words);
}

static char	*copy_word(const char *start, const char *end)
{
	char	*word;

	word = malloc(end - start + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, start, end - start + 1);
	return (word);
}

static void	ft_free_array(char **arr, int i)
{
	while (i-- > 0)
		free(arr[i]);
	free(arr);
}

static int	fill_result(char **result, char const *s, char c)
{
	int			i;
	const char	*word_start;

	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (!*s)
			break ;
		word_start = s;
		while (*s && *s != c)
			s++;
		result[i] = copy_word(word_start, s);
		if (!result[i])
		{
			ft_free_array(result, i);
			return (-1);
		}
		i++;
	}
	result[i] = NULL;
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	if (fill_result(result, s, c) == -1)
		return (NULL);
	return (result);
}
