/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_del_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 15:05:28 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 20:58:45 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <term.h>

static void	sh_reset_original_config(t_shell *sh)
{
	if (tcsetattr(sh->term_fd, TCSANOW, &sh->original_term_mode) == -1)
		sh_exit(sh, "tcsetattr: failed to make requested changes. Exiting..\n");
}

void		sh_del_struct(t_shell *sh)
{
	ft_mem_arrdel((void**)sh->built_ins);
	ft_strdel(&(sh->exec_path));
	ft_mem_arrdel((void **)sh->backslash);
	ft_mem_arrdel((void**)sh->env);
	sh_reset_original_config(sh);
}
