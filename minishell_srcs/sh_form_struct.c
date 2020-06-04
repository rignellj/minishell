/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_form_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/24 20:27:38 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/04 21:21:41 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	sh_update_shell_env(t_shell *d)
{
	size_t	i;
	char	cwd[1024];

	i = 0;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		while (d->env[i])
		{
			if (ft_strncmp(d->env[i], "SHELL=", 6) == 0)
			{
				ft_strdel(&d->env[i]);
				d->env[i] = ft_strjoin("SHELL=", cwd);
				return ;
			}
			i++;
		}
	}
}

void	sh_form_struct(t_shell *d)
{
	if (!(d->built_ins = (char**)ft_memalloc(sizeof(*d->built_ins) * 6)))
	{
		sh_error(ft_strdup("allocation error, exiting..\n"));
		exit(EXIT_FAILURE);
	}
	d->built_ins[0] = ft_strdup("echo");
	d->built_ins[1] = ft_strdup("cd");
	d->built_ins[2] = ft_strdup("env");
	d->built_ins[3] = ft_strdup("setenv");
	d->built_ins[4] = ft_strdup("unsetenv");
	d->exec_path = ft_strnew(0);
	d->backslash = ft_arraynew(0);
	sh_update_shell_env(d);
}
