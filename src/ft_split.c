/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:50:31 by shamizi           #+#    #+#             */
/*   Updated: 2021/10/21 14:13:11 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

char	**freestrings(char **tab)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

static int	nb_mot(char *s, char c)
{
	int		i;
	int		j;
	int		compt;

	i = 0;
	j = 0;
	compt = 0;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] == c)
			j = 0;
		else if (j == 0)
		{
			j = 1;
			compt++;
		}
		i++;
	}
	return (compt);
}

static int	len_word(char *s, char c, int i)
{
	int		len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

static char	**affect(char *s, char **tab, char c, int l)
{
	int		i;
	int		j;
	int		k;

	i = 0;
	j = 0;
	while (s[i] && j < l)
	{
		k = 0;
		while (s[i] == c)
			i++;
		tab[j] = malloc(sizeof(char) * (len_word(s, c, i) + 1));
		if (tab[j] == NULL)
			return (freestrings(tab));
		while (s[i] && s[i] != c)
			tab[j][k++] = s[i++];
		tab[j][k] = '\0';
		j++;
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(char *s, char c)
{
	char	**tab;
	int		i;

	if (!s)
		return (NULL);
	i = nb_mot(s, c);
	tab = (char **)malloc(sizeof(char *) * (i + 1));
	if (!tab)
		return (0);
	return (affect(s, tab, c, i));
}
