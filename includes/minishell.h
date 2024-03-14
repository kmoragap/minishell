/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:40:52 by kmoraga           #+#    #+#             */
/*   Updated: 2024/02/28 22:31:24 by kmoraga          ###   ########.fr       */
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
    WORD,
    CMD,
    SUBCMD,
    PIPE,
    REDIR_I,
    REDIR_O,
    EXPAND
} t_type;

typedef struct s_token
{
    int id;
    char *cmd; // "ls"
    char **args; // -la
    t_type type; // CMD or FILE or EXPAND or REDIR_I/O
    t_type delim; // PIPE or REDIR_I/O
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

//tokenizer
void tokenizer(t_data *data);
void parse_input(t_data **data);

/* FUNCTIONS */
void add_right(t_tree *parent, t_tree *child);
void add_left(t_tree *parent, t_tree *child);
t_tree *new_node(char *content, t_type type);
void print_dot_node(FILE *file, t_tree *node, int *node_counter);
void print_dot(t_tree *root);

/*checker*/
void check_tokens_lst(t_token *tokens);

#endif // MINISHELL_H