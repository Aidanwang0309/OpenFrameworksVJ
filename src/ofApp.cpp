#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //----------------------------------------------------------- Scene init
    ofEnableAlphaBlending();
    ofSetVerticalSync( true );
    ofSetWindowTitle("Final Project VJ");
    ofEnableSmoothing();
    ofDisableAlphaBlending();
    ofEnableDepthTest();
    ofBackground(0);

    sceneFirstOn = false;
    sceneSecondOn = false;
    sceneThirdOn = false;
    sceneFourOn = false;
    
    sceneSecond.init();
    sceneThird.init();
    bg.load("brain.jpg");
    //----------------------------------------------------------- Audio In
    // output channels,
    // 2 input channels,
    // 44100 samples per sec
    // 900 samples per buffer
    // 4 num buggers (latency)
//    player.load("Breathe.mp3");
//    player.play();
    soundStream.printDeviceList();
    soundStream.setup(this, 0, 2, 44100, bufferSize, 4);
    left.assign(bufferSize, 0.0);
    right.assign(bufferSize, 0.0);
    
    bufferCounter   = 0;
    drawCounter     = 0;
    smoothedVol     = 0.0;
    scaledVol       = 0.0;
    smoothedVolL     = 0.0;
    scaledVolL       = 0.0;
    smoothedVolR     = 0.0;
    scaledVolR       = 0.0;
    
    //----------------------------------------------------------- Serial > Send
    serial.setup("/dev/cu.usbmodem1421", 19200);
    serial.startContinuousRead(false);
    ofAddListener(serial.NEW_MESSAGE,this,&ofApp::onNewMessage);

//    message = "a";
    remember = false;
    //----------------------------------------------------------- postprocessing
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<FxaaPass>()->setEnabled(false);
    post.createPass<BloomPass>()->setEnabled(false);
    post.createPass<DofPass>()->setEnabled(true);
    post.createPass<KaleidoscopePass>()->setEnabled(false);
    post.createPass<NoiseWarpPass>()->setEnabled(false);
    post.createPass<PixelatePass>()->setEnabled(false);
    post.createPass<EdgePass>()->setEnabled(false);
    post.createPass<VerticalTiltShifPass>()->setEnabled(false);
    post.createPass<GodRaysPass>()->setEnabled(false);
    
    
    model.loadModel("Wolfdae.dae");
    model.setRotation(0,110,1,0,0);
//    model.setRotation(1,90,1,1,0);

    model.setScale(0.5,0.5,0.5);
    model.setPosition(ofGetWidth()/2, ofGetHeight()/2, 200);
    model.setLoopStateForAllAnimations(OF_LOOP_NORMAL);
    model.playAllAnimations();
    }

void ofApp::onNewMessage(string & message){
    cout << "onNewMessage, message: " << message << "\n";
}


//--------------------------------------------------------------
void ofApp::update(){
    model.update();
    beat.update(ofGetElapsedTimeMillis());

    for (int i = 0; i < sceneFirst.size(); i++ ) {
        sceneFirst[i].update();
        if(sceneFirst[i].dead) {
            sceneFirst.erase( sceneFirst.begin()+i );
        }
    }
    
    for(int i = 0; i < sceneThirdStars.size(); i++){
        sceneThirdStars[i].resetForce();
        sceneThirdStars[i].updateForce();
        sceneThirdStars[i].updatePos();
    }
}

//--------------------------------------------------------------
void ofApp::draw(){

    if(wolfOn){
    model.drawWireframe();
    }
    
    //----------------------------------------------------------- LED Lights
    float p = 0;
    float high = 0;

    float a = 0;
    float kick = beat.kick();
    float snare = beat.snare();
    float hihat = beat.hihat();
    
    for(int i = 0; i < bufferSize - 1; i+=2) {
        p += left[i];
        if (left[i] > high) {
            high = left[i];
        }

        if(sceneFourOn){
        ofPushStyle();
            ofPushMatrix();
        ofSetColor(100 + i/10, 50 + i / 6, 100 + i / 10);
        ofDrawLine((ofGetWidth()/2-50) - (300*(p/2)), i, (ofGetWidth()/2-50) - (300*(p/2)), i+1);
        ofDrawLine((ofGetWidth()/2+50) + (300*(p/2)),i, (ofGetWidth()/2+50) + (300*(p/2)), i+1);
            ofSetColor(0, 0 + i / 6, 0 + i / 10);
            ofDrawLine((ofGetWidth()/2-150) - (300*(p/2)), i, (ofGetWidth()/2-150) - (300*(p/2)), i+1);
            ofDrawLine((ofGetWidth()/2+150) + (300*(p/2)),i, (ofGetWidth()/2+150) + (300*(p/2)), i+1);
            ofPopMatrix();
        ofPopStyle();
        }
    }

    if(ofGetElapsedTimef()-elapsedTime > 0.5){
    
    if (p > .3 ) {
        float mapped = ofMap(p, 0, 30, 0, 1);
        a = round(mapped * 1400);
        serial.writeString(message);
        elapsedTime = ofGetElapsedTimef();
    }
   }
    
    post.begin();
    //----------------------------------------------------------- Scene First

    
    if(sceneFirstOn){
        for (int i = 0; i < sceneFirst.size(); i++ ) {
            sceneFirst[i].draw();
        }
        if (p > .2 ){
        if(kick == 1){
            ripple(ofGetWidth()/3-100, ofGetHeight()/3, ofRandom(0, 20), ofRandom(150, 255),ofRandom(150, 255)) ;
        };
        if(snare == 1){
            ripple(ofGetWidth()*2/3,ofGetHeight()/3 +100,ofRandom(150, 255), ofRandom(0, 20),ofRandom(150, 255));
        };
        if(hihat == 1){
            ripple(ofGetWidth()/2,ofGetHeight()*2/3 +100,ofRandom(150, 255), ofRandom(150, 255),ofRandom(0, 20));
        };
        }
    }
    //----------------------------------------------------------- Scene Second

    if(bgOn){
        bg.draw(0,0,ofGetWidth(),ofGetHeight());
    }
    
    if(sceneSecondOn){
        ofPushStyle();
        sceneSecond.customDraw(p);
        ofPopStyle();
    }
    
    
    if(sceneThirdOn){
        ofPushStyle();
        ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
        sceneThirdTrigger(ofRandom(-100,100),ofRandom(-100,100));
        sceneThirdStartDraw(p);
        ofPopStyle();
    }
    
        post.end();
    
}

