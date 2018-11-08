cmake_minimum_required(VERSION 3.12)
project(zhakal)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp Server.cpp Server.h)
add_executable(zhakal ${SOURCE_FILES})

#set(SFML_ROOT "/home/igorik18/SFML-2.5.1")
#set(CMAKE_MODULE_PATH "/home/igorik18/CLionProjects/untitled/Modules")

#find_package(SFML 2 COMPONENTS REQUIRED system window graphics network audio)
#include_directories(${SFML_INCLUDE_DIR})

#target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})

set(CMAKE_PREFIX_PATH "C:/Users/Igor/Documents/SFML-2.5.0")

# Detect and add SFML
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED system graphics window network audio)
if(SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(${PROJECT_NAME} ${SFML_LIBRARIES})
endif()



#add_executable(zhakal main.cpp)