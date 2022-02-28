#include "shell.h"

int main() 
{
	char **argv;
    char command[STRMAX];
	char current_directory[STRMAX];
	int argc;

    argv = (char**)malloc(STRLEN*sizeof(char*));

	for(int i=0; i<STRLEN; i++)
		argv[i] = (char*)malloc(STRLEN*sizeof(char));

	set_root_directory_and_user();

	while(true) 
   {
        get_command(current_directory, user, command);
        argc = parse_string(argv, command);

        if(exist_pipe(argv, argc))
			exec_pipe_command(argv, argc);
        else if(argc > 0)
            exec_simple_command(argv, argc);
	}
    
    return(0);
}
