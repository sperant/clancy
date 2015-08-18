#ifndef __HELLOMODULE__INCLUDED__
#define __HELLOMODULE__INCLUDED__

#include <string>
#include <regex>
#include "../message.h"
#include "../module.h"
#include "../bot.h"

class SayModule: public Module {
public:
  SayModule();
  void on(Message msg, std::smatch match, ClancyBot conn);
};

#endif