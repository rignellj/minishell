/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_form_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 20:27:38 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 20:59:32 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	sh_update_shell_env(t_shell *sh)
{
	size_t	i;
	char	cwd[1024];

	i = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		while (sh->env[i])
		{
			if (ft_strncmp(sh->env[i], "SHELL=", 6) == 0)
			{
				ft_strdel(&sh->env[i]);
				sh->env[i] = ft_strjoin("SHELL=", cwd);
				return ;
			}
			i++;
		}
	}
}

void	sh_form_struct(t_shell *sh)
{
	if (!(sh->built_ins = (char**)ft_memalloc(sizeof(*sh->built_ins) * 6)))
	{
		sh_error(ft_strdup("allocation error, exiting..\n"));
		exit(EXIT_FAILURE);
	}
	sh->built_ins[0] = ft_strdup("echo");
	sh->built_ins[1] = ft_strdup("cd");
	sh->built_ins[2] = ft_strdup("env");
	sh->built_ins[3] = ft_strdup("setenv");
	sh->built_ins[4] = ft_strdup("unsetenv");
	sh->exec_path = ft_strnew(0);
	sh->backslash = ft_arraynew(0);
	sh_update_shell_env(sh);
}
