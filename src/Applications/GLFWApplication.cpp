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
   
   if(!update_function_) {
      WARNING("You didn't provide an update function.");
   }

   if(!render_function_) {
      WARNING("You didn't provide a render function.");
   }

   if(!glext_initialize_function_) {
#ifdef USE_GLEW
      LOG("Using GLEW for OpenGL extension loading.");
      glext_initialize_function_ = std::bind([](){DEBUG_M("Initializing GLEW..."); glewInit();});
#elif USE_GL3
      LOG("Apparently using gl3.h for OpenGL extention loading. No initialization required.");
#else
      WARNING("There is no OpenGL extension initializer set.");
#endif
   }

   Initializer init;
   init.addInitializeFunction(std::bind(&dglw::GLFWApplication::initialize_, this)); //Initialize GLFW

   if(glext_initialize_function_) {
      init.addInitializeFunction(glext_initialize_function_);
   }

   // Initialize dglw
   init.addInitializeFunction(dglw::initialize);

   if(!initialize_function_) {
      WARNING("You didn't provide an initialization function.");
   } else {
      init.addInitializeFunction(initialize_function_);
   }

   init.initialize();

   while(running) {
      update_();
      render_();
   }
   glfwTerminate();
}

void GLFWApplication::initialize_() {
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
