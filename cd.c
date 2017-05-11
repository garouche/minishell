/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/26 17:16:08 by garouche          #+#    #+#             */
/*   Updated: 2017/05/03 15:15:17 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cd_error(char *dir)
{
	ft_putstr_fd("cd: ", 2);
	ft_putstr_fd(dir, 2);
	ft_putstr_fd(": No such file or directory\n", 2);
}

void	manage_path_cd(char *buf, char *path, char *pwd)
{
	int		i;
	char	**ptr;
	int		j;

	i = -1;
	(ptr = ft_strsplit(path, '/')) ? 0 : exit(EXIT_FAILURE);
	if (path[0] != '/')
		ft_memcpy(buf, pwd, ft_strlen(pwd) + 1);
	else if (ptr[0])
		buf[0] = 0;
	else
		ft_memcpy(buf, "/", 2);
	while (ptr[++i])
	{
		if (!ft_strcmp(ptr[i], "..") || (!i && !ft_strcmp(ptr[i], ".")))
			dot_dot((char*)buf, ptr[i]);
		else if (ft_strcmp(ptr[i], "."))
		{
			j = ft_strlen(buf);
			if ((j > 0 && buf[j - 1] != '/') || !j)
				ft_strcat((char*)buf, "/");
			ft_strcat((char*)buf, ptr[i]);
		}
	}
	free_double_ptr((void***)&ptr);
}

int		go_to(char ***environ, char **pwd, char *path)
{
	char buf[PATH_MAX + NAME_MAX];

	if (!ft_strcmp(path, "."))
		change_env_var(environ, "OLDPWD", *pwd);
	else
	{
		manage_path_cd(buf, path, *pwd);
		if (!chdir(buf))
		{
			change_env_var(environ, "OLDPWD", *pwd);
			change_env_var(environ, "PWD", buf);
		}
		else
		{
			cd_error(path);
			return (1);
		}
	}
	return (0);
}

int		builtin_cd(char **cmd, char ***environ)
{
	char	*pwd;
	char	*home;
	char	*ptr;
	int		i;

	i = 0;
	pwd = ft_strdup(find_env(*environ, "PWD") + 4);
	home = ft_strdup(find_env(*environ, "HOME"));
	if (!cmd[1] && home[5])
		i = go_to(environ, &pwd, &home[5]);
	else if (cmd[1] && !ft_strcmp(cmd[1], "-"))
	{
		if ((ptr = find_env(*environ, "OLDPWD")))
			i = go_to(environ, &pwd, find_env(*environ, "OLDPWD") + 7);
	}
	else if (cmd[1])
		i = go_to(environ, &pwd, cmd[1]);
	free(pwd);
	free(home);
	return (i);
}
