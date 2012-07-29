#ifndef DGLW_APPLICATION_HPP_
#define DGLW_APPLICATION_HPP_

#include <string>
#include <functional>
typedef std::function<void()> VoidFunction;

namespace dglw {

class Application {
   public:
      virtual void run() = 0;

      virtual void setTitle(std::string title) =0 ;
      virtual void setSize(const int width, const int height) = 0;

      virtual void setRenderFunction(VoidFunction render_function);
      virtual void setUpdateFunction(VoidFunction update_function);
      virtual void setInitilizeFunction(VoidFunction initilize_function);
      
      unsigned int getWidth();
      unsigned int getHeight();

   protected:
      unsigned int width_;
      unsigned int height_;

      VoidFunction render_function_;
      VoidFunction update_function_;
      VoidFunction initilize_function_;
};

inline void Application::setRenderFunction(VoidFunction render_function) {
   render_function_ = render_function;
}

inline void Application::setUpdateFunction(VoidFunction update_function) {
   update_function_ = update_function;
}

inline void Application::setInitilizeFunction(VoidFunction initilize_function) {
   initilize_function_ = initilize_function;
}

inline unsigned int Application::getWidth() {
   return width_;
}

inline unsigned int Application::getHeight() {
   return height_;
}

} /* namespace dglw */

#endif /* DGLW_APPLICATION_HPP_ */
