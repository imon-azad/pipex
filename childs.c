/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   childs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 04:52:37 by esamad-j          #+#    #+#             */
/*   Updated: 2023/06/26 01:55:27 by esamad-j         ###   ########.fr       */
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
			return (free(tmp), NULL);
		free(tmp);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		i++;
	}
	return (NULL);
}

void	ft_exe(char *cmd, char **envp, t_pdata data)
{
	char	**cmd_args;
	char	*cmd_exe;

	cmd_args = ft_split(cmd, ' ');
	if (cmd_path(cmd_args[0]))
		cmd_exe = ft_strdup(cmd_args[0]);
	else
		cmd_exe = get_cmd(&data, cmd_args[0]);
	if (!cmd_exe)
		return (ft_free_double_char(cmd_args), free(cmd_exe), pipex_exit(&data,
				7, cmd));
	if (execve(cmd_exe, cmd_args, envp) == -1)
		return (ft_free_double_char(cmd_args), free(cmd_exe), pipex_exit(&data,
				9, NULL));
}

void	first_child(char *cmd, char **envp, t_pdata p, char *in_file)
{
	int	in_fd;

	p.pid1 = fork();
	if (p.pid1 == 0)
	{
		in_fd = open(in_file, O_RDONLY);
		if (in_fd < 0)
		{
			ft_putstr_fd("pipex: ", 2);
			perror(in_file);
			pipex_exit(&p, 0, NULL);
		}
		close(p.tube[0]);
		if (dup2(p.tube[1], STDOUT_FILENO) == -1)
			pipex_exit(&p, 6, NULL);
		close(p.tube[1]);
		if (dup2(in_fd, STDIN_FILENO) == -1)
			pipex_exit(&p, 6, NULL);
		close(in_fd);
		ft_exe(cmd, envp, p);
	}
	else if (p.pid1 == -1)
		pipex_exit(&p, 2, NULL);
}

void	second_child(char *cmd, char **envp, t_pdata p, char *out_file)
{
	int	out_fd;

	out_fd = open(out_file, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (out_fd < 0)
		pipex_exit(&p, 3, out_file);
	p.pid2 = fork();
	if (p.pid2 == 0)
	{
		if (dup2(p.tube[0], STDIN_FILENO) == -1)
			pipex_exit(&p, 6, NULL);
		close(p.tube[1]);
		close(p.tube[0]);
		if (dup2(out_fd, STDOUT_FILENO) == -1)
			pipex_exit(&p, 6, NULL);
		close(out_fd);
		ft_exe(cmd, envp, p);
	}
	else if (p.pid2 == -1)
		pipex_exit(&p, 2, NULL);
}
