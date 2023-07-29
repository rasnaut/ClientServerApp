#pragma once
#pragma comment(lib, "ws2_32.lib")
#include <winsock2.h>
#include <Windows.h>
#include <vector>
#include <string>
#include <functional>
//#include <thread>

#pragma warning(disable: 4996)
const char* toCChar(System::String^ str);
//System::Void MessageReciver(System::Object^ sender, System::EventArgs^ e)
delegate System::Void myEvent();
using MyEvent = std::function<System::Void()>;
//MyEvent eventPointer;
ref class CClient : public System::Object
{
public:
  CClient();
  ~CClient();

  BOOL CtrlHandler(DWORD fdwCtrlType);
  void reciveMessage();
  static void messageHandler();
  bool connectClient();
  std::vector<std::string>* getMessageArrayPtr();
  /*void setEvent(const MyEvent* mEvent) {
    eventPointer = *mEvent;
  }*/
  //void disconnectClient();

  void sendMessage(System::String^ messageText);
  static event myEvent^ mEv;
  static void emitEvent() {
    mEv();
  }
  
  //System::EventHandler^ myEventHandler;

private:
  //SOCKET Connection;
  
  SOCKADDR_IN* addr;
  int addr_size;
  //std::thread* thrPointer;
};

