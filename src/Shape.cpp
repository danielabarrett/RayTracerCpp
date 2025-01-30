#include <iostream>
#include <cassert>
#include <memory>

#include "Shape.h"
#include "MatrixStack.h"
#include "tiny_obj_loader.h"

#define EPSILON3 1e-3
#define EPSILON6 1e-6
#define CROSS(dest,v1,v2) \
dest[0]=v1[1]*v2[2]-v1[2]*v2[1]; \
dest[1]=v1[2]*v2[0]-v1[0]*v2[2]; \
dest[2]=v1[0]*v2[1]-v1[1]*v2[0];
#define DOT(v1,v2) (v1[0]*v2[0]+v1[1]*v2[1]+v1[2]*v2[2])
#define SUB(dest,v1,v2) \
dest[0]=v1[0]-v2[0]; \
dest[1]=v1[1]-v2[1]; \
dest[2]=v1[2]-v2[2];

using namespace std;

// / / / / / / / / / / /
// Shape (parent of all other shape types)
// / / / / / / / / / / /

Shape::Shape()
{
}

Shape::~Shape()
{
}

// / / / / / / / / / / /
// Sphere
// / / / / / / / / / / /

Sphere::Sphere() : Shape()
{
}

Sphere::~Sphere()
{
}

std::vector<Hit> Sphere::findHits(const glm::vec3 p, const glm::vec3 v)
{
    std::vector<Hit> hits = std::vector<Hit>();
    float a, b, c, d;
    
    glm::vec3 pc = p - getPosition();
    
    a = dot(v, v);
    b = 2 * dot(v, pc);
    c = dot(pc, pc) - scale * scale;
    d = b * b - 4 * a * c;
    
    if (d < 0) return hits;
    
    float t1 = (- b - sqrt(d)) / (2 * a);
    float t2 = (- b + sqrt(d)) / (2 * a);
    if (abs(t1) < EPSILON3 || abs(t2) < EPSILON3) return hits;
    
    glm::vec3 x1 = glm::vec3(p + t1 * v);
    glm::vec3 x2 = glm::vec3(p + t2 * v);
    glm::vec3 n1 = (x1 - getPosition()) / scale;
    glm::vec3 n2 = (x2 - getPosition()) / scale;
    Material mat = {getKa(), getKd(), getKs(), getS(), getReflect()};
    Hit h1 = {x1, n1, t1, mat};
    Hit h2 = {x2, n2, t2, mat};
    if (h1.t > 0) hits.push_back(h1);
    if (h2.t > 0) hits.push_back(h2);
    return hits;
}

// / / / / / / / / / / /
// Ellipse
// / / / / / / / / / / /

Ellipsoid::Ellipsoid() : Shape()
{
}

Ellipsoid::~Ellipsoid()
{
}

void Ellipsoid::buildE()
{
    std::shared_ptr<MatrixStack> M = std::make_shared<MatrixStack>();
    M->translate(getPosition());
    M->rotate(getRotation().x, 1.0f, 0.0f, 0.0f);
    M->rotate(getRotation().y, 0.0f, 1.0f, 0.0f);
    M->rotate(getRotation().z, 0.0f, 0.0f, 1.0f);
    M->scale(getScale());
    
    E = M->topMatrix();
    Ei = glm::inverse(E);
    Eit = glm::transpose(Ei);
}

std::vector<Hit> Ellipsoid::findHits(const glm::vec3 p, const glm::vec3 v)
{
    std::vector<Hit> hits = std::vector<Hit>();
    glm::vec3 pe = glm::vec3(Ei * glm::vec4(p, 1.0f));
    glm::vec3 ve = normalize(glm::vec3(Ei * glm::vec4(v, 0.0f)));
    
    float a = dot(ve, ve);
    float b = 2 * dot(ve, pe);
    float c = dot(pe, pe) - 1;
    float d = b * b - 4 * a * c;

    if (d > 0) {
        float t1 = (- b - sqrt(d)) / (2 * a);
        float t2 = (- b + sqrt(d)) / (2 * a);
        if (abs(t1) < EPSILON3 || abs(t2) < EPSILON3) return hits;
        glm::vec3 x1 = glm::vec3(pe + t1 * ve);
        glm::vec3 x2 = glm::vec3(pe + t2 * ve);
        glm::vec3 n1 = x1;
        glm::vec3 n2 = x2;
        x1 = glm::vec3(E * glm::vec4(x1, 1.0f));
        x2 = glm::vec3(E * glm::vec4(x2, 1.0f));
        n1 = normalize(glm::vec3(Eit * glm::vec4(n1, 0.0f)));
        n2 = normalize(glm::vec3(Eit * glm::vec4(n2, 0.0f)));
        
        Material mat = {getKa(), getKd(), getKs(), getS(), getReflect()};
        t1 = length(x1 - p);
        t2 = length(x2 - p);
        if (dot(v, x1 - p) < 0) t1 = -t1;
        if (dot(v, x2 - p) < 0) t2 = -t2;
        Hit h1 = {x1, n1, t1, mat};
        Hit h2 = {x2, n2, t2, mat};
        if (h1.t > 0) hits.push_back(h1);
        if (h2.t > 0) hits.push_back(h2);
    }
    return hits;
}

