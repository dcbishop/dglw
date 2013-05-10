#include "OpenGL/Program.hpp"
#include "Support/UniformBind.hpp"

#include "console.h"

namespace dglw {

Program::Program() {
   program_id_ = glCreateProgram();
   logGLError();
}

Program::~Program() {
   glDeleteProgram(program_id_);
   logGLError();
}

void Program::attach(ShaderPtr shader) {
   DEBUG_M("Attaching shader '%d' to program '%d'", shader->getShaderId(), program_id_);
   if(shader == ShaderPtr()) {
      ERROR("Tried to attach NULL shader.");
      return;
   }
   glAttachShader(program_id_, shader->getShaderId());
   shaders_.insert(shader);
}

void Program::detach(ShaderPtr shader) {
   ShaderList::iterator itr = shaders_.find(shader);
   shaders_.erase(itr);
   detach(shader);
}

void Program::attach(Shader& shader) {
   // TODO: Remove me? To force use of ShaderPtr
   glAttachShader(program_id_, shader.getShaderId());
   logGLError();
}

void Program::detach(Shader& shader) {
   glAttachShader(program_id_, shader.getShaderId());
   logGLError();
}

void Program::debugLog() const {
   std::string program_log = getInfoLog();
   if(program_log.size() > 0) {
      LOG("ShaderLog: %s", &program_log[0]);
   }
}

std::string Program::getInfoLog() const {
   int length = 0;
   int written_length = 0;
   getProgram(Program::InfoLogLength, &length);
   if(length <= 0) {
      return std::string();
   }

   std::vector<char> program_log(length);
   glGetProgramInfoLog(program_id_, program_log.size(), &length, &program_log[0]);
   return std::string(&program_log[0], length);
}

AttributeList Program::getActiveAttributes() const {
   AttributeList al;

   // Get the number of active attributes
   GLint num_attributes;
   getProgram(Program::ActiveAttributes, &num_attributes);

   // The the maximum size of the attribe names
   GLsizei max_name_length;
   getProgram(Program::ActiveAttributeMaxLength, &max_name_length);

   GLsizei length;
   std::vector<GLchar> name(max_name_length);

   for(int index = 0; index < num_attributes; index++) {
      AttributeInfo ai;

      // Retrive atribute data and store it in the info struct
      ai.index = index;
      glGetActiveAttrib(getProgramId(),
         index,
         name.size(),
         &length,
         &ai.size,
         &ai.type,
         &name[0]);
      ai.name = std::string(&name[0], length);

      al.push_back(ai);
   }
   return al;
}

UniformInfo Program::getUniformInfo(const std::string& name) const {
   GLint index = getUniformLocation(name.c_str());
   return getUniformInfo(index);
}

UniformInfo Program::getUniformInfo(const GLint index) const {
   UniformInfo ui;
   ui.index = index;

   if(index < 0) {
      WARNING("Tried to get info on shader with bad index.");
      ui.name = "";
      ui.size = 0;
      ui.type = 0;
      return ui;
   }

   // The the maximum size of the attribe name
   GLsizei max_name_length;
   getProgram(Program::ActiveUniformMaxLength, &max_name_length);

   GLsizei length;
   std::vector<GLchar> name(max_name_length);

   // Retrive atribute data and store it in the info struct
   glGetActiveUniform(getProgramId(),
      index,
      name.size(),
      &length,
      &ui.size,
      &ui.type,
      &name[0]);
   ui.name = std::string(&name[0], length);
   return ui;
}

UniformList Program::getActiveUniforms() const {
   UniformList ul;

   // Get the number of active attributes
   GLint num_uniforms;
   getProgram(Program::ActiveUniforms, &num_uniforms);

   for(int index = 0; index < num_uniforms; index++) {
      ul.push_back(getUniformInfo(index));
   }
   return ul;
}

UniformBlockList Program::getActiveUniformBlocks() const {
   UniformBlockList ul;

   // Get the number of active attributes
   GLint num_uniform_blocks;
   getProgram(Program::ActiveUniformBlocks, &num_uniform_blocks); // GL: 3.1

   // The the maximum size of the attribe name
   GLsizei max_name_length;
   getProgram(Program::ActiveUniformBlockMaxNameLength, &max_name_length);
   DEBUG_M("Num unifrom blocks %d", num_uniform_blocks);
   for(int ubo_index = 0; ubo_index < num_uniform_blocks; ubo_index++) {
      UniformBlockInfo ubi;

      getActiveUniformBlock(
         ubo_index,
         Program::UniformBlockActiveUniforms,
         &ubi.num_active_uniforms);

      GLsizei name_length;
      getActiveUniformBlock(
         ubo_index,
         Program::UniformBlockNameLength,
         &name_length);

      GLsizei written_name_length;
      std::vector<GLchar> block_name(name_length);
      glGetActiveUniformBlockName(
         getProgramId(),
         ubo_index,
         block_name.size(),
         &written_name_length,
         &block_name[0]
      );

      ubi.name = std::string(&block_name[0], written_name_length);

      getActiveUniformBlock(
         ubo_index,
         Program::UniformBlockBinding,
         &ubi.binding);

      std::vector<GLint> active_uniforms(ubi.num_active_uniforms);
      getActiveUniformBlock(
         ubo_index,
         Program::UniformBlockActiveUniformIndices,
         &active_uniforms[0]);

      ul.push_back(ubi);
   }
   return ul;
}

} /* namespace dglw */
