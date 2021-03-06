################################################################################
# dglw CMake file. - The CMake script for building the project.                #
################################################################################
# Written in 2012 by David C. Bishop david@davidbishop.org                     #
#                                                                              #
# To the extent possible under law, the author(s) have dedicated all copyright #
# and related and neighboring rights to this software to the public domain     #
# worldwide. This software is distributed without any warranty.                #
#                                                                              #
# You should have received a copy of the CC0 Public Domain Dedication along    #
# with this software. If not, see                                              #
# <http://creativecommons.org/publicdomain/zero/1.0/>.                         #
################################################################################
# NOTE: The CC0 license applies only to this cmake file, not the entire        #
# project (unless otherwise stated). I just like ensuring there is no problem  #
# with people needing snippits of code for their CMake stuff.                  #
################################################################################

cmake_minimum_required(VERSION 2.8)

project(dglw)
message("Project ${PROJECT_NAME}...")


##############################
#  Projects default options  #
##############################
option( C++11           "C++11"         ON  )
option( Profile         "Profile"       OFF )
#option( Boost           "Boost"         ON  )
option( Demo            "Demo"          ON  )
option( Debug           "Debug"         OFF )
option( Coverage        "Coverage"      OFF )
option( Testing         "Testing"       ON  )
option( USE_GLFW        "USE_GLFW"      ON  )
option( USE_QT          "USE_QT"        ON  )
option( USE_GLEW        "USE_GLEW"      OFF )
option( USE_GLCOREARB   "USE_GLCOREARB" ON  )
option( USE_OPENGL      "USE_OPENGL"    ON  )

###########################
#  Some useful variables  #
###########################
set(SOURCES_SUBDIR src)
set(HEADERS_SUBDIR include)
set(TESTS_SUBDIR tests)
set(SOURCES_DIRECTORY ${CMAKE_SOURCE_DIR}/${SOURCES_SUBDIR})
set(HEADERS_DIRECTORY ${CMAKE_SOURCE_DIR}/${HEADERS_SUBDIR})
set(TESTS_DIRECTORY ${CMAKE_SOURCE_DIR}/${TESTS_SUBDIR})
set(CONFILE_FILENAME "Globals.hpp")
set(CONFILE_SUBDIR "${HEADERS_SUBDIR}/Main")
set(CONFILE_FILE "${PROJECT_SOURCE_DIR}/${CONFILE_SUBDIR}/${CONFILE_FILENAME}.in")
string(TOLOWER ${PROJECT_NAME} LOWER_NAME)
string(TOUPPER ${PROJECT_NAME} UPPER_NAME)
set(LIB_NAME ${LOWER_NAME})

# Add custom debug build compiler flags here...
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O3")

# Detect clang++ compiler
if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
   set(CMAKE_COMPILER_IS_CLANGXX_ TRUE)
endif()

# Generate compile_commands.json, useful for tools...
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

