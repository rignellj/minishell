/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_check_builtin.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 14:46:55 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 20:58:25 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdlib.h>

/*
********************************************************************************
** char *bic stands for builtin command                                       **
********************************************************************************
*/

static int	sh_echo(t_shell *sh)
{
	sh->commands[1] ? ft_printf("%s\n", sh->commands[1]) : ft_putchar('\n');
	return (1);
}

int			sh_check_builtin(t_shell *sh, char *bic)
{
	if (ft_strcmp(bic, "echo") == 0)
		return (sh_echo(sh));
	else if (ft_strcmp(bic, "cd") == 0)
		return (sh_change_dir(sh));
	else if (ft_strnstr(bic, "env", 8))
		return (sh_env(sh, ft_strlen(bic)));
	return (1);
}
