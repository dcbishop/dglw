#ifndef DGLW_SHADER_HPP_
#define DGLW_SHADER_HPP_

#include <vector>
#include <memory>

#include "OpenGL.hpp"

namespace dglw {

class Shader {
   public:
      enum Type: GLenum {
         Vertex         = GL_VERTEX_SHADER,
#ifdef GL_TESS_CONTROL_SHADER
         TessControl    = GL_TESS_CONTROL_SHADER,
#endif
#ifdef GL_TESS_EVALUATION_SHADER
         TessEvaluation = GL_TESS_EVALUATION_SHADER,
#endif
         Geometry       = GL_GEOMETRY_SHADER,
         Fragment       = GL_FRAGMENT_SHADER,
#ifdef GL_COMPUTE_SHADER
         Compute        = GL_COMPUTE_SHADER,
#endif
      };

      Shader(const Type type, std::vector<char> source_code);
      Shader(const Type type, const char* source_code = nullptr, const GLint size=0);
      ~Shader();
      void compile();
      void source(const std::vector<char>& source_code);
      void source(const char* source_code, const GLint size);
      void debugLog() const;
      GLuint getShaderId() const;

   private:
      void init_(const Type type, const char* source_code = nullptr, const GLint size=0);

      GLuint shader_id_;
      const Type type_;
      bool has_source_;
};

typedef std::shared_ptr<Shader> ShaderPtr;

} /* namespace dglw */

#endif /* DGLW_SHADER_HPP_ */
