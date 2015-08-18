#include <string>
#include <map>
#include "message.h"
#include "irc.h"
#include "module.h"

#ifndef __clancybot_h_included__
#define __clancybot_h_included__

class ClancyBot {
private:
  std::string nick;
  IRC conn;
  Module *module_list[1];
  void handle_msg(Message m);
  void load_modules();
public:
  ClancyBot(std::string _nick, IRC _conn) : nick(_nick), conn(_conn) { };
  void init();
  void listen();
  void send(std::string output);
  void reply(Message msg, std::string output);
  void error(const char * msg);
};

#endif