//
// Created by Dillon Yao on 6/29/17.
//

#ifndef PORTHOLE_PORTHOLE_H
#define PORTHOLE_PORTHOLE_H

#include "application.h"
#include "../detection/face_detector.h"
#include "../misc/shader.h"
#include <GL/glew.h>

class Porthole : public Application {
public:
    virtual void init();
    virtual void render();
    virtual void update(float dt);

private:
    FaceDetector face_detector;

    Shader shader;

    GLuint VAO, texture;
};

#endif //PORTHOLE_PORTHOLE_H
