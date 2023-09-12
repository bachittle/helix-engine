#pragma once

#include <opengl/buffer.hpp>
#include <opengl/shader.hpp>
#include <opengl/texture.hpp>

#include <optional>

namespace lwgle::draw_objects {

class Triangle {
public:
    Triangle() = default;
    virtual ~Triangle() = default;
    virtual void draw() = 0;
};

class Solid_Triangle : public Triangle {
public:
    Solid_Triangle();
    void draw() override;

private:
    shader::VertexShader vs;
    shader::FragmentShader fs;
    shader::ShaderProgram program;

    buffer::Buffer buf;
};

class Textured_Triangle : public Triangle {
public:
    Textured_Triangle();
    void draw() override;

private:
    shader::VertexShader vs;
    shader::FragmentShader fs;
    shader::ShaderProgram program;
    texture::Texture tex;

    buffer::Buffer buf;
};

class Rainbow_Triangle : public Triangle {
public:
    Rainbow_Triangle();
    void draw() override;

private:
    shader::VertexShader vs;
    shader::FragmentShader fs;
    shader::ShaderProgram program;

    buffer::Buffer buf;
};

enum class TriangleType { Solid, Textured, Rainbow };

class TriangleFactory {
public:
    TriangleFactory() = default;
    TriangleFactory(TriangleType type) : type(type) {}

    std::unique_ptr<Triangle> create();

private:
    TriangleType type;
};

} // namespace lwgle::draw_objects