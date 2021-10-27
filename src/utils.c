/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:55:57 by shamizi           #+#    #+#             */
/*   Updated: 2021/10/26 18:08:08 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	ft_strncmp(char *s1, char *s2, int n)
{
	int		i;

	i = 0;
	while (s1[i] && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (!s2[i] || i == n)
		return (0);
	else
		return (-s2[i]);
}

int	ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*str;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	str = (char *)malloc(sizeof(str) * (i + j + 1));
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	return (str);
}

char	*find_path(char **envp, char *str, int i)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, str, i))
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}

char	*final_path(char *cmd, char **envp)
{
	char	**path;
	char	*right_path;
	char	*tmp;
	char	**arg;
	int		i;

	i = 0;
	path = ft_split(find_path(envp, "PATH=", 5), ':');
	arg = ft_split(cmd, ' ');
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		right_path = ft_strjoin(tmp, arg[0]);
		if (access(right_path, X_OK) == 0)
		{
			freestrings(path);
			freestrings(arg);
			free(tmp);
			//free(right_path);
			return (right_path);
		}
		free(tmp);
		free(right_path);
		i++;
	}
	freestrings(arg);
	freestrings(path);
	return (NULL);
}
