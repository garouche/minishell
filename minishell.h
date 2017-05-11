/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 16:31:03 by garouche          #+#    #+#             */
/*   Updated: 2017/05/03 18:56:17 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <string.h>
# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <limits.h>
# include <signal.h>
# include <sys/wait.h>

int		exec_argv(char **av, char **environ);
int		init_fd(int ac, char **av, char **environ);
int		builtin_exit(char **line, char ***environ, int res);
char	**add_nenv(char **env, char **cmd, int nb);
void	shlvl(char ***environ);
void	manage_path_cd(char *buf, char *path, char *pwd);
void	add_or_modify(char ***environ, char **cmd, int i);
int		builtin_env(char **environ, char **cmd);
void	exec_bin(char **environ, char ***cmd, char *path, int *status);
int		builtin_unsetenv(char ***environ, char **cmd);
void	aff_env(char **env);
char	**copy_env(char **env);
int		builtin_setenv(char ***environ, char **cmd);
int		find_builtin(char ***cmd, char ***environ);
void	dot_dot(char *buf, char *dir);
void	change_env_var(char ***environ, char *var, char *new_value);
char	*find_env(char **environ, char *var);
int		check_space(char *line);
int		builtin_cd(char **cmd, char ***environ);
int		builtin_or_exec(char ***environ, char **line);
char	*find_func(char **environ, char **cmd);
void	free_double_ptr(void ***ptr);
int		test_path(char *path, char *cmd);
char	*split_path(char *environ, char *cmd);
int		display_error(char *cmd);
#endif
