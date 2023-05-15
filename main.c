/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/07 05:34:02 by esamad-j          #+#    #+#             */
/*   Updated: 2023/05/15 04:55:33 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	leaksssss(void)
{
	system("leaks -q pipex");
}
//atexit(leaksssss);

void	get_env_path(int argc, char **argv, char **envp, t_pdata *data)
{
	int	i;

	i = 0;
	data->in_fd = open(argv[1], O_RDONLY);
	if (data->in_fd == -1)
		pipex_exit(data, 2);
	data->out_fd = open(argv[argc - 1], O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (access(argv[argc - 1], F_OK) == -1)
		pipex_exit(data, 2);
	if (access(argv[argc - 1], W_OK) == -1)
		pipex_exit(data, 3);
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])))
		i++;
	data->env_path = ft_split(envp[i] + 5, ':');
	if (!data->env_path)
		(pipex_exit(data, 4));
}

int	main(int argc, char **argv, char **envp)
{
	t_pdata	p;

	if (argc != 5)
		return (print_error(1), -1);
	if (access(argv[1], F_OK) == -1)
		return (print_error(2), -1);
	if (access(argv[1], R_OK) == -1)
		return (print_error(3), -1);
	get_env_path(argc, argv, envp, &p);
	if (pipe(p.tube) == -1)
		print_error(5);
	p.pid1 = fork();
	if (p.pid1 == 0)
		first_child(p, argv, envp);
	p.pid2 = fork();
	if (p.pid2 == 0)
		second_child(p, argv, envp);
	close(p.tube[0]);
	close(p.tube[1]);
	waitpid(p.pid1, NULL, 0);
	waitpid(p.pid2, NULL, 0);
	pipex_exit(&p, 0);
	return (0);
}
