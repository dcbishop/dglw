#include <iostream>
#include <glm/glm.hpp>

#include "dglw.hpp"
using namespace dglw;

Cube cube;

void render() {
    cube.render();
}

int main(int argc, char* argv[]) {
    GLFWApplication app;
    
    auto rfunc = std::bind(&render);
    app.setRenderFunction(rfunc);

    app.setTitle("dglw demo!");
    app.setSize(800, 600);
    
    app.run();
}
