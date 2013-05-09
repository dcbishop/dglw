#ifndef DGLW_APPLICATIONS_GLWIDGET_HPP_
#define DGLW_APPLICATIONS_GLWIDGET_HPP_

#include <QGLWidget>
#include <dglw/Support/Initializer.hpp>

#include <dglw/console.h>

namespace dglw {

class GLWidget : public QGLWidget {
   Q_OBJECT

   public:
      GLWidget(QWidget *parent = 0) : QGLWidget(parent) {}

      void setInitializeFunction(VoidFunction initialize_function) {
         DEBUG_M("GLWidget::setInitializeFunction");
         this->initialize_function = initialize_function;
      }

      virtual void setRenderFunction(VoidFunction render_function) {
         this->render_function = render_function;
      }

      virtual void setResizeFunction(std::function<void(int, int)> resize_function) {
         this->resize_function = resize_function;
      }

   protected:
      void initializeGL();
      void resizeGL(int w, int h);
      virtual void resizeEvent(QResizeEvent* event);
      void paintGL();

   private:
      VoidFunction initialize_function              = nullptr;
      VoidFunction render_function                  = nullptr;
      std::function<void(int, int)> resize_function = nullptr;
};

} /* namespace dglw */

#endif /* WHITEGAME_APPLICATIONS_GLWIDGET_HPP_ */
