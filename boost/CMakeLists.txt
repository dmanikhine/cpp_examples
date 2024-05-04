cmake_minimum_required(VERSION 3.20)
project(boost_options)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


#set(ENV{BOOST_ROOT} "/usr/local/include/boost_1_82_0")
find_package(Boost 1.82.0 REQUIRED COMPONENTS program_options )
message(${Boost_INCLUDE_DIRS})

#message(${Boost_PROGRAM_OPTIONS_LIBRARY})

include_directories(${Boost_INCLUDE_DIRS})
add_executable(bo boost_options.cpp)
TARGET_LINK_LIBRARIES(bo ${Boost_LIBRARIES})




