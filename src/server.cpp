#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
    //1.创建监听的套接字
    int lfd=socket(AF_INET, SOCK_STREAM, 0);
    if(lfd==-1){
        perror("socket");
    }

    //2.绑定
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8989);
    addr.sin_addr.s_addr=INADDR_ANY;  // 0.0.0.0  表示绑定本地所有的ip地址
    int ret=bind(lfd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret==-1){
        perror("bind");
        exit(0);
    }

    ret=listen(lfd, 128);
    if(ret==-1){
        perror("listen");
        exit(0);
    }

    struct sockaddr_in cliaddr;
    int clilen=sizeof(cliaddr);
    int cfd=accept(lfd, (struct sockaddr*)&cliaddr, (socklen_t*)&clilen);
    if(cfd==-1){
        perror("accept");
        exit(0);
    }

    while (1) {
        char buf[1024];
        memset(buf, 0,sizeof(buf));
        int len=recv(cfd, buf, sizeof(buf),0);
        if(len==0){
            printf("客户端已经断开连接...\n");
            break;
        }else if (len>0) {
            printf("recv buf: %s\n",buf);
        }else{
            perror("recv");
            break;
        }

        send(cfd, buf, strlen(buf)+1,0);
    }

    close(cfd);
    close(lfd);
    return 0;
}