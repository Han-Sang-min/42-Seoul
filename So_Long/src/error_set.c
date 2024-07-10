/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 13:31:48 by hansangmin        #+#    #+#             */
/*   Updated: 2022/10/02 19:08:06 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

void	err_occur(int error_code)
{
	printf("Error\n");
	if (error_code == 1)
		perror("read_map file error ");
	else if (error_code == 2)
		perror("error_check file error ");
	else if (error_code == 3)
		perror("init_mlx file error ");
	exit(1);
}

void	err_occur_msg(char *msg)
{
	printf("Error\n");
	printf("%s\n", msg);
	exit(1);
}
