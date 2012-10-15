#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 

// ------------------------------------------------------------
// 
// 
void error(const char *msg)
{
    perror(msg);
    exit(0);
}

// ------------------------------------------------------------
//          GET a Beluga code from infchg.appspot.com
// 
int main(int argc, char *argv[])
{
    int sockfd, portn, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
	char buf[256]="GET / HTTP/1.0\r\n\r\n";  // "sss" for sending wrong method
										      // GET / HTTP/1.0\r\n\r\n for index page
    if (argc < 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       exit(0);
    }
    //portn = atoi(argv[2]);
	portn = 80;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    // erver = gethostbyname(argv[1]);
    server = gethostbyname("infchg.appspot.com"); 
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr, 
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(portn);
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    //printf("sending-message: ");
    bzero(buffer,256);
    //fgets(buffer,255,stdin);
    // jua: buffer-> buf
    n = write(sockfd,buf,strlen(buf));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    n = read(sockfd,buffer,255);
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%s\n",buffer);
    close(sockfd);
    return 0;
}

// ------------------------------------------------------------
/* example, when sending sss instead of the valid GET method we receive:
<!DOCTYPE HTML PUBLIC "-//IETF//DTD HTML 2.0//EN">
<html><head>
<title>501 Method Not Implemented</title>
</head><body>
<h1>Method Not Implemented</h1>
<p>sss to /index.dhtml not supported.<br />
</p>
</body></html>
*/ 

// ------------------------------------------------------------
/* when sending the right GET to infchg.appspot.com we get the graph page:
HTTP/1.1 200 OK
Date: Mon, 15 Oct 2012 14:01:15 GMT
Server: Apache
Last-Modified: Mon, 15 Oct 2012 14:01:15 GMT
ETag: W/"2be85-866-4cc197883e0c0"
Accept-Ranges: bytes
Content-Length: 2150
Cache-Control: max-age=0, no-store
Connection: close
....
*/
