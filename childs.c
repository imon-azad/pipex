/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 04:52:37 by esamad-j          #+#    #+#             */
/*   Updated: 2023/05/15 04:54:31 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd(t_pdata *data, char *cmd)
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
		{
			return (command);
		}
		free(command);
		i++;
	}
	return (NULL);
}

void	first_child(t_pdata data, char **argv, char **envp)
{
	char	**cmd_args;
	char	*cmd;

	dup2(data.tube[1], 1);
	if (dup2(data.tube[1], STDOUT_FILENO) == -1)
		pipex_exit(&data, 6);
	close(data.tube[0]);
	if (dup2(data.in_fd, STDIN_FILENO) == -1)
		pipex_exit(&data, 6);
	cmd_args = ft_split(argv[2], ' ');
	if (!cmd_args)
		(pipex_exit(&data, 4));
	cmd = get_cmd(&data, cmd_args[0]);
	printf("cmd_:%s\n", cmd);
	if (!cmd)
		pipex_exit(&data, 7);
	execve(cmd, cmd_args, envp);
	pipex_exit(&data, 0);
}

void	second_child(t_pdata data, char **argv, char **envp)
{
	char	**cmd_args;
	char	*cmd;

	close(data.tube[1]);
	if (dup2(data.tube[0], STDIN_FILENO) == -1)
		pipex_exit(&data, 6);
	close(data.tube[0]);
	if (dup2(data.out_fd, STDOUT_FILENO) == -1)
		pipex_exit(&data, 6);
	cmd_args = ft_split(argv[3], ' ');
	if (!cmd_args)
		(pipex_exit(&data, 4));
	cmd = get_cmd(&data, cmd_args[0]);
	if (cmd == NULL)
		pipex_exit(&data, 7);
	execve(cmd, cmd_args, envp);
	pipex_exit(&data, 0);
}
