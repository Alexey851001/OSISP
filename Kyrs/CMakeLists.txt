cmake_minimum_required(VERSION 3.17)
project(Kyrs)

set(CMAKE_CXX_STANDARD 14)


add_executable(Atomas WIN32 main.cpp atom/Atom.cpp atom/Atom.h
        circle/Circle.cpp circle/Circle.h
        atom/IAtom.cpp atom/IAtom.h
        atom/Plus.cpp atom/Plus.h
        circle/LinkedList.cpp circle/LinkedList.h
        application/Applicaton.cpp application/Applicaton.h)
