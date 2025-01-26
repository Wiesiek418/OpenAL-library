#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


//TODO: Do poprawy na razie testy
class Camera {
private:
	glm::vec3 position;
	glm::vec3 target;
	glm::vec3 up;
    glm::mat4 viewMatrix;

    void updateViewMatrix()
    {
        viewMatrix = glm::lookAt(position, position + target, up);
    }

public:

    Camera()
        :position(0.0f, 0.0f, 3.0f),
        target(0.0f, 0.0f, -1.0f),
        up(0.0f, 1.0f, 0.0f) 
    {
        updateViewMatrix();
    };
       
    void setPosition(glm::vec3 pos)
    {
        position = pos;
    }

    void moveForward(float delta)
    {
        position += target * delta;
        updateViewMatrix();
    }

    void moveBackward(float delta)
    {
        position -= target * delta;
        updateViewMatrix();
    }

    void moveLeft(float delta)
    {
        position -= glm::normalize(glm::cross(target, up)) * delta;
        updateViewMatrix();
    }

    void moveRight(float delta)
    {
        position += glm::normalize(glm::cross(target, up)) * delta;
        updateViewMatrix();
    }

    glm::mat4 getViewMatrix()
    {
        return viewMatrix;
    }
    


};