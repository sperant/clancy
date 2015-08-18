#include <iostream>
#include <regex>
#include "modules/say.h"
#include "bot.h"

void ClancyBot::init() {
    load_modules();

    if (!conn.create())
        error("Something went nasty!");

    listen();
}

void ClancyBot::listen() {
    conn.announce(nick);

    std::string raw;
    std::smatch m;
    std::regex msg_rgx(":(.+)!~(.+)@(.+) (.+) (.+) :(.+)");
    while(true) {
        raw = conn.listen();
        Message msg;

        if (std::regex_search (raw, m, msg_rgx)) {
            msg.nick = m.str(1);
            msg.realname = m.str(2);
            msg.hostname = m.str(3);
            msg.type = m.str(4);
            msg.channel = m.str(5);
            msg.content = m.str(6);

            handle_msg(msg);
        }

        raw.clear();
    }
}

void ClancyBot::handle_msg(Message msg) {
    for(int i = 0; i < 1; i++) {
        std::smatch m;
        if (std::regex_search(msg.content, m, module_list[i]->rgx))
            module_list[i]->on(msg, m, *this);
    }
}

void ClancyBot::error(const char *msg) {
    std::cerr << msg << std::endl;
    exit(0);
}

void ClancyBot::load_modules() {
    module_list[0] = new SayModule();
}

void ClancyBot::send(std::string output) {
    conn.send(output);
}

void ClancyBot::reply(Message msg, std::string output) {
    conn.send("PRIVMSG " + msg.channel + " :" + output);
}