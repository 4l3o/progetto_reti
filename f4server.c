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
		  int newsk = accept();
		}
	      else
	       {

	       }
	    }
	}
    }
  
}
