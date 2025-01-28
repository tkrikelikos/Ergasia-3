#define MAX_PROIONTA 20
#define BUFFER_SIZE 1024
#define PORT 6969

typedef struct Proion {
    char perigrafi[50];
    float timh;
    int proionta;
    int epityximena_aithmata;
    int apotyximena_aithmata;
}Proion;

typedef struct sinopsi{
    int synolikes_paraggelies;
    int epityximenes_paraggelies;
    int apotyximenes_paraggelies;
    float tziros;
}sinopsi;


void arxikopoihsh_katalogou(Proion *katalogos);
void xeirismos(int client_socket, Proion *katalogos,sinopsi *summary);
void anafora(Proion *katalogos,sinopsi summary);
