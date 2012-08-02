#include "Initializer.hpp"

#include "Cube.hpp"
#include "TextureQuad.hpp"

namespace dglw {

/*Initializer global_initializer_g;
global_initializer_g.setGlobalDefaults();

void init() {
   if(!global_initializer_g.isInitialized()) {
      global_initializer_g.initialize();
   }
}*/

Initializer::Initializer() {
   // Initialize cube
}

void Initializer::initialize() {
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
   init_list_.push_back(vf);
}

//void Initializer::setGlobalDefaults() {
   //addInitializeFunction(glewInit());
   //addInitializeFunction(Cube::init());
//}

void initialize() {
   DEBUG_M("Initializing dglw...");
   Cube::initialize();
   TextureQuad::initialize();
}

} /* namespace dglw */
