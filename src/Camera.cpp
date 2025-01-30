#include <iostream>
#include <cassert>
#include "Camera.h"
#include "MatrixStack.h"

using namespace std;

Camera::Camera() : 
    position(0.0f, 0.0f, 5.0f),
    rotation(0.0f),
    fov(M_PI / 4),
    aspect(1.0f),
    resolution(3)
{
    colors = new glm::vec3*[resolution];
    rays = new glm::vec3*[resolution];
    for (int i = 0; i < resolution; i++) {
        colors[i] = new glm::vec3[resolution];
        rays[i] = new glm::vec3[resolution];
    }
}

Camera::Camera(const glm::vec3 &position, float rotation, float fov, float aspect, int resolution) :
    position(position),
    rotation(rotation),
    fov(fov),
    aspect(aspect),
    resolution(resolution)
{
    colors = new glm::vec3*[resolution];
    rays = new glm::vec3*[resolution];
    for (int i = 0; i < resolution; i++) {
        colors[i] = new glm::vec3[resolution];
        rays[i] = new glm::vec3[resolution];
    }
}

Camera::~Camera()
{
    for (int i = 0; i < this->resolution; i++) {
        delete[] colors[i];
        delete[] rays[i];
    }
    delete[] colors;
    delete[] rays;
}

void Camera::setResolution(int resolution) {
    for (int i = 0; i < this->resolution; i++) {
        delete[] colors[i];
        delete[] rays[i];
    }
    delete[] colors;
    delete[] rays;
    
    this->resolution = resolution;
    
    colors = new glm::vec3*[resolution];
    rays = new glm::vec3*[resolution];
    for (int i = 0; i < resolution; i++) {
        colors[i] = new glm::vec3[resolution];
        rays[i] = new glm::vec3[resolution];
    }
}

void Camera::createRays()
{
    float height = 2 * tan(fov / 2);
    float delta = height / resolution;
    float offset = delta / 2;
    
    shared_ptr<MatrixStack> M = make_shared<MatrixStack>();
    M->rotate(rotation, 0.0f, 1.0f, 0.0f);
    glm::mat4 R = M->topMatrix();
    
    for (int i = 0; i < resolution; i++) {
        for (int j = 0; j < resolution; j++) {
            glm::vec3 ray = glm::vec3(-height/2 + offset + i * delta, -height/2 + offset + j * delta, -1);
            ray = glm::vec3(R * glm::vec4(ray, 1.0f));
            rays[i][j] = glm::normalize(ray);
        }
    }
}

void Camera::printRays()
{
    for (int i = 0; i < resolution; i++) {
        for (int j = 0; j < resolution; j++) {
            glm::vec3 ray = rays[i][j];
            printf("%.4f, %.4f, %.4f\n", ray.x, ray.y, ray.z);
        }
    }
}
