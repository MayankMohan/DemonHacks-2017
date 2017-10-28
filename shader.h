#pragma once

#include <string>

#include <GL/glew.h>

class Shader{
	public:
		Shader(const std::string& fileName);
		~Shader();
		
		void Bind();
		GLuint GenShader(const std::string& source, GLenum shaderType);
		
		std::string LoadShader(const std::string& fileName);
		void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
	private:
	static const size_t _NUM_SHADERS = 2;
	GLuint _prog;
	GLuint _shaders[_NUM_SHADERS];
};
