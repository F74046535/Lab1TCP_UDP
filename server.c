#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
void append(char *s,char c)
{
    int len=strlen(s);
    s[len]=c;
    s[len+1]='\0';
}
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
    forClientsock=accept(sockfd,(struct sockaddr *)&clientInfo,&addrlen);

   if(strcmp(argv[2],"recv")==0)
   {
    while(1)
    {
        //forClientsock=accept(sockfd,(struct sockaddr *)&clientInfo,&addrlen);
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
       if(check[0]=='j'||check[0]=='m'||check[0]=='p')
       {
        long int size;
        read(forClientsock,&size,sizeof(size));
        printf("reading picture byte array");
        char p_array[size];
        read(forClientsock,p_array,size);
        FILE *img;
        img=fopen("c1","w");
        fwrite(p_array,1,sizeof(p_array),img);
        printf("the file is received sucessfully\n");
        printf("the new file created is c1");
        fclose(img);
       }
    }
   }
   if(strcmp(argv[2],"send")==0)
   {
         char ch;
         FILE *f;
         int count=0;
         char filename[100];
         strcpy(filename,argv[5]);
         printf("%s\n",filename);
         int i=0;
         char buffer[10000];
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
             int a=write(forClientsock,check,2);
          while((ch=fgetc(f))!=EOF)
          {
              append(buffer,ch);
          }
         printf("%s",buffer);
         fclose(f);
         int n=write(forClientsock,buffer,10000);
         if(n<0)
         {
             printf("error to write");
         }
         printf("the file is sent sucessfully");
         }
         if(filename[count]=='j'||filename[count]=='m'||filename[count]=='p')
         {
             char check_t[2]="j";
             int b=write(forClientsock,check_t,2);
             long int size;
             fseek(f,0,SEEK_END);
             size=ftell(f);
             fseek(f,0,SEEK_SET);
             write(forClientsock,&size,sizeof(size));
             char send_buffer[size];
             while(!feof(f))
             {
                 fread(send_buffer,1,sizeof(send_buffer),f);
                 write(forClientsock,send_buffer,sizeof(send_buffer));
                 bzero(send_buffer,sizeof(send_buffer));
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
      //while(1)
      //{
          socklen_t peerlen;
          peerlen=sizeof(servaddr);
          char checku[2];
          int e=recvfrom(socku,checku,2,0,(struct sockaddr *)&servaddr,&peerlen);
          if(e<0)
          {
              printf("read error\n");
          }
          //printf("%s\n",checku);
         if(checku[0]=='t')
         {
             printf("yh\n");
          int nu=recvfrom(socku,bufferu,10000,0,(struct sockaddr *)&servaddr,&peerlen);
                  if(nu==-1)
                  {
                      printf("fail to recv");
                  }
           FILE *f;
           f=fopen("add2.txt","w");
          fprintf(f,"%s",bufferu);
          fclose(f);
         }
         if(checku[0]=='m'||checku[0]=='j'||checku[0]=='p')
         {
             printf("ok\n");
             long int sizeu;
             //read(socku,&sizeu,sizeof(sizeu));
             int w=recvfrom(socku,&sizeu,sizeof(sizeu),0,(struct sockaddr *)&servaddr,&peerlen);
             printf("reading picture byte array\n");
             printf("%1d\n",sizeu);
             char p_arrayu[sizeu];
             char p_arrayuu[sizeu];
             int bbc;
            //while(1)
            //{
             for(bbc=0;bbc<4;bbc++)
             {
                int v=recvfrom(socku,p_arrayu,60000,0,(struct sockaddr *)&servaddr,&peerlen);
                //v=recv(socku,p_arrayu,300000,0);
                int i=0;
                for(i=0;i<60000;i++)
                {
                    p_arrayuu[i+bbc*60000]=p_arrayu[i];
                }
                printf("%d\n",v);
             }
             int j;
             //for(j=0;j<20;j++)
             //{
                 //printf("%x",p_arrayu[j]);
             //}
             FILE*imgu;
             imgu=fopen("c1","w");
             fwrite(p_arrayuu,1,sizeof(p_arrayuu),imgu);
             printf("the file is send sucessfully\n");
             printf("the new file create is c1");
             fclose(imgu);
            //}
          }

      //}
     }
     if(strcmp(argv[2],"send")==0)
     {
         FILE *fp;
         char filename_u[100];
         strcpy(filename_u,argv[5]);
         int count_u=0;
         int iu=0;
         while(iu<100)
         {
             count_u++;
             if(filename_u[iu]=='.')
             {
                 break;
             }
             iu++;
         }
         fp=fopen(filename_u,"r");
       if(filename_u[count_u]=='t')
       {
           char checku[2]="t";
           char ch;
           int c=sendto(socku,checku,2,0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr));
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
       if(filename_u[count_u]=='m'||filename_u[count_u]=='j'||filename_u[count_u]=='p')
       {
           printf("yes");
           char checku_t[2]="j";
           int d=sendto(socku,checku_t,2,0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr));
           printf("%d\n",d);
           int sizeu;
           fseek(fp,0,SEEK_END);
           sizeu=ftell(fp);
           printf("%d\n",sizeu);
           fseek(fp,0,SEEK_SET);
           int g=sendto(socku,&sizeu,sizeof(sizeu),0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr));
           char send_bufferu[sizeu];
           while(!feof(fp))
           {
               bzero(send_bufferu,sizeof(send_bufferu));
               int ret=fread(send_bufferu,1,sizeu,fp);
               int bbc;
               int chat=0;
               while(sizeu>0)
               {
                   sizeu-=60000;
                   chat++;
               }
               int o;
               while(ret>0)
               {
                   ret=fread(send_bufferu,1,sizeu,fp);
                   printf("%d\n",ret);
                   for(bbc=0;bbc<chat;bbc++)
                   {
                       char send_bufferuu[60000];
                       int i;
                       for(i=0;i<60000;i++)
                       {
                           send_bufferuu[i]=send_bufferu[i+bbc*60000];
                       }
                     o=sendto(socku,send_bufferuu,60000,0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr));
                     printf("%d\n",o);
                   }
                   if(o<0)
                   {
                       printf("error");
                   }
               }
          }
           fclose(fp);
        FILE*op;
        op=fopen("c2.jpg","w");
        fwrite(send_bufferu,1,30000,op);
        fclose(op);
     }
    }
  }
}
