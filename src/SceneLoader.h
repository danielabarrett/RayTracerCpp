#ifndef SceneLoader_h
#define SceneLoader_h

#include <vector>
#include "Shape.h"

class SceneLoader
{
public:
    static void loadScene0(std::vector<Shape*> &shapes, std::vector<Light*> &lights);
    static void loadScene1(std::vector<Shape*> &shapes, std::vector<Light*> &lights);
    // scenes 1 and 2 match
    static void loadScene3(std::vector<Shape*> &shapes, std::vector<Light*> &lights);
    static void loadScene4(std::vector<Shape*> &shapes, std::vector<Light*> &lights);
    // scenes 4 and 5 match
    static void loadScene6(std::vector<Shape*> &shapes, std::vector<Light*> &lights);
    static void loadScene7(std::vector<Shape*> &shapes, std::vector<Light*> &lights);
    static void loadScene8(std::vector<Shape*> &shapes, std::vector<Light*> &lights);
    static void loadScene9(std::vector<Shape*> &shapes, std::vector<Light*> &lights);
};

#endif