// / / / / / / / / / / /
// Plane
// / / / / / / / / / / /

Plane::Plane() : Shape()
{
}

Plane::~Plane()
{
}

std::vector<Hit> Plane::findHits(const glm::vec3 p, const glm::vec3 v)
{
    std::vector<Hit> hits = std::vector<Hit>();
    float t = dot(normal, (getPosition() - p)) / dot(normal, v);
    if (t < EPSILON3) return hits;
    
    glm::vec3 x = p + t * v;
    Material mat = {getKa(), getKd(), getKs(), getS(), getReflect()};
    Hit h = {x, normal, t, mat};
    hits.push_back(h);
    return hits;
}

// / / / / / / / / / / /
// Object
// / / / / / / / / / / /

Object::Object(const string &meshName) : Shape()
{
    load_mesh(meshName);
    
    // Create bounding sphere
    glm::vec3 vmin(posBuf[0], posBuf[1], posBuf[2]);
    glm::vec3 vmax(posBuf[0], posBuf[1], posBuf[2]);
    for(int i = 0; i < (int)posBuf.size(); i += 3) {
        glm::vec3 v(posBuf[i], posBuf[i+1], posBuf[i+2]);
        vmin.x = min(vmin.x, v.x);
        vmin.y = min(vmin.y, v.y);
        vmin.z = min(vmin.z, v.z);
        vmax.x = max(vmax.x, v.x);
        vmax.y = max(vmax.y, v.y);
        vmax.z = max(vmax.z, v.z);
    }
    glm::vec3 center = 0.5f*(vmin + vmax);
    glm::vec3 diff = vmax - vmin;
    float r = max(max(diff.x, diff.y), diff.z);

    bSphere = Sphere();
    bSphere.setPosition(center);
    bSphere.setScale(r);
}

Object::~Object()
{
}

std::vector<Hit> Object::findHits(const glm::vec3 p, const glm::vec3 v)
{
    vector<Hit> hits = vector<Hit>();
    
    glm::vec3 pP = glm::vec3(Ei * glm::vec4(p, 1.0f));
    glm::vec3 vP = glm::vec3(Ei * glm::vec4(v, 0.0f));
    vP = glm::normalize(vP);
    
    if (bSphere.findHits(pP, vP).size() == 0) return hits;
    float arrP[] = {pP.x, pP.y, pP.z};
    float arrV[] = {vP.x, vP.y, vP.z};
    for(int i = 0; i < (int)posBuf.size(); i += 9) {
        float vert0[] = {posBuf[i+0], posBuf[i+1], posBuf[i+2]};
        float vert1[] = {posBuf[i+3], posBuf[i+4], posBuf[i+5]};
        float vert2[] = {posBuf[i+6], posBuf[i+7], posBuf[i+8]};
        float out_t = 0;
        float out_u = 0;
        float out_v = 0;
        if (intersect_triangle3(arrP, arrV, vert0, vert1, vert2, &out_t, &out_u, &out_v)) {
            float bary1 = out_u;
            float bary2 = out_v;
            float bary0 = 1 - bary1 - bary2;
            
            glm::vec3 pos0(vert0[0], vert0[1], vert0[2]);
            glm::vec3 pos1(vert1[0], vert1[1], vert1[2]);
            glm::vec3 pos2(vert2[0], vert2[1], vert2[2]);
            
            glm::vec3 nor0(norBuf[i+0], norBuf[i+1], norBuf[i+2]);
            glm::vec3 nor1(norBuf[i+3], norBuf[i+4], norBuf[i+5]);
            glm::vec3 nor2(norBuf[i+6], norBuf[i+7], norBuf[i+8]);
            
            glm::vec3 hitPos = bary0 * pos0 + bary1 * pos1 + bary2 * pos2;
            glm::vec3 hitNor = bary0 * nor0 + bary1 * nor1 + bary2 * nor2;
            hitNor = normalize(hitNor);
            
            hitPos = glm::vec3(E * glm::vec4(hitPos, 1.0f));
            hitNor = glm::vec3(Eit * glm::vec4(hitNor, 1.0f));
            hitNor = normalize(hitNor);
            
            Material mat = {getKa(), getKd(), getKs(), getS(), getReflect()};
            float t = length(hitPos - p);
            if (dot(v, hitPos - p) < 0) t = -t;
            Hit h = {hitPos, hitNor, t, mat};
            if (h.t > EPSILON3) hits.push_back(h);
        }
    }
    return hits;
}

