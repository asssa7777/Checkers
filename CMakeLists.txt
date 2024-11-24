cmake_minimum_required(VERSION 3.17)
project(CheckersCPPLogic)

set(CMAKE_CXX_STANDARD 20)


# Include paths for JNI
include_directories(/Users/***/Library/Java/JavaVirtualMachines/openjdk-20.0.1/Contents/Home/include)
include_directories(/Users/***/Library/Java/JavaVirtualMachines/openjdk-20.0.1/Contents/Home/include/darwin)

add_library(CheckersCPPLogic SHARED CheckersCPPLogic.cpp)
