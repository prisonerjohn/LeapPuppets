//
//  Ragdoll.h
//  Caterpillar
//
//  Created by Elie Zananiri on 2013-02-15.
//
//

#pragma once

#include "ofMain.h"
#include "ofxMtlBox2d.h"

#include "Control.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class Ragdoll
{
    public:
        Ragdoll(ofxMtlBox2dWorld *world, int x, int y);
        ~Ragdoll();

        void update();
        void draw();

        vector<ofxMtlBox2dBaseShape*> parts;
        vector<ofxMtlBox2dBaseJoint*> joints;

        Control* leftArmControl;
        Control* rightArmControl;
        Control* leftLegControl;
        Control* rightLegControl;
        Control* headControl;
};
