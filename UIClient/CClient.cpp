#include "pch.h"
#include "CClient.h"
#include <utility>


const char* toCChar(System::String^ str) {

  char* result_str = new char[str->Length+1];
  for (int i = 0; i < str->Length; i++) {
    result_str[i] = str[i];
  }
  result_str[str->Length] = '\0';
  return result_str;
}

CClient::CClient()
{
  WSAData wsaData;
  WORD DllVersion = MAKEWORD(2, 1);
  if (WSAStartup(DllVersion, &wsaData) != 0) {
    exit(1);
  }
  addr = new SOCKADDR_IN;
  addr->sin_addr.s_addr = inet_addr("127.0.0.1");
  addr->sin_port = htons(1111);
  addr->sin_family = AF_INET;
  addr_size = sizeof(*addr);

  Connection = socket(AF_INET, SOCK_STREAM, NULL);
}

CClient::~CClient()
{
  delete addr;
}

BOOL CClient::CtrlHandler(DWORD fdwCtrlType)
{
  return 0;
}

void CClient::reciveMessage(System::String^ messageText)
{
  thrPointer = new std::thread(messageHandler, 1, messageText);
}

void CClient::messageHandler(unsigned int connection, System::String^ messageText ) {
  char message[128];
  while (true) {
    //recv((SOCKET)connection, message, sizeof(message), NULL);
    //messageText += "text";//System::String(message);
  }
}

bool CClient::connectClient()
{
  if (connect(Connection, (SOCKADDR*)addr, addr_size)) {
    return false;
  }
  return true;
}

void CClient::sendMessage(System::String^ messageText)
{
  const char* msg = toCChar(messageText);
  send(Connection, msg, sizeof(msg), NULL);
}
