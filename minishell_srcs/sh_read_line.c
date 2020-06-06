/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_read_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 14:53:37 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 21:00:14 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>

char		*sh_read_line(t_shell *sh)
{
	char	*line;
	char	**file_commands;
	int		fd;
	int		ret;

	if ((ret = get_next_line(0, &line) == 1) && !ft_strncmp(line, "./", 2)
		&& (fd = open(line, O_RDONLY)) >= 0)
	{
		file_commands = ft_array_push(ft_arraynew(0), line);
		ft_strdel(&line);
		while ((get_next_line(fd, &line)) > 0)
		{
			file_commands = ft_array_push(file_commands, line);
			ft_strdel(&line);
		}
		line = ft_implode(file_commands);
		ft_mem_arrdel((void **)file_commands);
		sh->file_fd = fd;
		close(fd);
	}
	if (ret < 1)
		ft_putchar('\n');
	return (ret > 0 ? line : ft_strdup("\0"));
}