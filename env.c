/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 20:16:55 by garouche          #+#    #+#             */
/*   Updated: 2017/05/03 17:55:19 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**split_env_var(char *cmd, char *ptr)
{
	int		i;
	char	**res;

	i = ptr - cmd;
	if (!(res = ft_memalloc(sizeof(char*) * 4)))
		exit(EXIT_FAILURE);
	if (!(res[0] = ft_strdup("env")))
		exit(EXIT_FAILURE);
	if (!(res[1] = malloc(i + 1)))
		exit(EXIT_FAILURE);
	ft_memcpy(res[1], cmd, i);
	res[1][i] = 0;
	if (ptr[1])
	{
		if (!(res[2] = ft_strdup(ptr + 1)))
			exit(EXIT_FAILURE);
	}
	return (res);
}

int		add_all_var(char ***environ, char **cmd)
{
	int		i;
	char	**new_var;
	char	*str;

	i = 1;
	while (cmd[i] && (str = ft_strchr(cmd[i], '=')))
	{
		new_var = split_env_var(cmd[i], str);
		add_or_modify(environ, new_var, 1);
		free_double_ptr((void***)&new_var);
		i++;
	}
	return (i);
}

int		builtin_env(char **environ, char **cmd)
{
	char	*str;
	int		i;

	environ = copy_env(environ);
	i = add_all_var(&environ, cmd);
	if (cmd[i] && !ft_strchr(cmd[i], '='))
	{
		if ((str = find_func(environ, &cmd[i])))
		{
			cmd = &cmd[i];
			exec_bin(environ, &cmd, str, NULL);
		}
		else if (!str)
		{
			free_double_ptr((void***)&environ);
			return (display_error(cmd[i]));
		}
	}
	else
		aff_env(environ);
	free_double_ptr((void***)&environ);
	return (0);
}
