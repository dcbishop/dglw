################################################################################
# dglw-demo CMake file. - The CMake script for building the project.           #
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

string(TOLOWER "${PROJECT_NAME}-demo" DEMO_PROJECT_NAME)


######################
#  Handle libraries  #
######################

# Add dglw libs
find_package(dglw REQUIRED)
include_directories(${DGLW_INCLUDE_DIRS})

# GLEW
find_package(GLEW REQUIRED)
if(GLEW_FOUND)
   list(APPEND COMMON_LIBS ${GLEW_LIBRARIES})
   add_definitions(-DHAVE_GLEW)
   add_definitions(-DUSE_GLEW)
endif()

# Add Boost libs
find_package(Boost COMPONENTS filesystem system REQUIRED)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    add_definitions(-DHAVE_BOOST)
    list(APPEND COMMON_LIBS ${Boost_LIBRARIES})
else()
    message(FATAL_ERROR "Boost not found!")
endif()

# GLFW
if(USE_GLFW)
   find_package(GLFW)
endif()

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


#######################
#  Build the project  #
#######################
# GLFW target
if(GLFW_FOUND)
    set( GLFW_DEMO_NAME ${DEMO_PROJECT_NAME}-glfw )
    add_executable( ${GLFW_DEMO_NAME} ${GLFW_SOURCES} demo.cpp )
    target_link_libraries( ${GLFW_DEMO_NAME} ${COMMON_LIBS} ${GLFW_LIBRARIES} )
    set_target_properties( ${GLFW_DEMO_NAME} PROPERTIES COMPILE_DEFINITIONS "USE_GLFW" )
endif()

# QT Target
if(HAVE_QT)
   set( CMAKE_AUTOMOC TRUE )
   set( QT_DEMO_NAME ${DEMO_PROJECT_NAME}-qt )
   add_executable( ${QT_DEMO_NAME} demo.cpp )
   target_link_libraries( ${QT_DEMO_NAME} ${COMMON_LIBS} )
   qt5_use_modules( ${QT_DEMO_NAME} Widgets Gui OpenGL )
   set_target_properties( ${QT_DEMO_NAME} PROPERTIES COMPILE_DEFINITIONS "USE_QT" )
endif()
