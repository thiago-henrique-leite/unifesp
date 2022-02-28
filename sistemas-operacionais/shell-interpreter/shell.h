/****************************************************
  *                  Bibliotecas                    *
  ***************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

#define STRLEN 1024
#define STRMAX 255

/****************************************************
  *                    Funções                      *
  ***************************************************/

int   get_command(char current_directory[], char user[], char command[]);
int   parse_string(char** argv, char command[]);
bool  exist_pipe(char** argv, int argc);
bool  special_command(char* command, char* directory);
bool  contain_operator(char** argv, int argc, char op[]);
void  separate_command(char** argv, int argc, char** cmd1, char** cmd2, int* argc1, int* argc2, char op[]);
bool  verify_semicolon(char** argv, int argc);
bool  verify_conditionals_command(char** argv, int argc);
int   background(char** argv, int argc);
int   exec_simple_command(char** argv, int argc);
void  set_root_directory_and_user();
void  set_current_directory(char curr_directory[], char root_directory[]);
int   exec_pipe_command(char** argv, int argc);

char root_directory[STRMAX] = "/home/";
char user[STRMAX];

int get_command(char current_directory[], char user[], char command[]) 
{
    char charac;
    int i=0;
        
    // Limpa o buffer
    memset(command,0,strlen(command)); 
    memset(current_directory,0,strlen(current_directory));  
    
    set_current_directory(current_directory, root_directory);   
    printf("\033[1;32m%s:\033[1;34m%s\033[0;37m$ ", user, current_directory);
        
    while(true)
    {
        charac = getchar();

        if(charac == '\n')
            break;
        else
            command[i] = charac;
        i++;   
    }

    command[i] = '\0';
    return 1;
}

int parse_string(char** argv, char command[]) 
{
    char *str;  
    int index=0, argc=0;

    argc = 0;	  

    str = strtok(command," ");

    if(str==NULL)
    {
        if(command[0] != '\0')
        {
            argv[index] = command;
            argc++;
        }
    }
    else 
    {
        argv[index] = str;  

        while(str != NULL)
        {
            argc++;
            index++;
            str = strtok(NULL," ");
            argv[index] = str;
        }
    }

    return argc;
}

bool exist_pipe(char** argv, int argc) 
{
    int i=0;

	while(argv[i] != NULL) {
		if(strcmp(argv[i], "|") == 0)
			return true;
		i++;
	}

	return false;
}

bool special_command(char* command, char* directory) 
{
	if(strcmp(command, "cd") == 0) 
	{
        char dir[STRMAX], target[STRMAX], curr[STRMAX];
        int i, j;

        getcwd(curr, sizeof(curr));

        if(directory == (char*) NULL)
        {
            strcat(dir, root_directory);
        }    
        else if(directory[0] == '~') 
        {
            int index = strlen(root_directory);

            strcat(dir, root_directory);
            dir[index] = '/';
            index++;
            
            for(i=2, j=0; directory[i] != (char) NULL; i++, j++)
                target[j] = directory[i];

            target[j] = '\0';

            strcat(dir, target);

            chdir(dir);
        }
        else 
        {
            strcat(dir, directory);
        }

        char new_directory[STRMAX];

        chdir(dir);
        getcwd(new_directory, sizeof(new_directory));

		return true;
	} 
    else if(strcmp(command, "exit") == 0)
    {
        exit(0);
    }

	return false;
}

bool contain_operator(char** argv, int argc, char op[]) 
{
    char str[STRMAX];

    for(int i=0; i<argc; i++) 
    {
        if(argv[i][0] != '\'' && argv[i][0] != '\"') 
        {
            strcpy(str, argv[i]);
            if(strpbrk(str, op) != NULL)
                return true;
        }
    }

    return false;
}

