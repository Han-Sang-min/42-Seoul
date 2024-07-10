/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:17:49 by sangmiha          #+#    #+#             */
/*   Updated: 2022/11/22 11:36:07 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	make_proc(int id, int ac, t_fds *fds)
{
	pid_t	pid;

	if (id == ac)
		return (id);
	pid = fork();
	if (pid == -1)
		err_exit();
	if (pid > 0)
		return (id);
	if (id != 0)
		close(fds->in[IN]);
	fds->in[IN] = fds->out[IN];
	fds->in[OUT] = fds->out[OUT];
	close(fds->in[OUT]);
	pipe(fds->out);
	return(make_proc(id + 1, ac, fds));
}

int	main(int ac, char *av[], char *env[])
{
	t_fds	fds;
	int		id;

	if (ac < 4)
		ac_err();
	id = 0;
	pipe(fds.out);
	fds.doc = O_TRUNC;
	if (!ft_strncmp(av[1], "here_doc", 8))
	{
		here_doc(av, &fds);
		id++;
	}
	id = make_proc(id, ac - 4, &fds);
	if (id == 0)
		execute_first_cmd(av, env, id, &fds);
	else if (id + 4 == ac)
		execute_last_cmd(av, env, id, &fds);
	else
		execute_middle_cmd(av, env, id, &fds);
  	return (0);
}
