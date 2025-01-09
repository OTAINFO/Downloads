cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(test-bt)
FILE(GLOB app_sources src/*.c)
target_sources(app PRIVATE ${app_sources})
target_include_directories(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(app PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/lib/hal_02_seed_studio_xiao_nrf52840_sense.c.obj)

