/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 19:57:54 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/19 18:05:58 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_error(void *data, char *str)
{
	if (data)
		free(data);
	if (str)
		printf("%s\n", str);
	return (NULL);
}
