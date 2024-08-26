project (order_service)
cmake_minimum_required (VERSION 3.28)

find_package(cppzmq CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt 10 REQUIRED)

set( SOURCES
	"order_service.cpp"
	"order_manager.cpp"
	"order_reciever.cpp"
)

set( INCLUDE 
	"order_service.h"
	"order_manager.h"
	"order_receiver.h"
	"order.h"

	"${CMAKE_SOURCE_DIR}/include"
)

set( LINK_DEPENDENSIES
	"cppzmq"
	"cppzmq-static"
	"nlohmann_json::nlohmann_json"
	"fmt::fmt"
)


add_executable( ${PROJECT_NAME} ${SOURCES} )
target_include_directories( ${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include" )
target_link_libraries( ${PROJECT_NAME} PRIVATE ${LINK_DEPENDENSIES} )

set_property( TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20 )
