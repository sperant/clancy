#ifndef __message_h_included__
#define __message_h_included__

struct Message {
    std::string nick;
    std::string realname;
    std::string hostname;
    std::string type;
    std::string channel;
    std::string content;
};

#endif