void separate_command(char** argv, int argc, char** cmd1, char** cmd2, int* argc1, int* argc2, char op[])
{
    int found=0, ind1=0, ind2=0;
    bool next;
    char str[STRMAX];

    for(int i=0; i<argc; i++) 
    {
        next = false;

        if(!found && argv[i][0] != '\'' && argv[i][0] != '\"')
        {
            strcpy(str, argv[i]);
            if(strpbrk(str, op) != NULL)
            {
                found = 1;
                next  = true;
            }
        }

        if(next==false) 
        {
            if(!found)
            {
                strcpy(cmd1[ind1], argv[i]);
                ind1++;
            }
            else
            {
                strcpy(cmd2[ind2], argv[i]);
                ind2++;
            }
        }
    }

    cmd1[ind1] = NULL;
    cmd2[ind2] = NULL;

    *argc1 = ind1;
    *argc2 = ind2;
}

bool verify_semicolon(char** argv, int argc) 
{
    char **cmd1 = (char**)malloc(STRLEN*sizeof(char*));
    char **cmd2 = (char**)malloc(STRLEN*sizeof(char*));

    for(int i=0; i<STRLEN; i++)
    {
  	    cmd1[i] = (char*)malloc(STRLEN*sizeof(char));
        cmd2[i] = (char*)malloc(STRLEN*sizeof(char));
    }

    int *argc1 = (int*)malloc(sizeof(sizeof(int)));
    int *argc2 = (int*)malloc(sizeof(sizeof(int)));

    if(contain_operator(argv, argc, ";")) {
        separate_command(argv, argc, cmd1, cmd2, argc1, argc2, ";");
        exec_simple_command(cmd1, *argc1);
        exec_simple_command(cmd2, *argc2);
        return true;
    }

    return false;
}

bool verify_conditionals_command(char** argv, int argc)
{
    char **cmd1 = (char**)malloc(STRLEN*sizeof(char*));
    char **cmd2 = (char**)malloc(STRLEN*sizeof(char*));

    for(int i=0; i<STRLEN; i++)
    {
  	    cmd1[i] = (char*)malloc(STRLEN*sizeof(char));
        cmd2[i] = (char*)malloc(STRLEN*sizeof(char));
    }

    int *argc1 = (int*)malloc(sizeof(sizeof(int)));
    int *argc2 = (int*)malloc(sizeof(sizeof(int)));

    int status;

    pid_t pid;

    if(contain_operator(argv, argc, "||")) 
    {

        separate_command(argv, argc, cmd1, cmd2, argc1, argc2, "||");

        pid = fork();

        if(pid < 0) 
        {
            perror("fork()");
            return -1;
        } 
        else if(pid==0)
        {
            exec_simple_command(cmd1, *argc1);
        }
        else 
        {
            sleep(1);
            waitpid(0, NULL, WNOHANG);
            exec_simple_command(cmd2, *argc2);
        }
            
        sleep(2);

        return true;
    }

    if(contain_operator(argv, argc, "&&")) {

        separate_command(argv, argc, cmd1, cmd2, argc1, argc2, "&&");

        pid = fork();

        if(pid < 0) 
        {
            perror("fork()");
            return -1;
        } 
        else if(pid==0)
        {
            exec_simple_command(cmd1, *argc1);
        }
        else 
        {
            sleep(1);
            if(waitpid(0, NULL, WNOHANG)==0)
                exec_simple_command(cmd2, *argc2);
        }

        sleep(2);
            
        return true;
    }


    return false;
}

int background(char** argv, int argc)
{
    int pid_background;

    if(strcmp(argv[argc-1], "&") == 0)
    {
        pid_t pid;

        int response, dup_resp;
        int status;

        response = open("/tmp/a.txt", O_RDWR, S_IRUSR | S_IWUSR);

        if(response < 0)
            perror("open()");

        dup_resp = dup(fileno(stdout));

        if(dup2(response, fileno(stdout)) < 0) {
            perror("dup2()");
        }

        pid = fork();

        if (pid == 0) // Processo filho
        {
            pid_background = getpid();
            setpgid(0, 0);
            argv[argc-1] = (char*) NULL;
            execvp(argv[0], argv);
            exit(0);
        }
        else 
        {
            //waitpid(pid, &status, 0);
            dup2(dup_resp, fileno(stdout));
            close(dup_resp);
            close(response);
        }

        printf("[%d]\n", pid_background);
        return true;
    } 
    else 
    {
        return false;
    }
}

