#ifndef DGLW_GLFWAPPLICATION_HPP_
#define DGLW_GLFWAPPLICATION_HPP_

#include "Application.hpp"

#include <GLFW/glfw3.h>

namespace dglw {

class GLFWApplication : public Application {
   public:
      ~GLFWApplication();

      virtual void run() override;

      void setTitle(const std::string& title) override;
      virtual void setSize(const int width, const int height) override;
      void setResizeFunction(std::function<void(int, int)> resize_function);

   private:
      static void resize_(GLFWwindow* window, int width, int height);
      static void error_(int err, const char* desc);
      void initialize_();
      void update_();
      void render_();

      bool is_initialized_ = false;
      static std::function<void(int, int)> static_resize_function_;
      GLFWwindow* window_id;
};

} /* namespace dglw */

#endif /* DGLW_GLFWAPPLICATION_HPP_ */