////--------------------------------------------------------------
void ofApp::audioIn( float * input, int bufferSize, int nChannels ){
    //float curVol = 0.0;
    float curVolL = 0.0;
    float curVolR = 0.0;

    // samples are interleaved
    int numCounted = 0;

    // lets go through each sample and calculate the root mean square which is a rough way to calculate vol
    for ( int i = 0; i < bufferSize; i++ ) {
        left[i]     = input[i*2]*.5;
        right[i]    = input[i*2+1]*.5;

        curVolL += left[i] * left[i];
        curVolR += right[i] * right[i];

        numCounted += 2;
    }

    // get the mean of rms
    //curVol /= (float)numCounted;
    curVolL /= (float)numCounted;
    curVolR /= (float)numCounted;

    // get the root of rms :)
    //curVol = sqrt( curVol );
    curVolL = sqrt( curVolL );
    curVolR = sqrt( curVolR );


    //smoothedVol *= .83;
    smoothedVolL *= .83;
    smoothedVolR *= .83;
    smoothedVolL += .07 * curVolL;
    smoothedVolR += .07 * curVolR;

    bufferCounter++;
    
    beat.audioReceived(input, bufferSize, nChannels);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    // Audio In
    if( key == 'z'){
        sceneFirstOn = true;
        message = 'a';
    } else if (key == 'x'){
        sceneFirstOn = false;
        sceneSecondOn = true;
        message = 'd';
    } else if(key == 'c'){
        sceneFirstOn = false;
        sceneSecondOn = false;
        sceneThirdOn = true;
        message = 'd';
    } else if (key == 'm'){
        sceneFirstOn = false;
        sceneSecondOn = false;
        sceneThirdOn = false;
    } else if (key == 'v'){
        sceneFirstOn = false;
        sceneSecondOn = false;
        sceneThirdOn= false;
        sceneFourOn = !sceneFourOn;
    }
    
    if(key == 'b'){
        wolfOn = !wolfOn;
    }
    if(key == 'n'){
        bgOn = !bgOn;
    }
    
    
    unsigned idx = key - '0';
    if (idx < post.size()) post[idx]->setEnabled(!post[idx]->getEnabled());
    
    if (key == 'q'){
        sceneSecond.Sres = 2;
    }
    if (key == 'w'){
        sceneSecond.Sres = 3;
    }
    if (key == 'e'){
        sceneSecond.Sres = 4;
    }
    if (key == 'r'){
        sceneSecond.Sres = 8;
    }
    if (key == 't'){
        sceneSecond.Sres = 16;
    }
    
//    if( key == 's' ) {
//        soundStream.start();
//    }
//
//    if ( key == 'e' ) {
//        soundStream.stop();
//    }

    // Serial > send
    switch (key) {
        case 32: //space
            remember = true;
            break;
    }
}


void ofApp::ripple(int posx, int posy,int r, int g, int b){
    
    class sceneFirst sampleCircle;
    
    sampleCircle.x = posx;
    sampleCircle.y = posy;
    sampleCircle.r = r;
    sampleCircle.g = g;
    sampleCircle.b = b;
    
    sceneFirst.push_back(sampleCircle);
}

void ofApp::sceneThirdTrigger(int x, int y){
    for(int i = 0; i < 1; i++){
        ofVec3f pos = ofVec3f(x, y, 0);
        float length = ofRandom(5);
        float angle = ofRandom(PI * 2);
        ofVec3f vel = ofVec3f(cos(angle) * length, sin(angle) * length, ofRandom(20));
        class sceneThird p;
        p.start(pos, vel);
        p.radius = 1;
        p.friction = 0.002;
        sceneThirdStars.push_back(p);
    }
}

void ofApp:: sceneThirdStartDraw(float kick){
    for(int i = 0; i < sceneThirdStars.size(); i++){
        ofFill();
        ofSetColor(100);
        if(kick>.4){
            ofSetColor(ofRandom(150,255),ofRandom(111,238),ofRandom(92,180));
        }
        sceneThirdStars[i].draw();
    }
}
