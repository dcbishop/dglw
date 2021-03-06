#ifndef DGLW_PROGRAM_HPP_
#define DGLW_PROGRAM_HPP_

#include <set>
#include <memory>

#include "OpenGL.hpp"
#include "Shader.hpp"

#include <glm/glm.hpp>

namespace dglw {

struct DataTypeInfo {
   std::string name;
   GLuint index;
   GLenum type;
   GLint size;
};

typedef DataTypeInfo AttributeInfo;
typedef DataTypeInfo UniformInfo;

struct UniformBlockInfo {
   GLuint index;
   std::string name;
   GLint binding;
   GLint num_active_uniforms;
   GLsizei max_name_length;
};

typedef std::vector<AttributeInfo> AttributeList;
typedef std::vector<UniformInfo> UniformList;
typedef std::vector<UniformBlockInfo> UniformBlockList;

typedef std::set<ShaderPtr> ShaderList;
class Program {
   public:
      enum Paramater: GLenum {
         UniformBlockBinding = GL_UNIFORM_BLOCK_BINDING,
         UniformBlockDataSize = GL_UNIFORM_BLOCK_DATA_SIZE,
         UniformBlockNameLength = GL_UNIFORM_BLOCK_NAME_LENGTH,
         UniformBlockActiveUniforms = GL_UNIFORM_BLOCK_ACTIVE_UNIFORMS,
         UniformBlockActiveUniformIndices = GL_UNIFORM_BLOCK_ACTIVE_UNIFORM_INDICES,
         UniformBlockRefrencedByVertexShader = GL_UNIFORM_BLOCK_REFERENCED_BY_VERTEX_SHADER,
         UniformBlockRefrencedByGeometryShader = GL_UNIFORM_BLOCK_REFERENCED_BY_GEOMETRY_SHADER,
         UniformBlockRefrencedByFragmentShader = GL_UNIFORM_BLOCK_REFERENCED_BY_FRAGMENT_SHADER,
         UniformType = GL_UNIFORM_TYPE,
         UniformSize = GL_UNIFORM_SIZE,
         UniformNameLength = GL_UNIFORM_NAME_LENGTH,
         UniformBlockIndex = GL_UNIFORM_BLOCK_INDEX,
         UniformOffset = GL_UNIFORM_OFFSET,
         UniformArrayStride = GL_UNIFORM_ARRAY_STRIDE,
         UniformMatrixStride = GL_UNIFORM_MATRIX_STRIDE,
         UniformIsRowMajor = GL_UNIFORM_IS_ROW_MAJOR,
#ifdef GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX
         UniformAtomicCounterBuffer = GL_UNIFORM_ATOMIC_COUNTER_BUFFER_INDEX
#endif
      };
      
      enum ProgramParam: GLenum {
         DeleteStatus = GL_DELETE_STATUS,
         LinkStatus = GL_LINK_STATUS,
         ValidateStatus = GL_VALIDATE_STATUS,
         InfoLogLength = GL_INFO_LOG_LENGTH,
         AttachedShaders = GL_ATTACHED_SHADERS,
         ActiveAttributes = GL_ACTIVE_ATTRIBUTES,
         ActiveAttributeMaxLength = GL_ACTIVE_ATTRIBUTE_MAX_LENGTH,
         ActiveUniforms = GL_ACTIVE_UNIFORMS,
         ActiveUniformBlocks = GL_ACTIVE_UNIFORM_BLOCKS,
         ActiveUniformBlockMaxNameLength = GL_ACTIVE_UNIFORM_BLOCK_MAX_NAME_LENGTH,
         ActiveUniformMaxLength = GL_ACTIVE_UNIFORM_MAX_LENGTH,
#ifdef GL_COMPUTE_WORK_GROUP_SIZE
         ComputeWorkGroupSize = GL_COMPUTE_WORK_GROUP_SIZE,
#endif
#ifdef GL_PROGRAM_BINARY_LENGTH
         ProgramBinaryLength = GL_PROGRAM_BINARY_LENGTH,
#endif
         TransformFeedbackBufferMode = GL_TRANSFORM_FEEDBACK_BUFFER_MODE,
         TransformFeedbackVaryings = GL_TRANSFORM_FEEDBACK_VARYINGS,
         TransformFeedbackVaryingMaxLength = GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH,
         GeometryVerticesOut = GL_GEOMETRY_VERTICES_OUT,
         GeometryInputType = GL_GEOMETRY_INPUT_TYPE,
         GeometryOutputOype = GL_GEOMETRY_OUTPUT_TYPE
      };

