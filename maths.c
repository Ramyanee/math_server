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
  int listenfd = 0,connfd = 0,n=0,num=0; 
  struct sockaddr_in serv_addr;
 
  
  char sendBuff[1025];
  char recvBuff[1024];  
 
  int new,x,y,r;
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  printf("socket retrieve success\n");
  

      
  serv_addr.sin_family = AF_INET;    
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); 
  serv_addr.sin_port = htons(5000);    
 
  bind(listenfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
  
  if(listen(listenfd, 10) == -1){
      printf("Failed to listen\n");
      return -1;
  }
   

  
  while(1)
    {	
      
        connfd = accept(listenfd,NULL,NULL);	  // accept awaiting request



  



	num = recv(connfd, recvBuff, sizeof(recvBuff),0);
                if ( num <= 0 )
                {
                        printf("Either Connection Closed or Error\n");
                       
                }

                recvBuff[num] = '\0';
              
                char exp[num];
		strcpy(exp,recvBuff);
		puts(exp);

		char n[num];
		
			n[0]=exp[0];
			n[1]='\0'; 
			x=atoi(n);
			n[0]='\0';
			n[0]=exp[2];
			n[1]='\0';
			y=atoi(n);

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
