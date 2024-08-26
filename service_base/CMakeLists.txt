project( client )
cmake_minimum_required( VERSION 3.28 )

find_package(cppzmq CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)
find_package(fmt 10 REQUIRED)
find_package(spdlog CONFIG REQUIRED)

set( SOURCES
	service_base.cpp
	service_base.h
)

set( LINK_DEPENDENSIES
	"cppzmq"
	"cppzmq-static"
	"nlohmann_json::nlohmann_json"

	"fmt::fmt"
	"spdlog::spdlog_header_only"
)

add_executable( ${PROJECT_NAME} ${SOURCES} )
target_include_directories( ${PROJECT_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include" )
target_link_libraries( ${PROJECT_NAME} PRIVATE ${LINK_DEPENDENSIES} )

set_property( TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 20 )

