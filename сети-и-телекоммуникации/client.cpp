#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>

#define SERVER_IP "192.168.104.164"
#define PORT 5000

int main() {
  setlocale(LC_ALL, "RUS");
  int clientSocket;
  struct sockaddr_in serverAddr;
  char buffer[1024];
  int bytesRead;

  clientSocket = socket(AF_INET, SOCK_STREAM, 0);
  if (clientSocket == -1) {
    std::cerr << "Ошибка создания сокета." << std::endl;
    return 1;
  }

  std::cout << "Попытка подключения к ip " << SERVER_IP << ", порт: " << PORT << "\n";
  serverAddr.sin_family = AF_INET;
  serverAddr.sin_port = htons(PORT);
  inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

  if (connect(clientSocket, (struct sockaddr *)&serverAddr,
              sizeof(serverAddr)) == -1) {
    std::cerr << "Ошибка подключения к серверу." << std::endl;
    close(clientSocket);
    return 1;
  }

  std::cout << "Подключено к серверу." << std::endl;

  while (true) {
    std::string message;
    std::cout << "Введите сообщение для сервера: ";
    std::getline(std::cin, message);
    send(clientSocket, message.c_str(), message.size(), 0);

    bytesRead = recv(clientSocket, buffer, sizeof(buffer), 0);
    if (bytesRead <= 0) {
      std::cerr << "Ошибка получения данных от сервера." << std::endl;
      break;
    }

    buffer[bytesRead] = '\0';
    std::cout << "Ответ сервера: " << buffer << std::endl;
  }

  close(clientSocket);

  return 0;
}
