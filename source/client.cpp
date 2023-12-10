#include "includes.hpp"

int main(int argc, char** argv){
    SOCKET clientSocket;
    int port = 55555;
    WSADATA wsaData;
    int wsaerr;

    WORD wVersionRequest = MAKEWORD(2, 2);
    wsaerr = WSAStartup(wVersionRequest, &wsaData);

    if(wsaerr != 0){
        std::cout << "The Winsock dll not found" << std::endl;
        return 0;
    }else{
        std::cout << "The Winsock dll found" << std::endl;
        std::cout << "The status: " << wsaData.szSystemStatus << std::endl;
    }

    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(clientSocket == INVALID_SOCKET){
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
    }else{
        std::cout << "socket() is OK" << std::endl;
    }

    sockaddr_in clientService;
    clientService.sin_family = AF_INET;

    InetPton(AF_INET, _T("127.0.0.1"), &clientService.sin_addr.s_addr);
    clientService.sin_port = htons(port);

    if(connect(clientSocket, (SOCKADDR*)&clientService, sizeof(clientService)) == SOCKET_ERROR){
        std::cout << "Client: connect() - failed to connetct" << std::endl;
        WSACleanup();
        return 0;
    }else{
        std::cout << "Client: connect() is OK." << std::endl;
        std::cout << "Client: Can start sending and receiving data..." << std::endl;
    }
    system("pause");
    WSACleanup();
    return 0;
}