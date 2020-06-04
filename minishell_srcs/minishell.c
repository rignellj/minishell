/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 10:40:32 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/26 14:44:15 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>
// #include <stdio.h>

int			sh_error(char *error)
{
	ft_putstr_fd(error, FT_STDERR_FILENO);
	ft_strdel(&error);
	return (0);
}

int			shell_execute(char **commands, t_shell *d)
{
	pid_t	pid;
	int		status;
	
	if (!ft_strcmp("exit", commands[0]) || !ft_strcmp("bye", commands[0]))
		return (sh_exit(d, NULL));
	if (sh_builtin_exec(d, commands))
		return (1);
	if ((pid = fork()) == 0)
	{
		if (execve(d->exec_path, d->commands, d->env) == -1)
			sh_error(ft_strjoin(d->commands[0], ": command not found\n"));
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		sh_error(ft_strdup("Forking error\n"));
	else
	{
		d->child_status = -1;
		waitpid(pid, &status, WUNTRACED);
		d->child_status = 0;
	}
	return (1);
}

char		*sh_read_line(t_shell *d)
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
		d->file_fd = fd;
		close(fd);
	}
	if (ret < 1)
		ft_putchar('\n');
	return (ret > 0 ? line : ft_strdup("\0"));
}

void		minishell(t_shell *data)
{
	int		status;
	char	*line;
	char	**commands;

	status = 1;
	while (status)
	{
		sh_display_prompt(data);
		line = sh_read_line(data);
		data->user_command = ft_strdup(line);
		commands = ft_strsplit(line, ' ');
		status = *commands && **commands ? shell_execute(commands, data) : 1;
		sh_del_command(data, line, commands);
		sh_init_struct(data);
	}
	sh_del_struct(data);
}
