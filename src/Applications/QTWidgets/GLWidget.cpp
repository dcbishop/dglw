#ifdef USE_QT

#include <dglw/Applications/QTWidgets/GLWidget.hpp>
using namespace dglw;

#include <QResizeEvent>

GLWidget::GLWidget(QWidget *parent) : QGLWidget(parent) {}

void GLWidget::setInitializeFunction(VoidFunction initialize_function) {
   this->initialize_function = initialize_function;
}

void GLWidget::setRenderFunction(VoidFunction render_function) {
   this->render_function = render_function;
}

void GLWidget::setResizeFunction(std::function<void(int, int)> resize_function) {
   this->resize_function = resize_function;
}

void GLWidget::initializeGL() {
   initialize_function();
}

void GLWidget::resizeEvent(QResizeEvent* event) {
   DEBUG_M("Resize event...");
   int width = event->size().width();
   int height = event->size().height();

   if(resize_function) {
      resize_function(width, height);
   }
}

void GLWidget::resizeGL(int w, int h) {
   DEBUG_M("ResizeGL event...");
}

void GLWidget::paintGL() {
   if(render_function) {
      render_function();
   }
}

#endif /* USE_QT */
