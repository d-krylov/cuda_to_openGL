#include "cuda_graphics_resource.h"
#include "glad/glad.h"
#include "renderer.h"
#include "shader_pipeline.h"
#include "vertex_array.h"
#include "window.h"

const char *vertex_shader_source =
    "#version 450\n"
    "layout (location = 0) out vec2 texture_coordinates;\n"
    "out gl_PerVertex {\n"
    " vec4 gl_Position;\n"
    "};\n"
    "void main() {\n"
    " vec2 position = vec2(gl_VertexID % 2, gl_VertexID / 2) * 4.0 - 1;\n"
    " gl_Position = vec4(position, 0.0, 1.0);\n"
    " texture_coordinates = (position + 1) * 0.5;\n"
    "}\0";

const char *fragment_shader_source =
    "#version 450\n"
    "layout (location = 0) in vec2 texture_coordinates;\n"
    "out vec4 fragColor;\n"
    "uniform sampler2D cuda_image;\n"
    "void main() {\n"
    " fragColor = texture(cuda_image, texture_coordinates);\n"
    "}\0";

int main() {

  Window window;

  ShaderPipeline pipeline(vertex_shader_source, fragment_shader_source);

  Texture texture(512, 512);

  VertexArray vao;
  vao.Bind();
  pipeline.Bind();
  texture.Bind(0);

  CUDAGraphicsResource resource;

  resource.RegisterTexture(texture);

  Renderer renderer(512, 512);

  while (!window.ShouldClose()) {

    resource.Begin();

    auto image = resource.GetMappedArray();

    renderer.RunKernel(image);

    resource.End();

    glDrawArrays(GL_TRIANGLES, 0, 3);

    window.Update();
  }

  return 0;
}