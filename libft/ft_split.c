/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maneddam <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/17 00:04:10 by maneddam          #+#    #+#             */
/*   Updated: 2023/03/17 00:04:12 by maneddam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

static size_t	count_words(const char *str, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	while (str[i] && str[i] == c)
		i++;
	while (str[i])
	{
		if (str[i] == c && str[i + 1] != c)
		{
			count++;
		}
		i++;
	}
	if (str[i - 1] != c && str[i] == '\0')
		count++;
	return (count);
}

static size_t	word_len(const char *s, char c)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = 0;
	while (s[i] == c && s[i])
	{
		i++;
	}
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

void	ft_free(char **tab, size_t i)
{
	while (i > 0)
	{
		i--;
		free(tab[i]);
	}
	free(tab);
}

static char	**fill_ptr(char **ptr, char *s, size_t words_num, char c)
{
	size_t	i;
	size_t	j;
	size_t	k;

	i = 0;
	j = 0;
	k = 0;
	while (i < words_num)
	{
		while (s[j] && s[j] == c)
			j++;
		ptr[i] = malloc(word_len(s + j, c) + 1);
		if (!ptr[i])
		{
			ft_free(ptr, i);
			return (NULL);
		}
		k = 0;
		while (s[j] && s[j] != c)
			ptr[i][k++] = s[j++];
		ptr[i][k] = '\0';
		i++;
	}
	ptr[i] = NULL;
	return (ptr);
}

char	**ft_split(char *s, char c)
{
	char	**ptr;
	size_t	words_num;

	if (!s)
	{
		return (NULL);
	}
	if (s[0] != '\0')
		words_num = count_words(s, c);
	else
		words_num = 0;
	ptr = (char **)malloc(sizeof(char *) * (words_num + 1));
	if (!ptr)
		return (NULL);
	return (fill_ptr(ptr, s, words_num, c));
}
