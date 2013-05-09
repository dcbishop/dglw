#ifndef DGLW_CUBE_HPP_
#define DGLW_CUBE_HPP_

#include <memory>

#include <glm/glm.hpp>

#include <dglw/OpenGL/VertexArray.hpp>
#include <dglw/OpenGL/Buffer.hpp>

namespace dglw {

class Cube {
   public:
      Cube();
      ~Cube();
      static void initialize();
      static void deinitialize();
      void render();

   private:
      static bool is_initialized_;
      static std::unique_ptr<VertexArray> array_;
      static std::unique_ptr<Buffer> buffer_;
      static unsigned int refs_;
};

} /* namespace dglw */

#endif /* DGLW_CUBE_HPP_ */
