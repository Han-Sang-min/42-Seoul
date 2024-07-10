/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 18:15:48 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/22 01:11:05 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef PIPEX_H
#define PIPEX_H

# include "../libft/include/ft_printf.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <stdio.h>
# include <string.h>

#define IN 0
#define OUT 1

typedef struct s_fds
{
	int	in[2];
	int	out[2];
}	t_fds;

/* error part */
void	err_exit(void);
void	cmd_err(void);
void	ac_err(void);

/* parsing part */
char	*parsing_cmd(char *av[], char *env[], int id);
char	**parsing_av(char *av[], int id);

/* execute part */
void	execute_first_cmd(char *av[], char *env[], int id, t_fds *fds);
void	execute_middle_cmd(char *av[], char *env[], int id, t_fds *fds);
void	execute_last_cmd(char *av[], char *env[], int id, t_fds *fds);

#endif