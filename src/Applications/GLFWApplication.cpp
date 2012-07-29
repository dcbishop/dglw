#include "GLFWApplication.hpp"

#include <dglw/dglw.hpp>
#include <GL/glfw.h>

#include "console.h"

using namespace dglw;

GLFWApplication::GLFWApplication() {
   if(!glfwInit()) {
      ERROR("Failed to initilize GLFW.");
      return;
   }
   setSize(800, 600);
}

GLFWApplication::~GLFWApplication() {
   glfwTerminate();
}

void GLFWApplication::setSize(const int width, const int height) {
   width_ = width;
   height_ = height;

   if(is_initilized_) {
      glfwSetWindowSize(width, height);
   }
}

void GLFWApplication::run() {
   bool running = true;

#ifdef USE_GLEW
   glewInit();
#endif

   if(!glfwOpenWindow(width_, height_, 0, 0, 0, 0, 0, 0, GLFW_WINDOW)) {
      ERROR("Could now open GLFW window.");
      glfwTerminate();
      return;
   }
   glfwSetWindowTitle("GLFW Application");
   
   initilize_function_();

   while(running) {
      update_();
      render_();
   }
}

void GLFWApplication::setTitle(std::string title) {
   glfwSetWindowTitle(title.c_str());
}

void GLFWApplication::update_() {
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
   render_function_();
   glfwSwapBuffers();
}
