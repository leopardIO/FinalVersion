/*************************************************************************
	> File Name: main.cpp
	> Author: cooperz
	> Mail: zbzcsn@qq.com
	> Created Time: Sat 08 Aug 2015 08:14:28 PM UTC
 ************************************************************************/

#include<iostream>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netdb.h>
#include<stdlib.h>
#include<string.h>
//#include<netinet/in.h>
#include<arpa/inet.h>

#include"ProInnerMessage.pb.h"

#define SERV_PORT 6002
#define PIC_LEN 36124
using namespace std;

int connectNodeServer()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    connect(sockfd, (sockaddr*)&servaddr, sizeof(servaddr));
    return sockfd;
}

int main(int argn, char** argv)
{
    int fd = open( "./test.jpg", O_RDONLY); 
    char* buf = (char*)malloc(36124); 
    int n = read( fd, buf, 36124);
    printf("read from file : %d\n", n ); 
    int netfd = connectNodeServer();
    leopardIO::ProInnerMessage inner_msg;
    inner_msg.set_content_length(PIC_LEN);
    inner_msg.set_end_time(0.0);
    inner_msg.set_start_time(0.0);
    inner_msg.set_content_type(1);
    inner_msg.set_message_type(1);
    inner_msg.set_session_id(1);
    size_t protobuf_len = inner_msg.ByteSize();
    void* protobuf_buf = malloc(protobuf_len);
    inner_msg.SerializeToArray(protobuf_buf,protobuf_len);
    int len1 = write(netfd, &protobuf_len, sizeof(protobuf_len));
    int len2 = write(netfd, protobuf_buf, protobuf_len);
    int len3 = write(netfd, buf, n);
    cout<<"发送成功: proto len ="<<len1<<endl;
    cout<<"发送成功: protobuf_len ="<<len2<<endl;
    cout<<"发送成功: file len ="<<len3<<endl;
    read(netfd, &protobuf_len, sizeof(protobuf_len));
    read(netfd, protobuf_buf, protobuf_len);
    read(netfd, buf, 17);
    string wakak(buf,17);
    cout<<"发送成功: proto len ="<<len1<<endl;
    cout<<"发送成功: protobuf_len ="<<protobuf_len<<endl;
    cout<<"发送成功: response ="<<wakak<<endl;
    while(1)
    {
        sleep(5);
        cout<<"5s passwd"<<endl;
    }
    return 1;
}
