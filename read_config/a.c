#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>

#define CONFIG_FILE "client.ttyEcho.conf"
#define CONFIG_FILE_SIZE 4096
#define warn(msg, arg...)  printf(msg, ##arg)

int get_port_num_from_file(const char* file_name);

int get_port_num_from_file(const char* config_file_name)
{
    const char *config_name = "ssh_port";
    char *name, *value;
    char *p, *line;
    char buf[CONFIG_FILE_SIZE]={0};
    int filesize;
	int rc;

    // Open and read config file
    int  fp = open(config_file_name, O_RDONLY);
	if (fp < 0) {
		warn("%s:Can't raed client file %s", __FUNCTION__, config_file_name);
		return -1;
	}
	filesize = read(fp, buf, CONFIG_FILE_SIZE);
	close(fp);
	if (filesize == CONFIG_FILE_SIZE){
		// If the read size is equal to the maximum size, show error.
		warn("Config file size too large, maximum is %d", CONFIG_FILE_SIZE);
		return -1;
	}

    // Parsing config
	for (p = NULL, line = strtok_r(buf, "\n", &p); line;
			line = strtok_r(NULL, "\n", &p)) {

		/* trim leading space */
		for (;*line == ' ' || *line == '\t'; line++)
			;

		/* skip comments */
		if (*line == '#')
			continue;

		name = value = NULL;
        
		rc = sscanf(line, "%m[^ =] = %ms ", &name, &value);
		if (rc != 2 || !strlen(name) || !strlen(value) || (strcmp(name, config_name) != 0)) {
			free(name);
			free(value);
			continue;
		}
        else{
            rc = atoi(value);
			free(name);
			free(value);
            return rc;
        }
    }
    // not found 
    warn("%s not found from file %s", config_name, config_file_name);
    return 0;
}

int main (int argc, char *argv[])
{
    int port = get_port_num_from_file(CONFIG_FILE);
    printf("port = %d\n", port);

    return 0;
}

