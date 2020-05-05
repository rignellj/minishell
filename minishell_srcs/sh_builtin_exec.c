/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 12:10:09 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/05 17:13:39 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	sh_check_exec_path(t_shell *d, char *str, char **paths)
{
	ft_strdel(&d->exec_path);
	d->exec_path = str;
	ft_mem_arrdel((void **)paths);
	return (0);
}

static int	sh_exec(t_shell *d)
{
	size_t		i;
	char		*str;
	char		*tmp;
	char		**paths;

	if ((str = ft_arraystr((const char **)d->env, "PATH=")) == NULL)
		return (0);
	i = 0;
	paths = ft_strsplit(ft_strchr(str, '/'), ':');
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		str = ft_strjoin(tmp, d->commands[0]);
		ft_strdel(&tmp);
		if (str && access(str, F_OK) == 0)
			return (sh_check_exec_path(d, str, paths));
		i++;
		ft_strdel(&str);
	}
	ft_mem_arrdel((void **)paths);
	return (0);
}

static int	sh_builtin(t_shell *d)
{
	size_t	i;

	i = 0;
	while (d->built_ins[i])
	{
		if (ft_strcmp(d->built_ins[i], d->commands[0]) == 0)
		{
			// ft_printf("%s~~~~~~~~~~~~%s\n", CBLUEB, CRESET);
			// ft_printf("MATCH\n");
			// ft_printf("%s~~~~~~~~~~~~%s\n", CBLUEB, CRESET);
			return (sh_check_builtin(d, d->built_ins[i]));
		}
		i++;
	}
	return (0);
}

int			sh_builtin_exec(t_shell *d, char **commands)
{
	d->commands = ft_arraydup((const char**)commands);
	d->i = 1;
	sh_trim_command(d);
	if (sh_builtin(d))
		return (1);
	if (!sh_exec(d))
	{
		// ft_printf("%s~~~~~~~~~~~~%s\n", CREDB, CRESET);
		// ft_printf("NOT BUILTIN COMMAND\n");
		// ft_printf("%s~~~~~~~~~~~~%s\n", CREDB, CRESET);
		return (0);
	}
	return (0);
}
