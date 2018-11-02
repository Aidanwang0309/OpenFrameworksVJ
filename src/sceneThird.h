#pragma once

#include "ofMain.h"


class sceneThird {
    
public:
    void init();
    void start(ofVec3f _position, ofVec3f _velocity);
    void resetForce();
    void updateForce();
    void updatePos();
    void draw();
    
    ofVec3f position;
    ofVec3f velocity;
    ofVec3f force;
    
    float friction;
    float radius;
    
};


