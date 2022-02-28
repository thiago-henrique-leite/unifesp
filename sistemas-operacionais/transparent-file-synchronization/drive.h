#ifndef DRIVE_H
#define DRIVE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/stat.h>

#define BLOCK_SIZE 4096

char *build_file_path(char* folder, char* file);
void syncronize_directory(char *original_folder, char *backup_folder);
int  exec_backup_file(char *original, char *backup);
bool file_need_update(struct stat file_in_original, struct stat file_in_backup, char* backup_file_path);

#endif