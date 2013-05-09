#ifndef DGLW_GLFWAPPLICATION_HPP_
#define DGLW_GLFWAPPLICATION_HPP_

#include "Application.hpp"

namespace dglw {

class GLFWApplication : public Application {
   public:
      ~GLFWApplication();

      virtual void run() override;

      void setTitle(const std::string& title) override;
      virtual void setSize(const int width, const int height) override;

   private:
      void initialize_();
      void update_();
      void render_();

      bool is_initialized_ = false;
};

} /* namespace dglw */

#endif /* DGLW_GLFWAPPLICATION_HPP_ */
