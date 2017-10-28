#include <vector>
#include <map>
#include <cstdio>
#include <cstring>

#include <glm/glm.hpp>

#include "mesh.h"

int parseOBJ(const char* f, Vertex** verts){

	std::vector< unsigned int > vertexIndices;
	std::map<glm::vec2, bool> mappings;
	std::vector< glm::vec3 > temp_vertices;
	
	bool mapinit = false;
		FILE * file = fopen(f, "r");
	if( file == NULL ){
		printf("Impossible to open the file !\n");
		return 0;
	}

	while(true){
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader
		
		if ( strcmp( lineHeader, "v" ) == 0 ){
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			temp_vertices.push_back(vertex);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			
			unsigned int vertexIndex[4];
			int matches = fscanf(file, "%u %u %u %u\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2], &vertexIndex[3]);
			
			//if(matches == 4){
				for(int i = 0; i < matches; i++){
					printf("%d ", vertexIndex[i]);
					printf("%d ", vertexIndex[(i + 1) % matches]);
					//if(mappings.count(glm::vec2(vertexIndex[i], vertexIndex[(i + 1) % matches])) == 0){
					vertexIndices.push_back(vertexIndex[i]);
					vertexIndices.push_back(vertexIndex[(i + 1) % matches]);
					//mappings.insert(std::pair<glm::vec2, bool>(glm::vec2(vertexIndex[i], vertexIndex[(i + 1) % matches]), true));
					//mappings.insert (std::pair<glm::vec2, bool>(glm::vec2(vertexIndex[(i + 1) % matches], vertexIndex[i]), true));
					//}
				
				}
				printf("\n");
			//}
		}
	}
	
	*verts = new Vertex[vertexIndices.size()];
	for(unsigned int i = 0; i < vertexIndices.size(); i++){
		(*verts)[i] = temp_vertices[vertexIndices[i] - 1];
		printf("%f %f %f\n",temp_vertices[vertexIndices[i] - 1].x,temp_vertices[vertexIndices[i] - 1].y,temp_vertices[vertexIndices[i] - 1].z);
	}
	
	fclose(file);
	return vertexIndices.size();
}
