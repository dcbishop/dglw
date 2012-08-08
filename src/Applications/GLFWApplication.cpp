﻿#include "Applications/GLFWApplication.hpp"

#include "dglw.hpp"
#include <GL/glfw.h>

#include "console.h"
#include "Support/Initializer.hpp"

using namespace dglw;

GLFWApplication::GLFWApplication() {
   is_initialized_ = false;
   use_core_profile_ = false;
   opengl_major_ = -1;
   opengl_minor_ = -1;
   opengl_forward_compat_ = -1;
   width_ = 800;
   height_ = 600;
   setCoreProfile(false);
}

GLFWApplication::~GLFWApplication() {
   glfwTerminate();
}

void GLFWApplication::setSize(const int width, const int height) {
   width_ = width;
   height_ = height;

   if(is_initialized_) {
      glfwSetWindowSize(width, height);
   }
}

void GLFWApplication::run() {
   DEBUG_M("Initializing GLFWApplication...");

   bool running = true;
   
   init_list_.addInitializeFunction(std::bind(&dglw::GLFWApplication::initialize_, this)); //Initialize GLFW
   Application::initialize();
   
   while(running) {
      update_();
      render_();
   }
   glfwTerminate();
}

void GLFWApplication::initialize_() {
   LOG("Initializing GLFW...");

   if(!glfwInit()) {
      ERROR("Failed to initialize GLFW.");
      return;
   }

   int major, minor, revision;
   glfwGetVersion(&major, &minor, &revision);
   LOG("GLFW version %d.%d.%d", major, minor, revision);

   if(opengl_forward_compat_ > 0) {
      DEBUG_M("Setting OpenGL forward Compatiblity profile");
      glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   }

   if(use_core_profile_) {
      DEBUG_M("Setting OpenGL core profile");
      glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   }

   if(opengl_major_ >= 0) {
      DEBUG_M("Setting OpenGL major version to %s", opengl_major_);
      glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, opengl_major_);
   }

   if(opengl_minor_ >= 0) {
      DEBUG_M("Setting OpenGL minor version to %s", opengl_minor_);
      glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, opengl_minor_);
   }

   if(!glfwOpenWindow(width_, height_, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
      ERROR("Could now open GLFW window.");
      glfwTerminate();
      return;
   }

   glfwSetWindowTitle("GLFW Application");
   glfwSwapInterval(1);
}

void GLFWApplication::setTitle(std::string title) {
   glfwSetWindowTitle(title.c_str());
}

void GLFWApplication::update_() {
   if(!update_function_) {
      return;
   }

   static double last = glfwGetTime();

   static double current;
   current = glfwGetTime();

   static double diff;
   diff = current - last;

   if(glfwGetTime() != 0.0) {
      last = current;
      update_function_();
   }
}

void GLFWApplication::render_() {
   if(!render_function_) {
      return;
   }

   render_function_();
   glfwSwapBuffers();
}
