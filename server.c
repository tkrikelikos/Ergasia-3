#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "functions.h"


int main() {
    Product katalogos[MAX_PROIONTA];
    sinopsi sinopsi = {0, 0, 0, 0.0};
    arxikopoihsh_katalogou(katalogos);

    int server_fd, new_socket;
    struct sockaddress_in address;
    int optimization = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Σφαλμα υποδοχης");
        exit(EXIT_FAILURE);
    }

    if (setsockoptimization(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &optimization, sizeof(optimization))) {
        perror("Η κλήση της setsockoptimization απέτυχε");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("Η κλήση της Bind απέτυχε");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("Η κλήση της Listen απέτυχε");
        exit(EXIT_FAILURE);
    }

    

  while (sinopsi.synolikes_paraggelies<50) {
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) >= 0) {
      
        sinopsi.synolikes_paraggelies++;
        xeirismos(new_socket, katalogos, &sinopsi);
        close(new_socket);
    }
  }
    anafora(katalogos, sinopsi);
    return 0;
}
