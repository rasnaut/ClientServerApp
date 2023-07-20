#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <Windows.h>
#include <vector>
#include <string>
//#include <thread>

#pragma warning(disable: 4996)
delegate void myEvent(System::Object sender, System::EventArgs^ e);
ref class CClient : public System::Object
{
public:
  CClient();
  ~CClient();

  BOOL CtrlHandler(DWORD fdwCtrlType);
  void reciveMessage();
  //static void messageHandler();
  bool connectClient();
  std::vector<std::string>* getMessageArrayPtr();
  //void disconnectClient();

  void sendMessage(System::String^ messageText);
  event myEvent^ mEv;
  System::EventHandler^ myEventHandler;

private:
  //SOCKET Connection;
  
  SOCKADDR_IN* addr;
  int addr_size;
  //std::thread* thrPointer;
};

