/** server
 * Author: Bachechi Andrea
 **/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include "serverlib.h"
  
int main (int argc , char*argv[])
{
  user * listautenti;
  struct sockaddr_in myaddr , cl_addr;
  int sk, cn_sk , ret ,fdmax;
  if(argc < 3)
    {
      printf("Argomenti mancanti");
      return 1;
    }
  ret = serverInit( &myaddr , &sk ,argv[1],argv[2]);
  fd_set master;
  fd_set slave;
  FD_ZERO(&master);
  FD_ZERO(&slave);
  FD_SET(sk,&master);
  fdmax = sk;
  int return_cond = 0;
  while(return_cond == 0)
    {
      slave = master;
      if(select(fdmax+1,&slave,NULL,NULL,NULL)== -1)
	{
	  perror("server select error");
	  exit(1);
	}
      for(int i=0;i<=fdmax;i++)
	{
	  if(FD_ISSET(i,&slave))
	    {
	      if(i==sk)
		{
		  int addrlen = sizeof(cl_addr);
		  int newsk = accept(sk,(struct sockaddr *)&cl_addr,&addrlen);
		  if(newsk == -1 )
		    {
		      perror("server accept error");
		    }
		  else
		    {
		      FD_SET(newsk , &master);
		      fdmax = (newsk > fdmax)?newsk:fdmax;
		    }
		}
	      else
	       {
		 unsigned short op;
		 recv(i,&op,sizeof(unsigned short int),0);
		 switch (op)
		   {
		   case 0:
		     //registrazione nuovo utente
		     char usrname[20];
		     int udpport;
		     int len;
		     rcv(i,&udpport,sizeof(int),0);
		     rcv(i,&len,sizeof(int),0);
		     rcv(i,username,len*(sizeof(char)));
		     lista_utenti=nuovo_utente(lista_utenti,usrname,i,udpport,0);
		     printf("%s si e' connesso\r\n %s è libero ",lista_utenti->nome);
		     break;
		   }

	       }
	    }
	}
    }
  
}
