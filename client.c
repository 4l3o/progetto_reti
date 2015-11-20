/** client
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

int main(int argc , char*argv[])
{
  printf("client running!!")
  struct sockaddr_in srvr_addr;
  int ret = getServerInfo(srvr_addr , argc , argv);
  if(ret == 0)
    {
      printf("IP:",srvr_addr.sin_addr.s_addr);
      printf("port:",srvr_addr.sin_addr.s_addr);
      return ;
    }
  else
    {
      printf("errore");
      return;
    }
}

