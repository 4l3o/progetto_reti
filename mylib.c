/**
 ** Author: Bachechi Andrea
 **/
typedef struct game_struct
{
  int grid[6][7];
  int symbol;
  int turn;
}partita;

  void helper()
{
  printf("\r\n Sono disponibili i seguenti comandi :\r\n");
  printf(" * !help --> mostra l'elenco dei comandi disponibili\r\n");
  printf(" * !who --> mostra l'elenco dei client connessi al server\r\n");
  printf(" * !connect <nome_client> --> avvia una partita con l'utente nome_client\r\n");
  printf(" * !disconnect --> disconnette il client dalla partita attuale\r\n");
  printf(" * !quit --> disconnette il client dal server\r\n");
  printf(" * !show_map --> mostra la mappa di gioco\r\n");
  printf(" * !insert <column> --> inserisce il gettone in column (valido solo durante il proprio turno)\r\n");
  return;
}

int init_srvr_addr(struct sockaddr_in*srvr_addr , char*ip , char*port)
{
  int ok;
  memset(srvr_addr,0,sizeof(*srvr_addr));
  srvr_addr->sin_family=AF_INET;
  srvr_addr->sin_port = htons(atoi(port));
  ok = inet_pton(AF_INET,ip,&srvr_addr->sin_addr.s_addr);
  return ok;
}

int parse_cmd_strng(char * string)
{
  char command [15];
  sscanf(string , "%s" , command);
  if(strcmp(command ,"!quit") == 0)
    {
      return 1;
    }
  else if(strcmp(command , "!help") == 0)
    {
      return 2;
    }
  else if(strcmp(command , "!who") == 0)
    {
      return 3;
    }
  else if(strcmp(command , "!connect") == 0)
    {
      return 4;
    }
  else if(strcmp(command , "!disconnect") == 0)
    {
      return 5;
    }
  else if(strcmp(command , "!show_map") == 0)
    {
      return 6;
    }
  else if(strcmp(command , "!insert") == 0)
    {
      return 7;
    }
  else
    {
      return 0;
    }
}

int srvrSend(unsigned int op ,char * str ,int dimension ,int socket)
{
  int ret = 0;
  //invio l'operazione
  ret = send(socket ,&op ,sizeof(int),0);
  //inviare la dimensione
  ret = send(socket ,&dimension ,sizeof(int),0);
  //ret = send(socket ,str ,dimension, 0);
  //inviare la stringa
  ret = send(socket ,&str ,dimension ,0 );
  if(ret >0)
    {
      printf("invio username\r\n");
      ret = send(socket,str,dimension,0);
      return ret;
    }
  return ret;
}

int send_op(unsigned short op, int socket)
{
  int ret=0;
  ret = send(socket,&op,sizeof(unsigned short int),0);
  if(ret > 0)
    {
      return 0;
    }
  else
    {
      return -1;
    }
}

int send_len(int len , int socket )
{
  int ret = 0;
  ret = send(socket ,&len , sizeof(int),0);
  if(ret > 0 )
    {
      return 0;
    }
  else
    {
      return -1;
    }
}

int send_msg(int len , int socket ,char * msg)
{
  int ret = 0;
  ret = send(socket , msg , len*sizeof(char), 0);
  if(ret > 0 )
    {
      return 0;
    }
  else
    {
      return 1;
    }
}

void udp_port_init(struct sockaddr_in *udpaddr , int*udpsk , int udpport )
{
  if((*udpsk = socket(AF_INET,SOCK_DGRAM, 0)) == -1)
    {
      perror("errore sul socket udp");
      exit(1);
    }
  memset(udpaddr , 0, sizeof(*udpaddr));
  udpaddr -> sin_family = AF_INET;
  udpaddr -> sin_port = htons(udpport);
  udpaddr ->sin_addr.s_addr = htonl(INADDR_ANY);
  //inet_aton(ip , &udpaddr->sin_addr);
  if(bind(*udpsk,(struct sockaddr*)udpaddr ,sizeof(*udpaddr)) == -1)
    {
      perror("bind udp socket");
      exit(1);
    }
  
}

void init_client_addr(struct sockaddr_in *client_addr , int udpport , char* ip)
{
  memset(client_addr ,0,sizeof(*client_addr));
  client_addr->sin_family = AF_INET;
  client_addr->sin_port = htons(udpport);
  inet_aton(ip , &client_addr->sin_addr);
  //printf("client ip: %s , port: %i",ip,udpport);
}