#############################
#  Set install directories  #
#############################
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for dynamic libraries")
set(INSTALL_ARCHIVE_DIR lib CACHE PATH "Installation directory for static libraries")
set(INSTALL_INCLUDE_DIR include CACHE PATH "Installation directory for header files")


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
file(GLOB_RECURSE SOURCES ${SOURCES_DIRECTORY}/*.cpp)
file(GLOB_RECURSE HEADERS ${HEADERS_DIRECTORY}/*.h*)
file(GLOB_RECURSE HEADERS_SRC ${SOURCES_DIRECTORY}/*.h*)

include_directories("${HEADERS_DIRECTORY}/${LOWER_NAME}/")
include_directories("${SOURCES_DIRECTORY}/")

# CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake)


###################################
#  Pass variables to the program  #
###################################

# Get build time
include(GetDateTime)
DATETIME(BUILD_DATETIME)

# Build type
if(CMAKE_BUILD_TYPE)
   message("Build type: ${CMAKE_BUILD_TYPE}")
else()
   message(STATUS "Using default build type...")
endif()

# Git version info
include(GetGitRevisionDescription)
git_describe(GIT_DESCRIBE "--always")

# Get Git SHA1 hash
get_git_head_revision(GIT_REFSPEC GIT_SHA1)

# Compiler specific flags...
if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_COMPILER_IS_CLANGXX_)
   if(C++11)
      message(STATUS "Enabling C++11 support...")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
      add_definitions(-DUSE_CPP11_)
   endif()

   set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Werror") #-Weffc++
   
   if(Profile)
      message(STATUS "Profiling: ON...")
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
   endif()

   if(Coverage)
      set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0")
      link_libraries(gcov)
   endif()
endif()

# Genearte config header file
# [TODO]: Library should provide access to compile settings...
#configure_file("${CONFILE_FILE}" "${PROJECT_BINARY_DIR}/${CONFILE_SUBDIR}/${CONFILE_FILENAME}" @ONLY)
#include_directories(${PROJECT_BINARY_DIR}/${CONFILE_SUBDIR})


######################
#  Handle libraries  #
######################

# For glcorearb.h
if(USE_GLCOREARB)
   include_directories("${CMAKE_SOURCE_DIR}/extern")
   add_definitions(-DUSE_GLCOREARB)
   message(STATUS "Using glcorearb.h")
endif()

# OpenGL
#if(USE_OPENGL)
   find_package(OpenGL REQUIRED)
   if(OPENGL_FOUND)
      add_definitions(-DHAVE_OPENGL)
      list(APPEND COMMON_LIBS ${OPENGL_LIBRARIES})
   else()
      message(FATAL_ERROR "Could not find OpenGL libraries!")
   endif()
#endif()

# Add Boost libs
#if(Boost)
   find_package(Boost COMPONENTS filesystem system iostreams REQUIRED)
   if(Boost_FOUND)
      include_directories(${Boost_INCLUDE_DIRS})
      add_definitions(-DUSE_BOOST_)
      list(APPEND COMMON_LIBS ${Boost_LIBRARIES})
   else()
      message(FATAL_ERROR "Boost not found!")
   endif()
#endif()

# QT
if(USE_QT)
   find_package(Qt5Core)
   find_package(Qt5Widgets)
   find_package(Qt5Gui)
   find_package(Qt5OpenGL)

   if(Qt5Core_FOUND AND Qt5Widgets_FOUND AND Qt5Gui_FOUND AND Qt5OpenGL_FOUND)
      set(HAVE_QT TRUE)
   endif()
endif()

if(USE_GLFW)
   find_package(GLFW)
   if(GLFW_FOUND)
      set(HAVE_GLFW TRUE)
   endif()
endif()


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
add_library(${LIB_NAME} ${SOURCES})

if(HAVE_GLFW)
   list(APPEND COMMON_DEFS "USE_GLFW")
   list(APPEND COMMON_LIBS ${GLFW_LIBRARIES})
   include_directories(${GLFW_INCLUDE_DIR})
endif()

if(HAVE_QT)
   list(APPEND COMMON_LIBS ${QT_LIBRARIES})
   list(APPEND COMMON_DEFS "USE_QT")
   set(CMAKE_INCLUDE_CURRENT_DIR ON)
   qt5_use_modules(${LIB_NAME} Core Widgets Gui OpenGL)
endif()

set_target_properties(${LIB_NAME} PROPERTIES COMPILE_DEFINITIONS "${COMMON_DEFS}" AUTOMOC TRUE)

if(Demo)
   add_subdirectory(demo)
endif(Demo)

#############
#  Install  #
#############

# Install the system wide headers in /include...
foreach(FILE ${HEADERS})
   file(RELATIVE_PATH REL_FILE ${HEADERS_DIRECTORY}/ ${FILE})
   get_filename_component(REL_PATH ${REL_FILE} PATH)
   install(FILES ${HEADERS_DIRECTORY}/${REL_FILE} DESTINATION ${INSTALL_INCLUDE_DIR}/${REL_PATH} COMPONENT dev)
endforeach()

# Also have to process GLWidget.hpp (in src due to automoc not finding it elsewhere)...
foreach(FILE ${HEADERS_SRC})
   file(RELATIVE_PATH REL_FILE ${SOURCES_DIRECTORY}/ ${FILE})
   get_filename_component(REL_PATH ${REL_FILE} PATH)
   install(FILES ${SOURCES_DIRECTORY}/${REL_FILE} DESTINATION ${INSTALL_INCLUDE_DIR}/${LOWER_NAME}/${REL_PATH} COMPONENT dev)
endforeach()

# Install the <Project>Config.cmake file
install(FILES ${PROJECT_BINARY_DIR}/install/${CONFIG_FILENAME} DESTINATION ${INSTALL_ARCHIVE_DIR}/${LOWER_NAME})

# Install static lib (.a) in /lib
install(TARGETS ${LOWER_NAME} ARCHIVE DESTINATION ${INSTALL_ARCHIVE_DIR}/${LOWER_NAME})


#############
#  Testing  #
#############
if(Testing)
   add_subdirectory(${TESTS_SUBDIR})
endif()
