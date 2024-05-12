#include <iostream>
#include <arpa/inet.h>
//网络通信，IP和端口都是大端模式
//通常IP地址的使用是字符串形式，端口是整数形式
// host to network unsigned short
uint16_t htons(uint16_t hostshort); //端口
uint32_t htonl(uint32_t hostlong); //IP

// network to host unsigned short
uint16_t ntohs(uint16_t netshort);
uint32_t ntohl(uint32_t netlong);

// inet_pton() 字符串ip转换为整数ip
// inet_ntop() 整数ip转换为字符串ip
// int inet_net_pton(int af, const char *cp, void *buf)
// af : 地址族，AF_INET, AF_INET6  src : 字符串ip地址  dst : 存放转换后的整数ip地址  返回值：成功返回1，失败返回0
// const char *inet_net_ntop(int af, const void *cp, char *buf, socklen_t len);
// af : 地址族，AF_INET, AF_INET6  src : 整数ip地址  dst : 存放转换后的字符串ip地址  len : dst的大小 返回值：成功返回dst地址，失败返回NULL
int main() {

    int socket(int domain, int type, int protocol);
        /*  domain  AF_INET ipv4    AF_INET6 ipv6
            type    SOCK_STREAM TCP    SOCK_DGRAM UDP 
            protocol 0 默认协议    
            返回值：成功返回套接字描述符，失败返回-1
        */
    struct sockaddr_in addr;//用这个做初始化，然后做类型转换 内存是一样大的
    int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
        /*
            将监听套接字好额本地ip和端口进行关联
            sockfd  套接字描述符
            addr    本地ip地址和端口信息的结构体
            addrlen 记录第二个参数指针指向的内存大小
            返回值：成功返回0，失败返回-1

            struct sockaddr
                __SOCKADDR_COMMON (sa_);  地址协议族v4 v6
                char sa_data[14];		  端口2B+IP4B+填充8B
        */
    int listen(int sockfd, int backlog);
    /*
        backlog 指可以同时检测的连接数 最大值128
        成功返回0 失败-1
    */
    int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
    /*
        等待并接受客户端连接 阻塞函数 没有客户端连接则堵塞
        读缓冲区有数据就解除阻塞 -> 连接建立
        返回一个通信的文件描述符
        addr 传出参数 保存了建立连接的客户端地址信息
    */
    ssize_t read (int sockfd, void *buf, size_t len);
    ssize_t recv (int sockfd, void *buf, size_t len, int flags);
    /*
        socketfd    accept返回值（服务器端）
                    通过socket函数创建得到的，通过connect初始化链接（客户端）
        buf         存储接受的数据 来自于文件描述符的读缓冲区
        len         buf对应的内存容量
        flag        一般为0
    */
    ssize_t write(int sockfd, const void *buf, size_t len);
    ssize_t send (int sockfd, const void *buf, size_t len, int flags);
    /*
        socketfd    accept返回值（服务器端）
                    通过socket函数创建得到的，通过connect初始化链接（客户端）
        buf         要发送的数据 数据进入通信文件描述符写缓冲区
        len         发送数据的实际长度 strlen()
        flag        一般为0
    */
    int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
    /*
        客户端来连接服务器
        sockfd  通信文件描述符 socket()获得
        addr    连接的服务器IP和端口
        addrlen addr指向内存的大小
        成功返回0 失败-1
    */
    int close(int sockfd);
    int shutdown(int sockfd, int how);
    std::cout << "hello world!" << std::endl;
    return 0;
}
