/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_trim_command.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/04 14:48:44 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/05 17:32:56 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

static void	sh_find_backslash(t_shell *d)
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
}

static void	sh_dollar(t_shell *d)
{
	char	*env;
	char	*dollar;

	if (!d->commands[1][1])
	{
		ft_strdel(&d->commands[1]);
		d->commands[1] = ft_strdup("\0");
		return ;
	}
	dollar = ft_strjoin(&d->commands[1][1], "=");
	if (!(env = ft_strchr(ft_arraystr((const char **)d->env, dollar), '=')))
	{
		ft_strfee(d->commands[1], dollar, NULL);
		d->commands[1] = ft_strdup("\0");
		return ;
	}
	ft_strfee(d->commands[1], dollar, NULL);
	d->commands[1] = ft_strdup(++env);
}

static void	sh_expansions(t_shell *d)
{
	char	*home;
	char	*tmp;

	if (d->commands[1][0] == '~' &&
		(home = ft_strchr(ft_arraystr((const char **)d->env, "HOME"), '/')))
	{
		if (!(tmp = ft_strdup(ft_strchr(d->commands[1], '/'))))
		{
			ft_strdel(&d->commands[1]);
			d->commands[1] = ft_strdup(home);
			return ;
		}
		ft_strdel(&d->commands[1]);
		d->commands[1] = ft_strjoin(home, tmp);
		ft_strdel(&tmp);
		return ;
	}
	else if (d->commands[1][0] == '$')
		return (sh_dollar(d));
	ft_strdel(&d->commands[1]);
	d->commands[1] = ft_strdup("\0");
}

int			sh_trim_command(t_shell *d)
{
	sh_find_backslash(d);
	// sh_read_more_input(d);
	d->commands[1] && (*d->commands[1] == '~' || *d->commands[1] == '$') ?
		sh_expansions(d) : 0;
	return (1);
}
