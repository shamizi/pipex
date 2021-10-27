/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:24:38 by shamizi           #+#    #+#             */
/*   Updated: 2021/10/27 16:17:10 by shamizi          ###   ########.fr       */
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

void	ft_error(char *str, int out)
{
	if (out)
		close(out);
	if (errno)
		perror(str);
	else
		ft_putstr_fd(2, str);
	exit(EXIT_FAILURE);
}

void	father(int *pfd, int in, char **argv, char **envp)
{
	char **tab;
	char *path;

	path = final_path(argv[2], envp);
	tab = ft_split(argv[2], ' ');
	if (!path)
	{
		free(path);
		freestrings(tab);
		ft_error("Command not found :", 0);
	}

	close(pfd[0]);
	dup2(pfd[1], 1);
	close(pfd[1]);
	dup2(in, 0);
	if (execve(path, tab , envp) == -1)
		ft_error("Command not found :", in);
	free(path);
	freestrings(tab);
}

void	child(int *pfd, char **argv, char **envp)
{
	int	out;
	char **tab;
	char *path;

	path = final_path(argv[3], envp);
	tab = ft_split(argv[3], ' ');
	if (!path)
	{
		free(path);
		freestrings(tab);
		ft_error("Command not found :", 0);
	}
	out = open(argv[4], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	close(pfd[1]);
	dup2(pfd[0], 0);
	dup2(out, 1);
	close(pfd[0]);
	if (execve(path, tab , envp) == -1)
		ft_error("Command not found :", out);
	freestrings(tab);
	close(out);
}

int	main(int argc, char **argv, char **envp)
{
	int		pfd[2];
	pid_t	pid;
	int		in;

	if (argc != 5)
		ft_error("format d'argument invalide\n", 0);
	in = open(argv[1], O_RDONLY);
	if (in == -1)
		ft_error("fichier d'entrer invalide\n", 0);
	if (pipe(pfd) == -1)
		ft_error("pipe failed\n", 0);
	pid = fork();
	if (pid == 0)
		father(pfd, in, argv, envp);
	else
		child(pfd, argv, envp);
	close(in);
	return (0);
}
