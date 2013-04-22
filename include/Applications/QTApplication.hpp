#ifndef WHITEGAME_APPLICATIONS_QTAPPLICAION_HPP_
#define WHITEGAME_APPLICATIONS_QTAPPLICAION_HPP_

#ifdef USE_GLEW
#include <GL/glew.h>
#endif

#include <memory>

#include <Applications/Application.hpp>

class QApplication;
class QWidget;
class QMainWindow;
class GLWidget;

class QTApplication : public dglw::Application {
   public:
      QTApplication();
      QTApplication(int& argc, char* argv[]);
      ~QTApplication();

      virtual void run() override;
      virtual void setTitle(const std::string& title) override;
      virtual void setSize(const int width, const int height) override;
      virtual void setRenderFunction(VoidFunction render_function) override;

   private:
      std::unique_ptr<QApplication> qapp;;
      std::unique_ptr<GLWidget> gl;
};

#endif /* WHITEGAME_APPLICATIONS_QTAPPLICAION_HPP_ */
