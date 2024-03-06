/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_tokens_lst.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 22:19:53 by kmoraga           #+#    #+#             */
/*   Updated: 2024/03/06 09:48:35 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



// Function to check the token list
void check_tokens_lst(t_token *tokens) {
    printf("Token list:\n");
    t_token *current = tokens;
    while (current != NULL) {
        printf("cmd: %s\n", current->cmd);
        printf("args: %s\n", current->args);
        printf("id: %d\n", current->id);
        printf("type: %d\n", current->type);
        printf("delim: %d\n", current->delim);
        if (current->next != NULL) {
            printf("next: %s\n", current->next->cmd);
        } else {
            printf("next: NULL\n");
        }
        if (current->prev != NULL) {
            printf("prev: %s\n", current->prev->cmd);
        } else {
            printf("prev: NULL\n");
        }
        current = current->next;
    }
}