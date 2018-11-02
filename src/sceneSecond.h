#pragma once
//
//  sceneSecond.cpp
//  FinalProject
//
//  Created by shuai wang on 4/23/18.
//

#include "ofMain.h"
#define NUM 100

class sceneSecond : public ofBaseApp {
    
public:
    void init();
    void update();
    void customDraw(float beats);
    
    ofSpherePrimitive sphere;
    ofBoxPrimitive box;
    
    ofBoxPrimitive stars[NUM];
    ofMaterial material;
    ofVideoGrabber vidGrabber;
    
    int Sres = 4;
    
    ofLight light1;
    ofLight light2;
    ofLight light3;
    
    ofTexture mTex;
    ofTexture mTex1;
    vector<ofMeshFace> triangles;
    ofEasyCam easyCam;
};

