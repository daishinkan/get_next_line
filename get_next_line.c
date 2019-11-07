/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekindomb <ekindomb@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 15:31:33 by ekindomb          #+#    #+#             */
/*   Updated: 2019/11/06 12:41:13 by ekindomb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_verify_line(char **buf, char **line)
{
	char	*buffer;
	char	*buf_chr;
	int		i;

	i = 0;
	buf_chr = *buf;
	while (buf_chr[i])
	{
		if (buf_chr[i] == '\n')
		{
			buffer = &buf_chr[i];
			*buffer = '\0';
			*line = ft_strdup(buf_chr);
			*buf = ft_strdup(buffer + 1);
			free(buf_chr);
			return (1);
		}
		i++;
	}
	*line = *buf;
	return (0);
}

static int	ft_read_file(int fd, char *heap, char **buf, char **line)
{
	int		i;
	char	*buffer;

	while ((i = read(fd, heap, BUFFER_SIZE)) > 0)
	{
		heap[i] = '\0';
		if (*buf)
		{
			buffer = *buf;
			*buf = ft_strjoin(buffer, heap);
			free(buffer);
			buffer = NULL;
		}
		else
			*buf = ft_strdup(heap);
		if (ft_verify_line(buf, line))
			break ;
	}
	return (RET(i));
}

int			ft_value_end(int i, char **line)
{
	if (!i)
	{
		*line = ft_strdup("\0");
		return (0);
	}
	return (1);
}

void		ft_fill_(char *heap)
{
	int i;

	i = -1;
	while (++i < BUFFER_SIZE)
		heap[i] = '\0';
}

int			get_next_line(int fd, char **line)
{
	static char	*stack[MAX_FD];
	char		*heap;
	int			i;

	if (!line || (fd < 0 || fd > MAX_FD) || (read(fd, stack[fd], 0) < 0)
			|| (!(heap = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1))))
		return (-1);
	if (stack[fd])
		if (ft_verify_line(&stack[fd], line))
		{
			free(heap);
			return (1);
		}
	ft_fill_(heap);
	i = ft_read_file(fd, heap, &stack[fd], line);
	free(heap);
	if (i != 0 || stack[fd] == NULL || stack[fd][0] == '\0')
	{
		if (!ft_value_end(i, line))
			return (0);
		return (1);
	}
	*line = stack[fd];
	stack[fd] = NULL;
	return (RET(i));
}
