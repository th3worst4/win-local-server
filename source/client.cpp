#include "includes.hpp"

std::mutex m;
bool running = true;

void receivemsg(SOCKET clientSocket, char buf[4096]){ 
    while(running){
        int bytesReceived = recv(clientSocket, buf, 4096, 0);
        if(bytesReceived > 0){
            m.lock();
            std::cout << std::string(buf, 0, bytesReceived) << std::endl;
            ZeroMemory(buf, 4096);
            m.unlock();
        }
    }
}

void sendmsg(SOCKET clientSocket, char buf[4096]){
    while(running){
        std::string userInput;
        getline(std::cin, userInput);
        if(userInput.size() > 0){
            if(userInput[0] == '\\'){
                if(userInput == "\\quit"){
                    std::cout << "quiting the server\n";
                    running = false;
                    continue;
                }
            }
            int sendResult = send(clientSocket, userInput.c_str(), userInput.size() + 1, 0);
            if(sendResult != SOCKET_ERROR){
                ZeroMemory(buf, 4096);
            }
        }
    }
}


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
    }

    clientSocket = INVALID_SOCKET;
    clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if(clientSocket == INVALID_SOCKET){
        std::cout << "Error at socket(): " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 0;
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
        std::cout << "Client: Can start sending and receiving data..." << std::endl;
    }

    char buf[4096];
    std::string userInput;

    int bytesReceived = recv(clientSocket, buf, 4096, 0);
    std::cout << "SERVER> " << std::string(buf, 0, bytesReceived) << std::endl;
    ZeroMemory(buf, 4096);

    std::thread thread1;
    std::thread thread2;

    thread1 = std::thread(receivemsg, clientSocket, buf);
    thread2 = std::thread(sendmsg, clientSocket, buf);

    thread1.join();
    thread2.join();

    closesocket(clientSocket);
    WSACleanup();
    return 0;
}