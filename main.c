/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shamizi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/20 13:15:21 by shamizi           #+#    #+#             */
/*   Updated: 2021/06/21 16:01:20 by shamizi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


/* pipe = creation dun tube
 * pas besoin d'open un tube (fait de base) mais besoin de le close
 * utilser read pour le lecteur (sortie) et write pour les ecrivain (entrer du tube)
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>


//pour execve (path (ligne envp= dans envp quon split qvec :, char **avec split ls -l par exemple (cmd), envp)

int		main(int argc, char **argv, char **envp)
{
	printf("%s",envp[0]);
	return 0;
	/*

	int p[2];
	pipe(p);
	if (fork() == 0)
	{
		close(p[1]);
		dup2(p[0], 0);
		close(p[0]);
	//	execlp("wc", "wc", (char *)0);
	}
	else
	{
		close(p[0]);
	//	dup2(p[1], 1);
		close(p[1]);
	//	execlp("ls", "ls", (char *)0);
	}
	return (0);*/
}
