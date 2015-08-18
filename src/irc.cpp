#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <regex>
#include <sstream>
#include "irc.h"

bool IRC::create() {
  int n;
  struct sockaddr_in serv_addr;
  struct hostent *server;

  char buffer[256];

  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0)
      error("ERROR opening socket");
  server = gethostbyname(host);
  if (server == NULL)
      error("ERROR no such host");
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  bcopy((char *)server->h_addr,
        (char *)&serv_addr.sin_addr.s_addr,
        server->h_length);
  serv_addr.sin_port = htons(portno);
  if (connect(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
      error("ERROR connecting");

  return true;
}

void IRC::announce(std::string nick) {
  send("1");
  for(int i = 0; i < 2; i++)
    listen();
  send("PASS none");
  send("NICK " + nick);
  send("USER clancybot 0 * clancybot");
  while (listen().find("/MOTD") == std::string::npos) { }
  send("JOIN #TestChannel");
}

std::string IRC::listen() {
  std::string output(512, 0);

  if (read(sockfd, &output[0], 512-1) < 0)
    error("ERROR reading from socket");

  std::cout << output << std::endl;
  handle_incoming(output);
  return output;
}

void IRC::send(const char * s) {
  std::cout << "<< " << s << std::endl;
  char out[256];
  strcpy(out, s);
  strcat(out, "\r\n");
  int n = write(sockfd,out,strlen(out));
  if (n < 0)
    error("ERROR writing to socket");
}
void IRC::send(std::string s) {
  send(s.c_str());
}

void IRC::msg(std::string channel, std::string s) {
  send("PRIVMSG " + channel + " :" + s);
}

void IRC::error(const char * msg) {
  std::cout << msg << std::endl;
  exit(0);
}

void IRC::handle_incoming(std::string s) {
  if (s.find("PING :") != std::string::npos)
    send("PONG :" + s.substr(6));
  /*std::string s(buffer, strlen(buffer));  
  std::smatch m;
  std::regex ping_rgx("PING :(.+)");

  if (std::regex_search (s, m, ping_rgx)) {
    char out[256];
    strcpy(out, "PONG :");
    strcat(out, m.str(1).c_str());
    send(out);
  }*/
}