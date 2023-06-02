/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 04:49:50 by esamad-j          #+#    #+#             */
/*   Updated: 2023/06/02 03:04:27 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_error(int error_code, char *param)
{
	if (error_code == 1)
		write(2, "pipex: Invalid number of arguments", 34);
	if (error_code == 2)
		write(2, "pipex: no such file or directory: ", 34);
	if (error_code == 3)
		write(2, "pipex: permission denied", 24);
	if (error_code == 4)
		write(2, "pipex: Malloc", 13);
	if (error_code == 5)
		write(2, "pipex: pipe_ft", 14);
	if (error_code == 6)
		write(2, "pipex: dup_ft", 13);
	if (error_code == 7)
		write(2, "pipex: command not found", 24);
	if (error_code == 8)
		write(2, "pipex: environment error", 24);
	if(param)
		ft_putstr_fd(param, 2);
	write(2,"\n", 1);
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
	print_error(error_code, NULL);
}
