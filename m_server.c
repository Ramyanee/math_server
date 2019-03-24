#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <string.h>
#include<time.h>


int main(void)
{	

int x,y,r;
  int listenfd = 0,connfd = 0,num;
  struct sockaddr_in serv_addr;
  struct sockaddr_in serverStorage;
  socklen_t addr_size;

  serv_addr.sin_family = AF_INET;    
  serv_addr.sin_addr.s_addr = INADDR_ANY; 
  serv_addr.sin_port = htons(5000);    

  char sendBuff[1025];
  char recvBuff[1024];  
  

	//listenfd is tge server socket
	//connfd is the client socket



  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("socket retrieve success\n");
  
  memset(&serv_addr, '0', sizeof(serv_addr));
  memset(sendBuff, '0', sizeof(sendBuff));
      
  
  bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
  
  if(listen(listenfd, 10) == -1){
      printf("Failed to listen\n");
      return -1;
  }
  
  
  while(1)
    {	
	addr_size = sizeof serverStorage;
      
        connfd = accept(listenfd,NULL,NULL);


	num = recv(connfd, recvBuff, sizeof(recvBuff),0);
                if ( num <= 0 )
                {
                        printf("Either Connection Closed or Error\n");
                       
                }

                recvBuff[num] = '\0';

		char exp[num];
		strcpy(exp,recvBuff);
		puts(exp);
                
                

		
		x=atoi(exp[0]);
		y=atoi(exp[2]);

		printf("x=%d y=%d",x,y);

		
                if(exp[1]=='+')
                  {     
			r=x+y;
                   }
		else if(exp[1]=='-')
                  {

			r=x-y;
                   }
		else if(exp[1]=='*')
                  {
                        r=x*y;
                   }
		else if(exp[1]=='/')
                  {
                       r=x/y;
                   }


   

		printf("\n\nRESULT=");
                printf("%d",r);
                sprintf(sendBuff,"%d %c %d = %d\n",x,exp[1],y,r);
		printf("%s\n",sendBuff);
		if ((send(connfd,sendBuff,strlen(sendBuff),0))== -1) 
                {
                     fprintf(stderr, "Failure Sending Message\n");
                     close(connfd);
                }

		

       
      close(connfd); //Close Connection Socket   
      sleep(1);
    } //End of Inner While...
 
 
  return 0;
}
