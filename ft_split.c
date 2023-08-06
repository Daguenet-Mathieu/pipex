/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: madaguen <madaguen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 19:25:13 by madaguen          #+#    #+#             */
/*   Updated: 2023/08/06 21:45:50 by madaguen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	is_sep(char c, char a)
{
	if (c == a)
		return (1);
	return (0);
}

static char	get_nb_word(char *s, char c)
{
	int	i;
	int	word;

	i = 0;
	word = 0;
	if (*s == 0)
		return (0);
	if (!is_sep(c, s[i]))
		word++;
	i++;
	while (s[i])
	{
		if (is_sep(c, s[i - 1]) == 1 && is_sep(c, s[i]) == 0)
			word++;
		i++;
	}
	return (word);
}

static char	*get_word(char *s, char c, int *i)
{
	char	*new_word;
	int		a;
	int		j;

	a = 0;
	j = 0;
	if (!s)
		return (NULL);
	while (s[*i] && is_sep(c, s[*i]))
		(*i)++;
	while (s[*i + j] && !is_sep(c, s[*i + j]))
		j++;
	new_word = malloc(sizeof(char) * (j + 1));
	if (!new_word)
		return (NULL);
	while (a < j)
	{
		new_word[a] = s[*i];
		a++;
		(*i)++;
	}
	new_word[a] = '\0';
	return (new_word);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		j;
	char	**tab;
	int		nb_word;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	nb_word = get_nb_word((char *)s, c);
	tab = malloc(sizeof(char *) * (nb_word + 1));
	if (!tab)
		return (NULL);
	while (j < nb_word)
	{
		tab[j] = get_word((char *)s, c, &i);
		if (!tab[j])
		{
			ft_freetab(tab);
			return (NULL);
		}
		j++;
	}
	tab[j] = NULL;
	return (tab);
}