int exec_simple_command(char** argv, int argc)
{
    if(background(argv, argc)) 
        return 1;
    else if(verify_conditionals_command(argv, argc))
        return 1;
    else if(verify_semicolon(argv, argc))
        return 1;
    else if(special_command(argv[0], argv[1]))
		return 1;
    else 
    {  
        pid_t pid = fork();

        if(pid == 0) 
        {
            if(execvp(argv[0], argv) < 0)
            {
                printf("shell: command not found\n");
                return -1;
            }
        }
        else if(pid > 0)
        {
            waitpid(-1, NULL, 0);
            return 1;
        }
        else 
        {
            perror("fork()");
            return -1;
        }
    }
}

void set_root_directory_and_user()
{
    int i, j;
	char cwd[STRMAX];
	
    getcwd(cwd, sizeof(cwd));

	for(j=0, i=6; cwd[i] != '/'; i++, j++)
		user[j] = cwd[i];

	strcat(root_directory, user);
}

void set_current_directory(char curr_directory[], char root_directory[]) 
{
    char cwd[STRMAX], cwd_origin[STRMAX];

    getcwd(cwd, sizeof(cwd));
    strcpy(cwd_origin, cwd);
    
    int size_diff = strlen(cwd) - strlen(root_directory);
    
    cwd[strlen(cwd) - size_diff] = '\0';

    int i, j, aux=0;

    if(strcmp(cwd, root_directory) == 0) 
    {   
        if(size_diff != 0) {
            strcpy(curr_directory, "~/");
            aux += 2;
        } else {
            strcpy(curr_directory, "~");
            aux += 1;
        }

        for(i=0, j=strlen(root_directory)+1; i<size_diff; i++, j++) 
            curr_directory[i+aux] = cwd_origin[j];
    } 
    else 
    {
        strcat(curr_directory, cwd_origin);
    }
}

int exec_pipe_command(char** argv, int argc) 
{
    char **cmd1 = (char**)malloc(STRLEN*sizeof(char*));
    char **cmd2 = (char**)malloc(STRLEN*sizeof(char*));

    for(int i=0; i<STRLEN; i++)
    {
  	    cmd1[i] = (char*)malloc(STRLEN*sizeof(char));
        cmd2[i] = (char*)malloc(STRLEN*sizeof(char));
    }

    int *argc1 = (int*)malloc(sizeof(sizeof(int)));
    int *argc2 = (int*)malloc(sizeof(sizeof(int)));

    separate_command(argv, argc, cmd1, cmd2, argc1, argc2, "|");

    pid_t pid1, pid2;
    
    int fd[2]; 
  
    if(pipe(fd) < 0) 
    {
        perror("pipe()");
        return -1;
    }

    pid1 = fork();

    if(pid1 < 0) 
    {
        perror("fork()");
        return -1;
    }
    else if(pid1 == 0) 
    {
        close(fd[0]); // fd[0] não será usado neste processo
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
  
        if(execvp(cmd1[0], cmd1) < 0) 
        {
            printf("shell: command not found\n");
            return -1;
        }
    } 
    else 
    {
        pid2 = fork();
  
        if(pid2 < 0) 
        {
            perror("fork()");
            return -1;
        }
  
        if (pid2 == 0) 
        {
            close(fd[1]); // fd[1] não será usado neste processo
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
        
            if(exist_pipe(cmd2, *argc2)) 
            {   
                exec_pipe_command(cmd2, *argc2);
            } 
            else {
                if(exist_pipe(cmd2, *argc2))
                {
                    exec_pipe_command(cmd2, *argc2);
                }
                if(execvp(cmd2[0], cmd2))
                {
                    printf("shell: command not found\n");
                    exit(0);
                }
            }
        } 
        else 
        {
            waitpid(-1, NULL, 0);
            sleep(1);
            return 0;
        }
    }
}
