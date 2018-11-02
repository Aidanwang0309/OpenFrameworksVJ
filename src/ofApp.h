#pragma once
#include "ofMain.h"
#include "sceneFirst.h"
#include "sceneSecond.h"
#include "sceneThird.h"

// Add On
#include "ofxAssimpModelLoader.h"
#include "ofxSimpleSerial.h"
#include <vector>
#include "ofUtils.h"
#include "ofxBeat.h"
#include "ofxPostProcessing.h"

//#define NUM 1


using namespace std;

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void sceneThirdTrigger(int x, int y);
    void ripple(int posx, int posy, int r, int g, int b);
    void sceneThirdStartDraw(float kick);
    void drawSenceFirst();
    
    
    bool sceneFirstOn;
    bool sceneSecondOn;
    bool sceneThirdOn;
    bool sceneFourOn;
    bool wolfOn;
    bool bgOn;
    ofxPostProcessing post;
    //----------------------------------------------------------- Audio In
    ofSoundStream soundStream;
    ofSoundPlayer player;
    ofxBeat beat;
    void audioIn( float * input, int bufferSize, int nChannels );
    vector <float> left;
    vector <float> right;
    
    int bufferSize = 1024;
    int bufferCounter;
    int drawCounter;
    
    float smoothedVol;
    float smoothedVolL;
    float smoothedVolR;
    float scaledVol;
    float scaledVolL;
    float scaledVolR;
    


    //----------------------------------------------------------- Serial
    void                onNewMessage(string & message);
    ofxSimpleSerial     serial;
    string              message;
    bool                remember;
    bool                requestRead;
    int                 serial01;
    float               elapsedTime = 0.0f;
    
    vector <sceneFirst> sceneFirst;
    class sceneSecond sceneSecond;
    
    vector<sceneThird> sceneThirdStars;
    class sceneThird sceneThird;
    
    ofEasyCam  cam;
    ofxAssimpModelLoader model;
    
    ofImage bg;
    
};
