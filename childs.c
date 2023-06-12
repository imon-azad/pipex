/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 04:52:37 by esamad-j          #+#    #+#             */
/*   Updated: 2023/06/12 02:28:13 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 get_cmd(t_pdata *data, char *cmd)
{
	char	*tmp;
	char	*command;
	int		i;

	i = 0;
	while (data->env_path[i])
	{
		tmp = ft_strjoin(data->env_path[i], "/");
		if (!tmp)
			return (NULL);
		command = ft_strjoin(tmp, cmd);
		if (!command)
			return (NULL);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	first_child(t_pdata data, char **argv, char **envp)
{
	char	**cmd_args;
	char	*cmd;

	if (dup2(data.tube[1], STDOUT_FILENO) == -1)
		//printf("hola");
		pipex_exit(&data, 6, NULL);
	close(data.tube[0]);
	close(data.tube[1]);
	if (dup2(data.in_fd, STDIN_FILENO) == -1 && data.in_fd != -1)
		//printf("hola");
		pipex_exit(&data, 6, NULL);
	cmd_args = ft_split(argv[2], ' ');
	if (!cmd_args)
		(pipex_exit(&data, 4, NULL));
	cmd = get_cmd(&data, cmd_args[0]);
	if (!cmd)
		pipex_exit(&data, 7, argv[2]);
	execve(cmd, cmd_args, envp);
	pipex_exit(&data, 9, NULL);
}

void	second_child(t_pdata data, char **argv, char **envp)
{
	char	**cmd_args;
	char	*cmd;

	
	if (dup2(data.tube[0], STDIN_FILENO) == -1)
		//printf("hola");
		pipex_exit(&data, 6, NULL);
	close(data.tube[1]);
	close(data.tube[0]);
	if (dup2(data.out_fd, STDOUT_FILENO) == -1)
		//printf("hola");
		pipex_exit(&data, 6, NULL);
	cmd_args = ft_split(argv[3], ' ');
	if (!cmd_args)
		(pipex_exit(&data, 4, NULL));
	cmd = get_cmd(&data, cmd_args[0]);
	if (cmd == NULL)
		pipex_exit(&data, 7, argv[3]);
	execve(cmd, cmd_args, envp);
	pipex_exit(&data, 9, NULL);
}
