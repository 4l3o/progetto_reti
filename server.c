/** server
 ** Author: Bachechi Andrea
**/
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc , char*argv[])
{
  printf("server running!!\r\n");
  printf("connecting to:\r\n");
  printf("ip:%s",argv[1]);
  printf("\r\n");
  printf("port:%s",argv[2]);
  printf("\r\n");
  struct sockaddr_in my_addr, cl_addr;
  int sk , cn_sk;
  //int ret = getServerInfo(&srvr_addr , argc ,&argv);
  int ret =1;
  if(argc < 3)
    {
      ret =1;
    }
  else
    {
      memset(&my_addr,0,sizeof(my_addr));
      my_addr.sin_family= AF_INET;
      //srvr_addr.sin_addr.s_addr = htonl(argv[2]);
      int ok;
      ok = inet_pton(AF_INET,argv[1],&my_addr.sin_addr.s_addr);
      my_addr.sin_port = htons(atoi(argv[2]));
      ret = (ok==0)?0:1;
    }
  if(ret == 1)
    {
      printf("------------ creazione dell'indirizzo----------- \r\n");
      printf("IP:%u",my_addr.sin_addr.s_addr);
      printf("\r\n");
      printf("port:%u",my_addr.sin_port);
      printf("\r\n");
      sk=socket(AF_INET,SOCK_STREAM,0);
      ret = bind(sk,(struct sockaddr *)&my_addr,sizeof(my_addr));
      ret = listen(sk,10);
      int cl_addr_len = sizeof(cl_addr);
       printf("associazione con il socket effettuata , attendo connessione del client.\r\n");
      cn_sk = accept(sk,(struct sockaddr * )&cl_addr,&cl_addr_len);
      char r[20];
      int dim;
      recv(cn_sk,&dim,sizeof(int),0);
      //recv(cn_sk,r,5*sizeof(char),0);
      printf("leggo %i bit\r\n",dim);
      //printf("connesso utente :%s\r\n",r);
      recv(cn_sk,r,dim*sizeof(char),0);
      r[dim]='\0';
      printf("%s si è connesso!!!\r\n",r);
    }
  else
    {
      printf("errore");
      return 0;
    }
  
}
