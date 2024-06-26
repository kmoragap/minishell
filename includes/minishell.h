/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/01 15:43:08 by creuther          #+#    #+#             */
/*   Updated: 2024/05/29 22:54:16 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define PROMPT "\033[1;32m>minishell$\033[0m "

# define BUFFER_SIZE 1000
# define ACTIVE 1
# define IGNORE 2
# define DEFAULT 3
# define HEREDOC 4

# include "../srcs/utils/get_next_line/get_next_line.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

extern int			g_sigint;

typedef enum e_builtin
{
	ECHO,
	CD,
	PWD,
	EXPORT,
	UNSET,
	ENV,
	EXIT
}					t_builtin;

typedef enum e_type
{
	NOTHING,
	CMD,
	FLE,
	FD,
	EXPAND,
	PIPE,
	REDIR_I,
	REDIR_O,
	REDIR_A,
	REDIR_H
}					t_type;

typedef enum e_error
{
	ER_NO,
	ER_SHUTDOWN,
	ER_MALLOC,
	ER_INPUT
}					t_error;

typedef enum e_free
{
	NO_FREE,
	F_INPUT,
	F_EMPTOK,
	F_TOKCMD,
	F_TOKS,
	F_ENV,
	F_PIPES,
	NO_FREE_PIDS,
	F_PIDS,
	F_EXITSTATE
}					t_free;

typedef struct s_token
{
	int				id;
	char			*cmd;
	char			**args;
	int				args_num;
	int				exit_status;
	int				quotes;
	char			*path;
	t_type			type;
	t_type			delim;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_child
{
	int				cnt_childn;
	pid_t			*pids;
	int				exit_state;
	int				**pipes;
}					t_child;

typedef struct s_data
{
	char			*input;
	char			**env;
	int				env_len;
	t_error			err_code;
	t_free			free_code;
	int				exit_code;
	t_token			*tokens;
	t_child			*childn;
	int				token_num;
}					t_data;

// main.c
int					main(int ac, char **av, char **env);
void				read_input(t_data **data);
t_data				*init_data(char **envp);

// tokenizer.c
t_token				*tokenizer(t_data *data);
void				create_tokens(char *input, t_token **tokens, t_data *data);
t_token				**next_token(t_token **tokens, t_data *data);
void				skip_whitespace(int *i, char *input);

// check_input.c
int					check_input(t_data *data);
int					check_pipe(char *input);
int					check_quotes(char *input);
int					check_andslash(char *input);

// check_special.c
void				space_special(int *i, char *input, t_token **token,
						t_data *data);
void				check_special(int *i, char *input, t_token **tokens,
						t_data *data);
void				add_delim(int *i, char *input, t_token **tokens);
int					check_whitespaces(t_data *data, char *input, int *i);

// get_cmd.c
void				get_cmd(int *i, char *input, t_token **tokens,
						t_data *data);
void				check_quote(char c, int *column, int *j);
int					delim_space(char c);
int					text_in_quotes_cmd(int quote, int i, int *j, char *input);
int					text_in_quotes(int column, int i, int *j, char *input);
int					input_cmd(char *input, int *i, int j, t_token **tokens);

// get_args.c
void				get_args(int *i, char *input, t_token **tokens,
						t_data *data);
int					get_total_arg_len(char *input, int i);
void				get_args_num(char *input, int *i, int total_arg_len,
						t_token **tokens);
void				arg_num_loop(char *input, int *j);
int					malloc_args(char *input, int *i, t_token **tokens);
int					get_arg_len(char *input, int *i);
void				input_arg(char *input, int *i, t_token **tokens, int arg);
void				create_empty_args(t_token **tokens, t_data *data);

// parser.c
t_data				*parser(t_data *data);
int					check_expand(t_data *data);
int					check_empty_cmd(t_token *move, t_data *data);
int					check_fd(t_token *move);
int					check_file(t_token *move);

// expander.c
char				*resolve_token_value(char *token, char **env);
char				*expand_work(char *arg, char **env, int status);
int					find_end(char *arg, int i, char quote);
char				*expander_fun(char *arg, char **env, int status);
char				*handle_no_quotes(char *arg, char **env, int status);
void				handle_dollar_question(char **result, int *end, int status);
char				*handle_double_quotes(char *arg, char **env, int status);
char				*expand_variable(char *var, char **env);
char				valid_delim_expand(char c);
void				expand_cmd(t_token *token, char **env, int status);
void				expand_args(t_token *token, char **env, int status);
char				*expand_token(char *token, char **env);
char				*get_fragment(char *arg, int *i);
char				*expand_and_join(char **fragments, int frag_count,
						char **env, int status);
char				*extract_variable(char *arg, int *i);
char				*extract_regular(char *arg, int *i);
char				*extract_quoted(char *arg, int *i, char quote);

// expander_utils.c
void				remove_quotes_from_args(t_data *data);
int					check_expand_var(char *var);
int					is_valid_variable_char(char c);
int					check_expand_args(char **args);

// builtins_utils.c
int					check_builtins(char *cmd);
void				execute_builtin(t_data *data);
char				*ft_strtok(char *str, const char *delim);

// export.c
void				execute_export_builtin(t_data *data);
int					do_export_loop(t_data *data, char *var, int i);
void				sort_env_case(t_data *data);
int					write_error(char *str1, char *str2, char *str3,
						int exit_code);
void				create_env_var(t_data *data, int arg_num, char *arg);
void				write_env(char *str);
char				**cpy_envi(char **env_cpy);
int					replace_var_env(t_data *data, char *arg);
int					free_ar(char *ar);
void				free_two(char *var, char *ar);
void				sort_env_case2(t_data *data, char **env_cpy, int i);

// env
void				put_env(t_data *data);

// pwd
void				get_pwd(t_data *data);

// exit
void				ft_exit(t_data *data);
int					exit_many_args(t_data *data, int exit_status);
void				ft_exit_255(t_data *data, char *args);
void				free_exit(t_data *data, int exit_status);
void				end_child(t_data *data);

// cd.c
void				execute_cd(t_data *data, char *path, char *old_pwd);
int					check_arg_num(t_data *data);
char				*get_env(t_data *data, char *path);
void				ft_cd(t_data *data);
void				update_env_vars(t_data *data, char *old_pwd, char *new_pwd);

// unset
void				ft_unset(t_data *data);
void				unset_env(t_data *data, int arg_num, char *for_pwd);
void				unset_env2(t_data *data, char *arg, char **env, int i);

// echo.c
void				ft_echo(t_data *data);
void				check_next_token(t_token *curr_token, int *newline);

// execution
// execution.c
t_data				*execute_token(t_data *data);

// piping.c
t_data				*piping(t_data *data);
int					count_pipes(t_data *data);
int					malloc_fds(t_data *data);
int					fill_fds(t_data *data);

// dup_pipes.c
void				dup_pipes(t_data *data, int child_id);
void				single_redir(t_data *data);
int					redir_in(t_data *data);
int					redir_out(t_data *data);
void				check_redir_out_last(t_data *data);
void				check_redir_in_first(t_data *data);
void				check_redir_in(t_data *data, int child_id);
void				check_redir_out(t_data *data, int child_id);

// close_pipes.c
void				close_pipes(t_data *data, int child_id);
void				free_pipes(int **pipes, t_data *data);

// children.c
t_data				*create_children(t_data *data);
void				child_creation(t_data *data);
void				child_routine(t_data *data, int child_id);
void				get_token(t_data *data, int child_id);
void				error_in_child(t_data *data, int exit_code, char *cmd,
						char *error_message);
void				ex_error_in_child(t_data *data, int exit_code,
						char *error_message);

// check_cmd_path.c
void				check_cmd_path(t_data *data);
t_data				*remove_quotes(char *cmd, t_data *data);
char				*remove_quotes_args(char *arg);
void				loop_quotes(char *cmd, char **new, int *i, int *check);
int					check_relative(char *cmd);
int					find_path(t_data *data);
char				*path_from_env(char **env);
void				check_absolute_path(t_data *data);

// join_cmd_arg.c
char				**join_cmd_arg(t_data *data);
int					size_of_args(t_data *data);
char				*get_cmd_for_args(t_data *data);
char				**cpy_token_args(t_data *data, char **args, int *args_cntr);
char				**cpy_next_token_args(t_data *data, char **args,
						int *args_cntr);

// parent_wait.c
void				parent_wait(t_data *data);

// shlvl.c
void				shlvl(t_data *data);

// utils
int					f_len(int n);
int					ft_strnum(const char *str);
int					is_valid_number(char *str);
int					ft_atoi(char *str);
char				*ft_strncpy(char *dest, const char *src, size_t n);
char				*ft_strcat(char *dest, const char *src);
int					is_valid_expand_var(char *str, int c);
char				*ft_strchr_before_c(const char *s, int c);
char				*ft_strchr_after_c(const char *s, int c);
int					ft_strchr(const char *str, int c);
char				*ft_itoa(int n);
int					ft_isascii(int c);
int					ft_isdigit(int c);
int					ft_isalpha(int c);
int					ft_isalnum(int c);
int					ft_strcmp(char *s1, char *s2);
char				*ft_strdup(char *src);
char				*ft_strcpy(char *src, char *dest);
int					ft_strlen(const char *str);
void				*ft_calloc_norm(size_t n, size_t size);
void				ft_bzero(void *str, size_t n);
int					ft_calloc(t_data *data, t_free code, void **arr,
						size_t size);
t_token				*move_to_first_token(t_token *token);
char				*ft_strrchr(const char *str, int c);
char				*ft_strjoin(char *s1, char *s2);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
char				**ft_split(char const *s, char c);
char				*ft_strnjoin(char *s1, char *s2, int len2);
char				*ft_strndup(char *src, int len);
char				*ft_strtrim(char const *s1, char const *set);
int					ft_strncmp(const char *s1, const char *s2, size_t n);

// error.c
void				input_error(t_data *data, t_free code, int exit_code,
						char *txt);
void				malloc_error(t_data *data, t_free code);

// free.c
void				free_all_child(t_data *data);
void				free_all(t_data *data);
void				free_toks(t_data *data);
void				free_env(t_data *data);
void				free_args(char **args, int *cnt);
void				reinit_data(t_data *data);
void				free_args2(char **args, int *cnt, int i);

// signals.c
void				handle_sigquit(int sig);
void				init_signals(int sig);
void				handle_eof(t_data *data);
void				handle_sigint_heredoc(int sig);

// heredoc.c
t_data				*heredoc(t_data *data);
void				read_in_here(t_token *token, char **env, int fd,
						int status);
void				handle_heredoc(t_token *token, char **env, int status);
int					has_quotes(char *cmd);

#endif // MINISHELL_H