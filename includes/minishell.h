/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:40:52 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/25 16:36:20 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define PROMPT "\033[1;32m>minishell$\033[0m "

#include <readline/history.h>  //add_history
#include <readline/readline.h> //readline
#include <signal.h>            //signal
#include <stdio.h>             //printf
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h> 
#define MAX_ARGS 100
#define TRUE 1
#define  FALSE 0

typedef enum e_errcode
{
    WORD,
    CMD,
    SUBCMD,
    PIPE,
    REDIR_I,
    REDIR_O,
    EXPAND,
    BUILT_IN,
    NULL_TYPE
} t_type;

typedef struct s_token
{
    int id;
    int exit_status;
    char *cmd;    // "ls"
    char *args;   // "-la"
    t_type type;  // CMD or FILE or EXPAND
    t_type delim; // PIPE or REDIR_I/O
    struct s_token *next;
    struct s_token *prev;
} t_token;

/*not finish*/

typedef struct s_data
{
    char *input;     // read the line
    char **env;      //save the env
    t_token *tokens; //token list
    int env_len;     //env len

} t_data;

void read_input(t_data **data);
void parser(t_data **data);
void lexer(t_data **data);




/* FUNCTIONS */
void expand_token(t_token *token, char **env);
char *expand_cmd(char *cmd, char **env);
int check_expand_args(char *args);
int is_valid_variable_char(char c);
void execute(t_token *token, char **env, int is_pipe, int is_redir);
void parse_args(char *input, int *index, t_token *tokens);
void detect_delimiter(char *input, int *index, t_token *new_token);
void parse_command(char *input, int *index, t_token *tokens);
int is_delimiter(char c);
int is_whitespace(char c);
void read_input(t_data **data);


/*checker*/
void check_tokens_lst(t_token *tokens);

#endif // MINISHELL_H