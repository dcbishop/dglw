#include "GLFWApplication.hpp"

#include "dglw.hpp"
#include <GL/glfw.h>

#include "console.h"
#include "Initializer.hpp"

using namespace dglw;

GLFWApplication::GLFWApplication() {
   setSize(800, 600);
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

   if(use_core_profile_) {
      glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
      glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 2);
      glfwOpenWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
      glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
