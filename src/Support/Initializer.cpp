#include <stdexcept>
#include <dglw/Support/Initializer.hpp>

#include <dglw/OpenGL/OpenGL.hpp>
#include <dglw/Renderable/Cube.hpp>
#include <dglw/Renderable/TextureQuad.hpp>

namespace dglw {

Initializer::Initializer() {
   is_initialized_ = false;
}

void Initializer::initialize() {
   if(is_initialized_) {
      DEBUG_M("Already initialized this list...");
      return;
   }

   for(VoidFunction vf : init_list_) {
      if(vf) {
         vf();
      } else {
         DEBUG_M("Bad function in initializing list!");
      }
   }
   is_initialized_ = true;
}

bool Initializer::isInitialized() {
   return is_initialized_;
}

void Initializer::addInitializeFunction(VoidFunction vf) {
   if(is_initialized_) {
      std::string error_msg("Tried to add stuff to an initializer after it was initilized.");
      ERROR("%s", error_msg.c_str());
      throw std::runtime_error(error_msg);
   }
   init_list_.push_back(vf);
}

void initialize() {
   DEBUG_M("Initializing dglw...");
   logGLError();
   if(glGenVertexArrays == nullptr) {
      ERROR("Vertex Array Objects not supported...");
      return;
   }
   Cube::initialize();
   TextureQuad::initialize();
}

} /* namespace dglw */
