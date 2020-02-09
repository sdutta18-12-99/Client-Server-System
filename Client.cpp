#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include<iostream>
#include<fstream>
using namespace std;
   
int main(int argc, char const *argv[])
{
    int sock = 0;
    long valread;
    int port_num;
    char ip_addr[10];
    cout<<"Enter the IP address of the server: "<<endl;
    cin>>ip_addr;
    cout<<"Enter the port number of the server: "<<endl;
    cin>>port_num;
    struct sockaddr_in serv_addr;
    //char filename[10];
    char filename[10];
    cout<<"IP Address: "<<ip_addr<<"     "<<"Port Number: "<<port_num<<endl;
    char buffer[1024];
    for(int i=0;i<1024;i++)
    {
        buffer[i]=0;
    }
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)//SOCK_STREAM implies usage of TCP protocol. and AF_INET implies IPv4.
    {
        cout<<"Socket Creation Error"<<endl;
        return -1;
    }
    //The above piece of code tries to create a socket on the client to hear from the server.
    serv_addr.sin_family = AF_INET;//Program to use IPv4
    serv_addr.sin_port = htons(port_num);
       
    // Convert IPv4 and IPv6 addresses from text to binary form
    if(inet_pton(AF_INET, ip_addr , &serv_addr.sin_addr)<=0)
    {
        cout<<"Invalid Address"<<endl;
        return -1;
    }
    //The above piece of code checks whether the address is valid.
   
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        cout<<"Connect status: "<<"fail"<<endl;
        return -1;
    }
    else
    {
        cout<<"Connect status: "<<"success"<<endl;
    }
    //The above if/else condition tells us whether the connection has been established between client and server.
    int x1=1;
    while(x1)//while loop for the client to request multiple files from the server
    {
    cout<<"Input the filename to be requested from the server: ";
    cin>>filename;
    if(strncmp(filename,"exit",4)==0)
    {
        x1=0;
    }//to check if the user enters exit. If so, exits the while loop.
    cout<<endl;
    long x=send(sock , filename , strlen(filename) , 0 );//sends the name of the file to the server.
    if(x>0)
    {
        cout<<"Send status: "<<"success"<<endl;
    }
    else
    {
        cout<<"Send status: "<<"fail"<<endl;
    }
    //checks whether the program has been able to successfully send the name of the file.
    ofstream fout;
    fout.open("data.txt");//opens the file data.txt for entering the recieved details to the file.
    if(fout.is_open())
    {
        cout<<"Open file status: "<<"success"<<endl;
    }
    else
    {
        cout<<"Open file status: "<<"fail"<<endl;
    }
    //checks whether the file has been opened.
    recv(sock,buffer,1024,0);//program receives content from the server.
    cout<<"Received text: ";
    while(strlen(buffer)>0)
    {
        cout<<buffer<<endl;//displays received text.
        fout<<buffer<<endl;//inputs received text to the opened file.
        recv(sock,buffer,1024,0);//reads again.
    }
    cout<<endl;
    cout<<"Save text status: "<<"success"<<endl;
    fout.close();//closes the ofstream object.
    }
    return 0;
}

