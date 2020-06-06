/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_del_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 12:09:02 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 20:58:36 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sh_del_command(t_shell *sh, char *line)
{
	ft_strdel(&sh->user_command);
	ft_strdel(&line);
	sh->i ? ft_mem_arrdel((void **)sh->commands) : 0;
}
