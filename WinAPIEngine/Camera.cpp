#include "Camera.h"
#include <numbers>

//For now, rotate like in java3dEngine, using Euler angles
//then once that is working, look into using a forward vector and 
// top vector and then see how that can be converted into quaternions 
// im guessing quaternions are just a combination of forward and top
// since top is restricted by forward
Camera::Camera():
    pos(0.0f,0.0f,5.0f),
    dir(0, 0.0f, std::numbers::pi),
    top(1.0f, 0.0f, 0.0f){
}

void Camera::moveForward(float dt) {
    /*
    const float sinX = sin(dir.x);
    const float cosX = cos(dir.x);
    const float sinY = sin(dir.y);
    const float cosY = cos(dir.y);
    const float sinZ = sin(dir.z);
    const float cosZ = cos(dir.z);
    
    pos.x += sinX * cosY * (speed) * dt;
    pos.y += sinX * sinY * (speed) * dt;
    pos.z += cosX * (speed) * dt;
    */

    double zy = (dir.y);
    double xy = (dir.x + std::numbers::pi / 2.0f);
    double sinZY = sin(zy);
    double sinXY = sin(xy);
    double cosZY = cos(zy);
    double cosXY = cos(xy);

    pos.x -= (sinZY * cosXY * (speed)) * dt;
    pos.y -= (sinZY * sinXY * (speed)) * dt;
    pos.z -= (cosZY * (speed)) * dt;
}

void Camera::moveBack(float dt) {
    double zy = (dir.y);
    double xy = (dir.x + std::numbers::pi / 2.0f);
    double sinZY = sin(zy);
    double sinXY = sin(xy);
    double cosZY = cos(zy);
    double cosXY = cos(xy);

    pos.x += (sinZY * cosXY * (speed)) * dt;
    pos.y += (sinZY * sinXY * (speed)) * dt;
    pos.z += (cosZY * (speed)) * dt;
}

//moveLeft
void Camera::moveLeft(float dt) {
    double xy = (dir.y + std::numbers::pi / 2);
    double xyLeft = (xy + (std::numbers::pi / 2));
    double sinXYLeft = sin(xyLeft);
    double cosXYLeft = cos(xyLeft);

    double zyLeft = std::numbers::pi / 2;
    double sinZYLeft = sin(zyLeft);
    double cosZYLeft = cos(zyLeft);

    pos.x += (sinZYLeft * cosXYLeft * (speed)) * dt;
    pos.y += (sinZYLeft * sinXYLeft * (speed)) * dt;
    pos.z += (cosZYLeft * (speed)) * dt;
}

//moveRight
void Camera::moveRight(float dt) {
    double xy = (dir.y + std::numbers::pi / 2);
    double xyLeft = (xy + (std::numbers::pi / 2));
    double sinXYLeft = sin(xyLeft);
    double cosXYLeft = cos(xyLeft);

    double zyLeft = std::numbers::pi / 2;
    double sinZYLeft = sin(zyLeft);
    double cosZYLeft = cos(zyLeft);

    pos.x -= (sinZYLeft * cosXYLeft * (speed)) * dt;
    pos.y -= (sinZYLeft * sinXYLeft * (speed)) * dt;
    pos.z -= (cosZYLeft * (speed)) * dt;
}

//moveUp
void Camera::moveUp(float dt) {
    pos.z += speed * dt;
}

//moveDown
void Camera::moveDown(float dt) {
    pos.z -= speed * dt;
}

//rotateRight XY
void Camera::rotateRight(float dt) {
    dir.x -= speed * dt / 4;
}

//rotateLeft XY
void Camera::rotateLeft(float dt) {
    dir.x += speed * dt / 4;
}

//rotateUp ZY
void Camera::rotateUp(float dt) {
    dir.y -= speed * dt / 4;
}

//rotateDown ZY
void Camera::rotateDown(float dt) {
    dir.y += speed * dt / 4;
}

// XZ
void Camera::rotateCounterClockwise(float dt) {
    dir.z += speed * dt / 4;
}

// XZ
void Camera::rotateClockwise(float dt) {
    dir.z -= speed * dt / 4;
}
