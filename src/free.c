/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 13:23:06 by shamizi           #+#    #+#             */
/*   Updated: 2021/12/02 13:21:51 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	initialize(t_path *path)
{
	path->in = 0;
	path->out = 0;
	path->tab = NULL;
	path->path = NULL;
	path->tab2 = NULL;
	path->path2 = NULL;
}

char	*ft_access(char **path, char **arg, char *tmp, char *right_path)
{
	freestrings(path);
	freestrings(arg);
	free(tmp);
	return (right_path);
}

void	ft_free(t_path *path)
{
	if (path->in)
		close(path->in);
	if (path->out)
		close(path->out);
	if (path->tab)
		freestrings(path->tab);
	if (path->tab2)
		freestrings(path->tab2);
	if (path->path)
		free(path->path);
	if (path->path2)
		free(path->path2);
	if (path)
		free(path);
}

void	ft_error2(char *str, t_path *path, char *arg1, char *arg2)
{
	char	*one;
	char	*two;

	one = ft_strjoin(str, arg1);
	two = ft_strjoin(str, arg2);
	if (!path->path)
		ft_putstr_fd(2, one);
	else
		ft_putstr_fd(2, two);
	ft_putstr_fd(2, "\n");
	free(one);
	free(two);
	ft_free(path);
	exit(EXIT_FAILURE);
}
