#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
void append(char *s ,char c)
{
    int len=strlen(s);
    s[len]=c;
    s[len+1]='\0';
}
int main(int argc,char *argv[])
{
    char type[10];
    strcpy(type,argv[1]);
   if(type[0]=='t')
   {
    int sockfd=0;
    char ip[30];
    printf("ok\n");
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd==-1)
    {
        printf("fail to create a socket");
    }
    struct sockaddr_in info;
    bzero(&info,sizeof(info));
    info.sin_family=PF_INET;
    strcpy(ip,argv[3]);

    info.sin_addr.s_addr=inet_addr(ip);
    //printf("%s\n",ip);
    //info.sin_addr.s_addr=inet_addr("127.0.0.1");
    info.sin_port=htons(atoi(argv[4]));
    //info.sin_port=htons(8700); 
    int err=connect(sockfd,(struct sockaddr*)&info,sizeof(info));
    if(err==-1)
    {
         printf("Connection error\n");
    }
    printf("ok\n");
    char buffer[10000];
    int i=0;
    char ch;
    FILE *f;
    char filename[100];
    strcpy(filename,argv[5]);
    printf("%s\n",filename);
    f=fopen(filename,"r");
    
    while((ch=fgetc(f))!=EOF)
    {
        append(buffer,ch);
        //printf("%c\n",ch);
    }
    printf("%s",buffer);
    //fscanf(f,"%s",buffer);
   // while(!feof(f))
     //if(fgets(buffer,100,f)!=NULL);printf("%s",buffer);
    fclose(f);
    int n=write(sockfd,buffer,10000);
    if(n<0)
    {
        printf("error to write");
    }
    printf("the file is sent sucessfully");
   }
   if(type[0]=='u')
   {
       int socku;
       if((socku=socket(PF_INET,SOCK_DGRAM,0))<0)
               printf("fail to greate udp socket");
       struct sockaddr_in servaddr;
       memset(&servaddr,0,sizeof(servaddr));
       servaddr.sin_family=AF_INET;
       servaddr.sin_port=htons(atoi(argv[4]));
       char uip[30];
       strcpy(uip,argv[3]);
       servaddr.sin_addr.s_addr=inet_addr(uip);
       int ret;
   }
}

