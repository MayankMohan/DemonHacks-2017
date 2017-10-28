#include "shader.h"

#include <fstream>

Shader::Shader(const std::string& fileName){
	
	_prog = glCreateProgram();
	_shaders[0] = GenShader(LoadShader(fileName + "vsh"), GL_VERTEX_SHADER); //Vertex Shader
	_shaders[1] = GenShader(LoadShader(fileName + "fsh"), GL_FRAGMENT_SHADER); //Fragment Shader
	
	for(size_t i = 0; i < _NUM_SHADERS; i++){
		glAttachShader(_prog, _shaders[i]);
	}
	
	glBindAttribLocation(_prog, 0, "position");
	
	glLinkProgram(_prog);
	CheckShaderError(_prog, GL_LINK_STATUS, true, "Error: Shaders Failed to Link");
	glValidateProgram(_prog);
	CheckShaderError(_prog, GL_VALIDATE_STATUS, true, "Error: Shaders are Invalid");
}

Shader::~Shader(){
	for(size_t i = 0; i < _NUM_SHADERS; i++){
		glDetachShader(_prog, _shaders[i]);
		glDeleteShader(_shaders[i]);
	}
	
	glDeleteProgram(_prog);
	
}

void Shader::Bind(){
	glUseProgram(_prog);
}

GLuint Shader::GenShader(const std::string& source, GLenum shaderType){
	GLuint shader = glCreateShader(shaderType);
	if(shader == 0){
		fprintf(stderr, "Error: Shader Creation Failed!\n");
	}
	
	const GLchar* shaderSource[1];
	GLint shaderSourceLengths[1];
	
	shaderSource[0] = source.c_str();
	shaderSourceLengths[0] = source.length();
	
	glShaderSource(shader, 1, shaderSource, shaderSourceLengths);
	glCompileShader(shader);
	
	CheckShaderError(shader, GL_COMPILE_STATUS, false, "Error: Shader Compilation Failed!");

	
	return shader;
	
}

std::string Shader::LoadShader(const std::string& fileName){
	std::ifstream file;
    file.open(fileName.c_str());

    std::string output;
    std::string line;

    if(file.is_open())
    {
        while(file.good())
        {
            getline(file, line);
			output.append(line + "\n");
        }
    }
    else
    {
		fprintf(stderr, "Unable to load shader: %s\n", fileName.c_str());
    }

    return output;
}

void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage){
    GLint success = 0;
    GLchar error[1024] = { 0 };

    if(isProgram)
        glGetProgramiv(shader, flag, &success);
    else
        glGetShaderiv(shader, flag, &success);

    if(success == GL_FALSE)
    {
        if(isProgram)
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
        else
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);

        fprintf(stderr, "%s: '%s'\n", errorMessage.c_str(), error);
    }
}
