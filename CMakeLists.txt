cmake_minimum_required(VERSION 3.20)
project(PredOrPrey)

set(CMAKE_CXX_STANDARD 17)

# create the executable and use libimgLib created above
add_executable(${CMAKE_PROJECT_NAME}
        main.cpp
        lib/include/sampleClass.h
        lib/src/sampleClass.cpp
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE lib/include)
