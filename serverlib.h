/**
 *Author: Bachechi Andrea
 **/
#include "serverlib.c"
int serverInit(struct sockaddr_in * myaddr , int*listeningSk , char*ip, char*port);
int count_list(user*testa);

user* nuovo_utente(user*testa,char*nome,int sv_sk,int udpport ,struct sockaddr_in * myaddr ,int stato);
