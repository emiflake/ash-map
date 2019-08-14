/* ************************************************************************** */
/*                                                                            */
/*                                                             ::::::::       */
/*   ash_common.c                                            :+:    :+:       */
/*                                                          +:+               */
/*   By: emiflake <marvin@student.codam.nl>                +#+                */
/*                                                        +#+                 */
/*   Created: 2019/08/14 16:32:23 by emiflake            #+#    #+#           */
/*   Updated: 2019/08/14 18:05:38 by emiflake            ########   odam.nl   */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include "../inc/ash_common.h"

size_t	ash_strlen(const char *string)
{
	size_t length;

	length = 0;
	while (string[length])
		length++;
	return (length);
}

int	ash_strcmp(const char *s1, const char *s2)
{
	int				i;
	unsigned char	*us1;
	unsigned char	*us2;

	i = 0;
	us1 = (unsigned char*)s1;
	us2 = (unsigned char*)s2;
	while (us1[i] && us2[i] && us1[i] == us2[i])
		i++;
	return (us1[i] - us2[i]);
}
