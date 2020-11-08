# projetopa


After a command is entered, the following things are done:

-Command is entered and if length is non-null, keep it in history.
-Parsing : Parsing is the breaking up of commands into individual words and strings
-Checking for special characters like pipes, etc is done
-Checking if built-in commands are asked for.
-If pipes are present, handling pipes.
-Executing system commands and libraries by forking a child and calling execvp.
-Printing current directory name and asking for next input.