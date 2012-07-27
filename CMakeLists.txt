cmake_minimum_required(VERSION 2.8)

project(dglw)
message("Project ${PROJECT_NAME}...")


###########################
#  Some useful variables  #
###########################
set(SOURCES_SUBDIR src)
set(SOURCE_HEADERS_SUBDIR include)
set(SOURCES_DIRECTORY ${CMAKE_SOURCE_DIR}/${SOURCES_SUBDIR})
set(HEADERS_DIRECTORY ${CMAKE_SOURCE_DIR}/${SOURCE_HEADERS_SUBDIR})
string(TOLOWER ${PROJECT_NAME} LOWER_NAME)
string(TOUPPER ${PROJECT_NAME} UPPER_NAME)


##############################
#  Projects default options  #
##############################
option( C++11           "C++11"         ON  )
option( Profile         "Profile"       OFF )
option( Boost           "Boost"         ON  )
option( Demo            "Demo"          ON  )
option( Debug           "Debug"         OFF )
option( Testing         "Testing"       ON  )
option( USE_GLFW        "USE_GLFW"      ON  )
option( USE_GLEW        "USE_GLEW"      ON  )
option( USE_OPENGL      "USE_OPENGL"    ON  )

set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for dynamic libraries")
set(INSTALL_ARCHIVE_DIR lib CACHE PATH "Installation directory for static libraries")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")

# Lazy way to manually add custom debug build compiler flags here...
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3")


###############
#  Debugging  #
###############

# Ensure that setting the debug option also sets the build type and visaversa
if(Debug)
    set(CMAKE_BUILD_TYPE "Debug")
elseif(CMAKE_BUILD_TYPE MATCHES "Debug")
    option(Debug "Debug" ON)
endif()

# Set _DEBUG #define for project
if(Debug)
    add_definitions(-D_DEBUG)
endif()


#############################
#  Find the stuff to build  #
#############################
# Note this is the 'bad' way of doing this, but the recommended 
# alternative is to manually keep a list of *all* source files =/
file(GLOB_RECURSE SOURCES "${SOURCES_DIRECTORY}/*.cpp")
file(GLOB_RECURSE HEADERS "${HEADERS_DIRECTORY}/*.h*")

include_directories("${HEADERS_DIRECTORY}/")
#get_directory_property(INCLUDE_DIRECTORIES INCLUDE_DIRECTORIES)

# CMake modules
set(CMAKE_MODULE_PATH
     ${CMAKE_SOURCE_DIR}/cmake
     ${CMAKE_MODULE_PATH})


###################################
#  Pass variables to the program  #
###################################

# [TODO]: This should be done using config file with a custom .in rather than passing defines

# Set the project name
add_definitions(-DPROJECT_NAME_="${PROJECT_NAME}")

# Build time define
include(GetDateTime)
DATETIME(BUILD_DATETIME)
add_definitions(-DBUILD_DATE_="${BUILD_DATETIME}")

# Build type
if(CMAKE_BUILD_TYPE)
    add_definitions(-DBUILD_TYPE_="${CMAKE_BUILD_TYPE}")
    message("Build type: ${CMAKE_BUILD_TYPE}")
else()
    add_definitions(-DBUILD_TYPE_="Default")
    message(STATUS "Using default build type...")
endif()

# Git version info
include(GetGitRevisionDescription)
git_describe(GIT_DESCRIBE "--always")
add_definitions(-DGIT_VERSION_="${GIT_DESCRIBE}")

# Git SHA1 define
get_git_head_revision(GIT_REFSPEC GIT_SHA1)
add_definitions(-DGIT_SHA1_="${GIT_SHA1}")

# Detect clang++ compiler
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_COMPILER_IS_CLANGXX_)
endif()

# Compiler specific flags...
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX_)
    if(C++11)
        message(STATUS "Enabling C++11 support...")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
        add_definitions(-DUSE_CPP11_)
    endif()

    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Werror") #-Weffc++
    
    if(Profile)
        message("Profiling: ON...")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
    endif()
endif()


######################
#  Handle libraries  #
######################

# For GL3/gl3.h
if(USE_GL3H)
    include_directories("${CMAKE_SOURCE_DIR}/external")
    add_definitions(-DUSE_GL3H)
    message(STATUS "Using gl3.h")
endif()

# GLEW
if(USE_GLEW)
    find_package(GLEW REQUIRED)
    if(GLEW_FOUND)
        #set(COMMON_LIBS ${COMMON_LIBS} ${GLEW_LIBRARIES})
        list(APPEND COMMON_LIBS ${GLEW_LIBRARIES})
        add_definitions(-DHAVE_GLEW)
        add_definitions(-DUSE_GLEW)
    else()
        message(FATAL_ERROR "GLEW not found!")
        return()
    endif()
endif()

