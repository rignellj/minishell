/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 10:40:32 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 20:49:34 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>
#include <signal.h>
// #include <stdio.h>

int			sh_error(char *error)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_strdel(&error);
	return (0);
}

int			shell_execute(char **commands, t_shell *sh)
{
	pid_t	pid;
	int		status;
	
	if (!ft_strcmp("exit", commands[0]) || !ft_strcmp("bye", commands[0]))
		return (sh_exit(sh, NULL));
	if (sh_builtin_exec(sh, commands))
		return (1);
	if ((pid = fork()) == 0)
	{
		if (execve(sh->exec_path, sh->commands, sh->env) == -1)
			sh_error(ft_strjoin(sh->commands[0], ": command not found\n"));
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		sh_error(ft_strdup("Forking error\n"));
	else
	{
		sh->child_status = -1;
		waitpid(pid, &status, WUNTRACED);
		sh->child_status = 0;
	}
	return (1);
}

void		minishell(t_shell *sh)
{
	int		status;
	char	*line;
	char	**commands;

	status = 1;
	while (status)
	{
		sh_display_prompt(sh);
		line = sh_read_line(sh);
		sh->user_command = ft_strdup(line);
		sh_command_parse(sh);
		commands = sh->commands;
		status = *commands && **commands ? shell_execute(commands, sh) : 1;
		sh_del_command(sh, line);
		sh_init_struct(sh);
	}
	sh_del_struct(sh);
}
