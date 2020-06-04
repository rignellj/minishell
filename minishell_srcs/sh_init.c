/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sh_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 12:15:21 by jrignell          #+#    #+#             */
/*   Updated: 2020/05/27 19:12:02 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <stdlib.h>
#include <term.h>

static void	sh_assign_values(int ac, char *av[], char *env[], t_shell *d)
{
	g_shell = d;
	d->ac = ac;
	d->av = av;
	d->env = ft_arraydup((const char **)env);
}

static int	sh_validate_terminal(t_shell *d)
{
	char	*term_name;
	int		res;
	char	buf[2048];

	if ((d->term_fd = open(ttyname(0), O_RDWR | O_NDELAY | O_NOCTTY)) < 0)
		return (sh_exit(d, "Failed to open port\n"));
	if (!(term_name = getenv("TERM")))
		return
		(sh_exit(d, "Set a terminal type using `export TERM=<type>`. Exiting.\n"));
	if (!isatty(STDERR_FILENO))
		return sh_exit(d, "Not a terminal. Exiting..\n");
	if ((res = tgetent(buf, term_name)) < 1)
	{
		res == -1 ? sh_exit(d, "Could not access termcap data base. Exiting..\n")
		: sh_exit(d, "Terminal type not found. Exiting..\n");
	}
	return (0);
}

static void	sh_configure_term_settings(t_shell *d)
{
	if (tcgetattr(d->term_fd, &d->original_term_mode) == -1)
		sh_exit(d, "tcgetattr: failed to get current state. Exiting..\n");
	d->current_term_mode = d->original_term_mode;
	d->current_term_mode.c_lflag &= ~(IEXTEN);
	// d->current_term_mode.c_lflag &= ~(ICANON);
	d->current_term_mode.c_iflag &= ~(IXON);
	d->current_term_mode.c_cc[VMIN] = 1;
	d->current_term_mode.c_cc[VTIME] = 0;
	if (tcsetattr(d->term_fd, TCSANOW, &d->current_term_mode) == -1)
		sh_exit(d, "tcsetattr: failed to make requested changes. Exiting..\n");
}

void		sh_init(int ac, char *av[], char *env[], t_shell *d)
{
	ft_bzero(d, sizeof(t_shell));
	sh_assign_values(ac, av, env, d);
	sh_form_struct(d);
	sh_validate_terminal(d);//
	sh_configure_term_settings(d);
	sh_init_signal_handlers();
}
