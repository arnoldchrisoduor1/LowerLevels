cmake_minimum_required(VERSION 3.12)
project(ExpenseTracker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add compiler warnings
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic")
endif()

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
endif()

# Include headers if needed (currently you seem to use src/*/*.h)
include_directories(src)

# Recursively get all .cpp files in src/
file(GLOB_RECURSE SOURCE_FILES
    "src/*.cpp"
)

# Create the executable
add_executable(ExpenseTracker ${SOURCE_FILES})

# Output binary to bin/
set_target_properties(ExpenseTracker PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)
