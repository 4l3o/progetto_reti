/**
 ** Author: Bachechi Andrea
 **/
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
  memset(srvr_addr,0,sizeof(srvr_addr));
  srvr_addr->sin_family=AF_INET;
  srvr_addr->sin_port = htons(atoi(port));
  ok = inet_pton(AF_INET,ip,&srvr_addr->sin_addr.s_addr);
  return ok;
}

int parse_cmd_strng(char * string)
{
  char command [10];
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
