#pragma once

#include <opengl/buffer.hpp>
#include <opengl/shader.hpp>
#include <opengl/texture.hpp>

namespace lwgle::draw_objects {

class Simple_Ortho_Cube {
public:
    Simple_Ortho_Cube() = default;
    virtual ~Simple_Ortho_Cube() = default;
    virtual void draw() = 0;
};

class Solid_Simple_Ortho_Cube : public Simple_Ortho_Cube {
public:
    Solid_Simple_Ortho_Cube();
    void draw() override;

private:
    shader::VertexShader vs;
    shader::FragmentShader fs;
    shader::ShaderProgram program;

    buffer::Buffer buf;
};

class Textured_Simple_Ortho_Cube : public Simple_Ortho_Cube {
public:
    Textured_Simple_Ortho_Cube();
    void draw() override;

private:
    shader::VertexShader vs;
    shader::FragmentShader fs;
    shader::ShaderProgram program;
    texture::Texture tex;

    buffer::Buffer buf;
};

class Rainbow_Simple_Ortho_Cube : public Simple_Ortho_Cube {
public:
    Rainbow_Simple_Ortho_Cube();
    void draw() override;

private:
    shader::VertexShader vs;
    shader::FragmentShader fs;
    shader::ShaderProgram program;

    buffer::Buffer buf;
};

enum class CubeType { Solid, Textured, Rainbow };

class CubeFactory {
public:
    CubeFactory() = default;
    CubeFactory(CubeType type) : type(type) {}
    std::unique_ptr<Simple_Ortho_Cube> create();

private:
    CubeType type;
};

} // namespace lwgle::draw_objects