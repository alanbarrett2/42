/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arrays.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vtouffet <vtouffet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/26 18:48:10 by vtouffet          #+#    #+#             */
/*   Updated: 2017/11/30 14:01:33 by vtouffet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../../includes/core.h"

int	type_a(va_list args, t_flags *flags)
{
	int		*tab;
	int		index;
	int		size;
	char	c;

	size = 0;
	tab = va_arg(args, int*);
	index = -1;
	while (tab[++index])
	{
		size += ft_write("array[", 6, flags);
		ft_putnbr_fd(index, STDOUT);
		ft_get_number_size_u((uintmax_t)index, 10, &size);
		size += ft_write("] = ", 4, flags);
		if (ft_isprint(tab[index]) && (c = (char)tab[index]))
			size += ft_write(&c, 1, flags);
		else
		{
			ft_get_number_size_u((uintmax_t)(tab[index] < 0 ? -tab[index] :
											tab[index]), 10, &size);
			ft_putnbr_fd(tab[index], STDOUT);
		}
		size += ft_write("\n", 1, flags);
	}
	return (size);
}

int	type_a_upper(va_list args, t_flags *flags)
{
	char	**tab;
	int		index;
	int		size;

	(void)flags;
	size = 0;
	tab = va_arg(args, char**);
	index = 0;
	while (tab[index])
	{
		size += ft_write("array[", 6, flags);
		ft_putnbr_fd(index, STDOUT);
		ft_get_number_size_u((uintmax_t)index, 10, &size);
		size += ft_write("] = \"", 5, flags);
		size += ft_write(tab[index], (int)ft_strlen(tab[index]), flags);
		size += ft_write("\"\n", 2, flags);
		++index;
	}
	return (size);
}
