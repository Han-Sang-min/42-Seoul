/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 15:03:54 by sangmiha          #+#    #+#             */
/*   Updated: 2023/01/21 08:53:35 by hansangmin       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/include/ft_printf.h"
# include <stdio.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <limits.h>
# include <termios.h>

# define READ 0
# define WRITE 1

# define ERROR -1
# define SUCCESS 1

# define SEPAR 1
# define REDIR_I 2
# define REDIR_O 3
# define REDIR_APPEND 4
# define HEREDOC 5
# define PIPE_TYPE 6
# define DFL 7

# define TRUE	(1)
# define FALSE	(0)
# define IN 	(0)
# define OUT	(1)
# define WORD	(1)
# define REDIR	(2)
# define PIPE	(3)

typedef struct s_var
{
	char	***environ;
	int		exit_code;
}	t_var;

extern t_var	g_var;

typedef struct s_export
{
	char			*key;
	char			*value;
	struct s_export	*next;
}	t_export;

typedef struct s_stat
{
	pid_t				pid;
	int					stat;
}	t_stat;

typedef struct s_redir
{
	int		type;
	char	*file_name;
}	t_redir;

typedef struct s_info
{
	int				id;
	int				pipe;
	int				path;
	t_redir			redir[2];
	int				fds[2][2];
	char			*cmd;
	char			**av;
	int				ac;
	t_stat			stat;
	struct s_info	*next;
	struct s_info	*prev;
}	t_info;

// signals
void		init_signal_handler(void);
void		init_child_signal_handler(void);
void		init_heredoc_signal_handler(void);
void		sig_handle_proc(int sig);
void		sig_handle_sigint(int sig);

// parser
void		change_quote_flag(char c, char *flag);
int			check_quote_pairs(char *input);
int			check_input(char *input);
char		**ft_split_info(char *str);
char		**parse_cmds(char **commands);
void		set_path_flag(t_info *cmd);
int			check_redir(t_info *curr, char **commands, int *i);
void		init_info_list(char **commands, t_info	*cur, int i, int i_argv);
void		make_file(char *filename);
void		free_double_array(char **ptr);
int			parser(char **input, t_info **head);
void		ft_strjoin_char(char **dst, char ch);

// expander
int			expand_env(char **temp, char *command, int start);
void		expand_home(char **temp, char *key, int *i);

// info lst_utils
t_info		*create_info_node(t_info *prev, int i);
void		delete_info_list(t_info **cmd);
void		malloc_info_list(char **commands, t_info **head);

// builtin
int			builtin_echo(t_info *cur_info);
int			builtin_cd(t_info *cur_info);
int			builtin_env(t_info *cur_info);
int			builtin_exit(t_info *cur_info);
int			builtin_pwd(t_info *cur_info);
int			builtin_unset(t_info *cur_info, t_export **export_env, \
size_t av_idx, size_t key_len);
int			builtin_export(t_info *cur_info, t_export **export_env);
int			is_builtin(t_info *cur_info);
int			last_info_code(t_info *info);

//errors
void		malloc_error(void);
int			invalid_cmd_error(char *cmd);
int			check_syntax_errors(char **cmd);
int			err_redir_in(t_info *cur_info);
int			err_here_doc(t_info *cur_info);
int			err_redir_out(t_info *cur_info);


// inits
void		shlvl_oldpwd(void);
void		init_environ(void);

// exec
int			extra_len(char *str);
int			set_redir(t_info *cur_info);
void		err_exit(char *cmd);
char		*parsing_cmd(char *cmd);
void		exec_cmd(t_info *cur_info);
void		ft_close(int fd);
void		ft_dup2(int fd1, int fd2);
void		ft_pipe(int fds[2]);
void		execute_middle_cmd(t_info *cur_info);
void		execute_last_cmd(t_info *cur_info);
void		parsing_line(char *line);
int			obs_strlen(char *str, char lmt);
t_export	split_key_value(char *line);
int			builtin_pwd(t_info *cur_info);
int			builtin_export(t_info *cur_info, t_export **export_env);
int			builtin_check(t_info *cur_info);

#endif
