# minishell

making progress ✨
minishell

# TO-DO

- [] Implement own versions of some utils functions, like , strdup, etc.
- [] Improve the split function...
- [] Improve the linked list implementation

# Reminder
- change the token->exit_status in expand func to token->prev->exit_status. To avoid a seg fault with the previous token, i decide to put the exit_status for the current token
- verificar single quotes

# Flags to check
valgrind --leak-check=full --track-fds=all --trace-children=yes ./minishell

1. pipe (redirections!)
# Executor
2. fork all children
3. in child: give it the specific cmd & overall data
4. check if builtin or not
5. if builtin: execute builtin and exit child
5. if not builtin: get the absolute path of the command (e.g. "/bin/ls") with access --> return error here if path is wrong or doesn't exist
- check if its an absolute or relative path ("/")
- if absolute: check if valid mit access()
- if relative: joine  "/" mit "cmd" und lasse durch whileloop gehen in der jeweils mit jedem PATH-Teil (splitte davor nach ":") joine und checke mit access ob der path valid ist jeweils (if valid -> break out of loop) & return den path
- if valid path: execve mit path, 2dimensional array with {1. cmd} {2. arg} {3. arg2} {...} 
5. parent: waitpid (in order of creation of children)

path = "/bin/ls"
args = "ls" "-l" "NULL"



--> right now the filename after redirection is seen as a command and being tried to be executed --> should be skipped!