#include <iostream>

#include "SceneLoader.h"

using namespace std;

void SceneLoader::loadScene0(vector<Shape*> &shapes, vector<Light*> &lights) {
    Light *light1 = new Light();
    light1->pos = glm::vec3(-2.0f, 1.0f, 1.0f);
    light1->i = 1.0f;
    lights.push_back(light1);
    
    Sphere *sphere1 = new Sphere();
    sphere1->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    sphere1->setScale(1.0f);
    sphere1->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    sphere1->setKd(glm::vec3(1.0f, 0.0f, 0.0f));
    sphere1->setKs(glm::vec3(1.0f, 1.0f, 0.5f));
    sphere1->setS(100.0f);
    sphere1->setReflect(0.0f);
    shapes.push_back(sphere1);
}

void SceneLoader::loadScene1(vector<Shape*> &shapes, vector<Light*> &lights)
{
    Light *light1 = new Light();
    light1->pos = glm::vec3(-2.0f, 1.0f, 1.0f);
    light1->i = 1.0f;
    lights.push_back(light1);
    
    Sphere *sphere1 = new Sphere();
    sphere1->setPosition(glm::vec3(-0.5f, -1.0f, 1.0f));
    sphere1->setScale(1.0f);
    sphere1->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    sphere1->setKd(glm::vec3(1.0f, 0.0f, 0.0f));
    sphere1->setKs(glm::vec3(1.0f, 1.0f, 0.5f));
    sphere1->setS(100.0f);
    sphere1->setReflect(0.0f);
    shapes.push_back(sphere1);
    
    Sphere *sphere2 = new Sphere();
    sphere2->setPosition(glm::vec3(0.5f, -1.0f, -1.0f));
    sphere2->setScale(1.0f);
    sphere2->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    sphere2->setKd(glm::vec3(0.0f, 1.0f, 0.0f));
    sphere2->setKs(glm::vec3(1.0f, 1.0f, 0.5f));
    sphere2->setS(100.0f);
    sphere2->setReflect(0.0f);
    shapes.push_back(sphere2);
    
    Sphere *sphere3 = new Sphere();
    sphere3->setPosition(glm::vec3(0.0f, 1.0f, 0.0f));
    sphere3->setScale(1.0f);
    sphere3->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    sphere3->setKd(glm::vec3(0.0f, 0.0f, 1.0f));
    sphere3->setKs(glm::vec3(1.0f, 1.0f, 0.5f));
    sphere3->setS(100.0f);
    sphere3->setReflect(0.0f);
    shapes.push_back(sphere3);
}

void SceneLoader::loadScene3(vector<Shape*> &shapes, vector<Light*> &lights) {
    Light *light1 = new Light();
    light1->pos = glm::vec3(1.0f, 2.0f, 2.0f);
    light1->i = 0.5f;
    lights.push_back(light1);
    
    Light *light2 = new Light();
    light2->pos = glm::vec3(-1.0f, 2.0f, -1.0f);
    light2->i = 0.5f;
    lights.push_back(light2);
    
    Plane *plane1 = new Plane();
    plane1->setPosition(glm::vec3(0.0f, -1.0f, 0.0f));
    plane1->setNormal(glm::vec3(0.0f, 1.0f, 0.0f));
    plane1->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    plane1->setKd(glm::vec3(1.0f, 1.0f, 1.0f));
    plane1->setKs(glm::vec3(0.0f, 0.0f, 0.0f));
    plane1->setS(0.0f);
    plane1->setReflect(0.0f);
    shapes.push_back(plane1);
    
    Ellipsoid *ellipsoid1 = new Ellipsoid();
    ellipsoid1->setPosition(glm::vec3(0.5f, 0.0f, 0.5f));
    ellipsoid1->setScale(glm::vec3(0.5f, 0.6f, 0.2f));
    ellipsoid1->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
    ellipsoid1->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    ellipsoid1->setKd(glm::vec3(1.0f, 0.0f, 0.0f));
    ellipsoid1->setKs(glm::vec3(1.0f, 1.0f, 0.5f));
    ellipsoid1->setS(100.0f);
    ellipsoid1->setReflect(0.0f);
    shapes.push_back(ellipsoid1);
    
    Sphere *sphere1 = new Sphere();
    sphere1->setPosition(glm::vec3(-0.5f, 0.0f, -0.5f));
    sphere1->setScale(1.0f);
    sphere1->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    sphere1->setKd(glm::vec3(0.0f, 1.0f, 0.0f));
    sphere1->setKs(glm::vec3(1.0f, 1.0f, 0.5f));
    sphere1->setS(100.0f);
    sphere1->setReflect(0.0f);
    shapes.push_back(sphere1);
}

