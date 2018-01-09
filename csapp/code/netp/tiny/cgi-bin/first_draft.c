/*
 * echoclient.c - An echo client
 */
/* $begin echoclientmain */
#include "../csapp.h"

int main() 
{
    int clientfd;
    char *host, *port, buf[MAXLINE];
    rio_t rio;
    /*always needs host and port...as a client. Here, it's choosing to read the host and port from the arguments passed in by the user who called it*/
    /*if (argc != 3) {
	fprintf(stderr, "usage: %s <host> <port>\n", argv[0]);
	exit(0);
	}*/
    host = "www.dunkindonuts.com";
    port = "80";
    /* we specify theh host and port we need!This gives us back a file descriptor which we will read*/
    clientfd = Open_clientfd(host, port);
    /*we need to do a write here - where we send a get command to the server*/
    Rio_readinitb(&rio, clientfd);

    /*Step 1:Fgets -- reads some stuff from the keyboard*/
    while (Fgets(buf, MAXLINE, stdin) != NULL) { /*we probably don't need a while loop*/
      Rio_writen(clientfd, buf, strlen(buf)); /*step 2: send what came from keyboard to the server*/
      Rio_readlineb(&rio, buf, MAXLINE);/*step 3: read from the server - the server's response*/
      Fputs(buf, stdout);/*prints the response to the terminal*/
    }
    Close(clientfd); //line:netp:echoclient:close
    exit(0);
}
/* $end echoclientmain */
