#ifdef USE_GLFW
#include "Applications/GLFWApplication.hpp"

#include "dglw.hpp"
#include <GLFW/glfw3.h>

#include "console.h"
#include "Support/Initializer.hpp"

using namespace dglw;

std::function<void(int, int)> GLFWApplication::static_resize_function_ = nullptr;

GLFWApplication::~GLFWApplication() {
   glfwTerminate();
}

void GLFWApplication::setSize(const int width, const int height) {
   width_ = width;
   height_ = height;

   if(is_initialized_) {
      glfwSetWindowSize(window_id, width, height);
   }
}

void GLFWApplication::resize_(GLFWwindow* window, int width, int height) {
   DEBUG_M("Resize...");
   if(static_resize_function_) {
      static_resize_function_(width, height);
   }
}

void GLFWApplication::run() {
   DEBUG_M("Initializing GLFWApplication...");

   bool running = true;
   
   init_list_.addInitializeFunction(std::bind(&dglw::GLFWApplication::initialize_, this)); //Initialize GLFW
   Application::initialize();

   while(!glfwWindowShouldClose(window_id)) {
      update_();
      render_();
      glfwPollEvents();
   }
   glfwTerminate();
}

void GLFWApplication::initialize_() {
   LOG("Initializing GLFW...");

   if(!glfwInit()) {
      ERROR("Failed to initialize GLFW.");
      return;
   }

   glfwSetErrorCallback(&GLFWApplication::error_);

   int major, minor, revision;
   glfwGetVersion(&major, &minor, &revision);
   LOG("GLFW version %d.%d.%d", major, minor, revision);

   if(opengl_forward_compat_ > 0) {
      DEBUG_M("Setting OpenGL forward Compatiblity profile");
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
   }

   if(use_core_profile_) {
      DEBUG_M("Setting OpenGL core profile");
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
   }

   if(opengl_major_ >= 0) {
      DEBUG_M("Setting OpenGL major version to %s", opengl_major_);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, opengl_major_);
   }

   if(opengl_minor_ >= 0) {
      DEBUG_M("Setting OpenGL minor version to %s", opengl_minor_);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, opengl_minor_);
   }

   if(opengl_debug_) {
      DEBUG_M("Setting OpenGL debug context...");
      glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
   }

   // Create the window
   window_id = glfwCreateWindow(width_, height_, "GLFW Application", NULL, NULL);
   if(!window_id) {
      ERROR("Could now open GLFW window.");
      glfwTerminate();
      return;
   }
   glfwMakeContextCurrent(window_id);

   glfwSetFramebufferSizeCallback(window_id, &GLFWApplication::resize_);

   glfwSwapInterval(1);
}

void GLFWApplication::setTitle(const std::string& title) {
   glfwSetWindowTitle(window_id, title.c_str());
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
   glfwSwapBuffers(window_id);
}

void GLFWApplication::setResizeFunction(std::function<void(int, int)> resize_function) {
   static_resize_function_ = resize_function;
   Application::setResizeFunction(resize_function);
}

void GLFWApplication::error_(int err, const char* desc) {
   ERROR("GLFW Error #%d: '%s'", err, desc);
}
#endif /* USE_GLFW */
