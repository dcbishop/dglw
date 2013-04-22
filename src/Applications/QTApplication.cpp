#ifdef USE_QT

#include "Applications/QTApplication.hpp"

#include <QApplication>
#include <QMainWindow>
#include <QGLWidget>
#include <QTranslator>

#include "Applications/QTWidgets/GLWidget.hpp"
#include <dglw/Support/Support.hpp>
using namespace std;
using namespace dglw;

QTApplication::QTApplication() {
   /*int argc = 0;
   QTApplication(&argc, (char**)nullptr);*/
}

QTApplication::~QTApplication() {
    // Empty deconstructor needed for unique_ptr
}

QTApplication::QTApplication(int& argc, char* argv[]) {
   qapp = dglw::make_unique<QApplication>(argc, argv);
   gl = dglw::make_unique<GLWidget>();
}

void QTApplication::run() {
   DEBUG_M("QTApplication::run()");
   gl->setInitializeFunction(std::bind(&Application::initialize, this));
   if(gl) {
      gl->show();
   }
   qapp->exec();
}

void QTApplication::setTitle(const std::string &title) {
   if(gl) {
      gl->setWindowTitle(QObject::tr(title.c_str()));
   }
}

void QTApplication::setSize(const int width, const int height) {
   //Application::setSize(width, height);
   width_ = width;
   height_ = height;
   if(gl) {
      gl->resize(width, height);
   }
}

void QTApplication::setRenderFunction(VoidFunction render_function) {
   Application::setRenderFunction(render_function);
   gl->setRenderFunction(render_function);
}

#endif /* USE_QT */