void SceneLoader::loadScene4(vector<Shape*> &shapes, vector<Light*> &lights) {
    Light *light1 = new Light();
    light1->pos = glm::vec3(-1.0f, 2.0f, 1.0f);
    light1->i = 0.5f;
    lights.push_back(light1);
    
    Light *light2 = new Light();
    light2->pos = glm::vec3(0.5f, -0.5f, 0.0f);
    light2->i = 0.5f;
    lights.push_back(light2);
    
    Sphere *sphere1 = new Sphere();
    sphere1->setPosition(glm::vec3(0.5f, -0.7f, 0.5f));
    sphere1->setScale(0.3f);
    sphere1->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    sphere1->setKd(glm::vec3(1.0f, 0.0f, 0.0f));
    sphere1->setKs(glm::vec3(1.0f, 1.0f, 0.5f));
    sphere1->setS(100.0f);
    sphere1->setReflect(0.0f);
    shapes.push_back(sphere1);
    
    Sphere *sphere2 = new Sphere();
    sphere2->setPosition(glm::vec3(1.0f, -0.7f, 0.0f));
    sphere2->setScale(0.3f);
    sphere2->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    sphere2->setKd(glm::vec3(0.0f, 0.0f, 1.0f));
    sphere2->setKs(glm::vec3(1.0f, 1.0f, 0.5f));
    sphere2->setS(100.0f);
    sphere2->setReflect(0.0f);
    shapes.push_back(sphere2);
    
    Sphere *sphere3 = new Sphere();
    sphere3->setPosition(glm::vec3(-0.5f, 0.0f, -0.5f));
    sphere3->setScale(1.0f);
    sphere3->setKa(glm::vec3(0.0f, 0.0f, 0.0f));
    sphere3->setKd(glm::vec3(0.0f, 0.0f, 0.0f));
    sphere3->setKs(glm::vec3(0.0f, 0.0f, 0.0f));
    sphere3->setS(100.0f);
    sphere3->setReflect(1.0f);
    shapes.push_back(sphere3);
    
    Sphere *sphere4 = new Sphere();
    sphere4->setPosition(glm::vec3(1.5f, 0.0f, -1.5f));
    sphere4->setScale(1.0f);
    sphere4->setKa(glm::vec3(0.0f, 0.0f, 0.0f));
    sphere4->setKd(glm::vec3(0.0f, 0.0f, 0.0f));
    sphere4->setKs(glm::vec3(0.0f, 0.0f, 0.0f));
    sphere4->setS(100.0f);
    sphere4->setReflect(1.0f);
    shapes.push_back(sphere4);
    
    Plane *plane1 = new Plane();
    plane1->setPosition(glm::vec3(0.0f, -1.0f, 0.0f));
    plane1->setNormal(glm::vec3(0.0f, 1.0f, 0.0f));
    plane1->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    plane1->setKd(glm::vec3(1.0f, 1.0f, 1.0f));
    plane1->setKs(glm::vec3(0.0f, 0.0f, 0.0f));
    plane1->setS(0.0f);
    plane1->setReflect(0.0f);
    shapes.push_back(plane1);
    
    Plane *plane2 = new Plane();
    plane2->setPosition(glm::vec3(0.0f, 0.0f, -3.0f));
    plane2->setNormal(glm::vec3(0.0f, 0.0f, 1.0f));
    plane2->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    plane2->setKd(glm::vec3(1.0f, 1.0f, 1.0f));
    plane2->setKs(glm::vec3(0.0f, 0.0f, 0.0f));
    plane2->setS(0.0f);
    plane2->setReflect(0.0f);
    shapes.push_back(plane2);
}

void SceneLoader::loadScene6(vector<Shape*> &shapes, vector<Light*> &lights) {
    Light *light1 = new Light();
    light1->pos = glm::vec3(-1.0f, 1.0f, 1.0f);
    light1->i = 1.0f;
    lights.push_back(light1);
    
    Object *obj1 = new Object("../../resources/bunny.obj");
    obj1->setPosition(glm::vec3(0.0f, 0.0f, 0.0f));
    obj1->setScale(glm::vec3(1.0f, 1.0f, 1.0f));
    obj1->setRotation(glm::vec3(0.0f, 0.0f, 0.0f));
    obj1->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    obj1->setKd(glm::vec3(0.0f, 0.0f, 1.0f));
    obj1->setKs(glm::vec3(1.0f, 1.0f, 0.5f));
    obj1->setS(100.0f);
    obj1->setReflect(0.0f);
    shapes.push_back(obj1);
}

