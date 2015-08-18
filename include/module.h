#ifndef __module_h_included__
#define __module_h_included__

#include <string>
#include <regex>
#include <map>
#include "message.h"

class Module;

#include "bot.h"

class Module {
public:
  std::regex rgx;
  Module() { }
  virtual void on(Message msg, std::smatch match, ClancyBot bot) { }
};

#endif