/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:40:52 by kmoraga           #+#    #+#             */
/*   Updated: 2024/04/05 17:37:42 by codespace        ###   ########.fr       */
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
#include <unistd.h>

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
    t_token **tokens; //token list
    int token_num;
    //t_tree *node;    //tree
    int env_len;     //env len

} t_data;

// main.c
int main(int ac, char **av, char **env);
void read_input(t_data **data);
t_data *init_data(char **envp);

// tokenizer.c
void    tokenizer(t_data **data);
void    create_tokens(char *input, t_token **tokens, t_data **data);
void    skip_whitespace(int *i, char *input);

// check_special.c
void    check_special(int *i, char *input, t_token **tokens, t_data **data);
void    add_delim(int *i, char *input,t_token **tokens);
int     check_whitespaces(char *input, int *i);

// get_cmd.c
void    get_cmd(int *i, char *input, t_token **tokens); //add t_data **data noch!
void    check_quote(char c, int *column, int *j);
int     delim_space(char c);
int     text_in_quotes(int column, int i, int *j, char *input);
int     input_cmd(char *input, int *i, int j, t_token **tokens);

// get_args.c
void    get_args(int *i, char *input, t_token **tokens, t_data **data);
void    get_args_num(char *input, int *i, int total_arg_len, t_token **tokens);
int     malloc_args(char *input, int *i, t_token **tokens);
int     get_arg_len(char *input, int *i);
void    input_arg(char *input, int *i, int len, t_token **tokens, int arg);
void    create_empty_args(t_token **tokens);

// parser.c
void    parser(t_data **data);
int     check_empty_cmd(t_token **move);
int     check_expand(t_token **move);
int     check_fd(t_token **move);
int     check_file(t_token **move);

//print.c
void    print(t_data **data);

#endif // MINISHELL_H