//
//  sceneFirst.cpp
//  FinalProject
//
//  Created by shuai wang on 4/23/18.
//

#include "sceneFirst.h"

sceneFirst::sceneFirst(){
    
    ofSetFrameRate(60);
    ofSetCircleResolution(150);
    ofSetRectMode(OF_RECTMODE_CORNER);


    radius = ofRandom(10, 30);
    lineWidth = ofRandom(0.5, 0.9);
    expandRate = ofRandom(2,5);
    
    dead = false;
    timer = 100;
}

void sceneFirst::update() {
    radius += expandRate;
    
    r += 1;
    g += 1;
    b += 1;
    
    timer -= 1;
    
    if (timer < 0) {
        dead = true;
    }
}



void sceneFirst::draw(){
    ofSetColor(r, g, b, 255);
    ofNoFill();
    ofSetLineWidth(lineWidth);
    ofDrawRectangle (x - radius/2, y-radius/2, radius,radius);
    ofPushMatrix();
    ofRotate(sin(ofGetElapsedTimef()*radius));
    ofDrawRectangle(ofGetWidth()/2 - radius/2 -100, ofGetHeight()/2 - radius/2 -100 , radius+200, radius+200);
    ofPopMatrix();

}

