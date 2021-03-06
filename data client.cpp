//
//  main.cpp
//  paste
//
//  Created by 黃鈺舒 on 2021/7/5.
//  Copyright © 2021 黃鈺舒. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>     /* provide functions about string, ex: `bzero()`, `strlen()`*/
#include <sys/types.h>  /* contains a number of basic derived types */
#include <sys/socket.h> /* provide functions and data structures of socket */
#include <arpa/inet.h>  /* convert internet address and dotted-decimal notation */
#include <netinet/in.h> /* provide constants and structures needed for internet domain addresses*/
#include <unistd.h>     /* `read()` and `write()` functions */

#define MAX_SIZE 2048
#define PORT 8888

int main (int argc , char **argv) {
  int cli_fd;                   // descriptor of client, used by `socket()`
  struct sockaddr_in svr_addr;  // address of server, used by `connect()`

  int read_bytes;               // number of bytes, return by `read()`
  char buf[MAX_SIZE];           // buffer to store msg

  /* 1) Create the socket, use `socket()`
        AF_INET: IPv4
        SOCK_STREAM: Stream Socket (TCP)
  */
  cli_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (cli_fd < 0) {
    perror("Create socket failed.");
    exit(1);
  }

  /* 2) Connect to server with prepared sockaddr_in structure */
  bzero(&svr_addr, sizeof(svr_addr));
  svr_addr.sin_family = AF_INET;
  svr_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  svr_addr.sin_port = htons(PORT);

  if (connect(cli_fd, (struct sockaddr *)&svr_addr, sizeof(svr_addr)) < 0) {
    perror("Connect failed");
    exit(1);
  }
  printf("Server connected\n");

  /* Handle message, read current from the server */
  read_bytes = read(cli_fd, buf, sizeof(buf));//read server傳送過來的訊息
  if (read_bytes < 0) {
    perror("Read failed");
    exit(1);
  }
  buf[read_bytes] = '\0';
  printf("Server datetimes: %s\n", buf);
  
  char fromclient[] = {"Hi there, it is from client~"};
  char fromclient2[] = {"my studentID : 106062304"};
  char fromclient3[] = {"finish lab3~"};
  char fromserver[100] = {};
  
  send(cli_fd,fromclient,sizeof(fromclient),0);//傳送hi there
  recv(cli_fd,fromserver,sizeof(fromserver),0);//接收server
  
  printf("%s\n",fromclient);
  printf("Server returns : %s\n\n",fromserver);//再印出
  
  
  send(cli_fd,fromclient2,sizeof(fromclient2),0);//傳送(成功
  
  
  recv(cli_fd,fromserver,sizeof(fromserver),0);//再接收server
  printf("%s\n",fromclient2);
  printf("Server returns : %s\n\n",fromserver);//再印出
  
  send(cli_fd,fromclient3,sizeof(fromclient3),0);//傳送(成功
  
  
  recv(cli_fd,fromserver,sizeof(fromserver),0);//再接收server
  printf("%s\n",fromclient3);
  printf("Server returns : %s\n\n",fromserver);//再印出
  
  
  
  printf("\n");
  close(cli_fd);

  return 0;
}
