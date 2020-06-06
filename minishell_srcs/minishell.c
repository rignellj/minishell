/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 10:40:32 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 22:11:26 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
// #include <stdio.h>

int			sh_error(char *error)
{
	ft_putstr_fd(error, STDERR_FILENO);
	ft_strdel(&error);
	return (0);
}

void		minishell(t_shell *sh)
{
	int		status;
	char	*line;

	status = 1;
	while (status)
	{
		sh_display_prompt(sh);
		line = sh_read_line(sh);
		sh->user_command = ft_strdup(line);
		sh_command_parse(sh);
		status = *sh->commands && **sh->commands ? sh_shell_execute(sh) : 1;
		sh_del_command(sh, line);
		sh_init_struct(sh);
	}
	sh_del_struct(sh);
}
