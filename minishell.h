/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/22 12:40:52 by kmoraga           #+#    #+#             */
/*   Updated: 2024/02/22 14:29:12 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H


# define PROMPT "\033[1;32m>minishell$\033[0m "


# include <readline/history.h>  //add_history
# include <readline/readline.h> //readline
# include <signal.h>            //signal
# include <stdio.h>             //printf
# include <stdlib.h>
# include <string.h>

typedef enum e_token
{
    CMD,
    PIPE,
    REDIR
} t_token; 

typedef struct s_cmd
{
    char *content;
    t_token type;
    struct s_cmd *next;
} t_cmd;

typedef struct s_data
{
    char *input; // read the line
    char **env; //save the env
    t_cmd *cmd; // cmd content
    int env_len; //env len
    
    
} t_data;

void read_input(t_data **data);
void parse_input(t_data **data);


#endif // MINISHELL_H