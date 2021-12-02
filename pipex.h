/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:11:22 by shamizi           #+#    #+#             */
/*   Updated: 2021/12/02 13:18:08 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_path	t_path;
struct					s_path
{
	int		in;
	int		out;
	int		pfd[2];
	pid_t	pid;
	char	**tab;
	char	*path;
	char	**tab2;
	char	*path2;
};

void	ft_error(char *str, t_path *path);
void	initialize(t_path *path);
void	ft_putstr_fd(int fd, char *s);
void	ft_error2(char *str, t_path *path, char *arg1, char *arg2);
void	ft_free(t_path *path);
char	*find_path(char **envp, char *str, int i);
char	**freestrings(char **tab);
char	**ft_split(char *s, char c);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*final_path(char *cmd, char **envp, int i);
char	*ft_access(char **path, char **arg, char *tmp, char *right_path);
#endif
