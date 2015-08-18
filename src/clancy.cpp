#include <iostream>
#include <regex>
#include "irc.h"
#include "bot.h"

int main(int argc, const char * argv[]) {
  IRC conn ("irc.freenode.net", 6667);
  ClancyBot bot("Clancybot", conn);
  bot.init();

  return 0;
}