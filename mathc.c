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
  

	
	int condition=1;
while(condition){

struct sockaddr_in serv_addr;

  if((sockfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
    {
      printf("\n Error : Could not create socket \n");
      return 1;
    }
 
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(5000);//assign the port number
  serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");//assign a the ip address of server
 

	 if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
   		 {
		      printf("\n Error : Connect Failed \n");
		      return 1;
		  }
	
	printf("Please enter the exp:\n");
	
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

                recvBuff[num] = '\0';
		puts(recvBuff);
		
		printf("enter 1 to continue and 0 to exit\n");
		scanf("%d",&condition);
		getchar();
	
		 close(sockfd); 
}
               // printf("Client:Message Received From Server -  %s\n",recvBuff);
           

  return 0;
}
