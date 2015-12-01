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
//#include"myLib.h"

int main(int argc , char*argv[])
{
  printf("client running!!\r\n");
  printf("ip:%s",argv[1]);
  printf("\r\n");
  printf("port:%s",argv[2]);
  printf("\r\n");
  struct sockaddr_in srvr_addr;
  //int ret = getServerInfo(&srvr_addr , argc ,&argv);
  int ret =1;
  int sk;
  if(argc < 3)
    {
      ret =1;
    }
  else
    {
      memset(&srvr_addr,0,sizeof(srvr_addr));
      srvr_addr.sin_family= AF_INET;
      //srvr_addr.sin_addr.s_addr = htonl(argv[2]);
      int ok;
      ok = inet_pton(AF_INET,argv[1],&srvr_addr.sin_addr.s_addr);
      srvr_addr.sin_port = htons(atoi(argv[2]));
      ret = (ok==0)?0:1;
    }
  if(ret == 1)
    {
      printf("------------ creazione dell'indirizzo----------- \r\n");
      printf("IP:%u",srvr_addr.sin_addr.s_addr);
      printf("\r\n");
      printf("port:%u",srvr_addr.sin_port);
      printf("\r\n");
      printf("connessione al server\r\n");
      sk = socket(AF_INET ,SOCK_STREAM,0);
      ret = connect(sk,(struct sockaddr *)&srvr_addr , sizeof(srvr_addr));
      if(ret == 0)
	{
	  printf("CONNESSSO!!!!!!!!\\r\n");
	}
      return 0;
    }
  else
    {
      printf("errore");
      return 0;
    }
}

