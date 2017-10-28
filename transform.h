#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Transform{
	private:
		glm::vec3 _pos;
		glm::vec3 _rot;
		glm::vec3 _scale;
	public:
		Transform(const glm::vec3 &pos = glm::vec3(), const glm::vec3 &rot = glm::vec3(), const glm::vec3 &scale = glm::vec3(1.0f, 1.0f, 1.0f)):
			_pos(pos),
			_rot(rot),
			_scale(scale)
			{
			
		}
		
		//Getters
		inline glm::vec3& getPos(){return _pos;}
		inline glm::vec3& getRot(){return _rot;}
		inline glm::vec3& getScale(){return _scale;}
		
		//Setters
		inline void setPos(glm::vec3& pos){_pos = pos;}
		inline void setRot(glm::vec3& rot){_rot = rot;}
		inline void setScale(glm::vec3& scale){_scale = scale;}
		
		inline glm::mat4 getModel() const{
			glm::mat4 posMat = glm::translate(_pos);
			glm::mat4 xrotMat = glm::rotate(_rot.x, glm::vec3(1,0,0));
			glm::mat4 yrotMat = glm::rotate(_rot.y, glm::vec3(0,1,0));
			glm::mat4 zrotMat = glm::rotate(_rot.z, glm::vec3(0,0,1));
			glm::mat4 scaleMat = glm::translate(_scale);
			
			glm::mat4 rotMat = zrotMat * yrotMat * xrotMat;
			
			return posMat * rotMat * scaleMat;
		}
};
