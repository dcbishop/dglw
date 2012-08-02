#ifndef DGLW_APPLICATION_HPP_
#define DGLW_APPLICATION_HPP_

#include <string>

#include "common.hpp"

namespace dglw {

class Application {
   public:
      virtual void run() = 0;

      virtual void setTitle(std::string title) = 0;
      virtual void setSize(const int width, const int height) = 0;

      virtual void setRenderFunction(VoidFunction render_function);
      virtual void setUpdateFunction(VoidFunction update_function);
      virtual void setGLExtInitializeFunction(VoidFunction initialize_function);
      virtual void setInitializeFunction(VoidFunction initialize_function);
      
      virtual void setCoreProfile(const bool use_core=true);
      
      unsigned int getWidth();
      unsigned int getHeight();

   protected:
      unsigned int width_;
      unsigned int height_;
      bool use_core_profile_;

      VoidFunction render_function_;
      VoidFunction update_function_;
      VoidFunction initialize_function_;
      VoidFunction glext_initialize_function_;
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

inline void Application::setGLExtInitializeFunction(VoidFunction glext_initilize_function) {
   glext_initialize_function_ = glext_initilize_function;
}

inline void Application::setInitializeFunction(VoidFunction initilize_function) {
   initialize_function_ = initilize_function;
}

inline unsigned int Application::getWidth() {
   return width_;
}

inline unsigned int Application::getHeight() {
   return height_;
}

} /* namespace dglw */

#endif /* DGLW_APPLICATION_HPP_ */
