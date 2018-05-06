cmake_minimum_required(VERSION 3.10)
project(code)

set(CMAKE_CXX_STANDARD 98)

add_executable(code main1.cpp library1.h PlayerTree.cpp PlayerTree.h ClanTree.cpp ClanTree.h Tree.h CoinTree.cpp
        CoinTree.h Oasis.cpp Oasis.h Pair.h)