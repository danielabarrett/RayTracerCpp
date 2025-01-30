#pragma once
#ifndef Camera_h
#define Camera_h

#include <string>
#include <vector>
#include "Shape.h"
#include "Hit.h"

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

class Camera
{
public:
    Camera();
    Camera(const glm::vec3 &position, float rotation, float fov, float aspect, int resolution);
    virtual ~Camera();
    
    glm::vec3 getPosition() { return position; }
    void setPosition(glm::vec3 position) { this->position = position; }
    float getRotation() { return rotation; }
    void setRotation(float rotation) { this->rotation = rotation; }
    float getFov() { return fov; }
    void setFov(float fov) { this->fov = fov; }
    int getResolution() { return resolution; }
    void setResolution(int resolution);
    glm::vec3** getRays() { return rays; }
    glm::vec3** getColors() { return colors; }
    glm::vec3 getColor(int i, int j) { return colors[i][j]; }
    void setColor(int i, int j, glm::vec3 col) { colors[i][j] = col; }
    void setHit(int i, int j, Hit h);
    Hit h;
    
    
    void createRays();
    void printRays();
private:
    glm::vec3 position;
    float rotation;
    float fov;
    float aspect;
    int resolution;
    glm::vec3 **rays;
    glm::vec3 **colors;
};

#endif
