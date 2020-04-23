/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jrignell <jrignell@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/24 10:55:43 by jrignell          #+#    #+#             */
/*   Updated: 2020/04/12 14:42:37 by jrignell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*fresh;
	char	*ptr;

	if (!s || !(fresh = ft_memalloc(ft_strlen((const char*)s) + 1)))
		return (NULL);
	ptr = (char*)s;
	while (*ptr && f)
		*fresh++ = f(*ptr++);
	return (fresh - (ft_strlen((const char*)s)));
}
