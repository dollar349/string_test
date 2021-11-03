#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#define configfile "./config"

#define CONFIG_FILE_SIZE 4096
int update_config(const char* config_file_name, const char* config, const char* value);
#if 1
int update_config(const char* config_file_name, const char* config, const char* value)
{
    size_t config_len = strlen(config);
    int  fp;
    char buf[CONFIG_FILE_SIZE];
    size_t filesize;

    char* insert_str;
    // Make insert sting (+4 is for " = " + '\0' )
    insert_str = malloc( strlen(config) + strlen(value) + 4 );
    sprintf(insert_str, "%s = %s", config, value);

    // Open config file
    fp = open(config_file_name, O_RDONLY);
    filesize = read(fp, buf, CONFIG_FILE_SIZE);
    close(fp);
    if (filesize == CONFIG_FILE_SIZE){
        printf("Config file size too large, maximum is %d\n", CONFIG_FILE_SIZE);
        free(insert_str);
        return -1;
    }
    // Create new config buffer
    char *p, *line;
    bool new_config=true;
    char new_buf[CONFIG_FILE_SIZE]={0};
    for (p = NULL, line = strtok_r(buf, "\n", &p); line;
		line = strtok_r(NULL, "\n", &p)) {
        if ( new_config &&
             (strncmp ( line, config , config_len) == 0) &&
             ( (line[config_len] == ' ') || (line[config_len] == '=') )
           ) {
            // Found config in this line
            strcat(new_buf, insert_str);
            strcat(new_buf, "\n");
            new_config = false;
        }
        else{
            // Copy original config 
            strcat(new_buf, line);
            strcat(new_buf, "\n");
        }
    }
    if (new_config){
        // Append new line for new config
        strcat(new_buf, insert_str);
        strcat(new_buf, "\n");
    }
    fp = open(config_file_name, O_WRONLY | O_TRUNC);
    write(fp, new_buf, strlen(new_buf));
    close(fp);
    free(insert_str);
    return 0;
}
#else
int update_config(const char* config_file_name, const char* config, const char* value)
{
    size_t config_len = strlen(config);
    FILE *fp;
    char buf[CONFIG_FILE_SIZE];

    char* insert_str;
    // Make insert sting (+4 is for " = " + '\n' )
    insert_str = malloc( strlen(config) + strlen(value) + 3 );
    sprintf(insert_str, "%s = %s", config, value);

    // Open config file
    fp = fopen(config_file_name, "r");

    // get file length
    fseek(fp, 0, SEEK_SET);
    long begin = ftell(fp);
    fseek(fp, 0, SEEK_END);
    long end = ftell(fp);
    long filesize = end - begin;
    if (filesize > CONFIG_FILE_SIZE){
        printf("Config file size too large, maximum is %d", CONFIG_FILE_SIZE);
        fclose(fp);
        free(insert_str);
        return -1;
    }

    // Read orignal config to buf 
    fseek( fp, 0, SEEK_SET);
    fread( buf, filesize, 1 , fp );

    // Read completed, close it first.  
    // fclose(fp);

    // Create new config buffer
    char *p, *line;
    bool new_config=true;
    char new_buf[CONFIG_FILE_SIZE]={0};
    for (p = NULL, line = strtok_r(buf, "\n", &p); line;
		line = strtok_r(NULL, "\n", &p)) {
        if ( new_config &&
             (strncmp ( line, config , config_len) == 0) &&
             ( (line[config_len] == ' ') || (line[config_len] == '=') )
           ) {
            // Found config in this line
            strcat(new_buf, insert_str);
            strcat(new_buf, "\n");
            new_config = false;
        }
        else{
            // Copy original config 
            strcat(new_buf, line);
            strcat(new_buf, "\n");
        }
    }
    if (new_config){
        // Append new line for new config
        strcat(new_buf, insert_str);
        strcat(new_buf, "\n");
    }

    // Reopen file and write new config.
    //fp = fopen(config_file_name, "w");
    freopen(config_file_name, "w", fp);
    fwrite(new_buf, strlen(new_buf), 1, fp);

    fclose(fp);
    free(insert_str);

    return 0;
}
#endif
int main (int argc, char *argv[])
{
    if (argc == 3)
    {
        update_config(configfile, argv[1], argv[2]);
    }   
}

