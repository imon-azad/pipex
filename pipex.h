/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esamad-j <esamad-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 14:47:14 by esamad-j          #+#    #+#             */
/*   Updated: 2023/06/26 11:41:01 by esamad-j         ###   ########.fr       */
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
	pid_t	pid1;
	pid_t	pid2;
	int		tube[2];
	char	**env_path;

}			t_pdata;

/*Get Path*/
void		get_env_path(char **envp, t_pdata *data);
int			cmd_path(char *cmd);

/*Childs*/
char		*get_cmd(t_pdata *data, char *cmd);
void		first_child(char *cmd, char **envp, t_pdata p, char *in_file);
void		second_child(char *cmd, char **envp, t_pdata p, char *out_file);
void		ft_exe(char *cmd, char **envp, t_pdata data);

/*Exit*/
void		pipex_exit(t_pdata *data, int error_code, char *error);
void		print_error(int error_code, char *param);
void		close_fd(t_pdata *data, int error_code, char *param);
void		ft_free_double_char(char **str);
void		check_127(char **argv, t_pdata p);

/*Libft*/
size_t		ft_strlen(const char *s);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char const *str1, char const *str2);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strdup(char *src);

#endif
