cmake_minimum_required(VERSION 3.17)
project(Lab4)

set(CMAKE_CXX_STANDARD 14)

add_executable(app main.cpp queueElem/QueueElem.cpp
        queueElem/QueueElem.h
        queueHandler/ThreadpoolQueueProcessor.cpp queueHandler/ThreadpoolQueueProcessor.h
        queue/Queue.cpp queue/Queue.h)