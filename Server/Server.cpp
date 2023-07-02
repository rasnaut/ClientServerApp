#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>

#include <iostream>
#include <vector>
#include <thread>

#pragma warning(disable: 4996)
std::vector<SOCKET> Connection;

void ClientHandler(int indexClient) {
    char message[128];
    while (true) {
        recv(Connection[indexClient], message, sizeof(message), NULL);
        if (message[0] == '0') {
            std::cout << "close connection " << indexClient << "\n";
            std::vector<SOCKET>::const_iterator iter = Connection.cbegin() + indexClient;
            closesocket(Connection[indexClient]);
            Connection.erase(iter);
        }
        for (int i = 0; i < Connection.size(); i++) {
            if (i != indexClient) {
                send(Connection[i], message, sizeof(message), NULL);
            }
                
        }
    }
}

void NewConnectionCreator(const SOCKET& sListen, SOCKADDR_IN& addr, int& addr_size, int client_index)
{
    SOCKET newConnection = accept(sListen, (SOCKADDR*)&addr, &addr_size);
    if (!newConnection) 
        std::cerr << "Error 2" << std::endl;
    else {
        std::cout << "Client Connected!" << std::endl;
        char msg[64] = "Welcome!";
        send(newConnection, msg, sizeof(msg), NULL);
        Connection.push_back(newConnection);
        CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)ClientHandler,
            (LPVOID)client_index, NULL, NULL);
    }
}

int main()
{
    WSAData wsaData;
    WORD DllVersion = MAKEWORD(2, 1);
    if (WSAStartup(DllVersion, &wsaData) != 0) {
        std::cerr << "Error" << std::endl;
        exit(1);
    }

    SOCKADDR_IN addr;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(1111);
    addr.sin_family = AF_INET;
    int addr_size = sizeof(addr);

    SOCKET sListen = socket(AF_INET, SOCK_STREAM, NULL);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);
    for (int i = 0; i < 100; i++) {
        NewConnectionCreator(sListen, addr, addr_size, i);
    }

    system("pause");

    return 0;
}