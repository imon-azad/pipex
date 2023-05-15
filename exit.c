/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 04:49:50 by esamad-j          #+#    #+#             */
/*   Updated: 2023/05/15 04:51:55 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(int error_code)
{
	if (error_code == 1)
		write(1, "Error: Invalid number of arguments\n", 35);
	if (error_code == 2)
		write(1, "Error: No such file or directory\n", 33);
	if (error_code == 3)
		write(1, "Error: Permission denied\n", 33);
	if (error_code == 4)
		write(1, "Error: Malloc\n", 14);
	if (error_code == 5)
		write(1, "Error: pipe_ft\n", 15);
	if (error_code == 6)
		write(1, "Error: dup_ft\n", 14);
	if (error_code == 7)
		write(1, "Error: cmd not found\n", 21);
	exit(-1);
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
