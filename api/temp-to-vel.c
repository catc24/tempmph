#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcgi_stdio.h>

#define COMMAND "./temp-to-vel"

void handle_request() {
    char *query_string = getenv("QUERY_STRING");
    if (!query_string) {
        printf("Status: 400 Bad Request\r\n\r\n");
        printf("Missing query string parameter 'temp'");
        return;
    }

    char command[1024];
    snprintf(command, sizeof(command), "%s %s", COMMAND, query_string);

    FILE *fp = popen(command, "r");
    if (!fp) {
        printf("Status: 500 Internal Server Error\r\n\r\n");
        printf("Failed to execute command: %s", command);
        return;
    }

    char buf[1024];
    while (fgets(buf, sizeof(buf), fp)) {
        printf("%s", buf);
    }

    int status = pclose(fp);
    if (status != 0) {
        printf("Status: 500 Internal Server Error\r\n\r\n");
        printf("Command exited with non-zero status: %d", status);
        return;
    }

    printf("Status: 200 OK\r\n\r\n");
}

int main() {
    while (FCGI_Accept() >= 0) {
        handle_request();
    }

    return 0;
}
