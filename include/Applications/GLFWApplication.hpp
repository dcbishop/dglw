#ifndef DGLW_GLFWAPPLICATION_HPP_
#define DGLW_GLFWAPPLICATION_HPP_

#include "Application.hpp"

namespace dglw {

class GLFWApplication : public Application {
   public:
      GLFWApplication();
      ~GLFWApplication();

      virtual void run() override;

      void setTitle(std::string title) override;
      virtual void setSize(const int width, const int height) override;

   private:
      void initialize_();
      void update_();
      void render_();

      bool is_initialized_;
};

} /* namespace dglw */

#endif /* DGLW_GLFWAPPLICATION_HPP_ */
