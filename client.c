#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>
#include<math.h>
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
    if(filename[count]=='j'||filename[count]=='m'||filename[count]=='p')
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
    if(strcmp(argv[2],"recv")==0)
    {
       while(1)
       {
         char buffer[10000];
         char check[2];
         int m=read(sockfd,check,2);
         if(check[0]=='t')
         {
             FILE *fp;
             int n=read(sockfd,buffer,10000);
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
            read(sockfd,&size,sizeof(size));
            printf("read picture byte array");
            char p_array[size];
            read(sockfd,p_array,size);
            FILE *img;
            img=fopen("c1","w");
            fwrite(p_array,1,sizeof(p_array),img);
            printf("the file is received sucessfully\n");
            printf("the new file create is c1\n");
            fclose(img);
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
               printf("fail to create udp socket");
       //printf("%d\n",socku);
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
      if(filename_u[count_u]=='p'||filename_u[count_u]=='m'||filename_u[count_u]=='j')
       {
           printf("yes\n");
           char checku_t[2]="j";
           int d=sendto(socku,checku_t,2,0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr));
           //printf("%d\n",d);
           int sizeu;
           fseek(fp,0,SEEK_END);
           sizeu=ftell(fp);
           printf("%d\n",sizeu);
           fseek(fp,0,SEEK_SET);
           //write(socku,&sizeu,sizeof(sizeu));
           int g=sendto(socku,&sizeu,sizeof(sizeu),0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr));
           char send_bufferu[sizeu];
           //send_bufferu=(char*)malloc(sizeu);
           while(!feof(fp))
           {
               //int ret=fread(send_bufferu,1,sizeu,fp);
               //int o=sendto(socku,send_bufferu,strlen(send_bufferu)+1,0,(struct sockaddr *)&servaddr,sizeof(struct sockaddr));
               //int o=send(socku,send_bufferu,ret,0);
               //printf("%d\n",o);
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
                  //while(sizeu>0)
                  //{
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
                   //printf("%d\n",o);
                   if(o<0)
                    {
                        printf("erroe");
                    }
                  //}
               }
           }
           fclose(fp);
          // printf("%hd\n",send_bufferu[5]);
           FILE *op;
           op=fopen("c2.jpg","w");
           fwrite(send_bufferu,1,30000,op);
           fclose(op);
           
       }   

      }
      if(strcmp(argv[2],"recv")==0)
      {
         
          socklen_t peerlen;
          peerlen=sizeof(servaddr);
          char checku[2];
          int e=recvfrom(socku,checku,2,0,(struct sockaddr *)&servaddr,&peerlen);
          printf("%s\n",checku);
          if(e<0)
          {
              printf("read error");
          }
          printf("yy\n");
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
          if(checku[0]=='j'||checku[0]=='m'||checku[0]=='p')
          {
              printf("ok\n");
              long int sizeu;
              int w=recvfrom(socku,&sizeu,sizeof(sizeu),0,(struct sockaddr *)&servaddr,&peerlen);
              printf("read picture in byte array\n");
              printf("%1d\n",sizeu);
              char p_arrayu[sizeu];
              char p_arrayuu[sizeu];
              int bbc;
              for(bbc=0;bbc<4;bbc++)
              {
                  int v=recvfrom(socku,p_arrayu,60000,0,(struct sockaddr *)&servaddr,&peerlen);
                  int i=0;
                  for(i=0;i<60000;i++)
                  {
                      p_arrayuu[i+bbc*60000]=p_arrayu[i];
                  }
                  printf("%d\n",v);
              }
             FILE *imgu;
             imgu=fopen("c1","w");
             fwrite(p_arrayuu,1,sizeof(p_arrayuu),imgu);
             printf("the file is sent sucessfully");
             printf("the new file create is c1");
             fclose(imgu);
          }
       }
   }
}

