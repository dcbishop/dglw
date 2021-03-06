#ifndef DGLW_HPP_
#define DGLW_HPP_

#include "OpenGL/OpenGL.hpp"
#include "OpenGL/Buffer.hpp"
#include "OpenGL/Framebuffer.hpp"
#include "Support/MatrixStack.hpp"
#include "OpenGL/Program.hpp"
#include "OpenGL/Renderbuffer.hpp"
#include "OpenGL/Shader.hpp"
#include "OpenGL/Texture.hpp"
#include "OpenGL/VertexArray.hpp"
#include "Applications/Application.hpp"

#ifdef DGLW_USE_GLFW
#include "Applications/GLFWApplication.hpp"
#endif

#ifdef DGLW_USE_QT
#include "Applications/QTApplication.hpp"
#endif

#include "Renderable/Cube.hpp"
#include "Renderable/TextureQuad.hpp"
#include "Support/ResourceManager.hpp"
#include "Support/UniformBind.hpp"
#include "Support/Initializer.hpp"

#endif /* DGLW_HPP_ */
