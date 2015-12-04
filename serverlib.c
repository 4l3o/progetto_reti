/**
 *Author:Bachechi Andrea
 **/
int serverInit(struct sockaddr_in * myaddr , int*listeningSk , char*ip, char*port)
{
  int ok = 0;
  memset(myaddr , 0 ,sizeof(*myaddr) );
  myaddr->sin_family = AF_INET;
  ok = inet_pton(AF_INET,ip , &myaddr->sin_addr.s_addr);
  if(ok != 1 )
    {
     printf("impossibile inizializzare l'indirizzo");
    return 0;
    }
  myaddr->sin_port= htons(atoi(port));
  *listeningSk = socket(AF_INET,SOCK_STREAM,0);
  ok = bind(*listeningSk,(struct sockaddr *)myaddr,sizeof(*myaddr));
  if(ok !=0)
    {
    printf("impossibile inizializzare il server");
    return 0;
    }
  ok = listen(*listeningSk,10);
  if(ok != 0)
    {
     printf("impossibile ascoltare sul socket");
    return 0;
    }
  printf("Inizializzazione del server effettuata con successo\r\n Indirizzo: %s (Porta: %i)\r\n Attendo connessione client\r\n",ip,atoi(port));
  return 1;
}
