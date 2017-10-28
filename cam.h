#pragma once
#include <glm/glm.hpp>

class Camera{
	private:
		glm::mat4 _perspective;
		glm::vec3 _pos;
		glm::vec3 _fwd;
		glm::vec3 _up;
		
	public:
		Camera(const glm::vec3 &pos, float fov, float aspect, float zmin, float zmax){
			_pos = pos;
			_fwd = glm::vec3(0,0,1);
			_up = glm::vec3(0,1,0);
			_perspective = glm::perspective(fov, aspect, zmin, zmax);
		}
		
		inline glm::mat4 getViewProjection() const{
			return _perspective * glm::lookAt(_pos, _pos + _fwd, _up);
		}
};
