/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <shamizi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 15:24:38 by shamizi           #+#    #+#             */
/*   Updated: 2021/10/04 19:23:21 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
static char **freestrings(char **tab)
{
    int     i;

    i = 0;
    while (tab[i])
    {
        free(tab[i]);
        i++;
    }
    free(tab);
    return (0);
}

static int  nb_mot(char *s, char c)
{
    int     i;
    int     j;
    int     compt;

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

static int  len_word(char *s, char c, int i)
{
    int     len;

    len = 0;
    while (s[i] && s[i] != c)
    {
        len++;
        i++;
    }
   return (len);
}

static char **affect(char *s, char **tab, char c, int l)
{
    int     i;
    int     j;
    int     k;

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

char        **ft_split(char *s, char c)
{
    char    **tab;
    int     i;

    if (!s)
        return (NULL);
    i = nb_mot(s, c);
    if (!(tab = (char **)malloc(sizeof(char *) * (i + 1))))
        return (0);
    return (affect(s, tab, c, i));
}


int ft_strncmp(char *s1, char *s2, int n) 
{ 
    int i; 
 
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

int		ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char    *ft_strjoin(char *s1, char *s2)
{
    int     i;
    int     j;
    char    *str;

    i = ft_strlen(s1);
    j = ft_strlen(s2);
    if (!(str = (char *)malloc(sizeof(str) * (i + j + 1))))
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

////////////////////////////////////////////////////////
char	*find_path(char **envp)
{
	while (*envp)
	{
		if (!ft_strncmp(*envp, "PATH=", 5))
			return (*envp + 5);
		envp++;
	}
	return (NULL);
}


char *final_path(char *cmd, char **envp)
{
	char **path;
	char *right_path;
	char *tmp;
	path = ft_split(find_path(envp), ':');
	

	int i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		right_path = ft_strjoin(tmp, cmd);
		if (access(right_path, X_OK) == 0)
			return (right_path);
		i++;
	}
	return (NULL);

}

void	ft_error(char *str, int i)
{
	write(1, str, i);
	exit(EXIT_FAILURE);
}

int		main(int argc, char **argv, char **envp)
{
	if (argc != 5)
		ft_error("format d'argument invalide\n", 27); 
	int pfd[2];
	pid_t pid;
	int in;
	int out;
	
	char *a[2] = {"/bin/ls", "/-l"};
	if (pipe(pfd) == -1)
		ft_error("pipe failed\n",12);
	pid = fork();
	if (pid == 0)
	{
		close(pfd[0]);
		dup2(pfd[1], 1);
		close(pfd[1]);
		in = open(argv[1], O_RDONLY);
		if (in == -1)
			return (-1);
		dup2(in, 0);
		execve(final_path(argv[2], envp), a /*ft_split(argv[2], ' ')*/, envp);
	}
	else
	{

		out = open(argv[4], O_WRONLY | O_CREAT, 777);
		wait(0);
		close(pfd[1]);
		dup2(pfd[0], 0);
		dup2(out, 1);
		close(pfd[0]);
		execve(final_path(argv[3], envp),a /*ft_split(argv[3], ' ')*/, envp);
	}
	return (0);
}

//au futur moi j'ai toujours un probleme sur les flags -l et j'écrit toujours pas dans se putin de fichier"
