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
		  
		  //int addrlen = sizeof(cl_addr);
		  socklen_t addrlen = (socklen_t)sizeof(cl_addr);
		  int newsk = accept(sk,(struct sockaddr *)&cl_addr,&addrlen);
		  if(newsk == -1 )
		    {
		      perror("server accept error");
		    }
		  else
		    {
		      FD_SET(newsk , &master);
		      fdmax = (newsk > fdmax)?newsk:fdmax;
		      recv(newsk,&udpport,sizeof(int),0);
		      recv(newsk,&len,sizeof(int),0);
		      recv(newsk,username,len*(sizeof(char)),0);
		      listautenti=nuovo_utente(listautenti,username,newsk,udpport,&cl_addr,0);
		      printf("%s si e' connesso\r\n",listautenti->nome);
		      printf("%s e' disponibile\r\n",listautenti->nome);
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
			   user*temp = cerca_utente_sk(i,listautenti);
			   printf("%s si è disconnesso\r\n",temp->nome);
			   rimuovi_utente(i , listautenti);
			   FD_CLR(i,&master);
			   close(i);
			   break;
			 }
		     
		       case 3:
			 {
			 int usrnumber = count_list(listautenti);
			 printf("%i",usrnumber);
			 send(i,&usrnumber,sizeof(int),0);
			 if(usrnumber >0)
			   {
			     for(user*k=listautenti;k!=NULL;k=k->next)
			       {
				 printf("%s : %i\r\n",k->nome , k->stato);
				 //printf("%s\r\n",k->nome);
				 int len = sizeof(k->nome)/sizeof(k->nome[0]);
				 send(i,&len,sizeof(int),0);
				 send(i,&k->nome,len*sizeof(char),0);  
			       }
			   }
			 break;
			 }
			  case 4:
			 {
			   int len;
			   recv(i,&len,sizeof(int),0);
			   printf("caratteri da leggere:%i\r\n",len);
			   recv(i,username,len*(sizeof(char)),0);
			   printf("utente richiesto %s\r\n",username);
			   user*target=cerca_utente(username,listautenti);
			   if(!target)
			     {
			       len = -1;
			       send(i,&len,sizeof(int),0);
			     }
			   else
			     {
			       if(target->stato == 1)
				 {
				   len = -2;
				   send(i,&len,sizeof(int),0);
				 }
			       else
				 {
				   user*sender =cerca_utente_sk(i,listautenti);
				   len = sizeof(sender->nome)/sizeof(sender->nome[0]);
				   send(target->sk,&len,sizeof(int),0);
				   send(target->sk,&sender->nome,len*sizeof(char),0);
				   //ricevo la risposta del client
				   int risposta;
				   recv(target->sk,&risposta,sizeof(int),0);
				   send(i,&risposta,sizeof(int),0);
				   if(risposta == 1)
				     {
				       send(i,&target->udpport,sizeof(int),0);
				       send(target->sk,&sender->udpport,sizeof(int),0);
				       int ipaddr = target->indirizzo.sin_addr.s_addr;
				       char ip[INET_ADDRSTRLEN];
				       inet_ntop(AF_INET,&ipaddr,ip,INET_ADDRSTRLEN);
				       send(i,ip,INET_ADDRSTRLEN * sizeof(char),0);
				       ipaddr = sender->indirizzo.sin_addr.s_addr;
				       inet_ntop(AF_INET,&ipaddr,ip,INET_ADDRSTRLEN);
				       send(target->sk,ip,INET_ADDRSTRLEN * sizeof(char),0);
				     }
				 }
			       } 
			 break;
			 }
		       case 5:
			 {
			   user * temp = cerca_utente_sk(i,listautenti);
			   temp ->stato =0;
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
