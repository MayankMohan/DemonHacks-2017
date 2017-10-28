#include <glm/glm.hpp>
#include <GL/glew.h>
#include "mesh.h"

Mesh::Mesh(Vertex* verts, size_t numverts){
	_drawq = numverts;
	
	glGenVertexArrays(1, &_vertexArray);
	glBindVertexArray(_vertexArray);
	
	glGenBuffers(_NUM_BUFFERS, _vertexBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffers[_BUF_POS]);
	glBufferData(GL_ARRAY_BUFFER, numverts * sizeof(verts[0]), verts, GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	
	glBindVertexArray(0);
}

Mesh::~Mesh(){
	glDeleteVertexArrays(1, &_vertexArray);
}

void Mesh::Draw(){
	glBindVertexArray(_vertexArray);
	
	glDrawArrays(GL_TRIANGLES_ADJACENCY, 0, _drawq);
	
	glBindVertexArray(0);
}
