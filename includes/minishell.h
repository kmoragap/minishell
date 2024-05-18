/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/05/18 14:03:29 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef MINISHELL_H
#define MINISHELL_H

#define PROMPT "\033[1;32m>minishell$\033[0m "

#include <readline/history.h>  //add_history
#include <readline/readline.h> //readline
#include <signal.h>            //signal
#include <stdio.h>             //printf
#include <sys/types.h>         //fork
#include <sys/wait.h>           //waitpid
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

typedef enum e_builtin
{
    ECHO,
    CD,
    PWD,
    EXPORT,
    UNSET,
    ENV,
    EXIT
} t_builtin;

typedef enum e_type
{
    NOTHING,
    CMD,
    FLE,
    FD,
    EXPAND,
    PIPE,
    REDIR_I, // < (redirect input)
    REDIR_O, // > (redirect output)
    REDIR_A, // >> (append)
    REDIR_H  // << (here-document)
} t_type;

typedef enum e_error
{
    ER_NO,
    ER_SHUTDOWN,
    ER_MALLOC,
    ER_INPUT,
}   t_error;

typedef enum e_free
{
    NO_FREE,
    NO_FREE_PIDS,
    F_INPUT,
    F_ENV,
    F_EMPTOK,
    F_TOKCMD,
    F_TOKS, 
    F_PIPES,
    F_PIDS, 
    F_EXITSTATE,
}   t_free;

typedef struct s_token
{
    int id;
    char *cmd;   // "ls"
    char **args; // -la
    int args_num;
    int exit_status;
    char    *path;
    t_type type;  // CMD or FILE or EXPAND
    t_type delim; // PIPE or REDIR_I/O/A/H
    struct s_token *next; 
    struct s_token *prev;
} t_token;

typedef struct s_child
{
    int cnt_childn;
    pid_t *pids;
    int exit_state;
    int **pipes;
}               t_child;

typedef struct s_data
{
    char *input;        // read the line
    char **env;         // save the env
    int env_len;        // env len
    t_error err_code;   // error code 
    t_free  free_code;  // code which says how much we got to free
    int     exit_code;
    t_token *tokens;    // token list
    t_child *childn;
    int token_num;      // number of tokens
    //t_tree *node;     // tree
} t_data;

// main.c
int main(int ac, char **av, char **env);
void read_input(t_data **data);
t_data *init_data(char **envp);

// tokenizer.c
t_token  *tokenizer(t_data *data);
void    create_tokens(char *input, t_token **tokens, t_data *data);
t_token **next_token(t_token **tokens, t_data *data);
void    skip_whitespace(int *i, char *input);

// check_special.c
void    check_special(int *i, char *input, t_token **tokens, t_data *data);
void    add_delim(int *i, char *input,t_token **tokens);
int     check_whitespaces(char *input, int *i);

// get_cmd.c
void get_cmd(int *i, char *input, t_token **tokens, t_data *data);
void check_quote(char c, int *column, int *j);
int delim_space(char c);
int text_in_quotes(int column, int i, int *j, char *input);
int input_cmd(char *input, int *i, int j, t_token **tokens);

// get_args.c
void    get_args(int *i, char *input, t_token **tokens, t_data *data);
int     get_total_arg_len(char *input, int i);
void    get_args_num(char *input, int *i, int total_arg_len, t_token **tokens);
int     malloc_args(char *input, int *i, t_token **tokens);
int     get_arg_len(char *input, int *i);
void    input_arg(char *input, int *i, int len, t_token **tokens, int arg);
void    create_empty_args(t_token **tokens, t_data *data);

// parser.c
t_data  *parser(t_data *data);
int check_expand(t_data *data);
int     check_empty_cmd(t_token *move, t_data *data);
int     check_fd(t_token *move);
int     check_file(t_token *move);

// print.c
t_data  *print(t_data *data);

// expander.c
void expand_cmd(t_token *token, char **env, int status);
void expand_args(t_token *token, char **env, int status);
char *expand_token(char *token, char **env, int exit_status);

// expander_utils.c
char *remove_outer_parenthesis(char *arg);
char *remove_outer_quotes(char *arg);
char *check_special_expand(char *special, int exit_status);
int check_expand_var(char *var);
int is_valid_variable_char(char c);
int check_expand_args(char **args);