void SceneLoader::loadScene7(vector<Shape*> &shapes, vector<Light*> &lights) {
    Light *light1 = new Light();
    light1->pos = glm::vec3(1.0f, 1.0f, 2.0f);
    light1->i = 1.0f;
    lights.push_back(light1);
    
    Object *obj1 = new Object("../../resources/bunny.obj");
    obj1->setPosition(glm::vec3(0.3, -1.5, 0.0));
    obj1->setScale(glm::vec3(1.5f, 1.5f, 1.5f));
    obj1->setRotation(glm::vec3(M_PI / 9, 0.0f, 0.0f));
    obj1->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    obj1->setKd(glm::vec3(0.0f, 0.0f, 1.0f));
    obj1->setKs(glm::vec3(1.0f, 1.0f, 0.5f));
    obj1->setS(100.0f);
    obj1->setReflect(0.0f);
    shapes.push_back(obj1);
}

void SceneLoader::loadScene9(vector<Shape*> &shapes, vector<Light*> &lights) {
    Light *light1 = new Light();
    light1->pos = glm::vec3(-1.0f, 2.0f, 1.0f);
    light1->i = 0.5f;
    lights.push_back(light1);
    
    Light *light2 = new Light();
    light2->pos = glm::vec3(0.5f, -0.5f, 0.0f);
    light2->i = 0.5f;
    lights.push_back(light2);
    
    Sphere *sphere1 = new Sphere();
    sphere1->setPosition(glm::vec3(0.5f, -0.7f, 0.5f));
    sphere1->setScale(0.3f);
    sphere1->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    sphere1->setKd(glm::vec3(1.0f, 0.0f, 0.0f));
    sphere1->setKs(glm::vec3(1.0f, 1.0f, 0.5f));
    sphere1->setS(100.0f);
    sphere1->setReflect(0.0f);
    shapes.push_back(sphere1);
    
    Sphere *sphere2 = new Sphere();
    sphere2->setPosition(glm::vec3(1.0f, -0.7f, 0.0f));
    sphere2->setScale(0.3f);
    sphere2->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    sphere2->setKd(glm::vec3(0.0f, 0.0f, 1.0f));
    sphere2->setKs(glm::vec3(1.0f, 1.0f, 0.5f));
    sphere2->setS(100.0f);
    sphere2->setReflect(0.0f);
    shapes.push_back(sphere2);
    
    Sphere *sphere3 = new Sphere();
    sphere3->setPosition(glm::vec3(-0.5f, 0.0f, -0.5f));
    sphere3->setScale(1.0f);
    sphere3->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    sphere3->setKd(glm::vec3(1.0f, 0.0f, 0.0f));
    sphere3->setKs(glm::vec3(0.5f, 0.5f, 0.25f));
    sphere3->setS(100.0f);
    sphere3->setReflect(0.2f);
    shapes.push_back(sphere3);
    
    Sphere *sphere4 = new Sphere();
    sphere4->setPosition(glm::vec3(1.5f, 0.0f, -1.5f));
    sphere4->setScale(1.0f);
    sphere4->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    sphere4->setKd(glm::vec3(0.0f, 0.0f, 1.0f));
    sphere4->setKs(glm::vec3(0.5f, 0.5f, 0.25f));
    sphere4->setS(100.0f);
    sphere4->setReflect(0.4f);
    shapes.push_back(sphere4);
    
    Plane *plane1 = new Plane();
    plane1->setPosition(glm::vec3(0.0f, -1.0f, 0.0f));
    plane1->setNormal(glm::vec3(0.0f, 1.0f, 0.0f));
    plane1->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    plane1->setKd(glm::vec3(1.0f, 1.0f, 1.0f));
    plane1->setKs(glm::vec3(0.0f, 0.0f, 0.0f));
    plane1->setS(0.0f);
    plane1->setReflect(0.0f);
    shapes.push_back(plane1);
    
    Plane *plane2 = new Plane();
    plane2->setPosition(glm::vec3(0.0f, 0.0f, -3.0f));
    plane2->setNormal(glm::vec3(0.0f, 0.0f, 1.0f));
    plane2->setKa(glm::vec3(0.1f, 0.1f, 0.1f));
    plane2->setKd(glm::vec3(1.0f, 1.0f, 1.0f));
    plane2->setKs(glm::vec3(0.0f, 0.0f, 0.0f));
    plane2->setS(0.0f);
    plane2->setReflect(0.0f);
    shapes.push_back(plane2);
}

