#ifndef SHADER_PIPELINE_H
#define SHADER_PIPELINE_H

#include <cstdint>

class ShaderPipeline {
public:
  ShaderPipeline(const char *vertex_source, const char *fragment_source);

  void Bind();

  void LoadVertexShader(const char *source);
  void LoadFragmentShader(const char *source);

protected:
  bool Validate(uint32_t shader);

private:
  uint32_t shader_pipeline_{0};
  uint32_t vertex_shader_{0};
  uint32_t fragment_shader_{0};
};

#endif // SHADER_PIPELINE_H