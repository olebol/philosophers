/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: opelser <opelser@student.codam.nl>           +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 19:57:54 by opelser       #+#    #+#                 */
/*   Updated: 2023/07/18 23:06:56 by opelser       ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	ft_strlen(const char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	*ft_error(void *data, int err)
{
	const char	*errors[2] = {
	[0] = "Invalid arguments\n",
	[1] = NULL };

	if (data)
		free(data);
	if (err != -1)
		write(2, errors[err], ft_strlen(errors[err]));
	return (NULL);
}
