/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:24:38 by shamizi           #+#    #+#             */
/*   Updated: 2021/12/02 13:20:34 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

void	ft_putstr_fd(int fd, char *s)
{
	if (!s)
		return ;
	while (*s)
		write(fd, s++, 1);
}

void	ft_error(char *str, t_path *path)
{
	ft_free(path);
	if (errno)
		perror(str);
	else
		ft_putstr_fd(2, str);
	exit(EXIT_FAILURE);
}

void	father(t_path *path, char **envp)
{
	if (path->in == -1)
		return ;
	if (!path->path)
		ft_error("Command not found", path);
	if (!path->tab)
		ft_error("Command not found", path);
	close(path->pfd[0]);
	dup2(path->pfd[1], 1);
	close(path->pfd[1]);
	dup2(path->in, 0);
	if (execve(path->path, path->tab, envp) == -1)
		ft_error("Command not found", path);
}

void	child(t_path *path, char **envp)
{
	if (!path->path2)
		ft_error("Command not found", path);
	if (!path->tab2)
		ft_error("Command not found", path);
	close(path->pfd[1]);
	dup2(path->pfd[0], 0);
	dup2(path->out, 1);
	close(path->pfd[0]);
	if (execve(path->path2, path->tab2, envp) == -1)
		ft_error("Command not found", path);
}

int	main(int argc, char **argv, char **envp)
{
	t_path	*path;

	if (argc != 5)
		return (0);
	path = malloc(sizeof(*path));
	initialize(path);
	path->path = final_path(argv[2], envp, 0);
	path->tab = ft_split(argv[2], ' ');
	path->path2 = final_path(argv[3], envp, 0);
	path->tab2 = ft_split(argv[3], ' ');
	path->in = open(argv[1], O_RDONLY);
	path->out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipe(path->pfd) == -1)
		ft_error("pipe failed", path);
	path->pid = fork();
	if (path->pid == 0)
		father(path, envp);
	else
		child(path, envp);
	if (path->in == -1)
		ft_error("Pipex", path);
	ft_free(path);
	return (0);
}
