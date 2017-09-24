#pragma once

#include "shadershop.hh"

int32_t _create_program( std::string vs_shader, std::string fs_shader );
void GLAPIENTRY opengl_error_callback( GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam );