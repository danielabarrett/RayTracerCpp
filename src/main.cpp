#include <iostream>
#include <string>
#include <cmath>
#include <thread>

#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"

#include "Camera.h"
#include "Image.h"
#include "Shape.h"
#include "SceneLoader.h"

using namespace std;

int REFLECT_CAP = 10;
bool DO_SHADOWS = true;

Hit shootRay(glm::vec3 p, glm::vec3 v, vector<Shape*> shapes) {
    Hit h = Hit();
    for (Shape *shape : shapes) {
        std::vector<Hit> nHits = shape->findHits(p, v);
        if (nHits.size() != 0) {
            for (Hit nHit : nHits) {
                if (h.t == -1 || nHit.t < h.t) {
                    h = nHit;
                    h.mat.ka = shape->getKa();
                    h.mat.kd = shape->getKd();
                    h.mat.ks = shape->getKs();
                    h.mat.s = shape->getS();
                }
            }
        }
    }
    return h;
}

glm::vec3 getRayColor(glm::vec3 p, glm::vec3 v, const vector<Shape*> &shapes, const vector<Light*> &lights, int depth)
{
    Hit hit = shootRay(p, v, shapes);
    if (hit.t == -1) {
        return glm::vec3(0,0,0);
    } else {
        glm::vec3 ca = hit.mat.ka;
        glm::vec3 cd = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 cs = glm::vec3(0.0f, 0.0f, 0.0f);
        for (Light *light : lights) {
            // Shadow ray
            glm::vec3 lightVec = light->pos - hit.x;
            float lightDist = glm::length(lightVec);
            Hit shadowRayHit = shootRay(hit.x, normalize(lightVec), shapes);
            if (!DO_SHADOWS || shadowRayHit.t == -1.0 || shadowRayHit.t > lightDist) {
                glm::vec3 l = normalize(light->pos - hit.x);
                glm::vec3 e = normalize(p - hit.x);
                glm::vec3 h = normalize(l + e);
                cd += light->i * hit.mat.kd * max(0.0f, dot(hit.n, l));
                cs += light->i * hit.mat.ks * pow(max(0.0f, dot(hit.n, h)), hit.mat.s);
            }
        }
        glm::vec3 col = ca + cd + cs;
        
        // Uncomment to output normalsPr
//        col = 0.5f * (hit.n + glm::vec3(1.0f,1.0f,1.0f));
        
        col.x = min(255.0f * col.x, 255.0f);
        col.y = min(255.0f * col.y, 255.0f);
        col.z = min(255.0f * col.z, 255.0f);
        
        if (hit.mat.reflect > 0) {
            glm::vec3 reflCol(0.0f, 0.0f, 0.0f);
            if (depth < REFLECT_CAP) {
                glm::vec3 i = normalize(hit.x - p);
                reflCol = getRayColor(hit.x, glm::reflect(i, hit.n), shapes, lights, depth+1);
            }
            col = (1.0f-hit.mat.reflect) * col + hit.mat.reflect * reflCol;
        }
        
        return col;
    }
}

int main(int argc, char **argv)
{
	if(argc != 4) {
        cout << "Usage: ./A6 <scene number> <Image size> <Image filename>" << endl;
		return 0;
	}
    int sceneNumber = atoi(argv[1]);
    int imageSize = atoi(argv[2]);
    string filename(argv[3]);
    
    auto image = make_shared<Image>(imageSize, imageSize);
    
    Camera cam = Camera();
    cam.setResolution(imageSize);
    
    // / / / / / / / / / / / /
    // Create scene
    // / / / / / / / / / / / /
    
    vector<Shape*> shapes = vector<Shape*>();
    vector<Light*> lights = vector<Light*>();
    switch (sceneNumber) {
        case 1:
            DO_SHADOWS = false;
        case 2:
            SceneLoader::loadScene1(shapes, lights);
            break;
        case 3:
            SceneLoader::loadScene3(shapes, lights);
            break;
        case 4:
            REFLECT_CAP = 1;
        case 5:
            SceneLoader::loadScene4(shapes, lights);
            break;
        case 6:
            SceneLoader::loadScene6(shapes, lights);
            break;
        case 7:
            SceneLoader::loadScene7(shapes, lights);
            break;
        case 8:
            SceneLoader::loadScene1(shapes, lights);
            cam.setPosition(glm::vec3(-3.0f, 0.0f, 0.0f));
            cam.setRotation(-M_PI/2);
            cam.setFov(M_PI / 3);
            break;
        case 9:
            SceneLoader::loadScene9(shapes, lights);
            break;
        default:
            SceneLoader::loadScene0(shapes, lights);
            break;
    }
        
    // / / / / / / / / / / / /
    // Shoot rays
    // / / / / / / / / / / / /
    
    cam.createRays();
    for (int i = 0; i < cam.getResolution(); i++) {
        for (int j = 0; j < cam.getResolution(); j++) {
            glm::vec3 p = cam.getPosition();
            glm::vec3 v = cam.getRays()[i][j];
            cam.setColor(i, j, getRayColor(p, v, shapes, lights, 0));
        }
    }

    // / / / / / / / / / / / /
    // Draw image
    // / / / / / / / / / / / /
    
    float delta = imageSize / cam.getResolution();
    for (int i = 0; i < imageSize; i++) {
        for (int j = 0; j < imageSize; j++) {
            int I = min((float)cam.getResolution()-1, i / delta);
            int J = min((float)cam.getResolution()-1, j / delta);
            glm::vec3 col = cam.getColors()[I][J];
            image->setPixel(i, j, col.r, col.g, col.b);
        }
    }

    image->writeToFile(filename);
	return 0;
}
