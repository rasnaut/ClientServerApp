#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>

#include <iostream>
#include <vector>
#include <unordered_map>
#include <thread>

#pragma warning(disable: 4996)
std::vector<SOCKET> Connection;
std::unordered_map<int, SOCKET> ConnectionMap;

void ClientHandler(int idClient) {
    char message[128];
    while (true) {
        auto itr = ConnectionMap.find(idClient);
        if (itr == ConnectionMap.end()) 
          break;
        recv(itr->second, message, sizeof(message), NULL);
        if (message[0] == '0') {
            std::cout << "close connection " << idClient << "\n";

            closesocket(itr->second);
            ConnectionMap.erase(itr);
            break;
        }

        for (auto element : ConnectionMap) {
          if (element.first != idClient)
            send(element.second, message, sizeof(message), NULL);
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
        ConnectionMap.emplace(client_index, newConnection);
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