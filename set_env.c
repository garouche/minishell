/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 19:18:45 by garouche          #+#    #+#             */
/*   Updated: 2017/05/03 13:37:27 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**add_nenv(char **env, char **cmd, int nb)
{
	int		i;
	char	**envcpy;
	char	*ptr;

	i = 0;
	while (env[i])
		i++;
	if (!(envcpy = ft_memalloc(sizeof(char*) * (i + nb + 1))))
		exit(EXIT_FAILURE);
	i = -1;
	while (env[++i])
	{
		if (!(envcpy[i] = ft_strdup(env[i])))
			exit(EXIT_FAILURE);
	}
	if (!(ptr = ft_strjoin(cmd[1], "=")))
		exit(EXIT_FAILURE);
	if (cmd[2])
		envcpy[i] = ft_strjoin(ptr, cmd[2]);
	else
		envcpy[i] = ft_strdup(ptr);
	if (!envcpy[i])
		exit(EXIT_FAILURE);
	free(ptr);
	return (envcpy);
}

int		check_alphanum(char *cmd)
{
	int i;

	i = 0;
	if (!ft_isalpha(cmd[0]))
		return (-1);
	while (cmd[i])
	{
		if (!ft_isalnum(cmd[i]) && cmd[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	add_or_modify(char ***environ, char **cmd, int i)
{
	char	**buf;

	if (!find_env(*environ, cmd[1]))
	{
		buf = add_nenv(*environ, cmd, i);
		free_double_ptr((void***)environ);
		*environ = buf;
	}
	else
		change_env_var(environ, cmd[1], cmd[2]);
}

int		setenv_error(int nb_arg, int alphanum)
{
	ft_putstr_fd("setenv: ", 2);
	if (nb_arg > 3)
	{
		ft_putstr_fd("Too many arguments\n", 2);
		return (1);
	}
	if (alphanum == 0)
	{
		ft_putstr_fd("Only alphanumeric characters in variable name\n", 2);
		return (1);
	}
	else if (alphanum == -1)
	{
		ft_putstr_fd("setenv: Variable name must begin with a letter\n", 2);
		return (1);
	}
	return (1);
}

int		builtin_setenv(char ***environ, char **cmd)
{
	int	i;
	int j;

	i = 0;
	while (cmd[i])
		i++;
	if (i > 3)
		return (setenv_error(i, 0));
	else if (i == 1)
		aff_env(*environ);
	else if (i)
	{
		j = check_alphanum(cmd[1]);
		if (!j || j == -1)
			return (setenv_error(0, j));
		else
			add_or_modify(environ, cmd, i);
	}
	return (0);
}
