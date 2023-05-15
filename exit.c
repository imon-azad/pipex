/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 04:49:50 by esamad-j          #+#    #+#             */
/*   Updated: 2023/05/15 05:19:03 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(int error_code)
{
	if (error_code == 1)
		write(2, "pipex: Invalid number of arguments\n", 35);
	if (error_code == 2)
		write(2, "pipex: No such file or directory\n", 33);
	if (error_code == 3)
		write(2, "pipex: Permission denied\n", 25);
	if (error_code == 4)
		write(2, "pipex: Malloc\n", 14);
	if (error_code == 5)
		write(2, "pipex: pipe_ft\n", 15);
	if (error_code == 6)
		write(2, "pipex: dup_ft\n", 14);
	if (error_code == 7)
		write(2, "pipex: command not found\n", 25);
	exit(error_code);
}

void	pipex_exit(t_pdata *data, int error_code)
{
	int	i;

	i = 0;
	if (data->env_path)
	{
		while (data->env_path[i])
		{
			free(data->env_path[i]);
			i++;
		}
		free(data->env_path);
	}
	close(data->in_fd);
	close(data->out_fd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	print_error(error_code);
}
