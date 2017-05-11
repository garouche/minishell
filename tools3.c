/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/30 20:19:40 by garouche          #+#    #+#             */
/*   Updated: 2017/05/03 20:00:20 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_bin(char **environ, char ***cmd, char *path, int *status)
{
	pid_t	pid;
	int		i;

	i = 0;
	if (!(pid = fork()))
	{
		if (execve(path, *cmd, environ) == -1)
		{
			ft_putstr_fd("minishell: Permision denied: ", 2);
			ft_putstr_fd(path, 2);
			ft_putchar_fd('\n', 2);
			exit(1);
		}
	}
	else
		wait(status);
	free(path);
}

void	shlvl(char ***environ)
{
	char	**cmd;
	char	*str;
	int		i;

	if ((str = find_env(*environ, "SHLVL")))
	{
		*environ = copy_env(*environ);
		if (str[6])
			i = ft_atoi(&str[6]) + 1;
		else
			i = 1;
		if (!(str = ft_itoa(i)))
			exit(EXIT_FAILURE);
		change_env_var(environ, "SHLVL", str);
		free(str);
	}
	else
	{
		cmd = ft_memalloc(sizeof(char*) * 4);
		cmd[0] = ft_strdup("setenv");
		cmd[1] = ft_strdup("SHLVL");
		cmd[2] = ft_itoa(1);
		*environ = add_nenv(*environ, cmd, 1);
		free_double_ptr((void***)&cmd);
	}
}

int		prompt(int fd, char **line)
{
	char	buf[PATH_MAX];
	char	*ptr;

	if (fd == 0)
	{
		ft_putstr("\x1b[0;34;1m");
		if (getcwd(buf, 1024))
		{
			ptr = ft_strrchr(buf, '/');
			ptr[1] ? ft_putstr(ptr + 1) : ft_putstr(ptr);
			ft_putstr("-> ");
		}
		else
			ft_putstr("$> ");
		ft_putstr("\x1b[0m");
	}
	return (get_next_line(fd, line));
}

int		shell(int fd, char **environ)
{
	int		ret;
	char	*line;

	ret = 0;
	shlvl(&environ);
	while (prompt(fd, &line) == 1)
	{
		if (check_space(line))
		{
			if (!ft_strcmp(line, "exit"))
				return (builtin_exit(&line, &environ, ret));
			else
				ret = builtin_or_exec(&environ, &line);
		}
		free(line);
	}
	free(line);
	free_double_ptr((void***)&environ);
	return (ret);
}

int		init_fd(int ac, char **av, char **environ)
{
	int		fd;

	fd = 0;
	if (ac > 1)
	{
		if ((fd = open(av[1], O_RDONLY)) == -1)
		{
			ft_putstr_fd("minishell: can't open input file: ", 2);
			ft_putstr_fd(av[1], 2);
			ft_putstr_fd("\n", 2);
			return (1);
		}
	}
	return (shell(fd, environ));
}
