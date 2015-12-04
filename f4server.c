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
  struct sockaddr_in myaddr , cl_addr;
  int sk, cn_sk , ret;
  if(argc < 3)
    {
      printf("Argomenti mancanti");
      return 1;
    }
  ret = serverInit( &myaddr , &sk ,argv[1],argv[2]);
}
