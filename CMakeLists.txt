cmake_minimum_required(VERSION 3.2 FATAL_ERROR)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
set (CMAKE_CXX_STANDARD 14)
# if ( CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
message("turning on warnings")
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -Wextra -lpython3.8")
# else()
	# message("can't turn on warnings")
	# message(${CMAKE_CXX_COMPILER})
# endif()


project (pendulum_project CXX)

#file globing
file(GLOB_RECURSE sources src/*.cpp src/*.h)
# file(GLOB_RECURSE library_files lib/*.h)
file(GLOB_RECURSE data resources/*)

include_directories(lib)
add_executable(pendulum ${sources} ${data})

#copy resources to build directory
file(COPY ${data} DESTINATION resources)

#armadillo library
find_package(Armadillo)

#include the necessary libraries
find_package(SFML 2 REQUIRED system window graphics)
find_package(TGUI REQUIRED)

if(NOT SFML_FOUND)
    message(FATAL_ERROR "Could not find SFML")
endif()

if(NOT TGUI_FOUND)
    message(FATAL_ERROR "Could not find TGUI")
endif()

if(NOT ARMADILLO_FOUND)
	message(WARNING "Could not find armadillo")
endif()

find_package(Python3 COMPONENTS Development NumPy)
target_include_directories(pendulum PRIVATE ${Python3_INCLUDE_DIRS} ${Python3_NumPy_INCLUDE_DIRS})
include_directories(${SFML_INCLUDE_DIR})
include_directories(${TGUI_INCLUDE_DIR})
include_directories(${ARMADILLO_INCLUDE_DIRS})

target_link_libraries(pendulum ${SFML_LIBRARIES} ${TGUI_LIBRARY} ${ARMADILLO_LIBRARIES} Python3::Python Python3::NumPy)