void Object::buildE()
{
    std::shared_ptr<MatrixStack> M = std::make_shared<MatrixStack>();
    M->translate(getPosition());
    M->rotate(getRotation().x, 1.0f, 0.0f, 0.0f);
    M->rotate(getRotation().y, 0.0f, 1.0f, 0.0f);
    M->rotate(getRotation().z, 0.0f, 0.0f, 1.0f);
    M->scale(getScale());
    
    E = M->topMatrix();
    Ei = glm::inverse(E);
    Eit = glm::transpose(Ei);
}

void Object::load_mesh(const string &meshName)
{
    // Load geometry
    tinyobj::attrib_t attrib;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    string errStr;
    bool rc = tinyobj::LoadObj(&attrib, &shapes, &materials, &errStr, meshName.c_str());
    if(!rc) {
        cerr << errStr << endl;
    } else {
        // Some OBJ files have different indices for vertex positions, normals,
        // and texture coordinates. For example, a cube corner vertex may have
        // three different normals. Here, we are going to duplicate all such
        // vertices.
        // Loop over shapes
        for(size_t s = 0; s < shapes.size(); s++) {
            // Loop over faces (polygons)
            size_t index_offset = 0;
            for(size_t f = 0; f < shapes[s].mesh.num_face_vertices.size(); f++) {
                size_t fv = shapes[s].mesh.num_face_vertices[f];
                // Loop over vertices in the face.
                for(size_t v = 0; v < fv; v++) {
                    // access to vertex
                    tinyobj::index_t idx = shapes[s].mesh.indices[index_offset + v];
                    posBuf.push_back(attrib.vertices[3*idx.vertex_index+0]);
                    posBuf.push_back(attrib.vertices[3*idx.vertex_index+1]);
                    posBuf.push_back(attrib.vertices[3*idx.vertex_index+2]);
                    if(!attrib.normals.empty()) {
                        norBuf.push_back(attrib.normals[3*idx.normal_index+0]);
                        norBuf.push_back(attrib.normals[3*idx.normal_index+1]);
                        norBuf.push_back(attrib.normals[3*idx.normal_index+2]);
                    }
                }
                index_offset += fv;
                // per-face material (IGNORE)
                shapes[s].mesh.material_ids[f];
            }
        }
    }
}

// This function was copied from the source liked in the assignment overview for optimized triangle-ray tests by Thomas Akenine-Moller
// The url to the source can be found in README.md
int Object::intersect_triangle3(float orig[3], float dir[3], float vert0[3], float vert1[3], float vert2[3], float *t, float *u, float *v)
{
    float edge1[3], edge2[3], tvec[3], pvec[3], qvec[3];
    float det,inv_det;
    
    /* find vectors for two edges sharing vert0 */
    SUB(edge1, vert1, vert0);
    SUB(edge2, vert2, vert0);
    
    /* begin calculating determinant - also used to calculate U parameter */
    CROSS(pvec, dir, edge2);
    
    /* if determinant is near zero, ray lies in plane of triangle */
    det = DOT(edge1, pvec);
    
    /* calculate distance from vert0 to ray origin */
    SUB(tvec, orig, vert0);
    inv_det = 1.0 / det;
    
    CROSS(qvec, tvec, edge1);
    
    if (det > EPSILON6)
    {
        *u = DOT(tvec, pvec);
        if (*u < 0.0 || *u > det)
            return 0;
        
        /* calculate V parameter and test bounds */
        *v = DOT(dir, qvec);
        if (*v < 0.0 || *u + *v > det)
            return 0;
        
    }
    else if(det < -EPSILON6)
    {
        /* calculate U parameter and test bounds */
        *u = DOT(tvec, pvec);
        if (*u > 0.0 || *u < det)
            return 0;
        
        /* calculate V parameter and test bounds */
        *v = DOT(dir, qvec) ;
        if (*v > 0.0 || *u + *v < det)
            return 0;
    }
    else return 0;  /* ray is parallell to the plane of the triangle */
    
    *t = DOT(edge2, qvec) * inv_det;
    (*u) *= inv_det;
    (*v) *= inv_det;
    
    return 1;
}
