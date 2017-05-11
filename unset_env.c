/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_env.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 18:28:41 by garouche          #+#    #+#             */
/*   Updated: 2017/05/03 13:35:57 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	del_cmd(char ***environ, char *cmd)
{
	int		i;
	int		j;
	char	*ptr;

	i = 0;
	j = 0;
	while ((*environ)[i])
	{
		ptr = ft_strchr((*environ)[i], '=');
		if (!ft_strncmp((*environ)[i], cmd, ptr - (*environ)[i]))
		{
			j = 1;
			free((*environ)[i]);
		}
		if (j)
			(*environ)[i] = (*environ)[i + 1];
		i++;
	}
}

int		builtin_unsetenv(char ***environ, char **cmd)
{
	int i;

	i = 1;
	while (cmd[i])
	{
		del_cmd(environ, cmd[i]);
		i++;
	}
	if (i == 1)
	{
		ft_putstr_fd("unsetenv: Too few arguments\n", 2);
		return (1);
	}
	else
		return (0);
}
