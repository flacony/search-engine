cmake_minimum_required(VERSION 3.5)

project(search_engine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(search_engine
    main.cpp
)

add_library(tools my_lib/src/converterjson.cpp my_lib/src/invertedindex.cpp my_lib/src/searchserver.cpp my_lib/src/threadpool.cpp)

target_link_libraries(search_engine PRIVATE nlohmann_json::nlohmann_json tools)
