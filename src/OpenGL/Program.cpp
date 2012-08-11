#include "OpenGL/Program.hpp"

#include "console.h"

using namespace dglw;

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

void Program::link() {
   glLinkProgram(program_id_);
   logGLError();
}

bool Program::getLinkStatus() const {
   GLint param;
   glGetProgramiv(program_id_, GL_LINK_STATUS, &param);
   return param;
}

void Program::debugLog() const {
   std::string program_log = getInfoLog();
   if(program_log.size() > 0) {
      LOG("ShaderLog: %s", &program_log[0]);
   }
}

std::string Program::getInfoLog() const {
   int length = 0;
   glGetProgramiv(program_id_, GL_INFO_LOG_LENGTH, &length);
   if(length <= 0) {
      return std::string();
   }

   std::vector<char> program_log;
   program_log.resize(length);
   glGetProgramInfoLog(program_id_, length, &length, &program_log[0]);
   return std::string(&program_log[0], length);
}

AttributeList Program::getActiveAttributes() const {
   AttributeList al;

   // Get the number of active attributes
   GLint num_attributes;
   glGetProgramiv(getProgramId(), GL_ACTIVE_ATTRIBUTES, &num_attributes);

   // The the maximum size of the attribe names
   GLsizei max_name_length;
   glGetProgramiv(getProgramId(), GL_ACTIVE_ATTRIBUTE_MAX_LENGTH, &max_name_length);

   GLsizei length;
   GLchar name[max_name_length];

   for(int index = 0; index < num_attributes; index++) {
      AttributeInfo ai;

      // Retrive atribute data and store it in the info struct
      ai.index = index;
      glGetActiveAttrib(getProgramId(),
         index,
         max_name_length,
         &length,
         &ai.size,
         &ai.type,
         &name[0]);
      ai.name = std::string(&name[0], length);

      al.push_back(ai);
   }
   return al;
}
