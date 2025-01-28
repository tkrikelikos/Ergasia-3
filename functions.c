#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "header.h"

void pelates() {
    struct sockaddress_in server_address;
    int sock = 0;
    char buffer[BUFFER_SIZE];

    for (int i = 0; i < 10; i++) { 
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            printf("\nΠροβλημα δημιουργιας υποδοχης\n");
            exit(EXIT_FAILURE);
        }

        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(PORT);

        if (inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr) <= 0) {
            printf("\nΛαθος διευθυνση");
            exit(EXIT_FAILURE);
        }

        if (connect(sock, (struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
            printf("\nΑποτυχια συνδεσης\n");
            exit(EXIT_FAILURE);
        }

        int kodikos_proiontos = rand() % MAX_PROIONTA; 
        write(sock, &kodikos_proiontos, sizeof(kodikos_proiontos) + 1); 

        read(sock, buffer, BUFFER_SIZE); 
        printf("Ο πελατης (PID %d) δεχτηκεd: %s\n", getpid(), buffer);

        close(sock); 
        sleep(1); 
    }
}

void arxikopoihsh_katalogou(Proion *katalogos) {
    for (int i = 0; i < MAX_PROIONTA; i++) {
        snprintf(katalogos[i].perigrafi, sizeof(katalogos[i].perigrafi), "Προιον %d", i + 1);
        katalogos[i].timh = (float)((rand() % 1000) / 10.0);
        katalogos[i].proionta =2;
        katalogos[i].epityximena_aithmata =0;
        katalogos[i].apotyximena_aithmata=0;
    }
}

void xeirismos(int client_socket, Proion *katalogos, sinopsi *sinopsi) {
    char buffer[BUFFER_SIZE];
    int kodikos_proiontos;

    read(client_socket, &kodikos_proiontos, sizeof(kodikos_proiontos));

    if (kodikos_proiontos < 0 || kodikos_proiontos >= MAX_PROIONTA) {
        snprintf(buffer, BUFFER_SIZE, "Λαθος προιον");
        write(client_socket, buffer, strlen(buffer) + 1);
        sinopsi->apotixymenes_paraggelies++;
        return;
    }

    Proion *Proion = &katalogos[kodikos_proiontos];

    if (Proion->proionta > 0) {
        Proion->proionta--;
        sinopsi->epityximenes_paraggelies++;
        sinopsi->tziros += Proion->timh;
        snprintf(buffer, BUFFER_SIZE, "Επιτυχημενη αγορα: %s, $%.2f", Proion->perigrafi, Proion->timh);
    } else {
        sinopsi->apotixymenes_paraggelies++;
        Proion->apotyximena_aitimata++;
        snprintf(buffer, BUFFER_SIZE, "Ελλειμα: %s", Proion->perigrafi);
    }
    Proion->epityximena_aitimata++;
    write(client_socket, buffer, strlen(buffer) + 1);
    sleep(1);
}

void anafora(Proion *katalogos, sinopsi sinopsi) {
    printf("\n---Αναφορα ---\n");
    for (int i = 0; i < MAX_PROIONTA; i++) {
        printf("Προιον: %s, Sold: %d, Αιτημα: %d, Αποτυχημενο αιτημα:%d\n", katalogos[i].perigrafi, 2 - katalogos[i].proionta, katalogos[i].epityximena_aitimata, katalogos[i].apotyximena_aitimata);
    }
    printf("\nΣυνοψη:\n");
    printf("Συνολικες παραγγελιες: %d\n", sinopsi.synolikes_paraggelies);
    printf("Επιτυχημενες παραγγελιες: %d\n", sinopsi.epityximenes_paraggelies);
    printf("Αποτυχημενες παραγγελιες: %d\n", sinopsi.apotixymenes_paraggelies);
    printf("Συνολικος τζιρος: $%.2f\n", sinopsi.tziros);
}

