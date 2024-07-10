/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extra.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/19 14:24:57 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/22 01:10:29 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	err_exit(void)
{
	perror("");
	exit(1);
}

void	cmd_err(void)
{
	write(STDERR_FILENO, "Command not found\n", 19);
	exit(127);
}

void	ac_err(void)
{
	write(STDERR_FILENO, "Not correct number of arguments\n", 31);
	exit(1);
}
