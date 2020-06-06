/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 12:45:11 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 21:14:39 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
// #include <stdlib.h>

void	sh_init_struct(t_shell *sh)
{
	sh->file_fd = -1;
	sh->i = 0;
	ft_strdel(&(sh->exec_path));
	sh->exec_path = ft_strnew(0);
	ft_mem_arrdel((void **)sh->backslash);
	sh->backslash = ft_arraynew(0);
}
