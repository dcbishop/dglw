#ifdef USE_QT

#include "Applications/QTWidgets/GLWidget.hpp"

void GLWidget::initializeGL() {
   initialize_function();
}

void GLWidget::resizeGL(int w, int h) {

}

void GLWidget::paintGL() {
   if(render_function) {
      render_function();
   }
}

#endif /* USE_QT */
