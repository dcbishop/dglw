#include <iostream>
#include <glm/glm.hpp>

#include <dglw/dglw.hpp>
using namespace dglw;

Cube cube;

void render() {
    cube.render();
}

void loadExt() {
   // [TODO]: Load glew or something in here...
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

    app.setTitle("dglw demo!");
    app.setSize(800, 600);
    
    app.run();
}
