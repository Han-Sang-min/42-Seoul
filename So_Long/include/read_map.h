/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 18:24:18 by hansangmin        #+#    #+#             */
/*   Updated: 2022/10/02 19:36:07 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_MAP_H
# define READ_MAP_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

# define READ_MAP 1

typedef struct s_list_of_map
{
	char					part_of_map[11];
	struct s_list_of_map	*next;
}	t_list_of_map;

void	err_occur(int error_code);

#endif