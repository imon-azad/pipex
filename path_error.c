/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/24 16:25:44 by esamad-j          #+#    #+#             */
/*   Updated: 2023/06/24 16:34:19 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	get_env_path(char **envp, t_pdata *data)
{
	int	i;

	i = 0;
	while (envp[i] && !ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])))
		i++;
	if (envp[i] && ft_strnstr(envp[i], "PATH=", ft_strlen(envp[i])))
	{
		data->env_path = ft_split(envp[i] + 5, ':');
		if (!data->env_path)
			(pipex_exit(data, 4, NULL));
	}
	else
		print_error(8, NULL);
}

int	cmd_path(char *cmd)
{
	if (!cmd)
		return (0);
	if (cmd[0] != '.' && cmd[0] != '~' && cmd[0] != '/')
		return (0);
	if (access(cmd, X_OK) == 0)
		return (1);
	return (0);
}

void	check_127(char **argv, t_pdata p)
{
	char	**splited;
	char	*cmd;
	char	*cmd1;

	cmd1 = argv[3];
	splited = ft_split(cmd1, ' ');
	if (cmd_path(splited[0]))
		cmd = ft_strdup(splited[0]);
	else
		cmd = get_cmd(&p, splited[0]);
	if (!cmd)
	{
		ft_free_double_char(splited);
		free(cmd);
		pipex_exit(&p, 127, cmd);
	}
	ft_free_double_char(splited);
	free(cmd);
}
