#pragma once
//
//  sceneFirst.cpp
//  FinalProject
//
//  Created by shuai wang on 4/23/18.
//

#include "ofMain.h"


class sceneFirst : public ofBaseApp {
    
public:
    sceneFirst();
    void update();
    void draw();

    
    int r, g, b;
    int x, y;
    
    int radius;
    int lineWidth;
    int expandRate;
    int timer;
    
    bool dead;
};

