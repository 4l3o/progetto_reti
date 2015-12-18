/**client forza 4
 ** Author: Bachechi Andrea
 **/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include"myLib.h"

int main (int argc  ,char*argv[] )
{
  struct sockaddr_in srvr_addr;
  int ret, sk;
  if(argc < 3)
    {
      printf("argomenti mancanti!!");
      return 1;
    }
  else
    {
      ret = init_srvr_addr(&srvr_addr , argv[1], argv[2]);
      if(ret != 1)
	{
	  printf("impossibile inizializzare l'indirizzo del server\r\n");
	  return 1;
	}
      sk = socket(AF_INET , SOCK_STREAM , 0);
      ret = connect(sk,(struct sockaddr *)&srvr_addr , sizeof(srvr_addr));
      if(ret == 0 )
	{
	  printf("connessione con il server %s (%u) effettuata con successo\r\n",argv[1],atoi(argv[2]));
	  char usrName[20];
	  int udpPort;
	  char cmnd_string[25];
	  printf("Inserisci il tuo nome:");
	  fgets(cmnd_string,24,stdin);
	  sscanf(cmnd_string,"%19s",usrName);
	  printf("Inserisci la porta UDP di ascolto:");
	  fgets(cmnd_string,24,stdin);
	  sscanf(cmnd_string,"%4i",&udpPort);
	  srvrSend(usrName ,sk);
	  int loopCond = 0;
	  helper();
	  while(loopCond == 0)
	     {
	       fgets(cmnd_string , 25 , stdin);
	       int action ;
	       action = parse_cmd_strng(cmnd_string);
	       switch (action)
		 {
		 case 1:
		   printf("disconnessione in corso \n\r");
		   loopCond = 1;
		   break;
		    
		  case 2:
		    
		    break;
		    
		  case 3:

		    break;
		  case 4:
		    break;

		  case 5:
		    break;

		  case 6:
		    break;

		  case 7:
		    break;

		  case 0:
		    printf("comando non valido , digitare !help per visualizzare una lista di comandi validi\r\n");
		    break;
		  }
		// printf("l'utente ha digitato :%s il comando tradotto è: %i \r\n",cmnd_string,action);
	     }
	}
      else
	{
	  printf("impossibile connettersi al server\r\n");
	  return 1;
	}
      
    }
}
