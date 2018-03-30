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
    printf("start\n");
    char type[10];
    strcpy(type,argv[1]);
   if(strcmp(argv[1],"tcp")==0)
   {
      
    int sockfd=0;
    char ip[30];
    //printf("ok\n");
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
   if(strcmp(argv[2],"send")==0)
   {
    char ch;
    FILE *f;
    int count=0;
    char filename[100];
    strcpy(filename,argv[5]);
    printf("%s\n",filename);
    int i=0;
    while(i<100)
    {
        count++;
        if(filename[i]=='.')
         {
             break;
         }
        i++;
    }
    printf("%d\n",count);
    f=fopen(filename,"r");
    if(filename[count]=='t')
    {
        char check[2]="t";
        int a=write(sockfd,check,2);
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
    if(filename[count]=='j')
    {
        char check_t[2]="j";
        int b=write(sockfd,check_t,2);
        long int size;
        fseek(f,0,SEEK_END);
        size=ftell(f);
        fseek(f,0,SEEK_SET);
        write(sockfd,&size,sizeof(size));
        char send_buffer[size];
        while(!feof(f))
        {
            fread(send_buffer,1,sizeof(send_buffer),f);
            write(sockfd,send_buffer,sizeof(send_buffer));
            bzero(send_buffer,sizeof(send_buffer));
        }
    }

    }
   }
   if(strcmp(argv[1],"udp")==0)
   {
       int socku;
       char bufferu[10000];
       char ch;
       printf("start\n");
       if((socku=socket(PF_INET,SOCK_DGRAM,0))<0)
               printf("fail to greate udp socket");
       struct sockaddr_in servaddr;
       memset(&servaddr,0,sizeof(servaddr));
       servaddr.sin_family=AF_INET;
       servaddr.sin_port=htons(atoi(argv[4]));
       char uip[30];
       strcpy(uip,argv[3]);
       servaddr.sin_addr.s_addr=inet_addr(uip);
      if(strcmp(argv[2],"send")==0)
      {
       FILE*fp;
       char filename_u[100];
       strcpy(filename_u,argv[5]);
       fp=fopen(filename_u,"r");
       while((ch=fgetc(fp))!=EOF)
       {
           append(bufferu,ch);
       }
       fclose(fp);
       while(1)
       {
           int n=sendto(socku,bufferu,strlen(bufferu),0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr));
           if(n==-1)
           {
               printf("send wrong");
               break;
           }
       }
      }

   }
}

