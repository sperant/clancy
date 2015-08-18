cmake_minimum_required (VERSION 3.2.3)
project (clancy)

include_directories(include)
include_directories(include/modules)

add_executable (clancy src/clancy.cpp
                       src/bot.cpp
                       src/irc.cpp
                       src/modules/say.cpp
                       )
