#ifndef DGLW_APPLICATIONS_GLWIDGET_HPP_
#define DGLW_APPLICATIONS_GLWIDGET_HPP_

#include <QGLWidget>
#include "Support/Initializer.hpp"

#include "console.h"

namespace dglw {

class GLWidget : public QGLWidget {
   Q_OBJECT

   public:
      GLWidget(QWidget *parent = 0);
      void setInitializeFunction(VoidFunction initialize_function);
      void setRenderFunction(VoidFunction render_function);
      void setResizeFunction(std::function<void(int, int)> resize_function);

   protected:
      void initializeGL() override;
      void resizeGL(int w, int h) override;
      void paintGL() override;

   private:
      VoidFunction initialize_function              = nullptr;
      VoidFunction render_function                  = nullptr;
      std::function<void(int, int)> resize_function = nullptr;
};

} /* namespace dglw */

#endif /* WHITEGAME_APPLICATIONS_GLWIDGET_HPP_ */
