/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_current_node.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/10 12:39:30 by jrignell          #+#    #+#             */
/*   Updated: 2020/04/23 19:59:04 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_current_node(t_list **node)
{
	t_list	*current;

	current = *node;
	ft_putchar('\n');
	while (current)
	{
		if (current->content)
		{
			ft_printf("Previous %p\n", current->prev);
			ft_printf("Current address %p\n", current);
			ft_printf("Current content address %p\n", current->content);
			ft_printf("Current content size %d\n", current->content_size);
			ft_printf("Next %p\n", current->next);
			ft_printf("-----------------\n");
		}
		current = current->next;
	}
	ft_putchar('\n');
}
