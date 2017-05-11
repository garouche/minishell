/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 20:11:14 by garouche          #+#    #+#             */
/*   Updated: 2017/05/03 15:14:15 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_double_ptr(void ***ptr)
{
	int i;

	i = 0;
	if (!ptr || !*ptr)
		return ;
	while ((*ptr)[i])
		ft_memdel(&(*ptr)[i++]);
	free(ptr[0]);
}

int		display_error(char *cmd)
{
	char	*error;
	int		i;

	error = "command not found: ";
	i = ft_strlen(cmd);
	if (i >= 256 && i < 1024)
		error = "file name too long: ";
	else if (i >= 1024)
		error = "command too long: ";
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(error, 2);
	ft_putstr_fd(cmd, 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int		builtin_or_exec(char ***environ, char **line)
{
	char	*str;
	char	**cmd;
	int		status;

	status = 0;
	cmd = ft_strsplit_white(*line);
	if ((status = find_builtin(&cmd, environ)) != -1)
		;
	else if ((str = find_func(*environ, cmd)))
		exec_bin(*environ, &cmd, str, &status);
	else if (!str)
		status = display_error(cmd[0]);
	free_double_ptr((void***)&cmd);
	return (status);
}

int		check_space(char *line)
{
	int i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i++] > 32)
			return (1);
	}
	return (0);
}

char	*find_env(char **environ, char *var)
{
	int i;
	int j;

	j = ft_strlen(var);
	i = 0;
	while (environ[i] && ft_strncmp(environ[i], var, j))
		i++;
	return (environ[i]);
}
