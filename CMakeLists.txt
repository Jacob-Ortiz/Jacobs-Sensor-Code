cmake_minimum_required(VERSION 3.5)

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(dht11demo)

set(EXTRA_COMPONENT_DIRS "<path_to_dht11_component_directory>")

# Add DHT11 component
set(DHT11_COMPONENT_PATH ${EXTRA_COMPONENT_DIRS}/dht11)
idf_component_register(SRCS ${DHT11_COMPONENT_PATH}/dht11.c
                    INCLUDE_DIRS ${DHT11_COMPONENT_PATH})
