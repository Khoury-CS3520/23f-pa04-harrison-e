cmake_minimum_required(VERSION 3.20)
project(PredOrPrey)

set(CMAKE_CXX_STANDARD 17)

# create the executable and use libimgLib created above
add_executable(${CMAKE_PROJECT_NAME}
        main.cpp
        lib/include/Critter.h
        lib/include/Cell.h
        lib/include/Grid.h
        lib/include/Ant.h
        lib/include/Doodlebug.h
        lib/include/Simulation.h
        lib/src/Critter.cpp
        lib/src/Cell.cpp
        lib/src/Grid.cpp
        lib/src/Ant.cpp
        lib/src/Doodlebug.cpp
        lib/src/Simulation.cpp
        lib/include/Queen.h
        lib/src/Queen.cpp
        lib/include/Coordinate.h
)
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE lib/include)
