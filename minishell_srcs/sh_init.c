/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 12:15:21 by jrignell          #+#    #+#             */
/*   Updated: 2020/06/06 21:01:47 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <term.h>

static void	sh_assign_values(int ac, char *av[], char *env[], t_shell *sh)
{
	g_shell = sh;
	sh->ac = ac;
	sh->av = av;
	sh->env = ft_arraydup((const char **)env);
}

static int	sh_validate_terminal(t_shell *sh)
{
	char	*term_name;
	int		res;
	char	buf[2048];

	if ((sh->term_fd = open(ttyname(0), O_RDWR | O_NDELAY | O_NOCTTY)) < 0)
		return (sh_exit(sh, "Failed to open port\n"));
	if (!(term_name = getenv("TERM")))
		return
		(sh_exit(sh, "Set a terminal type using `export TERM=<type>`. Exiting.\n"));
	if (!isatty(STDERR_FILENO))
		return sh_exit(sh, "Not a terminal. Exiting..\n");
	if ((res = tgetent(buf, term_name)) < 1)
	{
		res == -1 ? sh_exit(sh, "Could not access termcap data base. Exiting..\n")
		: sh_exit(sh, "Terminal type not found. Exiting..\n");
	}
	return (0);
}

static void	sh_configure_term_settings(t_shell *sh)
{
	if (tcgetattr(sh->term_fd, &sh->original_term_mode) == -1)
		sh_exit(sh, "tcgetattr: failed to get current state. Exiting..\n");
	sh->current_term_mode = sh->original_term_mode;
	sh->current_term_mode.c_lflag &= ~(IEXTEN);
	// sh->current_term_mode.c_lflag &= ~(ICANON);
	sh->current_term_mode.c_iflag &= ~(IXON);
	sh->current_term_mode.c_cc[VMIN] = 1;
	sh->current_term_mode.c_cc[VTIME] = 0;
	if (tcsetattr(sh->term_fd, TCSANOW, &sh->current_term_mode) == -1)
		sh_exit(sh, "tcsetattr: failed to make requested changes. Exiting..\n");
}

void		sh_init(int ac, char *av[], char *env[], t_shell *sh)
{
	ft_bzero(sh, sizeof(t_shell));
	sh_assign_values(ac, av, env, sh);
	sh_form_struct(sh);
	sh_validate_terminal(sh);//
	sh_configure_term_settings(sh);
	sh_init_signal_handlers();
}
