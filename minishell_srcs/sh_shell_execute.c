/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_shell_execute.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 22:09:17 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 22:11:18 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

int			sh_shell_execute(t_shell *sh)
{
	pid_t	pid;
	int		status;
	
	if (!ft_strcmp("exit", sh->commands[0]) || !ft_strcmp("bye", sh->commands[0]))
		return (sh_exit(sh, NULL));
	if (sh_builtin_exec(sh))
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