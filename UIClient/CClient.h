#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <Windows.h>
#include <thread>

#pragma warning(disable: 4996)

ref class CClient
{
public:
  CClient();
  ~CClient();

  BOOL CtrlHandler(DWORD fdwCtrlType);
  void reciveMessage(System::String^ messageText);
  static void messageHandler(unsigned int connection, System::String^ messageText );
  bool connectClient();
  //void disconnectClient();

  void sendMessage(System::String^ messageText);

private:
  SOCKET Connection;
  SOCKADDR_IN* addr;
  int addr_size;
  std::thread* thrPointer;
};

