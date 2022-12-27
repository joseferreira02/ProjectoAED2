cmake_minimum_required(VERSION 3.24)
project (projetoAED2)

set(CMAKE_CXX_STANDARD 17)

add_executable(projetoAED2 main.cpp airport.h airport.cpp airline.h airline.cpp flight.h flight.cpp Manager.h Manager.cpp)
