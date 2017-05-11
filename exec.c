/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/24 17:40:10 by garouche          #+#    #+#             */
/*   Updated: 2017/05/03 15:12:29 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_func(char **environ, char **cmd)
{
	int		i;
	char	*str;
	char	buf[PATH_MAX];
	char	*ptr;

	i = 0;
	if (find_env(environ, "PATH"))
	{
		while (ft_strncmp(environ[i], "PATH", 4))
			i++;
		str = split_path(environ[i] + 5, cmd[0]);
		if (!access(cmd[0], F_OK) && !str)
		{
			ptr = find_env(environ, "PWD") + 4;
			manage_path_cd((char*)buf, *cmd, ptr);
			str = ft_strdup(buf);
		}
		return (str);
	}
	return (NULL);
}

void	create_bin_path(char *path, char *cmd, char **str)
{
	char buf[1024];

	buf[0] = 0;
	ft_strcat(buf, path);
	ft_strcat(buf, "/");
	ft_strcat(buf, cmd);
	if (!(*str = ft_strdup(buf)))
		exit(EXIT_FAILURE);
}

char	*split_path(char *environ, char *cmd)
{
	int		i;
	char	**path;
	char	*str;

	path = NULL;
	str = NULL;
	if (!(path = ft_strsplit(environ, ':')))
		exit(EXIT_FAILURE);
	i = 0;
	while (path[i])
	{
		if (test_path(path[i], cmd))
		{
			create_bin_path(path[i], cmd, &str);
			free_double_ptr((void***)&path);
			return (str);
		}
		i++;
	}
	free_double_ptr((void***)&path);
	return (NULL);
}

int		test_path(char *path, char *cmd)
{
	struct dirent	*d;
	DIR				*dir;

	if ((dir = opendir(path)))
	{
		while ((d = readdir(dir)))
		{
			if (!ft_strcmp(d->d_name, cmd))
			{
				closedir(dir);
				return (1);
			}
		}
		closedir(dir);
		return (0);
	}
	else
		return (-1);
}
