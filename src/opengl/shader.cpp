#include "opengl/shader.hpp"

#include <glad/gl.h>

#include <fstream>
#include <sstream>

namespace lwgle::shader {

Shader::Shader(ShaderType type) : type(type) {
    id = glCreateShader((type == ShaderType::Vertex) ? GL_VERTEX_SHADER
                                                     : GL_FRAGMENT_SHADER);
}

Shader::~Shader() {
    glDeleteShader(id);
}

void Shader::load_from_file(fs::path path) {
    std::ifstream ifs(path);

    if (!ifs.is_open()) {
        throw std::runtime_error("Failed to open file: " + path.string());
    }

    std::stringstream ss;
    ss << ifs.rdbuf();

    load_from_memory(ss.str().c_str());
}

void Shader::load_from_memory(const char* data) {
    glShaderSource(id, 1, &data, nullptr);
    glCompileShader(id);

    int success;
    char infoLog[512];
    glGetShaderiv(id, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        throw std::runtime_error(infoLog);
    }
}

void ShaderProgram::setMat4(const char* name, const glm::mat4& mat) {
    glUniformMatrix4fv(glGetUniformLocation(id, name), 1, GL_FALSE, &mat[0][0]);
}

ShaderProgram::ShaderProgram(VertexShader const& vertex,
                             FragmentShader const& fragment)
    : vertex(vertex), fragment(fragment) {
    id = glCreateProgram();
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(id);
}

void ShaderProgram::attachShaders() {
    glAttachShader(id, vertex.get_id());
    glAttachShader(id, fragment.get_id());
    glLinkProgram(id);

    int success;
    char infoLog[512];
    glGetProgramiv(id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(id, 512, NULL, infoLog);
        throw std::runtime_error(infoLog);
    }
}

void ShaderProgram::use() const {
    glUseProgram(id);
}

} // namespace lwgle::shader
