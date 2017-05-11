/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 18:13:07 by garouche          #+#    #+#             */
/*   Updated: 2017/05/03 15:14:35 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	change_env_var(char ***environ, char *var, char *new_value)
{
	char	*ptr;
	char	*str;
	int		i;

	i = 0;
	if (!new_value)
		new_value = "";
	if ((ptr = find_env(*environ, var)))
	{
		while ((*environ)[i] && ft_strncmp(var, (*environ)[i], ft_strlen(var)))
			i++;
		ptr = ft_strjoin(var, "=");
		str = ft_strjoin(ptr, new_value);
		free(ptr);
		ptr = (*environ)[i];
		(*environ)[i] = str;
		free(ptr);
	}
}

int		find_builtin(char ***cmd, char ***environ)
{
	if (!ft_strcmp((*cmd)[0], "cd"))
	{
		return (builtin_cd(*cmd, environ));
	}
	else if (!ft_strcmp((*cmd)[0], "setenv"))
	{
		return (builtin_setenv(environ, *cmd));
	}
	else if (!ft_strcmp((*cmd)[0], "unsetenv"))
	{
		return (builtin_unsetenv(environ, *cmd));
	}
	else if (!ft_strcmp((*cmd)[0], "env"))
	{
		return (builtin_env(*environ, *cmd));
	}
	else if (!ft_strcmp((*cmd)[0], "echo"))
	{
		aff_env(&(*cmd)[1]);
		return (0);
	}
	return (-1);
}

void	dot_dot(char *buf, char *dir)
{
	char	*ptr;
	int		i;

	i = 0;
	if (ft_strcmp(dir, "."))
	{
		ptr = ft_strrchr((char*)buf, '/');
		if ((i = ptr - (char*)buf) > 0)
			buf[i] = 0;
		else
			ft_memcpy(buf, "/", 2);
	}
	else
	{
		if (!buf[0])
			ft_strcpy(buf, "/");
	}
}

char	**copy_env(char **env)
{
	int		i;
	char	**envcpy;

	i = 0;
	while (env[i])
		i++;
	if (!(envcpy = malloc(sizeof(char*) * (i + 1))))
		exit(EXIT_FAILURE);
	i = 0;
	while (env[i])
	{
		if (!(envcpy[i] = ft_strdup(env[i])))
			exit(EXIT_FAILURE);
		i++;
	}
	envcpy[i] = 0;
	return (envcpy);
}

void	aff_env(char **env)
{
	int i;

	i = 0;
	while (env[i])
	{
		ft_putstr(env[i++]);
		ft_putchar('\n');
	}
}
