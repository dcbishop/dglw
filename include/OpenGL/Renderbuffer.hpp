#ifndef DGLW_RENDERBUFFER_HPP_
#define DGLW_RENDERBUFFER_HPP_

#include "OpenGL.hpp"

#include <memory>

namespace dglw {

class Renderbuffer {
   public:
      //static LookupNames FormatNames;

      Renderbuffer() {
         id_ = 0;
         glGenRenderbuffers(1, &id_);
         logGLError();
         DEBUG_M("Generated renderbuffer %d", id_);
      }

      ~Renderbuffer() {
         glDeleteRenderbuffers(1, &id_);
         logGLError();
         DEBUG_M("Deleted renderbuffer %d", id_);
      }

      void bind() {
         glBindRenderbuffer(GL_RENDERBUFFER, id_);
         logGLError();
      }

      void storage(const InternalFormat internalformat, const GLsizei width, const GLsizei height) {
         bind();
         //DEBUG_M("storage(%s, %d, %d)", dglw::FormatNames[internalformat].c_str(), width, height);
         glRenderbufferStorage(GL_RENDERBUFFER, internalformat, width, height);
         logGLError();
      }

      void storageMultisample(const GLsizei samples, const InternalFormat internalformat, const GLsizei width, const GLsizei height) {
         bind();
         glRenderbufferStorageMultisample(GL_RENDERBUFFER, samples, internalformat, width, height);
         logGLError();
      }
      
      GLuint getID() const {
         return id_;
      }

   private:
      GLuint id_;
};
typedef std::shared_ptr<Renderbuffer> RenderbufferPtr;

} /* namespace dglw */

#endif /* DGLW_RENDERBUFFER_HPP_ */

