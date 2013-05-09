#ifdef USE_QT

#include <dglw/Applications/QTWidgets/GLWidget.hpp>
using namespace dglw;

#include <QResizeEvent>

void GLWidget::initializeGL() {
   initialize_function();
}

void GLWidget::resizeEvent(QResizeEvent* event) {
   int width = event->size().width();
   int height = event->size().height();

   if(resize_function) {
      resize_function(width, height);
   }
}

void GLWidget::resizeGL(int w, int h) {
}

void GLWidget::paintGL() {
   if(render_function) {
      render_function();
   }
}

#endif /* USE_QT */
