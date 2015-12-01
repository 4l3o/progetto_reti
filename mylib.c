/**
 ** Author: Bachechi Andrea
 **/
int helper()
{
  printf("sono disponibili i seguenti comandi :\r\n");
  printf(" * !help --> mostra l'elenco dei comandi disponibili\r\n");
  printf(" * !who --> mostra l'elenco dei client connessi al server\r\n");
  printf(" * !connect <nome_client> --> avvia una partita con l'utente nome_client\r\n");
  printf(" * !disconnect --> disconnette il client dalla partita attuale\r\n");
  printf(" * !quit --> disconnette il client dal server\r\n");
  printf(" * !show_map --> mostra la mappa di gioco\r\n");
  printf(" * !insert <column> --> inserisce il gettone in column (valido solo durante il proprio turno)\r\n");
}
