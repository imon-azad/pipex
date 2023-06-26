/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 05:34:02 by esamad-j          #+#    #+#             */
/*   Updated: 2023/06/26 01:57:28 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* void	leaksssss(void)
{
	atexit(leaksssss);
	system("leaks -q pipex");
}  */
int	main(int argc, char **argv, char **envp)
{
	t_pdata	p;
	int		status1;
	int		status2;

	if (argc != 5)
		return (print_error(1, NULL), -1);
	if (pipe(p.tube) == -1)
		print_error(5, NULL);
	get_env_path(envp, &p);
	first_child(argv[2], envp, p, argv[1]);
	second_child(argv[3], envp, p, argv[4]);
	close(p.tube[0]);
	close(p.tube[1]);
	waitpid(p.pid1, &status1, 0);
	waitpid(p.pid2, &status2, 0);
	check_127(argv, p);
	return (pipex_exit(&p, 0, NULL), 0);
}
