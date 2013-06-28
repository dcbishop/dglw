#include <iostream>
#include <glm/glm.hpp>

#ifdef USE_GLFW
#define DGLW_USE_GLFW
#include <dglw/Applications/GLFWApplication.hpp>
#endif

#ifdef USE_QT
#define DGLW_USE_QT
#include <dglw/Applications/QTApplication.hpp>
#endif

#include <dglw/dglw.hpp>
using namespace dglw;

Cube cube;

void render() {
    cube.render();
}

void loadExt() {
    // [TODO]: Load glew or something in here...
}

void resize(int width, int height) {
    glViewport(0, 0, width, height);
}

int main(int argc, char* argv[]) {

#ifdef USE_GLFW
    GLFWApplication app;
#endif
#ifdef USE_QT
    QTApplication app {argc, argv};
#endif

    auto rfunc = std::bind(&render);
    app.setRenderFunction(rfunc);
    app.setExtensionInitFunction(std::bind(&loadExt));
    app.setResizeFunction(std::bind(&resize, std::placeholders::_1, std::placeholders::_2));

    app.setTitle("dglw demo!");
    app.setSize(800, 600);

    app.run();
}
