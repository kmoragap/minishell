/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:40:52 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/23 09:15:06 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#define PROMPT "\033[1;32m>minishell$\033[0m "

#include <readline/history.h>  //add_history
#include <readline/readline.h> //readline
#include <signal.h>            //signal
#include <stdio.h>             //printf
#include <stdlib.h>
#include <string.h>

typedef enum e_type
{
    CMD,
    FILE,
    EXPAND,
    PIPE,
    REDIR_I, // < (redirect input)
    REDIR_O, // > (redirect output)
    REDIR_A, // >> (append)
    REDIR_H // << (here-document)
} t_type;

typedef struct s_token
{
    int id;
    char *cmd; // "ls"
    char **args; // -la
    int args_num;
    t_type type; // CMD or FILE or EXPAND
    t_type delim; // PIPE or REDIR_I/O/A/H
    struct s_token *next; 
    struct s_token *prev;
} t_token;

typedef struct s_data
{
    char *input;     // read the line
    char **env;      //save the env
    t_token *tokens; //token list
    t_tree *node;    //tree
    int env_len;     //env len

} t_data;

void read_input(t_data **data);
void lexer(t_data **data);

//tokenizer.c
void    tokenizer(t_data *data);
void    create_tokens(char *input, t_token *tokens, t_data **data);
void    skip_whitespace(int *i, char *input);

// check_special.c
void    check_special(int *i, char *input, t_token *tokens, t_data **data);
void    add_delim(int *i, char *input,t_token **tokens);
int     check_whitespaces(char *input, int *i);

// get_cmd.c
void    get_cmd(int *i, char *input, t_token *tokens, t_data **data);
void    check_quote(char c, int *column, int *j);
int    delim_space(char c);
void    text_in_quotes(int column, int i, int *j, char *input);
void    input_cmd(char *input, int *i, int j, t_token *tokens);

// get_args.c
void    get_args(int *i, char *input, t_token *tokens, t_data **data);
void    get_args_num(char *input, int *i, t_token *tokens, int total_arg_len);
int     malloc_args(char *input, int *i, t_token *tokens, int total_arg_len);
int     get_arg_len(char *input, int *i);
void    input_arg(char *input, int *i, int len, char **arg);

//void parse_input(t_data **data);



/* FUNCTIONS */
void add_right(t_tree *parent, t_tree *child);
void add_left(t_tree *parent, t_tree *child);
t_tree *new_node(char *content, t_type type);
void print_dot_node(FILE *file, t_tree *node, int *node_counter);
void print_dot(t_tree *root);

/*checker*/
void check_tokens_lst(t_token *tokens);

#endif // MINISHELL_H