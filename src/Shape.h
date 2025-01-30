#ifndef Shape_h
#define Shape_h

#include <string>
#include <vector>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>

struct Material
{
    glm::vec3 ka {};
    glm::vec3 kd {};
    glm::vec3 ks {};
    float s {};
    float reflect {0};
};

struct Hit
{
    glm::vec3 x {};
    glm::vec3 n {};
    float t {-1};
    
    Material mat {};
};

struct Light
{
    glm::vec3 pos;
    float i;
};

class Shape
{
public:
    Shape();
    virtual ~Shape();
    
    glm::vec3 getKa() { return ka; }
    void setKa(glm::vec3 ka) { this->ka = ka; }
    glm::vec3 getKd() { return kd; }
    void setKd(glm::vec3 kd) { this->kd = kd; }
    glm::vec3 getKs() { return ks; }
    void setKs(glm::vec3 ks) { this->ks = ks; }
    float getS() { return s; }
    void setS(float s) { this->s = s; }
    float getReflect() { return reflect; }
    void setReflect(float reflect) { this->reflect = reflect; }
    
    virtual std::vector<Hit> findHits(const glm::vec3 p, const glm::vec3 v) = 0;
private:
    glm::vec3 ka;
    glm::vec3 kd;
    glm::vec3 ks;
    float s;
    float reflect;
};

class Sphere : public Shape
{
public:
    Sphere();
    ~Sphere();
    glm::vec3 getPosition() { return position; }
    void setPosition(glm::vec3 position) { this->position = position; }
    float getScale() { return scale; }
    void setScale(float scale) { this->scale = scale; }
    
    std::vector<Hit> findHits(const glm::vec3 p, const glm::vec3 v) override;
private:
    glm::vec3 position;
    float scale;
};

class Ellipsoid : public Shape
{
public:
    Ellipsoid();
    ~Ellipsoid();
    glm::vec3 getPosition() { return position; }
    void setPosition(glm::vec3 position) { this->position = position; buildE(); }
    glm::vec3 getRotation() { return rotation; }
    void setRotation(glm::vec3 rotation) { this->rotation = rotation; buildE(); }
    glm::vec3 getScale() { return scale; }
    void setScale(glm::vec3 scale) { this->scale = scale; buildE(); }
    
    std::vector<Hit> findHits(const glm::vec3 p, const glm::vec3 v) override;
private:
    void buildE();
    glm::mat4 E;
    glm::mat4 Ei;
    glm::mat4 Eit;
    
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

class Plane : public Shape
{
public:
    Plane();
    ~Plane();
    glm::vec3 getPosition() { return position; }
    void setPosition(glm::vec3 position) { this->position = position; }
    glm::vec3 getNormal() { return normal; }
    void setNormal(glm::vec3 normal) { this->normal = normal; }
    
    std::vector<Hit> findHits(const glm::vec3 p, const glm::vec3 v) override;
private:
    glm::vec3 position;
    glm::vec3 normal;
};

class Object : public Shape
{
public:
    Object(const std::string &meshName);
    ~Object();
    glm::vec3 getPosition() { return position; }
    void setPosition(glm::vec3 position) { this->position = position; buildE(); }
    glm::vec3 getRotation() { return rotation; }
    void setRotation(glm::vec3 rotation) { this->rotation = rotation; buildE(); }
    glm::vec3 getScale() { return scale; }
    void setScale(glm::vec3 scale) { this->scale = scale; buildE(); }
    
    std::vector<Hit> findHits(const glm::vec3 p, const glm::vec3 v) override;
    
private:
    void buildE();
    void load_mesh(const std::string &meshName);
    int intersect_triangle3(float orig[3], float dir[3], float vert0[3], float vert1[3], float vert2[3], float *t, float *u, float *v);
    
    Sphere bSphere;
    
    glm::mat4 E;
    glm::mat4 Ei;
    glm::mat4 Eit;
    
    std::vector<float> posBuf;
    std::vector<float> norBuf;
    
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;
};

#endif
