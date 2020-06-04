/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init_signal_handlers.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 12:36:44 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/26 14:20:24 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

/*
********************************************************************************
** SIGINT is for Ctrl-C, SIGSTP is for Ctrl-Z, SIGQUIT is for Ctrl-\          **
********************************************************************************
*/

static void	sh_signal_handlers(int sig)
{
	if (sig == SIGINT || sig == SIGTSTP || sig == SIGQUIT)
	{
		ft_putchar('\n');
		if (g_shell->child_status != -1)
			sh_display_prompt(g_shell);
	}
}
void	sh_init_signal_handlers(void)
{
	signal(SIGINT, sh_signal_handlers);
	signal(SIGTSTP, sh_signal_handlers);
	signal(SIGQUIT, sh_signal_handlers);
}
