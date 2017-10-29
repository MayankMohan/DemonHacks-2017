#pragma once

#include <glm/glm.hpp>
#include <GL/glew.h>

#include "transform.h"
#include "shader.h"

class Vertex{
	friend class Mesh;
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
		Mesh(){};
		Mesh(Mesh* m);
		Mesh(Transform* trans, Vertex* verts, size_t numverts);
		~Mesh();
		
		Transform* getTrans(){return _trans;};
		
		void Draw();
	private:
		Transform* _trans;
		
		enum{
			_BUF_POS,
			
			_NUM_BUFFERS //LAST ElEMENT!!!!! IMPORTANT!!!
		};
		
		GLuint _vertexArray;
		GLuint _vertexBuffers[_NUM_BUFFERS];
		
		size_t _drawq;
};
