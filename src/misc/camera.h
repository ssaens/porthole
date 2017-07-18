//
// Created by Dillon Yao on 6/29/17.
//

#ifndef PORTHOLE_CAMERA_H
#define PORTHOLE_CAMERA_H

// Std. Includes
#include <vector>

// GL Includes
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

using namespace glm;

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT,
    UP,
    DOWN,
};

// Default camera values
const float YAW        =  -90.0f;
const float PITCH      =  0.0f;
const float SPEED      =  3.0f;
const float SENSITIVTY =  0.1f;
const float ZOOM       =  M_PI / 4;
const float MIN_ZOOM   =  glm::radians(20.f);
const float MAX_ZOOM   =  ZOOM;
const float NCLIP      =  0.1f;
const float FCLIP      =  100.f;
const float VDIST      =  10.f;

const glm::vec3 DEFAULT_POS = glm::vec3(0.f, 0.f, 2.f);
const glm::vec3 DEFAULT_UP = glm::vec3(0.f, 1.f, 0.f);
const glm::vec3 DEFAULT_FRONT = glm::vec3(0.f, 0.f, -1.f);

class Camera {
public:
    // Camera Attributes
    glm::vec3 pos;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 world_up;

    // Eular Angles
    float yaw;
    float pitch;
    // Camera options
    float movement_speed;
    float mouse_sensitivity;
    float zoom;
    float min_zoom, max_zoom;
    float n_clip, f_clip;
    float view_dist;

    // Constructor with vectors
    Camera(
            glm::vec3 position = DEFAULT_POS,
            glm::vec3 up = DEFAULT_UP,
            float yaw = YAW,
            float pitch = PITCH) :
            pos(position),
            world_up(up),
            yaw(yaw),
            pitch(pitch),
            front(DEFAULT_FRONT),
            movement_speed(SPEED),
            mouse_sensitivity(SENSITIVTY),
            zoom(ZOOM),
            n_clip(NCLIP),
            f_clip(FCLIP),
            view_dist(VDIST),
            min_zoom(MIN_ZOOM),
            max_zoom(MAX_ZOOM)
    {
        this->update_vectors();
    }

    // Constructor with scalar values
    Camera(float posX, float posY, float posZ,
           float upX, float upY, float upZ,
           float yaw, float pitch) :
            front(DEFAULT_FRONT),
            movement_speed(SPEED),
            mouse_sensitivity(SENSITIVTY),
            zoom(ZOOM),
            n_clip(NCLIP),
            f_clip(FCLIP),
            view_dist(VDIST),
            min_zoom(MIN_ZOOM),
            max_zoom(MAX_ZOOM)
    {
        this->pos = glm::vec3(posX, posY, posZ);
        this->world_up = glm::vec3(upX, upY, upZ);
        this->yaw = yaw;
        this->pitch = pitch;
        this->update_vectors();
    }

    // Returns the view matrix calculated using Euler Angles and the LookAt Matrix
    glm::mat4 get_view_matrix() {
        return glm::lookAt(this->pos, this->pos + this->front, this->up);
    }

    void set_position(glm::vec3 new_pos) {
        this->pos = new_pos;
        update_vectors();
    }

private:
    // Calculates the front vector from the Camera's (updated) Euler Angles
    void update_vectors() {
        // Calculate the new Front vector
        glm::vec3 front;
        front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        front.y = sin(glm::radians(this->pitch));
        front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
        this->front = glm::normalize(front);
        // Also re-calculate the Right and Up vector
        this->right = glm::normalize(glm::cross(this->front, this->world_up));  // Normalize the vectors, because their             length gets closer to 0 the more you look up or down which results in slower movement.
        this->up    = glm::normalize(glm::cross(this->right, this->front));
    }
};

#endif //PORTHOLE_CAMERA_H
