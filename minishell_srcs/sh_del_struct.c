/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_del_struct.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 15:05:28 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/05 16:05:53 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_del_struct(t_shell *d)
{
	ft_mem_arrdel((void**)d->built_ins);
	ft_strdel(&(d->exec_path));
	ft_mem_arrdel((void **)d->backslash);
	ft_mem_arrdel((void**)d->env);
}
