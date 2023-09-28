#include "shader_pipeline.h"
#include "glad/glad.h"
#include <iostream>

bool ShaderPipeline::Validate(uint32_t shader) {
  int32_t compiled = 0, message_size = 0;
  glProgramParameteri(shader, GL_PROGRAM_SEPARABLE, GL_TRUE);
  glGetProgramiv(shader, GL_LINK_STATUS, &compiled);
  if (compiled == GL_TRUE) {
    return true;
  }
  glGetProgramiv(shader, GL_INFO_LOG_LENGTH, &message_size);
  if (message_size > 0) {
    std::string message(message_size, ' ');
    glGetProgramInfoLog(shader, message_size, nullptr, message.data());
    std::cout << message << std::endl;
  }
  return compiled == GL_TRUE;
}

ShaderPipeline::ShaderPipeline(const char *vertex_source,
                               const char *fragment_source) {
  glCreateProgramPipelines(1, &shader_pipeline_);
  LoadVertexShader(vertex_source);
  LoadFragmentShader(fragment_source);
}

void ShaderPipeline::LoadFragmentShader(const char *source) {
  fragment_shader_ = glCreateShaderProgramv(GL_FRAGMENT_SHADER, 1, &source);
  Validate(fragment_shader_);
  glUseProgramStages(shader_pipeline_, GL_FRAGMENT_SHADER_BIT,
                     fragment_shader_);
}

void ShaderPipeline::LoadVertexShader(const char *source) {
  vertex_shader_ = glCreateShaderProgramv(GL_VERTEX_SHADER, 1, &source);
  Validate(vertex_shader_);
  glUseProgramStages(shader_pipeline_, GL_VERTEX_SHADER_BIT, vertex_shader_);
}

void ShaderPipeline::Bind() { glBindProgramPipeline(shader_pipeline_); }
