/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: garouche <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 19:07:19 by garouche          #+#    #+#             */
/*   Updated: 2017/05/03 13:11:02 by garouche         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	join_line(char **dest, char *src, char *cpy)
{
	char *ptr2;

	ptr2 = *dest;
	*dest = ft_strjoin(src, cpy);
	free(ptr2);
	ptr2 = NULL;
}

int		free_rest(char **rest)
{
	if (*rest && !**rest)
	{
		free(*rest);
		*rest = NULL;
	}
	return (1);
}

int		get_line(char *ptr, char **line, char **rest, int r)
{
	char *buf2;
	char *lol;

	if (ptr != *rest)
		ptr[r] = '\0';
	lol = ft_memchr(ptr, '\n', ft_strlen(ptr));
	if (lol == NULL)
	{
		join_line(line, *line, ptr);
		*rest = NULL;
	}
	else
	{
		buf2 = malloc(lol - ptr + 1);
		ft_memcpy(buf2, ptr, lol - ptr);
		buf2[lol - ptr] = '\0';
		join_line(line, *line, buf2);
		join_line(rest, "", lol + 1);
		free(buf2);
	}
	if (lol != NULL || (lol == NULL && r < BUFF_SIZE && **line != '\0'))
		return (free_rest(rest));
	else
		return (0);
}

t_list	*get_fd(t_list **elem, int fd)
{
	t_list	*buf;

	if (*elem == NULL)
	{
		*elem = malloc(sizeof(t_list));
		(*elem)->content_size = fd;
		(*elem)->content = NULL;
		(*elem)->next = NULL;
	}
	buf = *elem;
	while (fd != (int)buf->content_size && buf->next)
		buf = buf->next;
	if ((int)buf->content_size != fd)
	{
		buf->next = malloc(sizeof(t_list));
		buf = buf->next;
		buf->content_size = fd;
		buf->next = NULL;
		buf->content = NULL;
	}
	return (buf);
}

int		get_next_line(const int fd, char **line)
{
	t_list			*rest;
	static t_list	*elem = NULL;
	char			buf[BUFF_SIZE + 1];
	int				r;

	r = BUFF_SIZE;
	rest = get_fd(&elem, fd);
	if (fd < 0 || line == 0)
		return (-1);
	*line = ft_memalloc(1);
	while (r != 0)
	{
		if (rest->content == NULL)
		{
			r = read(fd, buf, BUFF_SIZE);
			if (r == -1)
				return (-1);
			if (get_line(buf, line, (char**)&rest->content, r))
				return (1);
		}
		else if (get_line(rest->content, line, (char**)&rest->content, r))
			return (1);
	}
	free(rest->content);
	return (0);
}
