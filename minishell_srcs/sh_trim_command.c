/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_trim_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 14:48:44 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 21:01:01 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	sh_find_backslash(t_shell *sh)
{
	char	*tmp;
	char	*ptr;
	char	**array;
	size_t	i;

	i = 0;
	while (sh->commands[i])
	{
		tmp = ft_strtrim(sh->commands[i]);
		ft_strdel(&sh->commands[i]);
		sh->commands[i++] = tmp;
		while ((ptr = ft_strchr(tmp, '\\')) != NULL)
		{
			array = (char**)ft_ptr_push((void const**)sh->backslash, (void*)++ptr);//think about this
			ft_mem_arrdel((void**)sh->backslash);
			sh->backslash = ft_arraydup((const char **)array);
			free(array);
			tmp = ptr;
			tmp += tmp ? 1 : 0;
		}
	}
}

static void	sh_dollar(t_shell *sh)
{
	char	*env;
	char	*dollar;

	if (!sh->commands[1][1])
	{
		ft_strdel(&sh->commands[1]);
		sh->commands[1] = ft_strdup("\0");
		return ;
	}
	dollar = ft_strjoin(&sh->commands[1][1], "=");
	if (!(env = ft_strchr(ft_arraystr((const char **)sh->env, dollar), '=')))
	{
		ft_strfee(sh->commands[1], dollar, NULL);
		sh->commands[1] = ft_strdup("\0");
		return ;
	}
	ft_strfee(sh->commands[1], dollar, NULL);
	sh->commands[1] = ft_strdup(++env);
}

static void	sh_expansions(t_shell *sh)
{
	char	*home;
	char	*tmp;

	if (sh->commands[1][0] == '~' &&
		(home = ft_strchr(ft_arraystr((const char **)sh->env, "HOME"), '/')))
	{
		if (!(tmp = ft_strdup(ft_strchr(sh->commands[1], '/'))))
		{
			ft_strdel(&sh->commands[1]);
			sh->commands[1] = ft_strdup(home);
			return ;
		}
		ft_strdel(&sh->commands[1]);
		sh->commands[1] = ft_strjoin(home, tmp);
		ft_strdel(&tmp);
		return ;
	}
	else if (sh->commands[1][0] == '$')
		return (sh_dollar(sh));
	ft_strdel(&sh->commands[1]);
	sh->commands[1] = ft_strdup("\0");
}

int			sh_trim_command(t_shell *sh)
{
	sh_find_backslash(sh);
	sh_read_more_input(sh);
	sh->commands[1] && (*sh->commands[1] == '~' || *sh->commands[1] == '$') ?
		sh_expansions(sh) : 0;
	return (1);
}