      Program();
      ~Program();
      void attach(ShaderPtr shader);
      void detach(ShaderPtr shader);
      void attach(Shader& shader);
      void detach(Shader& shader);
      GLuint getProgramId() const;
      void setProgramId(const GLuint program_id);

      /**
       * Returns a parameter from a program object/
       */
      void getProgram(const ProgramParam param, GLint* params) const;

      /**
       * Gets the shader program's links status.
       * @return true if linked.
       */
      bool getLinkStatus() const;

      /**
       * Retrieves the shader program info log.
       * @return The program info log or an empty string if none exists.
       **/
      std::string getInfoLog() const;

      /**
       * Retrieves a list of the shader program's active attributes.
       * @return a AttributeList (std::vector of AttributeInfo) containg the active attributes.
       */
      AttributeList getActiveAttributes() const;

      /**
       * Retrieves a list of the shader program's active uniforms.
       * @return a UniformList (std::vector of UniformInfo) containg the active uniforms.
       */
      UniformList getActiveUniforms() const;
      UniformBlockList getActiveUniformBlocks() const;

      GLuint getUniformLocation(const GLchar* name) const;
      GLuint getUniformBlockIndex(const GLchar* uniformBlockName) const;
      void getActiveUniformBlock(const GLuint& uniformBlockIndex, const Paramater& pname, GLint* params) const;
      void getActiveUniformBlockName(const GLuint uniformBlockIndex, const GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName) const;
      void getUniformIndices(const GLsizei uniformCount, const GLchar **uniformNames, GLuint *uniformIndices) const; 
      void getActiveUniform(const GLuint& index, const GLsizei& bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) const;
      void getActiveUniformName(const GLuint& uniformIndex, const GLsizei& bufSize, GLsizei* length, GLchar* uniformName) const;
      void getActiveUniforms(const GLsizei& uniformCount, const GLuint* uniformIndices, const Paramater& pname, GLint* params) const;

      void uniformBlockBinding(const GLuint& uniformBlockIndex, const GLuint& uniformBlockBinding);
      void bindAttribLocation(const GLuint index, const GLchar* name);

      void uniform(const glm::mat4& matrix, const GLuint index);
      void uniform(const glm::mat3& matrix, const GLuint index);
      void uniform(const GLfloat& v0, const GLuint& index);
      void uniform(const glm::vec2& v, const GLuint& index);
      void uniform(const glm::vec3& v, const GLuint& index);
      void uniform(const glm::vec4& v, const GLuint& index);

      UniformInfo getUniformInfo(const std::string& name) const;
      UniformInfo getUniformInfo(const GLint index) const;

      void link();
      void use();
      static void unuse();
      void debugLog() const;


