/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_del_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 12:09:02 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/24 12:11:29 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_del_command(t_shell *d, char *line, char **c)
{
	ft_strdel(&d->user_command);
	ft_strdel(&line);
	d->i ? ft_mem_arrdel((void **)d->commands) : 0;
	ft_mem_arrdel((void **)(c));
}
