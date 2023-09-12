#pragma once

#include <filesystem>
#include <fstream>

#include <glm/glm.hpp>

namespace lwgle::shader {

namespace fs = std::filesystem;

enum class ShaderType { Vertex, Fragment };

class Shader {
private:
    unsigned int id;
    ShaderType type;

public:
    Shader(ShaderType type);
    ~Shader();

    void load_from_file(fs::path path);
    void load_from_memory(const char* data);

    unsigned int get_id() const {
        return id;
    };
};

class VertexShader : public Shader {
public:
    VertexShader() : Shader(ShaderType::Vertex) {}

    VertexShader(fs::path path) : Shader(ShaderType::Vertex) {
        load_from_file(path);
    }
};

class FragmentShader : public Shader {
public:
    FragmentShader() : Shader(ShaderType::Fragment) {}

    FragmentShader(fs::path path) : Shader(ShaderType::Fragment) {
        load_from_file(path);
    }
};

class ShaderProgram {
private:
    unsigned int id;

    VertexShader const& vertex;
    FragmentShader const& fragment;

public:
    ShaderProgram(VertexShader const& vertex, FragmentShader const& fragment);
    ~ShaderProgram();

    void attachShaders();
    void use() const;

    void setMat4(const char* name, const glm::mat4& mat);
};

} // namespace lwgle::shader