   private:
      GLuint program_id_;
      ShaderList shaders_;
};

typedef std::shared_ptr<Program> ProgramPtr;

inline GLuint Program::getProgramId() const {
   return program_id_;
}

inline void Program::setProgramId(const GLuint program_id) {
   program_id_ = program_id;
}

inline void Program::getProgram(const ProgramParam param, GLint* params) const {
   glGetProgramiv(getProgramId(), param, params);
}

inline GLuint Program::getUniformLocation(const GLchar* name) const {
   GLuint location = glGetUniformLocation(getProgramId(), name);
   logGLError();
   return location;
}

inline GLuint Program::getUniformBlockIndex(const GLchar* uniformBlockName) const {
   return glGetUniformBlockIndex(getProgramId(), uniformBlockName);
}

inline void Program::getUniformIndices(const GLsizei uniformCount, const GLchar **uniformNames, GLuint *uniformIndices) const {
   glGetUniformIndices(getProgramId(), uniformCount, uniformNames, uniformIndices);
}

inline void Program::getActiveUniform(const GLuint& index, const GLsizei& bufSize, GLsizei* length, GLint* size, GLenum* type, GLchar* name) const {
   glGetActiveUniform(getProgramId(), index, bufSize, length, size, type, name);
}

inline void Program::getActiveUniformName(const GLuint& uniformIndex, const GLsizei& bufSize, GLsizei* length, GLchar* uniformName) const {
   glGetActiveUniformName(getProgramId(), uniformIndex, bufSize, length, uniformName);
}

inline void Program::getActiveUniforms(const GLsizei& uniformCount, const GLuint* uniformIndices, const Paramater& pname, GLint* params) const {
   glGetActiveUniformsiv(getProgramId(), uniformCount, uniformIndices, pname, params);
}

inline void Program::uniformBlockBinding(const GLuint& uniformBlockIndex, const GLuint& uniformBlockBinding) {
   glUniformBlockBinding(getProgramId(), uniformBlockIndex, uniformBlockBinding);
}

inline void Program::getActiveUniformBlock(const GLuint& uniformBlockIndex, const Paramater& pname, GLint* params) const {
   glGetActiveUniformBlockiv(getProgramId(), uniformBlockIndex, pname, params);
}

inline void Program::getActiveUniformBlockName(const GLuint uniformBlockIndex, const GLsizei bufSize, GLsizei* length, GLchar* uniformBlockName) const {
   glGetActiveUniformBlockName(getProgramId(), uniformBlockIndex, bufSize, length, uniformBlockName);
}

inline void Program::bindAttribLocation(const GLuint index, const GLchar* name) {
   use();
   glBindAttribLocation(program_id_, index, name);
   logGLError();
}

// [TODO]: Provide fallbacks for OpenGL versions that don't support bindless
inline void Program::uniform(const glm::mat4& matrix, const GLuint index) {
   //glProgramUniformMatrix4fv(getProgramId(), index, 1, GL_FALSE, &matrix[0][0]);
   use();
   glUniformMatrix4fv(index, 1, GL_FALSE, &matrix[0][0]);
   logGLError();
}

inline void Program::uniform(const glm::mat3& matrix, const GLuint index) {
   //glProgramUniformMatrix3fv(getProgramId(), index, 1, GL_FALSE, &matrix[0][0]);
   use();
   glUniformMatrix3fv(index, 1, GL_FALSE, &matrix[0][0]);
   logGLError();
}

inline void Program::uniform(const GLfloat& v0, const GLuint& index) {
   //glProgramUniform1f(getProgramId(), index, v0);
   use();
   glUniform1f(index, v0);
}

inline void Program::uniform(const glm::vec2& v, const GLuint& index) {
   //glProgramUniform2f(getProgramId(), index, v[0], v[1]);
   use();
   glUniform2f(index, v[0], v[1]);
}

inline void Program::uniform(const glm::vec3& v, const GLuint& index) {
   //glProgramUniform3f(getProgramId(), index, v[0], v[1], v[2]);
   use();
   glUniform3f(index, v[0], v[1], v[2]);
}

inline void Program::uniform(const glm::vec4& v, const GLuint& index) {
   //glProgramUniform4f(getProgramId(), index, v[0], v[1], v[2], v[3]);
   use();
   glUniform4f(index, v[0], v[1], v[2], v[3]);
}

inline void Program::link() {
   glLinkProgram(program_id_);
   logGLError();
}

inline bool Program::getLinkStatus() const {
   GLint param;
   glGetProgramiv(program_id_, GL_LINK_STATUS, &param);
   return param;
}

inline void Program::use() {
   glUseProgram(program_id_);
   logGLError();
}

inline void Program::unuse() {
   glUseProgram(0);
}

} /* namespace dglw */

#endif /* DGLW_PROGRAM_HPP_ */
