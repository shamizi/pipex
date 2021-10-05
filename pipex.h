/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 16:11:22 by shamizi           #+#    #+#             */
/*   Updated: 2021/10/05 17:02:53 by shamizi          ###   ########.fr       */
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

char	**ft_split(char *s, char c);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strlen(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*final_path(char *cmd, char **envp);
#endif
