#include "drive.h"

char *build_file_path(char* folder, char* file) 
{
    char *file_path = (char*) malloc(200*sizeof(char));

    file_path[0] = '\0';
    
    strcat(file_path, folder);
    
    if(strcmp(folder, ".") == 0) 
        strcat(file_path, "/");
    
    strcat(file_path, "/");
    strcat(file_path, file);

    return file_path;
}

void syncronize_directory(char* original_folder, char* backup_folder) 
{

    struct dirent **original_files_name, **backup_files_name;
    struct stat file_in_original, file_in_backup;
    
    struct stat st = {0};

    if(stat(backup_folder, &st) == -1)
        mkdir(backup_folder, 0777);

    int original_folder_size, backup_folder_size;
    
    original_folder_size = scandir(original_folder, &original_files_name, NULL, alphasort);
    backup_folder_size   = scandir(backup_folder, &backup_files_name, NULL, alphasort);

    for(int i=2; i<original_folder_size; i++) 
    {

        char *original_file_path = build_file_path(original_folder, original_files_name[i]->d_name);
        
        if(original_files_name[i]->d_type == DT_DIR) 
        {
            char *backup_file_path = build_file_path(backup_folder, original_files_name[i]->d_name);

            if(lstat(backup_file_path, &file_in_backup) < 0) 
            {
                printf("[PASTA] Backup atualizado: %s\n", backup_file_path);
                mkdir(backup_file_path, 0700);
            }

            syncronize_directory(original_file_path, backup_file_path); 
        }

        else 
        {
            char *backup_file_path = build_file_path(backup_folder, original_files_name[i]->d_name);

            if(lstat(original_file_path, &file_in_original) < 0)
                perror("lstat#original");

            if(file_need_update(file_in_original, file_in_backup, backup_file_path)) 
            {
                printf("[ARQUIVO] Backup atualizado: %s\n", backup_file_path);
                exec_backup_file(original_file_path, backup_file_path);
            } 
        }

        free(original_files_name[i]);
    }

    free(original_files_name);
}

bool file_need_update(struct stat file_in_original, struct stat file_in_backup, char* backup_file_path) {
    return lstat(backup_file_path, &file_in_backup) == -1 || 
           difftime(file_in_original.st_mtime, file_in_backup.st_mtime) > 0;
}

int exec_backup_file(char *original, char *backup) 
{
    int n_bytes_read, n_bytes_written, n_bytes_increment, bytes_to_write;

    int original_file = open(original, O_RDONLY);
    int backup_file   = open(backup, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

    unsigned char buffer[BLOCK_SIZE];

    void *_buf;

    do {
    n_bytes_read = read(original_file, buffer, BLOCK_SIZE);
        n_bytes_written = read(backup_file, buffer, BLOCK_SIZE);

        _buf = buffer;

        bytes_to_write = n_bytes_read; n_bytes_increment = 0;
        
        do {
            n_bytes_written = write(backup_file, _buf + n_bytes_increment, bytes_to_write);

            n_bytes_increment += n_bytes_written; 
            bytes_to_write -= n_bytes_written;
        } while (bytes_to_write > 0);

    } while(n_bytes_read > 0);

    close(backup_file);
    close(original_file);
}

int main(int argc, char **argv) 
{
    char *original_folder = argv[1];
    char *backup_folder = argv[2];

    while(true) 
    {
        syncronize_directory(original_folder, backup_folder);
        printf(".\n");
        sleep(3);    
    }
}