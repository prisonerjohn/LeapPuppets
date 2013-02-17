//
//  Terrain.h
//  Caterpillar
//
//  Created by Elie Zananiri on 2013-02-14.
//
//

#pragma once

#include "ofMain.h"
#include "ofxMtlBox2d.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class Terrain
{
    public:
        Terrain(ofxMtlBox2dWorld *world);
        ~Terrain();

        void update();
        void draw();

        ofxMtlBox2dPolygon *polygon;
        vector<ofPoint>     points;

        static const int kMinStep;
        static const int kMaxStep;
        static const int kMaxHeight;
};
