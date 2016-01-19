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
  struct sockaddr_in srvr_addr,udp_addr ,client_addr;
  int ret, sk ,udpsk , c_udpport;
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
	  int len;
	  int partita_avviata = 0;
	  char cmnd_string[25];
	  printf("Inserisci il tuo nome (max 20 caratteri):\r\n> ");
	  fgets(cmnd_string,20,stdin);
	  sscanf(cmnd_string,"%19s%n",usrName,&len);
	  // printf("%i\r\n",len);
	  printf("Inserisci la porta UDP di ascolto:\r\n> ");
	  fgets(cmnd_string,24,stdin);
	  sscanf(cmnd_string,"%4i",&udpPort);
	  //invio la porta
	  send_len(udpPort,sk);
	  //invio la lunghezza
	  send_len(len+1,sk);
	  //invio il messaggio
	  send_msg(len+1,sk,usrName);
	  int a;
	  recv(sk,&a,sizeof(int),0);
	  if(a == 0)
	    {
	      printf("username gia esistente\r\n");
	      exit(1);
	    }
	  int loopCond = 0;
	  partita * game;
	  fd_set fd_master,fd;
	  FD_ZERO(&fd_master);
	  FD_ZERO(&fd);
	  FD_SET(0,&fd_master);
	  FD_SET(sk,&fd_master);
	  int fdmax = sk;
	  struct timeval timeout;
	  timeout.tv_sec = 60;
	  timeout.tv_usec = 0;
	  helper();
	  while(loopCond == 0)
	     {
	       struct timeval * mytimeout;
	       if(partita_avviata == 0)
		 {
		   mytimeout = NULL; 
		   //timeout.tv_sec=0;
		   // timeout.tv_usec=0;
		   printf("> ");
		 }
	       else
		 {
		   mytimeout = &timeout;
		   //timeout.tv_sec=60;
		   //timeout.tv_usec=0;
		   printf("# ");
		 }
	       fflush(stdout);
	       fd = fd_master;
	       if((ret = select(fdmax+1,&fd,NULL,NULL,mytimeout)) == -1)
		 {
		   perror("select() error");
		   exit(1);
		 }
	       if(ret == 0 && partita_avviata == 1)
		 {
		   printf("disconnessione automatica\r\n");
		   FD_CLR(udpsk,&fd_master);
	           fdmax = sk;
		   int op =0;
		   sendto(udpsk,&op,sizeof(int),0,(struct sockaddr*)&client_addr,sizeof(client_addr));		
      		   close(udpsk);
	   	   free(game);
	      	   partita_avviata = 0;
		   send_op(5,sk);
		 }
	       if(FD_ISSET(sk,&fd))
		 {
		   int len;
		   char nome[20];
		   //chiedere all'utente se vuole accettare la partita
		   recv(sk,&len,sizeof(int),0);
		   recv(sk,nome,len*sizeof(char),0);
		   printf("\r\n%s ti ha invitato a giocare , vuoi accettare la partita?(y/n)\r\n> ",nome);
		   //fflush(stdout);
		   int risposta_corretta = 0;
		   char risposta; 
		   while(risposta_corretta == 0)
		     {
		       scanf("%c",&risposta);
		       if(risposta == 'y' || risposta == 'Y' || risposta == 'n' || risposta == 'N')
			 risposta_corretta = 1;
		       else
			 {
			   printf("risposta non valida , inserire y se si vuole accettare o n altrimenti \r\n> ");
			   // fflush(stdout);
			 }
		     }
		   fgets(cmnd_string ,25 , stdin);
		   int codifica = codifica_risposta(risposta);
		   send(sk,&codifica,sizeof(int),0);
		   if(codifica == 1)
		     {
		       recv(sk,&c_udpport,sizeof(int),0);
		       char ip[INET_ADDRSTRLEN] ;
		       recv(sk,&ip,INET_ADDRSTRLEN * sizeof(char),0);
		       //udp_port_init(&udp_addr,&udpsk,udpPort );
		       udp_port_init(&udp_addr,&udpsk,udpPort);
		       init_client_addr(&client_addr , c_udpport,ip);
		       FD_SET(udpsk,&fd_master);
		       fdmax = (udpsk > fdmax) ?udpsk :fdmax;
		       game = init_game_structure(0,0);
		       partita_avviata = 1;
		     }
	       }
	       if(partita_avviata == 1)
		 {
		   if(FD_ISSET(udpsk,&fd))
		     {
		       struct sockaddr_in rec;
		       int op = 0;
		       socklen_t sl = sizeof(rec);
		       recvfrom(udpsk,&op,sizeof(int),0,(struct sockaddr*)&rec,&sl);
		       switch(op)
			 {
			 case 0:
			   {
			     printf("disconnessione automatica\r\n");
			     FD_CLR(udpsk,&fd_master);
			     fdmax = sk;
			     close(udpsk);
			     free(game);
			     partita_avviata = 0;
			     send_op(5,sk);
			   }
			 case 5:
			   {
			   //disconnect
			     printf("hai vinto!\r\n");
			     FD_CLR(udpsk,&fd_master);
			     fdmax = sk;
			     close(udpsk);
			     free(game);
			     partita_avviata = 0;
			     send_op(5,sk);
			     break;
			   }
	    
			 case 7:
			   {
			     //insert
			     char col;
			     recvfrom(udpsk,&col,sizeof(char),0,(struct sockaddr*)&rec,&sl);
			     int pl2symb = (game->symbol == 0)?1:0;
			     insert(col ,pl2symb,game);
			     printf("\r\ninserito gettone in %c:",col);
			     if(winner(col,game))
			       {
				 printf(" hai perso\r\n");
				 send_op(5,sk);
				 close(udpsk);
				 FD_CLR(udpsk,&fd_master);
				 fdmax = sk;
				 free(game);
				 partita_avviata = 0; 
			       }
			     else
			       {
				 game ->turn =1;
				 printf(" è il tuo turno\r\n");
			       }
			     break;
			   }
			 }
		     }
		 }
	       if(FD_ISSET(0,&fd))
		 {
		   fgets(cmnd_string , 25 , stdin);
		   //printf(" debug --- > %s\r\n",cmnd_string);
		   int action ;
		   char argument[10];
		   action = parse_cmd_strng(cmnd_string);
		   switch (action)
		     {
		     case 1:
		       {
			 if(partita_avviata == 1)
			   {
			     printf("devi prima disconnetterti dalla partita , usa il comando !disconnect\r\n");
			   }
			 else
			   {
			     send_op(1,sk);
			     close(sk);
			     loopCond = 1;
			     printf("client disconnesso correttamente\r\n");
			   }
			 break;
		       }
		     case 2:
		       helper();
		       break;
		    
		     case 3:
		       {
		       //!who
		       int number , len;
		       send_op(3,sk);
		       recv(sk,&number,sizeof(int),0);
		       if(number >0)
			 {
			   printf("sono disponibili %i  utenti:\r\n",number);
			   for(int i = 0;i< number ;i++)
			     {
			       recv(sk,&len,sizeof(int),0);
			       //printf("len : %i",len);
			       recv(sk,usrName,len*sizeof(char),0);
			       printf("%s\r\n",usrName);
			     }
			 }
		       else
			 {
			   printf("non ci sono altri utenti connessi\r\n");
			 }
		       break;
		       }
		     case 4:
		       {
			 if(partita_avviata == 1)
			   printf("sei gia connesso ad una partita\r\n");
			 else
			   {
			     //!connect
			     int diff;
			     sscanf(cmnd_string,"%*s %n%s%n",&diff,argument,&len);
			     //printf("%s : %i\r\n",argument,len-diff);
			     send_op(4,sk);
			     int invio = len-diff;
			     //send(sk,&invio,sizeof(int),0);
			     send_len(len-diff+1,sk);
			     send_msg(len-diff+1,sk,argument);
			     int risposta ;
			     recv(sk,&risposta,sizeof(int),0);
			     if(risposta == -1)
			       printf("%s nome inesistente\r\n",argument);
			     else if(risposta == -2)
			       printf("%s gia' impegnato in una partita\r\n",argument);
			     else if(risposta == -3)
			       printf("non puoi iniziare una partita con te stesso!!\r\n");
			     else if(risposta == 0)
			       printf("l'utente %s ha rifiutato la partita\r\n",argument);
			     else
			       {
				 printf("l'utente %s ha accettato la partita\r\n",argument);
				 recv(sk,&c_udpport,sizeof(int),0);
				 char ip[INET_ADDRSTRLEN];
				 recv(sk , &ip , INET_ADDRSTRLEN*sizeof(char),0);
				 udp_port_init(&udp_addr,&udpsk,udpPort);
				 init_client_addr(&client_addr , c_udpport,ip);
				 FD_SET(udpsk,&fd_master);
				 fdmax = (udpsk > fdmax) ?udpsk :fdmax;
				 game = init_game_structure(1,1);
				 //show_map(game);
				 partita_avviata = 1;
				 printf("partita avviata: è il tuo turno\r\n");
			       }
			   }
		       break;
		       }
		     case 5:
		       {
		         if(partita_avviata == 1)
			   {
			     int op = 5;
			     sendto(udpsk,&op,sizeof(int),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
			     printf("ti sei arreso\r\n");
			     send_op(5,sk);
			     FD_CLR(udpsk,&fd_master);
			     close(udpsk);
			     fdmax=sk;
			     free(game);
			     partita_avviata = 0;
			   }
			 else
			   {
			     printf("per eseguire questo comando devi essere all'interno di una partita\r\n");
			   }
			 break;
		       }
		     case 6:
		       {
			 //show_map
			 show_map(game);
		       
		       break;
		       }
		     case 7:
		       {
			 if(partita_avviata == 0)
			   {
			     printf("devi prima avviare una èartita per poter eseguire questo comando\r\n");
			   }
			 else
			   {
			     if(game->turn == 0)
			       printf("non è il tuo turno\r\n");
			     else
			       {
				 char col;
				 sscanf(cmnd_string ,"%*s %c",&col);
				 if(((int)col-97)<0 || ((int)col-97)>6)
				   {
				     printf("la colonna inserita non è corretta , inserire una lettera compresa tra a e g\r\n");
				   }
				 else
				   {
				     insert(col ,game->symbol, game);
				     int op =7;
				     sendto(udpsk,&op,sizeof(int),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
				     sendto(udpsk,&col,sizeof(char),0,(struct sockaddr*)&client_addr,sizeof(client_addr));
				     if(winner(col , game))
				       {
					 printf("hai vinto la partita!\r\n");
					 send_op(5,sk);
					 FD_CLR(udpsk,&fd_master);
					 close(udpsk);
					 fdmax=sk;
					 free(game);
					 partita_avviata = 0;
				       }
				     else
				       {
					 game ->turn = 0;
				       }
				   }
			       }
			   }
			 break;
		       }
		     case 0:
		       printf("comando non valido , digitare !help per visualizzare una lista di comandi validi\r\n");
		       break;
		       
		     }
	       	 }
	     }
	}
      else
	{
	  printf("impossibile connettersi al server\r\n");
	  return 1;
	}
      
    }
}
