//
//  Control.cpp
//  Caterpillar
//
//  Created by Elie Zananiri on 2013-02-16.
//
//

#include "Control.h"

#define kControlRadius 25.0f

//------------------------------------------------
Control::Control(ofxMtlBox2dWorld* world, ofxMtlBox2dBaseShape* body, const ofPoint& offset, const ofPoint& anchor)
{
    ofPoint pos = body->getPosition() + offset;
    
    m_body = new ofxMtlBox2dCircle();
    m_body->setup(world, pos.x, pos.y, kControlRadius, 0, true);

    m_joint = new ofxMtlBox2dDistanceJoint();
    m_joint->setPhysics(1.0f, 0.5f);
    m_joint->setup(world, body, m_body, anchor, pos);

    moverID = -1;
    
    ofAddListener(ofEvents().mousePressed,  this, &Control::onPress);
	ofAddListener(ofEvents().mouseDragged,  this, &Control::onDrag);
	ofAddListener(ofEvents().mouseReleased, this, &Control::onRelease);
}

//------------------------------------------------
Control::~Control()
{
	ofRemoveListener(ofEvents().mousePressed,  this, &Control::onPress);
	ofRemoveListener(ofEvents().mouseDragged,  this, &Control::onDrag);
	ofRemoveListener(ofEvents().mouseReleased, this, &Control::onRelease);

    // delete the joint and handle
    delete m_joint;
    delete m_body;
}

//------------------------------------------------
void Control::update()
{

}

//------------------------------------------------
void Control::draw()
{
    
}

//--------------------------------------------------------------
void Control::onPress(ofMouseEventArgs& args)
{
    ofPoint pos = ofPoint(args.x, args.y);

    if (moverID > 0 || m_body->getPosition().distance(pos) > kControlRadius)
        return;

    grab(0, pos);
}

//--------------------------------------------------------------
void Control::onDrag(ofMouseEventArgs& args)
{
    ofPoint pos = ofPoint(args.x, args.y);
    move(0, pos);
}

//--------------------------------------------------------------
void Control::onRelease(ofMouseEventArgs& args)
{
    ofPoint pos = ofPoint(args.x, args.y);
    release(0, pos);
}

//--------------------------------------------------------------
void Control::grab(int id, ofPoint& pos)
{
    moverID = id;
    offset = m_body->getPosition() - pos;
}

//--------------------------------------------------------------
void Control::move(int id, ofPoint& pos)
{
    if (moverID == id)
        m_body->setPosition(pos + offset);
}

//--------------------------------------------------------------
void Control::release(int id, ofPoint& pos)
{
    if (moverID == id)
		moverID = -1;
}
