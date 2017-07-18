//
// Created by Dillon Yao on 6/29/17.
//

#ifndef PORTHOLE_PORTHOLE_H
#define PORTHOLE_PORTHOLE_H

#include "application.h"
#include "../detection/face_detector.h"
#include "../misc/shader.h"
#include "../geometry/mesh.h"
#include "../misc/camera.h"
#include <glm/gtc/type_ptr.hpp>
#include <GL/glew.h>

class Porthole : public Application {
public:
    virtual void init();
    virtual void render();
    virtual void update(float dt);

private:
    FaceDetector face_detector;
    Shader cam_shader, wall_shader, focus_shader;

    GLuint cam_VAO, cam_texture;

    GLuint wall_VAO;

    Mesh focus;

    Camera camera;

    glm::vec3 cam_avg;
    float cam_zoom_avg;
};

#endif //PORTHOLE_PORTHOLE_H
