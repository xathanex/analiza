cmake_minimum_required(VERSION 2.8.4)
project(analiza)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    sources/battle_settings.h
    sources/bullet.cpp
    sources/bullet.h
    sources/engine.cpp
    sources/engine.h
    sources/events.h
    sources/main.cpp
    sources/radar.cpp
    sources/radar.h
    sources/ruby_bridge.cpp
    sources/ruby_bridge.h
    sources/ruby_bullet.cpp
    sources/ruby_bullet.h
    sources/ruby_ship.cpp
    sources/ruby_ship.h
    sources/ship.cpp
    sources/ship.h
    sources/turn_data.h
    sources/turret.cpp
    sources/turret.h
    tests/ruby_bridge_test.cpp
    tests/ruby_bullet_test.cpp
    tests/ruby_ship_test.cpp)

add_executable(analiza ${SOURCE_FILES})