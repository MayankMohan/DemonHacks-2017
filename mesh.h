#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

class Vertex{
	public:
		Vertex(){}
		Vertex(const glm::vec3 &pos){
			_pos = pos;
		}
		void set(const glm::vec3 &pos){
			_pos = pos;
		}
		
	private:
		glm::vec3 _pos;
};

class Mesh{
	public:
		Mesh(Vertex* verts, size_t numverts);
		~Mesh();
		
		void Draw();
	private:
		
		enum{
			_BUF_POS,
			
			_NUM_BUFFERS //LAST ElEMENT!!!!! IMPORTANT!!!
		};
		
		GLuint _vertexArray;
		GLuint _vertexBuffers[_NUM_BUFFERS];
		
		size_t _drawq;
};
