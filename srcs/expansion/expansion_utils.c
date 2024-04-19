/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kmoraga <kmoraga@student.42vienna.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 16:34:33 by kmoraga           #+#    #+#             */
/*   Updated: 2024/04/18 18:31:06 by kmoraga          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int check_expand_var(char *var)
{
    if (var[0] == '$' && (is_valid_variable_char(var[1])))
        return (1);
    else if (var[0] == 34 && var[1] == '$' && is_valid_variable_char(var[2]))
        return (1);
    return (0);
}

int is_valid_variable_char(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
           (c >= '0' && c <= '9') || c == '_';
}

int check_expand_args(char **args)
{
    int i; 
    int j;
    int k;
    
    i = 0;
    while (args[i] != NULL) {
        j = 0;
        while (args[i][j] != '\0') {
            if (args[i][j] == '$' && args[i][j + 1] != '\0' && args[i][j + 1] != ' ') {
                k = j + 1;
                while (is_valid_variable_char(args[i][k])) {
                    k++;
                }
                if (k > j + 1) {
                    return 1;
                }
            }
            j++;
        }
        i++;
    }
    return 0;
}



/*funcion que toma la variable
    //TAMBIÉN REVISAR QUE ENTRE $ Y () HAY ALGO  //
    verifica si
        empieza con "
        itera sobre ella si es asi
            luego verifica si es $
                si es asi:
                    verificar si es ascii lo siguiente
                    va al sig y busca (
                        luego busca el final del )
                    
                    
*/