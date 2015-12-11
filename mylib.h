#include"mylib.c"
//libreria contentente le primitive del server
void helper();

//inizializza le strutture dati per la connessione con il server 
int init_srvr_addr(struct sockaddr_in *srvr_addr, char*ip , char*port);

//traduce i comandi digitati dall'utente in un intero
int parse_cmd_string(char * string);
