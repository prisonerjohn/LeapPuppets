#pragma once

#include "ofMain.h"
#include "ofxLeapMotion.h"
#include "ofxMtlBox2d.h"

#include "Ragdoll.h"
#include "Terrain.h"

//--------------------------------------------------------------
class testApp : public ofBaseApp
{	
    public:	
        void setup();
        void update();
        void draw();
        
        void keyPressed(int key);
        void keyReleased(int key);
        void mouseMoved(int x, int y);
        void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void mouseReleased(int x, int y, int button);
        void windowResized(int w, int h);

        void buildTerrain();
        void buildRagdoll();

        bool bDebug;
        bool bInfo;

        ofxLeapMotion leap;
        vector<ofxLeapMotionSimpleHand> simpleHands;
        
        ofxMtlBox2dWorld* world;

        Terrain* terrain;
        Ragdoll* ragdoll;
};

