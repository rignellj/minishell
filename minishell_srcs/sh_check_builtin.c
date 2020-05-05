/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_check_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 14:46:55 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/05 16:05:48 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*
********************************************************************************
** char *bic stands for builtin command                                       **
********************************************************************************
*/

static int	sh_echo(t_shell *d)
{
	d->commands[1] ? ft_printf("%s\n", d->commands[1]) : ft_putchar('\n');
	return (1);
}

int			sh_check_builtin(t_shell *d, char *bic)
{
	if (ft_strcmp(bic, "echo") == 0)
		return (sh_echo(d));
	else if (ft_strcmp(bic, "cd") == 0)
		return (sh_change_dir(d));
	else if (ft_strnstr(bic, "env", 8))
		return (sh_env(d, ft_strlen(bic)));
	return (1);
}
