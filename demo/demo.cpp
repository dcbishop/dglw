#include <iostream>
#include <glm/glm.hpp>

#include "dglw.hpp"
using namespace dglw;

#include <GL/glfw.h>

void createWindow() {
    if(!glfwInit()) {
        std::cerr << "Could not initilize GLFW!\n";
        exit(-1);
    }
    if(!glfwOpenWindow(1024, 768, 0, 0, 0, 0, 32, 0, GLFW_WINDOW)) {
        std::cerr << "Could not opwn GLFW Window!\n";
        glfwTerminate();
        exit(-1);
    }

    glfwSetWindowTitle("This is a demonstration of DGLW!");

    glewInit();
}

void mainLoop() {
    glfwEnable(GLFW_STICKY_KEYS);
    while(glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS && glfwGetWindowParam(GLFW_OPENED)) {
        glfwSwapBuffers();
    }
}

void cleanUp() {
    glfwTerminate();
}

int main(int argc, char* argv[]) {
    createWindow();

    VertexArray va_;
    va_.bind();

    std::vector<GLfloat> triangle = { -1.0f, -1.0f,  0.0f,
                                     1.0f, -1.0f,  0.0f,
                                     0.0f,  1.0f,  0.0f};
    Buffer triangle_b;
    triangle_b.bind(Buffer::Array);
    triangle_b.data(triangle);

    mainLoop();
    cleanUp();
}
