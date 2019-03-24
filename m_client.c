#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

#include <arpa/inet.h>
 
int main(void)
{
  int sockfd = 0,n = 0,num=0;
  char recvBuff[1024];
  char sendBuff[1025];

 if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
	    {
	      printf("\n Error : Could not create socket \n");
	      return 1;
	    }
	   

struct sockaddr_in serv_addr;
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(5000);//assign the port number
serv_addr.sin_addr.s_addr =  INADDR_ANY;//

 if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))==-1)
   		  {
		      printf("\n Error : Connect Failed \n");
		      return 1;
		  }
	
	printf("Please enter the expression to be evaluated:\n");
	
        fgets(sendBuff,1025,stdin);

                if ((send(sockfd,sendBuff,strlen(sendBuff),0))== -1) 
                {
                     fprintf(stderr, "Failure Sending Message\n");
                     close(sockfd);
                }

                
                 num = recv(sockfd, recvBuff, sizeof(recvBuff),0);
                if ( num <= 0 )
                {
                        printf("Either Connection Closed or Error\n");
                       
                }

                puts(recvBuff);

		 close(sockfd); 
     
  return 0;
}
