/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/21 16:09:35 by shamizi           #+#    #+#             */
/*   Updated: 2021/06/21 16:36:06 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
donc le debut du cheminque je doit chercher il est apres pwd= dans envp
du coup fonctionpour avoir coordonner *envp[X]
puis une fois qu'on la il faut coller le nom de notre fichier (argv[1])

==

path fichier 1;

*/
#include 
int	line(char **envp, char *to_find)
{
	int i;

	i = 0;
	while(envp[i])
	{
		if (ft_strncmp(envp[i], to_find, ft_strlen(to_find)) != 0)
			i++;
	}
	return (i);
}

int	path_file(char **argv, char **envp)
{
	int i;
	char *pwd;
	char *part_path;
	char *final_path;

	i = line(envp, "PWD=");
	part_path = ft_strjoin(envp[i] + 4, "/");
	final_path = ft_strjoin(part_path, argv[1]);

}

int		main(int argc, char **argv, char **envp)
{
	path_file(argv[1], envp)
}
