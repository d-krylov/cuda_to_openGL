#include "cuda_graphics_resource.h"
#include "glad/glad.h"
#include "renderer.h"
#include "shader_pipeline.h"
#include "vertex_array.h"
#include "window.h"

const char *vertex_shader_source =
    "#version 450 core\n"
    "layout (location = 0) in vec2 in_position;\n"
    "layout (location = 1) in vec3 in_color;\n"
    "layout (location = 0) out vec3 vertex_color;\n"
    "out gl_PerVertex {\n"
    " vec4 gl_Position;\n"
    "};\n"
    "void main() {\n"
    " gl_Position = vec4(in_position, 0.0, 1.0);\n"
    " vertex_color = in_color;\n"
    "}\0";

const char *fragment_shader_source =
    "#version 450 core\n"
    "layout (location = 0) in vec3 vertex_color;\n"
    "out vec4 FragColor;\n"
    "void main() {\n"
    " FragColor = vec4(vertex_color, 1.0);\n"
    "}\0";

int main() {

  Window window;

  ShaderPipeline pipeline(vertex_shader_source, fragment_shader_source);

  VertexArray vao;
  Buffer vbo(512 * 512 * 20);

  vao.SetLayout();
  vao.SetVertexBuffer(vbo);

  vao.Bind();
  pipeline.Bind();

  CUDAGraphicsResource resource;

  resource.RegisterBuffer(vbo);

  while (!window.ShouldClose()) {

    resource.Begin();

    auto image = resource.GetMappedPointer();

    RunKernel((float *)(image.data), 512, 512);

    resource.End();

    glDrawArrays(GL_POINTS, 0, 512 * 512);
    window.Update();
  }

  return 0;
}