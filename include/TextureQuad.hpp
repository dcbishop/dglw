#ifndef DGLW_TEXTUREQUAD_HPP_
#define DGLW_TEXTUREQUAD_HPP_

#include <dglw/dglw.hpp>

namespace dglw {

class TextureQuad {
   public:
      TextureQuad();
      ~TextureQuad();
      void render();
      //void setProgram(const dglw::ProgramPtr& program);
      static void initialize();
      static void deinitialize();

   private:
      static unsigned int refs_;
      static bool is_initialized_;

      static dglw::VertexArrayPtr array_;
      static dglw::BufferPtr buffer_;
      //dglw::ProgramPtr program_;
      //GLuint texture_loc_;
      //GLuint time_loc_;
};

} /* namespace dglw */

#endif /* DGLW_TEXTUREQUAD_HPP_ */
