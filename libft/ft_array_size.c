/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_array_size.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijaaskel <ijaaskel@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/22 12:46:34 by ijaaskel          #+#    #+#             */
/*   Updated: 2023/01/22 12:47:20 by ijaaskel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

size_t	ft_array_size(const void **array)
{
	size_t	i;

	i = 0;
	while (array[i])
		i++;
	return (i);
}
