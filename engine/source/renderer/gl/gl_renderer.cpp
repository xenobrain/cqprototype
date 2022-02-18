#include "gl_renderer.h"
#include <core/logger.h>
#include <platform/sdl2/sdl2_platform.h>
#ifdef __EMSCRIPTEN__
#endif // __EMSCRIPTEN__
#include <SDL.h>
#include <glad.h>

namespace xc {

auto static constexpr vertices = std::array{
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
};

auto static constexpr vertex_shader_source = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;

    void main() {
        gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
    }
)";

auto static constexpr fragment_shader_source = R"(
    #version 330 core
    out vec4 FragColor;

    void main() {
        FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
    }
)";

std::uint32_t vertex_shader_id, fragment_shader_id, shader_program_id;
std::uint32_t vbo_id, vao_id;

SDL_GLContext gl_context;

gl_renderer::gl_renderer(int logical_width, int logical_height) {
    SDL_GL_LoadLibrary(nullptr);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    gl_context = SDL_GL_CreateContext(reinterpret_cast<SDL_Window*>(sdl2_platform::window_handle()));
    if (!gl_context) throw std::runtime_error(SDL_GetError());

    gladLoadGLLoader(SDL_GL_GetProcAddress);

    SDL_GL_SetSwapInterval(1);

    resize(logical_width, logical_height);

    // init
    vertex_shader_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_shader_id, 1, &vertex_shader_source, nullptr);
    glCompileShader(vertex_shader_id);

    auto result = 0;
    glad_glGetShaderiv(vertex_shader_id, GL_COMPILE_STATUS, &result);
    if (!result) {
        auto log_length = 0;
        auto info_log = std::string{};

        glGetShaderiv(vertex_shader_id, GL_INFO_LOG_LENGTH, &log_length);
        info_log.resize(log_length);
        glGetShaderInfoLog(vertex_shader_id, log_length, nullptr, info_log.data());

        log_error("%s", info_log.c_str());
    }

    fragment_shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_shader_id, 1, &fragment_shader_source, nullptr);
    glCompileShader(fragment_shader_id);

    glad_glGetShaderiv(fragment_shader_id, GL_COMPILE_STATUS, &result);
    if (!result) {
        auto log_length = 0;
        auto info_log = std::string{};

        glGetShaderiv(fragment_shader_id, GL_INFO_LOG_LENGTH, &log_length);
        info_log.resize(log_length);
        glGetShaderInfoLog(fragment_shader_id, log_length, nullptr, info_log.data());

        log_error("%s", info_log.c_str());
    }

    shader_program_id = glCreateProgram();
    glAttachShader(shader_program_id, vertex_shader_id);
    glAttachShader(shader_program_id, fragment_shader_id);
    glLinkProgram(shader_program_id);

    glGetProgramiv(shader_program_id, GL_LINK_STATUS, &result);
    if (!result) {
        auto log_length = 0;
        auto info_log = std::string{};

        glGetProgramiv(shader_program_id, GL_INFO_LOG_LENGTH, &log_length);
        info_log.resize(log_length);
        glGetProgramInfoLog(shader_program_id, log_length, nullptr, info_log.data());

        log_error("%s", info_log.c_str());
    }

    glDeleteShader(vertex_shader_id);
    glDeleteShader(fragment_shader_id);

    glGenVertexArrays(1, &vao_id);
    glGenBuffers(1, &vbo_id);

    // Bind the vertex array object
    glBindVertexArray(vao_id);

    // Copy vertex array into an OpenGL buffer
    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);
    glBufferData(GL_ARRAY_BUFFER, vertices.size(), vertices.data(), GL_STATIC_DRAW);

    // Set the vertex attrib pointers
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    // the call to vertex_attrib_pointer registered the vbo
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Rarely necessary ot unbind the VAO
    glBindVertexArray(0);
}

gl_renderer::~gl_renderer() {
    // cleanup
    glDeleteVertexArrays(1, &vao_id);
    glDeleteBuffers(1, &vbo_id);
    glDeleteProgram(shader_program_id);

    SDL_GL_DeleteContext(gl_context);
}

auto gl_renderer::create_texture(char const* path) -> resource_handle {
    return 0u;
}

auto gl_renderer::texture_size(resource_handle texture) -> vector2 {
    return vector2{};
}

auto gl_renderer::set_camera(xc::vector2 const& camera) -> void {

}

auto gl_renderer::clear_screen(color const& clear_color) -> void {
    glClearColor(remap(clear_color.r, 0, 255, 0.f, 1.f),
                 remap(clear_color.g, 0, 255, 0.f, 1.f),
                 remap(clear_color.b, 0, 255, 0.f, 1.f),
                 remap(clear_color.a, 0, 255, 0.f, 1.f));

    glClear(GL_COLOR_BUFFER_BIT);
}

auto gl_renderer::draw_texture(resource_handle          texture,
                               rectangle         const& rect) -> void {

}

auto gl_renderer::draw_texture(resource_handle          texture,
                               rectangle         const& rect,
                               float                    rotation) -> void {

}

auto gl_renderer::draw_texture(resource_handle          texture,
                               rectangle         const& rect,
                               float                    rotation,
                               color             const& tint) -> void {

}

auto gl_renderer::present() -> void {
    // draw some stuff here...
    glUseProgram(shader_program_id);
    glBindVertexArray(vao_id);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    // no need to unbind the vertex array every time

    // swap
    SDL_GL_SwapWindow(reinterpret_cast<SDL_Window*>(sdl2_platform::window_handle()));
}

auto gl_renderer::resize(int width, int height) -> void {
    glViewport(0, 0, width, height);
}

} // namespace xc