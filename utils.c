/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luguilla <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/23 13:52:03 by luguilla          #+#    #+#             */
/*   Updated: 2022/06/23 14:02:14 by luguilla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	check_char(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static size_t	ft_word_count(char const *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static char	*ft_ptr_tab(char const *s, char c)
{
	char		*tab;
	size_t		i;
	size_t		j;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	tab = malloc(sizeof(char) * (i + 1));
	if (tab == NULL)
		return (NULL);
	j = 0;
	while (j < i)
	{
		tab[j] = s[j];
		j++;
	}
	tab[j] = '\0';
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	word_count;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	word_count = ft_word_count(s, c);
	tab = malloc(sizeof(char *) * (word_count + 1));
	if (tab == NULL)
		return (0);
	while (s[i] != '\0')
	{
		while (s[i] && s[i] == c)
			i++;
		if (s[i] && s[i] != c)
		{
			tab[j] = ft_ptr_tab(&s[i], c);
			j++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	tab[j] = 0;
	return (tab);
}
