#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include <errno.h>
#include <pwd.h>
#include <limits.h>
#include <stdlib.h>


int main(int argc, const char** argv, const char** envp)
{
	DIR* dir;
	struct dirent* curr_file_info;
	struct stat sb;
	char* full_path = NULL;
	struct passwd  *pw_d;
	if(argc < 2)
	{
		printf("No arguments supplied\n");
		return -1;
	}
	dir = opendir(argv[1]);
	if(dir == NULL)
	{
		printf("Error - %d\n", errno);
		return -1;
	}
	full_path = realpath(argv[1], NULL);
	while( ( curr_file_info = readdir(dir) ) != NULL )
	{
		printf("--------------------------------------------\n");
		printf("File path:  %s/%s\n", full_path, curr_file_info->d_name);
		full_path = realpath(argv[1], NULL);
                char* tempp = full_path;
                tempp = strcat(tempp, "/");
                tempp = strcat(tempp, curr_file_info->d_name);
		if (stat(tempp, &sb) == -1) {
        	printf("Statistics couldn't be taken.");
        	return -1;
    	}	
    	printf("File size:                %lld bytes\n", (long long) sb.st_size);
    	pw_d = getpwuid ( sb.st_uid ); 
  		printf ( "File owner:               %s \n", pw_d->pw_name); 
    	printf("Mode:                     %lo (octal)\n", (unsigned long) sb.st_mode);
    	printf("Last file access:         %s", ctime(&sb.st_atime));
      printf("Last file modification:   %s", ctime(&sb.st_mtime));
      printf("File create time:         %s", ctime(&sb.st_ctime));
	}
	free(full_path);	
	closedir(dir);
	printf("%s %s\n", argv[0], argv[1]);
	return 0;
}