// builtins_utils.c
int check_builtins(char *cmd);
void execute_builtin(t_data *data);
char *ft_strtok(char *str, const char *delim);


// export.c 
void execute_export_builtin(t_data *data);
int replace_var_env(t_data *data, char *arg);

//env
void put_env(t_data *data);

//pwd
void get_pwd(void);

//exit
void ft_exit(t_data *data);

// cd.c
void execute_cd(t_data *data, char *path, char *old_pwd);
void ft_cd(t_data *data);
void update_env_vars(t_data *data, char *old_pwd, char *new_pwd);

//unset
void ft_unset(t_data *data);
void unset_env(t_data *data, int arg_num);

// echo.c
void ft_echo(t_data *data);

//execution
//execution.c
t_data  *execute_token(t_data *data);

//piping.c
t_data  *piping(t_data *data);
int     count_pipes(t_data *data);
int     malloc_fds(t_data *data);

//dup_pipes.c
void    dup_pipes(t_data *data, int child_id);
void    single_redir(t_data *data);
void    check_redir_out_last(t_data *data);
void    check_redir_in_first(t_data *data);
int     check_redir_in(t_data *data, int child_id);
int     check_redir_out(t_data *data, int child_id);

//close_pipes.c
void    close_pipes(t_data *data);
void    dup_pipes(t_data *data, int child_id);

//children.c
t_data  *create_children(t_data *data);
void    child_routine(t_data *data, int child_id);
void    get_token(t_data *data, int child_id);
void    error_in_child(t_data *data, int exit_code, char *cmd, char *error_message);

//check_cmd_path.c
void     check_cmd_path(t_data *data);
t_data    *remove_quotes(char *cmd, t_data *data);
void    loop_quotes(char *cmd, char **new, int *i, int *check);
int     check_relative(char *cmd);
int     find_path(t_data *data);
char    *path_from_env(char **env);
void     check_absolute_path(t_data *data);

//join_cmd_arg.c
char    **join_cmd_arg(t_data *data);
int     size_of_args(t_data *data);
char    *get_cmd_for_args(t_data *data);
char    **cpy_token_args(t_data *data, char **args, int *args_cntr);
char    **cpy_next_token_args(t_data *data, char **args, int *args_cntr);

//parent_wait.c
void    parent_wait(t_data *data);

// shlvl.c
void shlvl(t_data *data);

// utils
int ft_strnum(const char *str);
int is_valid_number(char *str);
int	ft_atoi(char *str);
char	*ft_strncpy(char *dest, const char *src, size_t n);
char *ft_strcat(char *dest, const char *src);
int is_valid_expand_var(char *str, int c);
char	*ft_strchr_before_c(const char *s, int c);
char	*ft_strchr_after_c(const char *s, int c);
int	ft_strchr(const char *str, int c);
char	*ft_itoa(int n);
int	ft_isascii(int c);
int	ft_isdigit(int c);
int	ft_isalpha(int c);
int	ft_isalnum(int c);
int ft_strcmp(char *s1, char *s2);
char	*ft_strdup(char *src);
char	*ft_strcpy(char *src, char *dest);
int	ft_strlen(const char *str);
void	*ft_calloc_norm(size_t n, size_t size);
void	ft_bzero(void *str, size_t n);
int		ft_calloc(t_data *data, t_free code, void **arr, size_t size);
t_token	*move_to_first_token(t_token *token);
char	*ft_strrchr(const char *str, int c);
char	*ft_strjoin(char *s1, char *s2);
void	*ft_memcpy(void *dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
char	**ft_split(char const *s, char c);
char	*ft_strnjoin(char *s1, char *s2, int len2);
char	*ft_strndup(char *src, int len);

// error.c
void    input_error(t_data *data, t_free code, int exit_code, char *txt);
void    malloc_error(t_data *data, t_free code);

// free.c
void    free_all(t_data *data);
void    free_toks(t_data *data);
void    free_env(t_data *data);
void    free_pipes(int **pipes, t_data *data);
void    free_args(char **args, int *cnt);
void    reinit_data(t_data *data);

// signals.c
void init_signals(void);
void handle_eof(t_data *data);


#endif // MINISHELL_H