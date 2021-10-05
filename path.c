/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:24:38 by shamizi           #+#    #+#             */
/*   Updated: 2021/10/05 17:29:22 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_error(char *str, int i)
{
	write(1, str, i);
	exit(EXIT_FAILURE);
}

void	father(int *pfd, int in, char **argv, char **envp)
{
	close(pfd[0]);
	dup2(pfd[1], 1);
	close(pfd[1]);
	dup2(in, 0);
	execve(final_path(argv[2], envp), ft_split(argv[2], ' '), envp);
}

void	child(int *pfd, int out, char **argv, char **envp)
{
	out = open(argv[4], O_WRONLY | O_CREAT, 777);
	wait(0);
	close(pfd[1]);
	dup2(pfd[0], 0);
	dup2(out, 1);
	close(pfd[0]);
	execve(final_path(argv[3], envp), ft_split(argv[3], ' '), envp);
}

int	main(int argc, char **argv, char **envp)
{
	int		pfd[2];
	pid_t	pid;
	int		in;
	int		out;

	if (argc != 5)
		ft_error("format d'argument invalide\n", 27);
	in = open(argv[1], O_RDONLY);
	if (in == -1)
		ft_error("fichier d'entrer invalide\n", 26);
	if (pipe(pfd) == -1)
		ft_error("pipe failed\n", 12);
	pid = fork();
	if (pid == 0)
		father(pfd, in, argv, envp);
	else
		child(pfd, out, argv, envp);
	return (0);
}
