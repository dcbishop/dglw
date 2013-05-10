#ifndef DGLW_APPLICATION_HPP_
#define DGLW_APPLICATION_HPP_

#include <string>

#include "Support/Initializer.hpp"
#include "OpenGL/OpenGL.hpp"
#include "common.hpp"
#include "console.h"

namespace dglw {

class Application {
   public:
      virtual void run() = 0;
      virtual void initialize();

      // Methods to set application properties
      virtual void setTitle(const std::string& title) = 0;
      virtual void setSize(const int width, const int height) = 0;

      // Methods to set function callbacks
      virtual void setRenderFunction(VoidFunction render_function);
      virtual void setUpdateFunction(VoidFunction update_function);
      virtual void setInitializeFunction(VoidFunction initialize_function);
      virtual void setExtensionInitFunction(VoidFunction extinit_function);
      virtual void setResizeFunction(std::function<void(int, int)> resize_function);
      
      virtual void setCoreProfile(const bool use_core=true);

      void setOpenGLVersion(const int major, const int minor);
      void setForwardCompat(const bool forward=true);
      void setDebugContext(const bool debug=true);

      unsigned int getWidth();
      unsigned int getHeight();

   protected:
      Initializer   init_list_;

      unsigned int  width_                  = 640;
      unsigned int  height_                 = 480;
      int           opengl_major_           = -1;
      int           opengl_minor_           = -1;
      char          opengl_forward_compat_  = -1;
      bool          use_core_profile_       = false;
      bool          is_initialized_         = false;
      bool          opengl_debug_           = false;

      VoidFunction  render_function_        = nullptr;
      VoidFunction  update_function_        = nullptr;
      VoidFunction  initialize_function_    = nullptr;
      VoidFunction  extinit_function_       = nullptr;
      std::function<void(int, int)> resize_function_ = nullptr;
};

inline void Application::setCoreProfile(const bool use_core_profile) {
   use_core_profile_ = use_core_profile;
}

inline void Application::setRenderFunction(VoidFunction render_function) {
   render_function_ = render_function;
}

inline void Application::setUpdateFunction(VoidFunction update_function) {
   update_function_ = update_function;
}

inline void Application::setInitializeFunction(VoidFunction initilize_function) {
   initialize_function_ = initilize_function;
}

inline void Application::setExtensionInitFunction(VoidFunction extinit_function) {
   extinit_function_ = extinit_function;
}

inline void Application::setResizeFunction(std::function<void(int, int)> resize_function) {
   resize_function_ = resize_function;
}

inline unsigned int Application::getWidth() {
   return width_;
}

inline unsigned int Application::getHeight() {
   return height_;
}

inline void Application::initialize() {
   DEBUG_M("Initializing Application...");

   bool running = true;

   if(!update_function_) {
      WARNING("You didn't provide an update function.");
   }

   if(!render_function_) {
      WARNING("You didn't provide a render function.");
   }

   // Initialize OpenGL extentions
   if(extinit_function_) {
      LOG("Using supplied OpenGL init function.");
      init_list_.addInitializeFunction(extinit_function_);
   } else {
#ifdef USE_GLEW
   LOG("Using GLEW for OpenGL extension loading.");
   init_list_.addInitializeFunction(
      [](){
         LOG("Initializing GLEW...");
         //glewExperimental = true;
         GLenum err = glewInit();
         if(err != GLEW_OK) {
            ERROR("Failed to initialize GLEW!");
         }
         LOG("GLEW Version: %s", glewGetString(GLEW_VERSION));
      }
   );
#elif USE_GLCOREARB
   // [TODO]: This is only the case when using GLCOREARB_PROTOTYPES on Linux...
   DEBUG_M("Apparently using glcorearb.h for OpenGL extention loading. No initialization required.");
#else
   WARNING("There is no OpenGL extension initializer set.");
#endif
   }

   // Log OpenGL version
   auto version_function = []() {
      if(glGetString == nullptr) {
         ERROR("glGetString is not defined!");
         return;
      } else {
         const GLubyte* gl_version = glGetString(GL_VERSION);
         LOG("OpenGL %s", gl_version);

      }
   };
   init_list_.addInitializeFunction(version_function);
   
   // Initialize dglw
   init_list_.addInitializeFunction(dglw::initialize);

   // Execute userdefined initilize function
   if(initialize_function_) {
      init_list_.addInitializeFunction(initialize_function_);
   }

   // Actually initilize everything
   init_list_.initialize();

   is_initialized_ = true; 
}

inline void Application::setOpenGLVersion(const int major, const int minor) {
   opengl_major_ = major;
   opengl_minor_ = minor;
}

inline void Application::setForwardCompat(const bool forward) {
   opengl_forward_compat_ = forward;
}

inline void Application::setDebugContext(const bool debug) {
   opengl_debug_ = debug;
}

} /* namespace dglw */

#endif /* DGLW_APPLICATION_HPP_ */
