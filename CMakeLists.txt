cmake_minimum_required(VERSION 3.10)

# Set the project name
project(mce_encryption_server_cpp)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify where Boost is installed (adjust this path if necessary)
if (WIN32)
  set(BOOST_ROOT "C:/local/boost_1_81_0")
  set(Boost_INCLUDE_DIR "C:/local/boost_1_81_0/boost")
endif()

# Add the Boost library dependency
find_package(Boost REQUIRED COMPONENTS system)

# Specify the location of the static library
set(MCE_CLIENT_AUTH_LIB ${CMAKE_SOURCE_DIR}/libMCEClientAuth.a)

# Add the executable
add_executable(mce_encryption_server_cpp main.cc)

# Include the current directory to find MCEClientAuth.h
target_include_directories(mce_encryption_server_cpp PRIVATE ${CMAKE_SOURCE_DIR})

# Link the static library and Boost libraries
target_link_libraries(mce_encryption_server_cpp PRIVATE ${MCE_CLIENT_AUTH_LIB} Boost::system)

# If additional dependencies like pthread are needed (for Boost), link them
find_package(Threads REQUIRED)
target_link_libraries(mce_encryption_server_cpp PRIVATE Threads::Threads)

# Disable PIE
target_link_options(mce_encryption_server_cpp PRIVATE -no-pie)
