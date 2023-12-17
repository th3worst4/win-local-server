#include "includes.hpp"

int main(int argc, char** argv){
    SOCKET serverSocket, acceptSocket;
    int port = 55555;
    WSADATA wsaData;
    int wsaerr;
    WORD wVersionRequested = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequested, &wsaData);
    if(wsaerr != 0){
        std::cout << "The Winsock dll not found" << std::endl;
        return 0;
    }

    serverSocket = INVALID_SOCKET;
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(serverSocket == INVALID_SOCKET){
        std::cout << "Error at socket()" << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }

    sockaddr_in service;
    service.sin_family = AF_INET;
    InetPton(AF_INET, _T("127.0.0.1"), &service.sin_addr.s_addr);
    service.sin_port = htons(port);

    if(bind(serverSocket, (SOCKADDR*)&service, sizeof(service)) == SOCKET_ERROR){
        std::cout << "bind() failed" << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 0;
    }

    if(listen(serverSocket, 1) == SOCKET_ERROR)
        std::cout << "listen(): Error listening on socket" << WSAGetLastError() << std::endl;
    else
        std::cout << "I'm waiting for connections" << std::endl;

    fd_set master;
    FD_ZERO(&master);
    FD_SET(serverSocket, &master);

    bool running = 1;
    std::string welcomeMsg = "Welcome\r\n";

    while(running){
        fd_set copy = master;
        int socketCout = select(0, &copy, nullptr, nullptr, nullptr);

        for(int i = 0; i < socketCout; i++){
            SOCKET sock = copy.fd_array[i];
            if(sock == serverSocket){
                SOCKET client = accept(serverSocket, nullptr, nullptr);
                FD_SET(client, &master);
                send(client, welcomeMsg.c_str(), welcomeMsg.size() + 1, 0);
                std::ostringstream logreg;
                logreg << sock;
                std::cout << logreg.str() << " is connected\n";
            }else{
                char buf[4096];
                ZeroMemory(buf, 4096);

                int bytesIn = recv(sock, buf, 4096, 0);

                if(bytesIn <= 0){
                    closesocket(sock);
                    FD_CLR(sock, &master);
                }else{
                    for(int i = 0; i < master.fd_count; i++){
                        SOCKET outSock = master.fd_array[i];
                        if(outSock != serverSocket && outSock != sock){
                            std::ostringstream ss;
                            ss << "SOCKET #" << sock << ": " << buf;
                            std::string strOut = ss.str();

                            send(outSock, strOut.c_str(), strOut.size() + 1, 0);
                        }
                    }
                }
            }
        }
    }

    FD_CLR(serverSocket, &master);
    closesocket(serverSocket);

    std::string msg = "Server is shutting down.\r\n";

    while(master.fd_count > 0){
        SOCKET sock = master.fd_array[0];

        send(sock, msg.c_str(), msg.size() + 1, 0);

        FD_CLR(sock, &master);
        closesocket(sock);
    }

    WSACleanup();
    return 0;
}