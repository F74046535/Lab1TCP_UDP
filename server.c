#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
int main(int argc,char *argv[])
{
    char type[10];
    strcpy(type,argv[1]);
    char role[10];
    strcpy(role,argv[2]);
  if(strcmp(argv[1],"tcp")==0)
  {
    int sockfd=0,forClientsock=0;
    sockfd=socket(AF_INET,SOCK_STREAM,0);

    if(sockfd==-1)
    {
        printf("Fail to create a socket");
    }
    struct sockaddr_in serverInfo,clientInfo;
    int addrlen=sizeof(clientInfo);
    bzero(&serverInfo,sizeof(serverInfo));
    serverInfo.sin_family=PF_INET;
    serverInfo.sin_addr.s_addr=INADDR_ANY;
    serverInfo.sin_port=htons(atoi(argv[4]));
    int check=bind(sockfd,(struct sockaddr *)&serverInfo,sizeof(serverInfo));
    if(check<0)
    {
        printf("error on binding\n");
    }
    listen(sockfd,5);
   if(strcmp(argv[2],"recv")==0)
   {
    while(1)
    {
        forClientsock=accept(sockfd,(struct sockaddr *)&clientInfo,&addrlen);
        char buffer[10000];
        char check[2];
        int m=read(forClientsock,check,2);
        if(check[0]=='t')
        {
           FILE *fp;
           int n=read(forClientsock,buffer,10000);
           if(n<0)
           {
             printf("error in read txt");
           }
          printf("%c\n",buffer[17]);
          fp=fopen("add1.txt","w");
          int i;
          fprintf(fp,"%s",buffer);
          fclose(fp);
          printf("the new file create is add1.txt");
        }
       if(check[0]=='j')
       {
        long int size;
        read(forClientsock,&size,sizeof(size));
        printf("reading picture byte array");
        char p_array[size];
        read(forClientsock,p_array,size);
        FILE *img;
        img=fopen("c1.jpg","w");
        fwrite(p_array,1,sizeof(p_array),img);
        printf("the file is received sucessfully\n");
        printf("the new file created is c1.jpg");
        fclose(img);
       }
    }
   }
  }
  if(strcmp(argv[1],"udp")==0)
  {
      int socku;
      char bufferu[10000];
      if((socku=socket(PF_INET,SOCK_DGRAM,0))<0)
          printf("udp socket fails");
      struct sockaddr_in servaddr;
      memset(&servaddr,0,sizeof(servaddr));
      servaddr.sin_family=AF_INET;
      servaddr.sin_port=htons(atoi(argv[4]));
      servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
      if(bind(socku,(struct sockaddr *)&servaddr,sizeof(servaddr))<0)
          printf("bind error");
     if(strcmp(argv[2],"recv")==0)
     {
      while(1)
      {
          socklen_t peerlen;
          peerlen=sizeof(servaddr);
          int nu=recvfrom(socku,bufferu,10000,0,(struct servaddr *)&servaddr,&peerlen);
                  if(nu==-1)
                  {
                      printf("fail to recv");
                  }
           FILE *f;
           f=fopen("add2.txt","w");
          fprintf(f,"%s",bufferu);
          fclose(f);
      }
     }
  }
}
