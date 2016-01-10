/**
 *Author:Bachechi Andrea
 **/
typedef struct utente
{
  struct utente* next;
  int udpport;
  struct sockaddr_in indirizzo;
  int sk;
  int stato;
  char nome[20];
  
}user;

user*  nuovo_utente(user*testa , char*nome ,int sv_sk , int udpport ,struct sockaddr_in *myaddr,int stato)
{
  user*nuovo;
  nuovo = (user*)malloc(sizeof(user));
  nuovo ->udpport = udpport;
  nuovo ->sk = sv_sk;
  nuovo ->stato = stato;
  strcpy(nuovo->nome,nome);
  nuovo ->indirizzo = *myaddr;
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

user* cerca_utente(char*username , user*testa)
{
  for(user*i=testa;i!=NULL;i=i->next)
    {
      if(strcmp(i->nome,username)==0)
	{
	  return i;
	}
    }
  printf("utente non trovato\r\n");
  return NULL;
}

user* cerca_utente_sk(int sk , user*testa)
{
  for(user*i=testa;i!=NULL;i=i->next)
    {
      if(sk == i->sk)
	return i;
    }
  return NULL;
}

int count_list(user*testa)
{
  //printf("conto il numero di utenti \r\n");
  int risultato = 0;
  for(user*i=testa;i!=NULL;i=i->next)
    {
      // printf("%s",i->nome);
      risultato ++ ;
    }
  return risultato;
}

