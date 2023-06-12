/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 04:49:50 by esamad-j          #+#    #+#             */
/*   Updated: 2023/06/11 16:26:58 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	close_fd(t_pdata *data, int error_code, char *param)
{
	close(data->in_fd);
	close(data->out_fd);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	
	print_error(error_code, param);
	
}

void	print_error(int error_code, char *param)
{
	if (error_code == 1)
		write(2, "pipex: invalid number of arguments", 34);
	if (error_code == 2)
		write(2, "pipex: no such file or directory: ", 34);
	if (error_code == 3)
		write(2, "pipex: permission denied: ", 26);
	if (error_code == 4)
		write(2, "pipex: memory error", 19);
	if (error_code == 5)
		write(2, "pipex: pipe_ft error", 20);
	if (error_code == 6)
		write(2, "pipex: dup_ft error", 19);
	if (error_code == 7)
		write(2, "pipex: command not found: ", 26);
	if (error_code == 8)
		write(2, "pipex: environment error", 24);
	if (error_code == 9)
		write(2, "pipex: execve error", 19);
	if(param || error_code == 7 || error_code == 2 || error_code == 3)
		ft_putstr_fd(param, 2);
	if (error_code != 0)
		write(2,"\n", 1);
	exit(error_code);
}

void	pipex_exit(t_pdata *data, int error_code, char *error)
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
	
	
	print_error(error_code, error);
}
