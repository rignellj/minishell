/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 12:10:09 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 22:26:29 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static int	sh_check_exec_path(t_shell *sh, char *str, char **paths)
{
	ft_strdel(&sh->exec_path);
	sh->exec_path = str;
	ft_mem_arrdel((void **)paths);
	return (0);
}

static int	sh_exec(t_shell *sh)
{
	size_t		i;
	char		*str;
	char		*tmp;
	char		**paths;

	if ((str = ft_arraystr((const char **)sh->env, "PATH=")) == NULL)
		return (0);
	i = 0;
	paths = ft_strsplit(ft_strchr(str, '/'), ':');
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		str = ft_strjoin(tmp, sh->commands[0]);
		ft_strdel(&tmp);
		if (str && access(str, F_OK) == 0)
			return (sh_check_exec_path(sh, str, paths));
		i++;
		ft_strdel(&str);
	}
	ft_mem_arrdel((void **)paths);
	return (0);
}

static int	sh_builtin(t_shell *sh)
{
	size_t	i;

	i = 0;
	while (sh->built_ins[i])
	{
		if (ft_strcmp(sh->built_ins[i], sh->commands[0]) == 0)
		{
			// ft_printf("%s~~~~~~~~~~~~%s\n", CBLUEB, CRESET);
			// ft_printf("MATCH\n");
			// ft_printf("%s~~~~~~~~~~~~%s\n", CBLUEB, CRESET);
			return (sh_check_builtin(sh, sh->built_ins[i]));
		}
		i++;
	}
	return (0);
}

int			sh_builtin_exec(t_shell *sh)
{
	// sh->commands = ft_arraydup((const char**)commands);
	sh->i = 1;
	// sh_trim_command(sh);
	if (sh_builtin(sh))
		return (1);
	if (access(sh->commands[0], F_OK) == 0 || sh_exec(sh))
	{
		ft_strdel(&sh->exec_path);
		sh->exec_path = ft_strdup(sh->commands[0]);
		// ft_printf("command: |%s|\n", sh->commands[0]);
		// ft_printf("%s~~~~~~~~~~~~%s\n", CREDB, CRESET);
		// ft_printf("NOT BUILTIN COMMAND\n");
		// ft_printf("%s~~~~~~~~~~~~%s\n", CREDB, CRESET);
		return (0);
	}
	return (0);
}
