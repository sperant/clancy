#include <iostream>
#include "say.h"

SayModule::SayModule() {
  rgx = "^.say(.+)";
}

void SayModule::on(Message msg, std::smatch match, ClancyBot bot) {
  bot.reply(msg, match.str(1));
}