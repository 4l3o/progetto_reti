/**
 *Author: Bachechi Andrea
 **/
#include "serverlib.c"
int serverInit(struct sockaddr_in * myaddr , int*listeningSk , char*ip, char*port);
int count_list(user*testa);

user* nuovo_utente(user*testa,char*nome,int sv_sk,int udpport ,struct sockaddr_in * myaddr ,int stato);

void rimuovi_utente(int sk,user ** testa);

user* cerca_utente(char*username , user*testa);

user* cerca_utente_sk(int sk , user* testa);


