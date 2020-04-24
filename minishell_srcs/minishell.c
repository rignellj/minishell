/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 10:40:32 by jrignell          #+#    #+#             */
/*   Updated: 2020/04/24 20:52:49 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
#include <fcntl.h>

void		sh_error(char *error)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_strdel(&error);
}

int			shell_execute(char **commands)
{
	size_t	i;
	pid_t	pid;
	char	*join;
	int		status;

	i = 0;
	while (commands[i])
	{
		if (ft_strcmp("exit", commands[i]) == 0)
			return (0);
		i++;
	}
	if (!commands)
		return (1);
	if ((pid = fork()) == 0 && (join = ft_strjoin("/bin/", commands[0])))
	{
		if (execve(join, commands, NULL) == -1)
			sh_error(ft_strjoin(commands[0], ": command not found\n"));
		ft_strdel(&join);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		sh_error(ft_strdup("Forking error\n"));
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

char		*sh_read_line(void)
{
	char	*line;
	char	**file_commands;
	int		fd;

	if ((get_next_line(0, &line) == 1) && !ft_strncmp(line, "./", 2)
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
		ft_mem_arrdel((void**)file_commands);
		close(fd);
	}
/*
	else if (ft_strcmp(line, "exit"))
	{
		ft_printf("%s: command not found\n", line);
	}
*/
	return (line);
}

void		minishell(t_shell *data)
{
	int		status;
	char	*line;
	char	**commands;

	sh_form_struct(data);
	status = 1;
	while (status)
	{
		ft_printf("$> ");
		line = sh_read_line();
		commands = ft_strsplit(line, ' ');
		// ft_printf("line : |%s|\n", line);
		status = shell_execute(commands);
		ft_strdel(&line);
		ft_mem_arrdel((void**)(commands));
	}
	ft_mem_arrdel((void**)data->env);
}


// if (pid == 0)
// {
//     if (execvp(args[0], args) == -1)
// 	{
//       perror("lsh");
//     }
//     exit(EXIT_FAILURE);
// }
// else if (pid < 0)
// {
//     // Error forking
//     perror("lsh");
// }
// else
// {
//     // Parent process
//     do
// 	{
//       wpid = waitpid(pid, &status, WUNTRACED);
//     }
// 	while (!WIFEXITED(status) && !WIFSIGNALED(status));
// }
