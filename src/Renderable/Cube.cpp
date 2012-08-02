#include "Cube.hpp"

#include <vector>
using std::vector;

using glm::vec3;



#include "console.h"

namespace dglw {

bool Cube::is_initialized_ = false;
unsigned int Cube::refs_ = 0;
std::unique_ptr<dglw::VertexArray> Cube::array_;
std::unique_ptr<dglw::Buffer> Cube::buffer_;

Cube::Cube() {
   /*if(!is_initialized_) {
      init();
   }*/

   refs_++;

   logGLError();
}

Cube::~Cube() {
   refs_--;
   /*if(refs_ == 0) {
      deinit();
   }*/
}

void Cube::initialize() {
   if(is_initialized_) {
      return;
   }
   DEBUG_M("Initializing Cube archtype...");
   GLfloat p = 0.5f;
   GLfloat n = -p;

   // Vertices   
   vec3 rtf (p, p, p);
   vec3 rtb (p, p, n);
   vec3 rbf (p, n, p);
   vec3 rbb (p, n, n);
   vec3 ltf (n, p, p);
   vec3 ltb (n, p, n);
   vec3 lbf (n, n, p);
   vec3 lbb (n, n, n);

   // Normals
   vec3 nf        (0.0f,  0.0f,  1.0f);
   vec3 nb        (0.0f,  0.0f, -1.0f);
   vec3 nu        (0.0f,  1.0f,  0.0f);
   vec3 nd        (0.0f, -1.0f,  0.0f);
   vec3 nl        (-1.0f, 0.0f,  0.0f);
   vec3 nr        (1.0f,  0.0f,  0.0f);

   // Colors
   vec3 red       (1.0f,  0.0f,  0.0f);
   vec3 green     (0.0f,  1.0f,  0.0f);
   vec3 blue      (0.0f,  0.0f,  1.0f);
   vec3 yellow    (1.0f,  1.0f,  0.0f);
   vec3 cyan      (0.0f,  1.0f,  1.0f);
   vec3 magenta   (1.0f,  0.0f,  1.0f);

   // C++11 only! Uniform initilization.
   vector<vec3> vertices {
      rtf, nf, red,     ltf, nf, red,     lbf, nf, red,     rbf, nf, red,     rtf, nf, red,     lbf, nf, red,     // Front
      rtb, nb, green,   lbb, nb, green,   ltb, nb, green,   rbb, nb, green,   lbb, nb, green,   rtb, nb, green,   // Back
      ltf, nl, blue,    ltb, nl, blue,    lbb, nl, blue,    ltf, nl, blue,    lbb, nl, blue,    lbf, nl, blue,    // Left 
      rtb, nr, yellow,  rtf, nr, yellow,  rbf, nr, yellow,  rbb, nr, yellow,  rtb, nr, yellow,  rbf, nr, yellow,  // Right
      ltf, nu, cyan,    rtf, nu, cyan,    rtb, nu, cyan,    rtb, nu, cyan,    ltb, nu, cyan,    ltf, nu, cyan,    // Top
      rbb, nd, magenta, rbf, nd, magenta, lbf, nd, magenta, lbf, nd, magenta, lbb, nd, magenta, rbb, nd, magenta  // Bottom
   };
   Cube::array_.reset(new VertexArray);
   Cube::buffer_.reset(new Buffer);

   Cube::array_->bind();
   logGLError();
   Cube::buffer_->bind();
   logGLError();
   Cube::buffer_->data(vertices.size()*sizeof(vec3), &vertices[0][0]);
   glVertexAttribPointer(AttributeIndex::Vertex, 3, GL_FLOAT, GL_FALSE, sizeof(vec3)*3, 0);
   glVertexAttribPointer(AttributeIndex::Normal, 3, GL_FLOAT, GL_FALSE, sizeof(vec3)*3, (char*)(sizeof(vec3)));
   glVertexAttribPointer(AttributeIndex::Color, 3, GL_FLOAT, GL_FALSE, sizeof(vec3)*3, (char*)((sizeof(vec3))*2));

   logGLError();
   glEnableVertexAttribArray(AttributeIndex::Vertex);
   glEnableVertexAttribArray(AttributeIndex::Normal);
   glEnableVertexAttribArray(AttributeIndex::Color);
   logGLError();
   Cube::is_initialized_  = true;
}

void Cube::deinitialize() {
   is_initialized_ = false;
   array_->bind();
   buffer_->bind();
   glDisableVertexAttribArray(AttributeIndex::Vertex);
   glDisableVertexAttribArray(AttributeIndex::Normal);
   glDisableVertexAttribArray(AttributeIndex::Color);
   buffer_->unbind();
   array_->unbind();
}

void Cube::render() {
   assert(this->is_initialized_);
   logGLError();
   array_->bind();
   logGLError();
   static int verticies_count = buffer_->getBufferSize()/sizeof(glm::vec3)/3;
   glDrawArrays(GL_TRIANGLES, 0, verticies_count);
   // Cheap hack to draw wireframe
   /*for(int i = 0; i < buffer_.getSize(); i += 3)
      glDrawArrays(GL_LINE_LOOP, i, 3);*/

   logGLError();
}

} /* namespace dglw */
