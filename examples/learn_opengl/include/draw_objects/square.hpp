#pragma once

#include <opengl/buffer.hpp>
#include <opengl/shader.hpp>
#include <opengl/texture.hpp>

namespace lwgle::draw_objects {

class Square {
public:
    Square() = default;
    virtual ~Square() = default;
    virtual void draw() = 0;
};

class Solid_Square : public Square {
public:
    Solid_Square();
    void draw() override;

private:
    shader::VertexShader vs;
    shader::FragmentShader fs;
    shader::ShaderProgram program;

    buffer::Buffer buf;
};

class Textured_Square : public Square {
public:
    Textured_Square();
    void draw() override;

private:
    shader::VertexShader vs;
    shader::FragmentShader fs;
    shader::ShaderProgram program;
    texture::Texture tex;

    buffer::Buffer buf;
};

class Rainbow_Square : public Square {
public:
    Rainbow_Square();
    void draw() override;

private:
    shader::VertexShader vs;
    shader::FragmentShader fs;
    shader::ShaderProgram program;

    buffer::Buffer buf;
};

enum class SquareType { Solid, Textured, Rainbow };

class SquareFactory {
public:
    SquareFactory() = default;
    SquareFactory(SquareType type) : type(type) {}
    std::unique_ptr<Square> create();

private:
    SquareType type;
};

} // namespace lwgle::draw_objects