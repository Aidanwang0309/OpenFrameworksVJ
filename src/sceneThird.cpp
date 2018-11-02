//
//  sceneThird.cpp
//  FinalProject
//
//  Created by shuai wang on 4/23/18.
//

#include "sceneThird.h"

void sceneThird::init(){
}

void sceneThird::start(ofVec3f _position, ofVec3f _velocity){
    position = _position;
    velocity = _velocity;
}



void sceneThird::resetForce(){
    force.set(0, 0, 0);
}

void sceneThird::updateForce(){
    force -= velocity * friction;
}

void sceneThird::updatePos(){
    velocity += force;
    position += velocity;
}


void sceneThird::draw(){
//    ofSetColor(ofRandom(150,255),ofRandom(111,238),ofRandom(92,180));
    ofDrawCircle(position.x, position.y, position.z, 5);
}


