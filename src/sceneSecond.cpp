//
//  sceneSecond.hpp
//  FinalProject
//
//  Created by shuai wang on 4/23/18.
//

#include "sceneSecond.h"

void sceneSecond::init(){
    //---------Lights Enable
    
    light1.enable();
    light2.enable();
    light3.enable();
    
    ofColor color1 = ofColor ( 100, 0, 100, 0.2 * 150) ;
    ofColor color2 = ofColor ( 255, 255, 0, 0.2 * 150 ) ;
    
    ofColor inBetween = color1.lerp( color2 , .66f ) ; // returns a color halfway between red and blue
    light1.setAmbientColor(inBetween);
    light1.setPosition(500, 500, 1000);

    light2.setDiffuseColor( ofFloatColor( 238.f/255.f, 57.f/255.f, 135.f/255.f ));
    light2.setSpecularColor(ofFloatColor(.8f, .8f, .9f));

    light3.setDiffuseColor( ofFloatColor(19.f/255.f,94.f/255.f,77.f/255.f) );
    light3.setSpecularColor( ofFloatColor(18.f/255.f,150.f/255.f,135.f/255.f) );
    
    //---------Texture loading
    ofDisableArbTex();
    ofLoadImage(mTex, "test.jpg");
    ofLoadImage(mTex1, "images.jpeg");
    
    //---------3D Obj Parameter
    float width     = ofGetWidth() * .35;
    float height    = ofGetHeight() * .35;
    sphere.setRadius( width/2 );
    vidGrabber.setup(1280, 960, true);
    sphere.mapTexCoordsFromTexture( vidGrabber.getTexture() );

    //---------Object Drawing
    for (int i=0; i<NUM; i++) {
        stars[i].setPosition(ofRandom(-500,500), ofRandom(-500,500), ofRandom(-500,500));
        stars[i].set(ofRandom(10.5f,20.5f));
    };
}

void sceneSecond::customDraw(float beats){
    update();
    

    //---------Object Auto Rotating
    float spinX = sin(ofGetElapsedTimef()*.35f);
    float spinY = cos(ofGetElapsedTimef()*.075f);
    
    //---------Planet Drawing
    
    sphere.setResolution(Sres);
    sphere.setPosition(ofGetWidth()*.5f, ofGetHeight()*.5f, 0);
    sphere.rotate(spinX, 1.0, 0.0, 0.0);
    sphere.rotate(spinY, 0, 1.0, 0.0);
    sphere.setMode( OF_PRIMITIVE_TRIANGLES );
    
    material.begin();
    ofFill();
    ofVec3f faceNormal;
    triangles = sphere.getMesh().getUniqueFaces();
    
    //speed
    float angle = ofGetElapsedTimef() * 3.5;
    //shaking range
    float range = beats * 5;
    float strength = -range*20 + sin(angle) * 30;
    
    for(int i = 0; i < triangles.size(); i++ ) {
        faceNormal = triangles[i].getFaceNormal();
        for(int j = 0; j < 3; j++ ) {
            triangles[i].setVertex( j, triangles[i].getVertex(j) + faceNormal * strength);
        }
    }
    
    sphere.getMesh().setFromTriangles( triangles );
    vidGrabber.getTexture().bind();
    mTex.bind();
    sphere.draw();
    mTex.unbind();
    vidGrabber.getTexture().unbind();
    material.end();
    
    //---------Planet Drawing

    ofPushMatrix();
    ofTranslate(ofGetWidth()/2 , ofGetHeight()/2 );
    ofRotateY(sin(ofGetElapsedTimef()/ 2) * 250 + range * ofRandom(-5,5));
    for (int i=2; i< NUM-2; i++) {
        mTex.bind();
        ofRotateY(sin(ofGetElapsedTimef())* range * ofRandom(-1,1));
        ofTranslate(range * ofRandom(-1,1), range * ofRandom(-1,1));
        stars[i].draw();
        mTex.unbind();
    }
    ofPopMatrix();
}

void sceneSecond::update(){
    
     vidGrabber.update();
    //---------Light Update

    light2.setPosition((ofGetWidth()*.5)+ cos(ofGetElapsedTimef()*.15)*(ofGetWidth()*.3),
                       ofGetHeight()*.5 + sin(ofGetElapsedTimef()*.7)*(ofGetHeight()), -300);
    
    light3.setPosition( cos(ofGetElapsedTimef()*1.5) * ofGetWidth()*.5,
                        sin(ofGetElapsedTimef()*1.5f) * ofGetWidth()*.5,
                        cos(ofGetElapsedTimef()*.2) * ofGetWidth()
                       );
}
