/**
 *Author:Bachechi Andrea
 **/
typedef struct utente
{
  struct utente* next;
  int udpport;
  int sk;
  int stato;
  char nome[20];
}user;

user*  nuovo_utente(user*testa , char*nome ,int sv_sk , int udpport ,int stato)
{
  user*nuovo;
  nuovo = (user*)malloc(sizeof(user));
  nuovo ->udpport = udpport;
  nuovo ->sk = sv_sk;
  nuovo ->stato = stato;
  strcpy(nuovo->nome,nome);
  nuovo ->next = testa;
  return nuovo;
}


int serverInit(struct sockaddr_in * myaddr , int*listeningSk , char*ip, char*port)
{
  int ok = 0;
  memset(myaddr , 0 ,sizeof(*myaddr) );
  myaddr->sin_family = AF_INET;
  ok = inet_pton(AF_INET,ip , &myaddr->sin_addr.s_addr);
  if(ok != 1 )
    {
     printf("impossibile inizializzare l'indirizzo");
    return -1;
    }
  myaddr->sin_port= htons(atoi(port));
  *listeningSk = socket(AF_INET,SOCK_STREAM,0);
  ok = bind(*listeningSk,(struct sockaddr *)myaddr,sizeof(*myaddr));
  if(ok !=0)
    {
    printf("impossibile inizializzare il server");
    return -1;
    }
  ok = listen(*listeningSk,10);
  if(ok != 0)
    {
     printf("impossibile ascoltare sul socket");
    return -1;
    }
  printf("Inizializzazione del server effettuata con successo\r\n Indirizzo: %s (Porta: %i)\r\n Attendo connessione client\r\n",ip,atoi(port));
  return 0;
}

int count_list(user*testa)
{
  int risultato = 0;
  for(user*i;i!=NULL;i=i->next)
    {
      risultato ++ ;
    }
  return risultato;
}
