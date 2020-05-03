/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_builtin_exec.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 12:10:09 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/03 18:47:32 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>
/*
static int	sh_check_exec(t_shell *d, char *p, size_t i)
{
	char	*join;
	// char	*tmp1;

	// ft_printf("%s\n", ft_strsub(p, 0, i));
	join = ft_joindel(ft_strsub(p, 0, i), ft_strdup("/"));
	// ft_printf("%shere9\n", CBYELLOWB);
	// ft_printf("join ptr: %p\n", join);
	// ft_printf("join: %s\n", join);
	join = ft_joindel(join, ft_strdup(d->commands[0]));
	// ft_printf("here10\n");
	if (join && access(join, F_OK) == 0)
	{
		// ft_printf("here11\n");
		ft_strdel(&d->exec_path);
		d->exec_path = ft_strdup(join);
		ft_strdel(&join);
		return (0);
	}
	// ft_printf("here12%s\n", CRESET);
	// if (join == 0x0)
		ft_strdel(&join);
	return (1);
}
*/

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

	if ((str = ft_arraystr((const char **)d->env, "PATH")) == NULL)
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
/*
	// tmp = tab;
	while (tab)
	{
		// ft_printf("%shere1\n", CREDB);
		i = 0;
		ptr = ft_strchr(tab, '/');
		// ft_printf("here2\n");
		while (ptr && ptr[i] && ptr[i] != ':')
			i++;
		// ft_printf("here3%s\n", CRESET);
		if (!sh_check_exec(d, ptr, i))
			break;
		// ft_printf("here5\n");
		tab = ptr + i;
	}
	// ft_strdel(&tmp);
*/

static int	sh_trim_command_and_find_backslash(t_shell *d)
{
	char	*tmp;
	char	*ptr;
	char	**array;
	size_t	i;

	i = 0;
	while (d->commands[i])
	{
		tmp = ft_strtrim(d->commands[i]);
		ft_strdel(&d->commands[i]);
		d->commands[i++] = tmp;
		while ((ptr = ft_strchr(tmp, '\\')) != NULL)
		{
			array = (char**)ft_ptr_push((void const**)d->backslash, (void*)++ptr);//think about this
			ft_mem_arrdel((void**)d->backslash);
			d->backslash = ft_arraydup((const char **)array);
			free(array);
			tmp = ptr;
			tmp += tmp ? 1 : 0;
		}
	}
	return (0);
}

static int	sh_builtin(t_shell *d)
{
	size_t	i;

	i = 0;
	while (d->built_ins[i])
	{
		// ft_printf("builtins: [%d] %s	", i, d->built_ins[i]);
		// ft_printf("command: [0] %s\n", d->commands[0]);
		if (ft_strcmp(d->built_ins[i], d->commands[0]) == 0)
		{
			ft_printf("%s~~~~~~~~~~~~%s\n", CBLUEB, CRESET);
			ft_printf("MATCH\n");
			ft_printf("%s~~~~~~~~~~~~%s\n", CBLUEB, CRESET);
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
	if (sh_trim_command_and_find_backslash(d))
		return (1);
	if (sh_builtin(d))
	{
		return (1);
	}
	if (!sh_exec(d))
	{	
		ft_printf("%s~~~~~~~~~~~~%s\n", CREDB, CRESET);
		ft_printf("NOT BUILTIN COMMAND\n");
		ft_printf("%s~~~~~~~~~~~~%s\n", CREDB, CRESET);
		return (0);
	}
	return (0);
}
