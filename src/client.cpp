#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

int main(){
    //1.
    int cfd=socket(AF_INET, SOCK_STREAM, 0);
    if(cfd==-1){
        perror("socket");
    }

    //2.lianjei 
    struct sockaddr_in addr;
    addr.sin_family=AF_INET;
    addr.sin_port=htons(8989);
    addr.sin_addr.s_addr=INADDR_ANY;  // 0.0.0.0  表示绑定本地所有的ip地址
    inet_pton(AF_INET, "192.168.102.129", &addr.sin_addr.s_addr);
    int ret=connect(cfd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret==-1){
        perror("connect");
        exit(0);
    }
    int num=0;
    while (1) {
        //发送
        char buf[1024];
        sprintf(buf, "hello,world, %d,......",num++);
        send(cfd, buf, strlen(buf)+1, 0);

        memset(buf, 0,sizeof(buf));
        int len=recv(cfd, buf, sizeof(buf),0);
        if(len==0){
            printf("服务器已经断开连接...\n");
            break;
        }else if (len>0) {
            printf("recv buf: %s\n",buf);
        }else{
            perror("recv");
            break;
        }

        sleep(1);
    }

    close(cfd);

    return 0;
}