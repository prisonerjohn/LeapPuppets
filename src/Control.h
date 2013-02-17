//
//  Control.h
//  Caterpillar
//
//  Created by Elie Zananiri on 2013-02-16.
//
//

#pragma once

#include "ofMain.h"
#include "ofxMtlBox2d.h"

//--------------------------------------------------------------
//--------------------------------------------------------------
class Control
{
    public:
                Control(ofxMtlBox2dWorld* world, ofxMtlBox2dBaseShape* body, const ofPoint& offset, const ofPoint& anchor);
                ~Control();

        void    update();
        void    draw();

        void    onPress(ofMouseEventArgs& args);
        void    onDrag(ofMouseEventArgs& args);
        void    onRelease(ofMouseEventArgs& args);

        void    grab(int id, ofPoint& pos);
        void    move(int id, ofPoint& pos);
        void    release(int id, ofPoint& pos);

        ofxMtlBox2dCircle* m_body;
        ofxMtlBox2dDistanceJoint* m_joint;

        int moverID;
        ofPoint offset;
};
