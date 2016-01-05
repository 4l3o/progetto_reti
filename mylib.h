#include"mylib.c"
//libreria contentente le primitive del server
void helper();

//inizializza le strutture dati per la connessione con il server 
int init_srvr_addr(struct sockaddr_in *srvr_addr, char*ip , char*port);

//traduce i comandi digitati dall'utente in un intero
int parse_cmd_string(char * string);

//invia una stringa al server
int srvrSend(unsigned int op,char * str ,int dimension, int socket );

//invia l'operazione al server
int send_op(unsigned short op , int socket);

//invia la lunghezza del messaggio al server
int send_len(int len , int socket);

//invia il messaggio al server
int send_msg(int len , int socket , char * msg);
