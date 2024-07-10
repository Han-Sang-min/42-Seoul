/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/09 16:14:18 by wonbpark          #+#    #+#             */
/*   Updated: 2023/04/29 16:57:27 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	check_identifier(char *id)
{
	if (!id)
		return (0);
	else if (!ft_strncmp(id, "A", 2))
		return (1);
	else if (!ft_strncmp(id, "C", 2))
		return (2);
	else if (!ft_strncmp(id, "L", 2))
		return (3);
	else if (!ft_strncmp(id, "sp", 3))
		return (4);
	else if (!ft_strncmp(id, "pl", 3))
		return (5);
	else if (!ft_strncmp(id, "cy", 3))
		return (6);
	else
		return (-1);
}

void	check_extension(char *file)
{
	char	*tmp;
	int		i;

	tmp = file;
	i = ft_strlen(tmp);
	tmp = tmp + i - 3;
	if (ft_strncmp(tmp, ".rt", 4))
		exit_error("Error: Invalid file extension\n");
}

char	*check_number(char *num)
{
	int			i;
	long long	sum;

	i = 0;
	sum = 0;
	while (num[i])
	{
		if (i == 0 && (num[i] == '-' || num[i] == '+'))
			i++;
		if (!ft_isdigit(num[i]))
			exit_error("Error: non-digit argument\n");
		sum = sum * 10 + (num[i] - '0');
		if (sum > INT_MAX)
			exit_error("Error: number out of INT range\n");
		i++;
	}
	return (num);
}
