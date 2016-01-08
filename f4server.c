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
  user * listautenti=NULL;
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
  char username[20];
  int udpport;
  int len;
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
		 unsigned short op = 0 ;
		 recv(i,&op,sizeof(unsigned short int),0);
		 //printf("op:%hu\r\n",op);
		 if(op!=0)
		   {
		     printf("%hu\r\n",op);
		     switch (op)
		       {
		       case 1:
			 {
			   //registrazione nuovo utente
			   recv(i,&udpport,sizeof(int),0);
			   recv(i,&len,sizeof(int),0);
			   recv(i,username,len*(sizeof(char)),0);
			   listautenti=nuovo_utente(listautenti,username,i,udpport,0);
			   printf("%s si e' connesso\r\n",listautenti->nome);
			   printf("%s e' disponibile\r\n",listautenti->nome);
			   break;
			 }
		       case 3:
			 {
			   //printf("invio lista utenti ");
			 int usrnumber = count_list(listautenti)-1;
			 //printf("%i",usrnumber);
			 send(i,&usrnumber,sizeof(int),0);
			 if(usrnumber >0)
			   {
			     for(user*k=listautenti;k!=NULL;k=k->next)
			       {
				 printf("%s : %i\r\n",k->nome , k->stato);
				 if(k->stato == 0 && k->sk != i)
				   {
				     //printf("%s\r\n",k->nome);
				     len = sizeof(k->nome)/sizeof(k->nome[0]);
				     send(i,&len,sizeof(int),0);
				     send(i,&k->nome,len*sizeof(char),0);
				   }
				 /**  questo fa parte della connect!!!!!
				      recv(sk,&size,sizeof(int),0);
				      recv(sk,username,size*sizeof(char),0);
				      user*target=cerca_utente(username , listautenti);
				      if(target == NULL)
				      {

				      }**/
			       }
			   }
			 break;
			 }
		       default:
			 printf("default\r\n");
			 break;
		       }
		   }

	       }
	    }
	}
    }
  
}