int codifica_risposta(char risposta)
{
  if(risposta == 'y'|| risposta == 'Y')
    return 1;
  else if(risposta == 'n' || risposta == 'N')
    return 0;
  else
    return -1;
}

partita* init_game_structure(int symbol,int turn)
{
  partita * nuova = (partita*)malloc(sizeof(partita));
  nuova ->turn =turn;
  nuova ->symbol = symbol;
  for(int i = 0;i<6;i++)
    {
      for(int j = 0;j<7;j++)
	{
	  //printf("i:%i j%i ",i,j);
	  nuova->grid[i][j]=-1;
	  //printf("grid :%i",nuova->grid[i][j]);
	}
    }
  return nuova;
}

void destroy_game_structure(partita * pointer)
{
  free(pointer);
}

int orizzontal_count(int colonna,int riga , int symbol ,partita * pointer , int increment)
{
  if(colonna == 7 || colonna == -1)
    {
      return 0;
    }
  else
    {
      if(pointer -> grid[riga][colonna] == symbol )
	return 1 + orizzontal_count(colonna+increment,riga,symbol,pointer,increment);
      else
	return 0;
    }
}

int vertical_count(int colonna,int riga , int symbol ,partita * pointer , int increment)
{
  if(riga == 6 || riga == -1)
    {
      return 0;
    }
  else
    {
      if(pointer -> grid[riga][colonna] == symbol )
	return 1 + vertical_count(colonna,riga+increment,symbol,pointer,increment);
      else
	return 0;
    }
}

int diagonal_count(int colonna,int riga , int symbol ,partita * pointer , int increment)
{
  if(colonna == 7 || colonna == -1 || riga == 6 || riga == -1)
    {
      return 0;
    }
  else
    {
      if(pointer -> grid[riga][colonna] == symbol )
	return 1 + diagonal_count(colonna+increment,riga+increment,symbol,pointer,increment);
      else
	return 0;
    }
}


int winner(char col,partita * pointer)
{
  int colonna = (int)col-97;
  int riga;
  for(int i = 0 ; i<6;i++)
    {
      if(pointer->grid[i][colonna] !=-1)
	riga = i;
    }
  int count_x = 1 + orizzontal_count(colonna+1,riga,pointer->grid[riga][colonna],pointer,1) + orizzontal_count(colonna-1,riga,pointer->grid[riga][colonna],pointer,-1);
  int count_y = 1 + vertical_count(colonna,riga+1,pointer->grid[riga][colonna],pointer,1) + vertical_count(colonna,riga-1,pointer->grid[riga][colonna],pointer,-1);
  int count_diag = 1 + diagonal_count(colonna+1,riga+1,pointer->grid[riga][colonna],pointer,1) + diagonal_count(colonna-1,riga-1,pointer->grid[riga][colonna],pointer,-1);
  if(count_x == 4 || count_y == 4 || count_diag == 4)
    return 1;
  else
    return 0;
}

int insert(char col ,int symbol, partita*pointer)
{
  int inserimento;
  int colonna;
  colonna = (int)col -97;
  //printf("colonna :%i\r\n",colonna);
  int i =0;
  while(pointer->grid[i][colonna] != -1)
    {
      i +=1;
    }
  if(i <=5)
    {
      pointer->grid[i][colonna]=symbol;
    }
  return 0;
}
void print_line()
{
  for(int i=0;i<8;i++)
    {
      if(i==0)
	printf("  ");
      else
	printf("_ _ ");
    }
  printf("\r\n");
}
void show_map(partita * pointer)
{
  printf("\r\n");
  print_line();
  for(int i =6 ; i>0;i--)
    {
      for(int j = 0;j<8;j++)
	{
	  if(j==0 )
	    {
	      printf("%i|",i);
	    }
	  else
	    {
	      int symbol = pointer->grid[i-1][j-1];
	      if(symbol == 0)
		{
		  printf(" o |");
		}
	      if(symbol == -1)
		{
		  printf("   |");
		}
	      if(symbol == 1)
		{
		  printf(" x |");
		}
	    }
	}
      printf("\r\n");
      print_line();
    }
   for(int i = 0;i<7;i++)
    {
      int j = i+97;
      if(i == 0)
	{
	  printf("   %c  ",(char)j);
	}
      else
	{
	  printf(" %c  ",(char)j);
	}
    }
   printf("\r\n");
 
}

