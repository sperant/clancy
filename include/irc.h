#include <string>

#ifndef __irc_h_included__
#define __irc_h_included__

class IRC {
  const char * host;
  int sockfd, portno;
public:
  IRC(const char * _host, int _portno) : host(_host), portno(_portno) { };
  bool create();
  void announce(std::string nick);
  std::string listen();
  void send(const char * s);
  void send(std::string s);
  void msg(std::string channel, std::string s);
private:
  void handle_incoming(std::string s);
  void error(const char * msg);
};

#endif