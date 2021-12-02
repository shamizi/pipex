/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:55:57 by shamizi           #+#    #+#             */
/*   Updated: 2021/11/10 23:12:52 by shamizi          ###   ########.fr       */
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
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*ptr;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (0);
	ptr = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!ptr)
		return (0);
	while (s1 && *s1)
		ptr[i++] = *s1++;
	while (s2 && *s2)
		ptr[i++] = *s2++;
	ptr[i] = 0;
	return (ptr);
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

char	*final_path(char *cmd, char **envp, int i)
{
	char	**path;
	char	*right_path;
	char	*tmp;
	char	**arg;

	if (cmd[0] == '.' || cmd[0] == '/')
		return (cmd);
	path = ft_split(find_path(envp, "PATH=", 5), ':');
	arg = ft_split(cmd, ' ');
	if (!arg || !path)
		return (NULL);
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		right_path = ft_strjoin(tmp, arg[0]);
		if (access(right_path, X_OK) == 0)
			return (ft_access(path, arg, tmp, right_path));
		free(tmp);
		free(right_path);
		i++;
	}
	freestrings(arg);
	freestrings(path);
	return (NULL);
}
