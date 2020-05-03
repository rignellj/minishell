/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_struct.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/25 12:45:11 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/03 18:50:29 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include <stdlib.h>

void	sh_init_struct(t_shell *data)
{
	data->fd = -1;
	ft_strdel(&(data->exec_path));
	data->exec_path = ft_strnew(0);
	ft_mem_arrdel((void **)data->backslash);
	data->backslash = ft_arraynew(0);
}
