cmake_minimum_required(VERSION 4.1)
project(pbd)

set(CMAKE_CXX_STANDARD 26)

add_executable(pbd src/main.cpp
        src/mesh/MeshData.h
        src/world/WorldDescription.h
        src/update/Stormer.h
        src/Types.h
        src/update/GaussSeidel.h
        src/update/PhysDescription.h)

if(WIN32)
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static-libgcc -static-libstdc++ -static")
endif()