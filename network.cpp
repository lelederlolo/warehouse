#define _WIN32_WINNT 0x0A00

#include <iostream>
//#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib ,"ws2_32.lib")
using namespace std ;

int main(){
    string host = "127.0.0.1" ;
    int port = 8888 ;
    struct sockaddr_in servName ;
    int status ;
    char inData[1024] = {0} ,outData[1024] = {0} ;

    //Strat Socket
    WSADATA data ;
    WORD wordVer = MAKEWORD(2, 2) ;
    int wsResult =WSAStartup(wordVer ,&data) ;
    if(wsResult != 0){
        cerr << "Error : Starting Socket - Err#" << wsResult <<endl ;
        exit(1) ;
    }

    //Create Socket
    SOCKET sock = socket (AF_INET ,SOCK_STREAM ,0) ;
    if(sock = INVALID_SOCKET){
        cerr << "Error : Creating Socket - Err#" << WSAGetLastError() <<endl ;
        exit(1);
    }
    //Server Address 
    servName.sin_family = AF_INET ;
    inet_pton(AF_INET, host, &servName.sin_addr);

    //Connect
    int connResult = connect(sock ,(sockaddr*)&hint ,sizeof(hint)) ;
    if (connResult == SOCKET_ERROR){
        cerr << "Error : Connect - Error#" << WSAGetLastError() <<endl ;
        closesocket(sock) ;
        WSACleanup() ;
        return 0;
    }

    //Send and Receive
    char buf[4096] ;
    string userInput ;
    do{
        getline(cin ,userInput) ;
        if(userInput.size() > 0 ){
            int sendResult = send(sock ,userInput.c_str() ,userInput.size() + 1 ,0) ;
            if(sendResult != SOCKET_ERROR){
                ZeroMemory(buf ,4096) ;
                int bytesReceived =recv(sock ,buf ,4096 ,0) ;
                if(bytesReceived > 0 ){
                    cout << "<SERVER>" << string(buf ,0 ,bytesReceived ) << endl ;
                }
            }
        }
    }while(userInput.size() > 0) ;
    return 0 ;
}