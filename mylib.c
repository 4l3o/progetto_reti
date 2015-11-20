/**
 ** Author: Bachechi Andrea
 **/
int getServerInfo(struct sockaddr_in *my_addr , int argc , char* argv)
{
  //controllo se la lunghezza degli argomeni passati è giusta
  if (argc<3)
    {
      return 0;
    }
  else
    {
      char*ip;
      char*port;
      ip=argv[2];
      port=argv[3];
    }
  //traduco i valori presi in una struttura che rappresenta un indirizzo di rete
  memset(my_addr,0,sizeof(my_addr));
  my_addr->sin_family= AF_INET;
  my_addr->sin_addr.s_addr = htonl(ip);
  my_addr->sin_port=htons(port);
  return 1;
}
