/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:47:14 by esamad-j          #+#    #+#             */
/*   Updated: 2023/05/15 04:55:57 by esamad-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipexdata
{
	int		in_fd;
	int		out_fd;
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	char	**env_path;

}			t_pdata;

/*Get Path*/
void		get_env_path(int argc, char **argv, char **envp, t_pdata *data);

/*Childs*/
char		*get_cmd(t_pdata *data, char *cmd);
void		first_child(t_pdata data, char **argv, char **envp);
void		second_child(t_pdata data, char **argv, char **envp);

/*Exit*/
void		pipex_exit(t_pdata *data, int error_code);
void		print_error(int error_code);

/*Libft*/
size_t		ft_strlen(const char *s);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *str1, char const *str2);

#endif
