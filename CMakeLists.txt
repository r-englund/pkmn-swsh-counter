# CMakeLists files in this project can
# refer to the root source directory of the project as ${HELLO_SOURCE_DIR} and
# to the root binary directory of the project as ${HELLO_BINARY_DIR}.
cmake_minimum_required(VERSION 3.1 FATAL_ERROR)
project (OpenCV-Test2)

set(BUILD_SHARED_LIBS OFF)
set(OpenCV_STATIC ON)
find_package(OpenCV REQUIRED PATHS ../opencv-build/install NO_DEFAULT_PATH)


add_executable(test1 
    test1.cpp
    src/encounterdetector.h
    src/encounterdetector.cpp
    src/textrecognizer.h
    src/textrecognizer.cpp
    src/utils.h
    src/utils.cpp
)

message("OpenCV_LIBS: " ${OpenCV_LIBS})
message("OpenCV_INCLUDE_DIRS: " ${OpenCV_INCLUDE_DIRS})


target_link_libraries(test1 PUBLIC ${OpenCV_LIBS})

target_compile_definitions(test1 PUBLIC _ITERATOR_DEBUG_LEVEL=0)

if(MSVC)
  target_compile_options(test1 PRIVATE /W4 /MT)
else()
  target_compile_options(test1 PRIVATE -Wall -Wextra -pedantic)
endif()

set_target_properties(test1 PROPERTIES
            CXX_STANDARD 17
            #CXX_EXTENSIONS OFF
            )