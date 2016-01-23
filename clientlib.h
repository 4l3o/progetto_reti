#include "clientlib.c"
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

//inizializza la porta udp
void udp_port_init(struct sockaddr_in * udpaddr , int*udpsk , int udpport);

//inizializza l'indirizzo del client p2p
void init_client_addr(struct sockaddr_in *client_addr , int udpport , char*ip);

// codifica la risposta  yes/no
int codifica_risposta(char risposta);

//inizializza le strutture dati del gioco
partita*init_game_structure(int symbol , int turn);

//elimina le strutture dati del gioco
void destroy_game_structure(partita*pointer);

//conta il numero di simboli uguali 
int orizzontal_count(int colonna , int riga , int symbol , partita*pointer , int increment);

int vertical_count(int colonna ,int riga , int symbol , partita*pointer , int increment);

int diagonal_count(int colonna , int riga , int symbol , partita*pointer , int increment);

//controlla la condizione di vittoria
int winner(char col,partita*pointer);

//inserisce un simbolo nella griglia
int insert(char col , int symbol , partita*pointer);

//stampa una riga di separazione della griglia
void print_line();

//stampa la griglia
void show_map(partita*pointer);