# OpenGL
#if(USE_OPENGL)
    find_package(OpenGL REQUIRED)
    if(OPENGL_FOUND)
        add_definitions(-DHAVE_OPENGL)
        set(COMMON_LIBS ${COMMON_LIBS} ${OPENGL_LIBRARIES})
    else()
        message(FATAL_ERROR "Could not find OpenGL libraries!")
    endif()
#endif()

# Add Boost libs
#if(USE_BOOST)
#    find_package(Boost COMPONENTS filesystem system REQUIRED)
#    if(Boost_FOUND)
#        include_directories(${Boost_INCLUDE_DIRS})
#        add_definitions(-DHAVE_BOOST)
#        list(APPEND COMMON_LIBS ${Boost_LIBRARIES})
#        #set(COMMON_LIBS ${COMMON_LIBS} ${Boost_LIBRARIES})
#    else()
#        message(FATAL_ERROR "Boost not found!")
#        return()
#    endif()
#endif()

# GLFW target
#if(USE_GLFW)
#    find_package(GLFW REQUIRED)
#    if(GLFW_FOUND)
#        set(GLFW_PROJECT_NAME "${PROJECT_NAME}-glfw")
#        add_executable(${GLFW_PROJECT_NAME} ${GLFW_SOURCES} ${SOURCES})
#        target_link_libraries(${GLFW_PROJECT_NAME} ${COMMON_LIBS} ${GLFW_LIBRARIES})
#        set_target_properties(${GLFW_PROJECT_NAME} PROPERTIES COMPILE_DEFINITIONS "USE_GLFW")
#    else()
#        message(FATAL_ERROR "GLFW not found!")
#        return()
#    endif()
#endif()


##########################################
#  Register the libraries the CMake way  #
##########################################

# Set the values for our build tree configure file
set(CONFIG_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(CONFIG_LIB_DIR ${PROJECT_BINARY_DIR})
set(${UPPER_NAME}_CMAKE_DIR ${INSTALL_ARCHIVE_DIR})

# Generate PackageConfig.cmake file for out build tree to expose it to find_package
set(CONFIG_FILENAME ${PROJECT_NAME}Config.cmake)
configure_file(${CONFIG_FILENAME}.in "${PROJECT_BINARY_DIR}/${CONFIG_FILENAME}" @ONLY)

# Register package's build directory in CMakes global package registery (ie ~/.cmake/packages/<ProjectName> or the windows registry)
export(PACKAGE ${PROJECT_NAME})

# Set the values for our install <Project>Config.cmake file
set(CONFIG_INCLUDE_DIR ${CMAKE_INSTALL_PREFIX}/${INSTALL_INCLUDE_DIR}/${LOWER_NAME})
set(CONFIG_LIB_DIR ${CMAKE_INSTALL_PREFIX}/${INSTALL_ARCHIVE_DIR}/${LOWER_NAME})

# Generate the install <Project>Config.cmake file
configure_file(${CONFIG_FILENAME}.in ${PROJECT_BINARY_DIR}/install/${CONFIG_FILENAME} @ONLY)


#######################
#  Build the project  #
#######################
add_library(${LOWER_NAME} ${SOURCES})
if(Demo)
    add_subdirectory(demo)
endif(Demo)


#############
#  Install  #
#############

# Install the system wide headers in /include...
install(FILES ${HEADERS} DESTINATION ${INSTALL_INCLUDE_DIR}/${LOWER_NAME} COMPONENT dev)

# Install the <Project>Config.cmake file
install(FILES ${PROJECT_BINARY_DIR}/install/${CONFIG_FILENAME} DESTINATION ${INSTALL_ARCHIVE_DIR}/${LOWER_NAME})

# Install static lib (.a) in /lib
install(TARGETS ${LOWER_NAME} ARCHIVE DESTINATION ${INSTALL_ARCHIVE_DIR}/${LOWER_NAME})


#############
#  Testing  #
#############
if(Testing)
    find_package(GTest)
    if(GTEST_FOUND)
        # Register the package with CMakes built in testing system ctest
        enable_testing()
        #include_directories("${CMAKE_SOURCE_DIR}/src/")
        LIST(REMOVE_ITEM SOURCES "${MAIN_SOURCE}")
        string(TOLOWER ${PROJECT_NAME}_unittest PROJECT_TEST_NAME)
        add_executable(${PROJECT_TEST_NAME} ${CMAKE_SOURCE_DIR}/tests/unittest.cpp ${SOURCES})
        target_link_libraries(${PROJECT_TEST_NAME} ${GTEST_BOTH_LIBRARIES} pthread ${COMMON_LIBS})
        message(STATUS "GTest libs: ${GTEST_BOTH_LIBRARIES}")
        add_test(${PROJECT_TEST_NAME}, ${PROJECT_TEST_NAME})
    else()
        message(AUTHOR_WARNING "Could not find Google Test libraries...")
    endif()
endif()
