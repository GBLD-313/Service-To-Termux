#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int is_service_installed(const char *service) {
    char command[100];
    snprintf(command, sizeof(command), "command -v %s > /dev/null 2>&1", service);
    return system(command) == 0;
}

void install_service(const char *service) {
    char command[100];
    snprintf(command, sizeof(command), "pkg install -y %s", service);
    system(command);
}

void start_service(const char *service) {
    if (strcmp(service, "ssh") == 0) {
        system("sshd");
    } else if (strcmp(service, "ftp") == 0) {
        system("ftpd");
    } else if (strcmp(service, "apache") == 0) {
        system("apachectl start");
    } else if (strcmp(service, "mysql") == 0) {
        system("mysqld");
    } else if (strcmp(service, "tor") == 0) {
        system("tor");
    } else if (strcmp(service, "vnc") == 0) {
        system("vncserver");
    } else if (strcmp(service, "nodejs") == 0) {
        system("node");
    } else if (strcmp(service, "termuxapi") == 0) {
        system("termux-api-start");
    } else {
        printf("Service '%s' not recognized.\n", service);
    }
}

void stop_service(const char *service) {
    if (strcmp(service, "ssh") == 0) {
        system("pkill sshd");
    } else if (strcmp(service, "ftp") == 0) {
        system("pkill ftpd");
    } else if (strcmp(service, "apache") == 0) {
        system("apachectl stop");
    } else if (strcmp(service, "mysql") == 0) {
        system("pkill mysqld");
    } else if (strcmp(service, "tor") == 0) {
        system("pkill tor");
    } else if (strcmp(service, "vnc") == 0) {
        system("vncserver -kill :1");
    } else if (strcmp(service, "nodejs") == 0) {
        system("pkill node");
    } else if (strcmp(service, "termuxapi") == 0) {
        system("termux-api-stop");
    } else {
        printf("Service '%s' not recognized.\n", service);
    }
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <service> <start|stop>\n", argv[0]);
        return 1;
    }

    const char *service = argv[1];
    const char *action = argv[2];

    if (!is_service_installed(service)) {
        printf("Service '%s' is not installed. Do you want to install it? (y/n): ", service);
        char response;
        scanf(" %c", &response);
        if (response == 'y' || response == 'Y') {
            install_service(service);
        } else {
            printf("Installation canceled. Exiting.\n");
            return 1;
        }
    }

    if (strcmp(action, "start") == 0) {
        start_service(service);
    } else if (strcmp(action, "stop") == 0) {
        stop_service(service);
    } else {
        printf("Invalid action '%s'. Use 'start' or 'stop'.\n", action);
    }

    return 0;
}
