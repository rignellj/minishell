/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_del_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 15:05:28 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/26 15:26:10 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>

static void	sh_reset_original_config(t_shell *d)
{
	if (tcsetattr(d->term_fd, TCSANOW, &d->original_term_mode) == -1)
		sh_exit(d, "tcsetattr: failed to make requested changes. Exiting..\n");
}

void		sh_del_struct(t_shell *d)
{
	ft_mem_arrdel((void**)d->built_ins);
	ft_strdel(&(d->exec_path));
	ft_mem_arrdel((void **)d->backslash);
	ft_mem_arrdel((void**)d->env);
	sh_reset_original_config(d);
}
