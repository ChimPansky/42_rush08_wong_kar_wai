/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkasbari <thomas.kasbarian@gmail.com>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 13:05:59 by tkasbari          #+#    #+#             */
/*   Updated: 2023/12/02 15:51:07 by tkasbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	fill_buf(int fd, t_buffer *buf, t_line *line)
{
	buf->last_read = read(fd, buf->str, BUFFER_SIZE);
	buf->len = buf->last_read;
	if (buf->last_read < 0)
	{
		buf->str[0] = '\0';
		line->error = -1;
	}
}

static void	move_buf_line(t_buffer *buf, t_line *line, int nbytes)
{
	char	*new;

	new = malloc(sizeof(char *) * (line->len + nbytes + 1));
	if (!new)
	{
		line->error = -1;
		return ;
	}
	if (line->str && line->len > 0)
		ft_memmove(new, line->str, line->len);
	ft_memmove(new + line->len, buf->str, nbytes);
	line->len += nbytes;
	new[line->len] = '\0';
	free(line->str);
	line->str = new;
	if (nbytes == buf->len)
	{
		buf->str[0] = '\0';
		buf->len = 0;
	}
	else
	{
		ft_memmove(buf->str, buf->str + nbytes, buf->len - nbytes);
		buf->len -= nbytes;
	}
}

static int	create_line(int fd, t_buffer *buf, t_line *line)
{
	int		nbytes;

	nbytes = 0;
	if (!line || buf->str[0] == '\0')
		fill_buf(fd, buf, line);
	if (line->error)
		return (1);
	while (nbytes < buf->len && buf->str[nbytes] != '\n')
		nbytes++;
	if (nbytes < buf->len)
		nbytes++;
	if (nbytes)
		move_buf_line(buf, line, nbytes);
	if (line->error)
		return (1);
	if ((line->str && line->str[line->len - 1] == '\n') || buf->last_read == 0)
		return (1);
	return (0);
}

t_line	get_next_line(int fd)
{
	static t_buffer	buf[MAX_FDS];
	t_line			line;

	line.str = NULL;
	line.len = 0;
	line.error = 0;
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		line.error = -1;
		return (line);
	}
	while (!create_line(fd, &buf[fd], &line))
		;
	if (line.error)
		ft_free_and_null((void **)&line.str);
	if (!line.str || (!buf[fd].len && !buf[fd].last_read))
	{
		buf[fd].str[0] = '\0';
		buf[fd].len = 0;
	}
	return (line);
}
