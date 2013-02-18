//
//  Ragdoll.cpp
//  Caterpillar
//
//  Created by Elie Zananiri on 2013-02-15.
//
//

#include "Ragdoll.h"

//------------------------------------------------
Ragdoll::Ragdoll(ofxMtlBox2dWorld *world, int x, int y)
{
    // build the head
    ofxMtlBox2dCircle *head = new ofxMtlBox2dCircle();
    head->setPhysics(1.0f, 0.4f, 0.3f);
    head->setup(world, x, y, 25.0f);
    parts.push_back(head);

    // build the torso in 3 parts
    ofxMtlBox2dBox *shoulders = new ofxMtlBox2dBox();
    shoulders->setPhysics(1.0f, 0.4f, 0.1f);
    shoulders->setup(world, x, y + 50.0f, 30.0f, 20.0f);
    parts.push_back(shoulders);

    ofxMtlBox2dBox *stomach = new ofxMtlBox2dBox();
    stomach->setPhysics(1.0f, 0.4f, 0.1f);
    stomach->setup(world, x, y + 86.0f, 30.0f, 20.0f);
    parts.push_back(stomach);

    ofxMtlBox2dBox *hips = new ofxMtlBox2dBox();
    hips->setPhysics(1.0f, 0.4f, 0.1f);
    hips->setup(world, x, y + 116.0f, 30.0f, 20.0f);
    parts.push_back(hips);

    // build the arms
    ofxMtlBox2dBox *upperArmLeft = new ofxMtlBox2dBox();
    upperArmLeft->setPhysics(1.0f, 0.4f, 0.1f);
    upperArmLeft->setup(world, x - 60.0f, y + 40.0f, 36.0f, 13.0f);
    parts.push_back(upperArmLeft);

    ofxMtlBox2dBox *upperArmRight = new ofxMtlBox2dBox();
    upperArmRight->setPhysics(1.0f, 0.4f, 0.1f);
    upperArmRight->setup(world, x + 60.0f, y + 40.0f, 36.0f, 13.0f);
    parts.push_back(upperArmRight);

    ofxMtlBox2dBox *lowerArmLeft = new ofxMtlBox2dBox();
    lowerArmLeft->setPhysics(1.0f, 0.4f, 0.1f);
    lowerArmLeft->setup(world, x - 114.0f, y + 40.0f, 34.0f, 12.0f);
    parts.push_back(lowerArmLeft);

    ofxMtlBox2dBox *lowerArmRight = new ofxMtlBox2dBox();
    lowerArmRight->setPhysics(1.0f, 0.4f, 0.1f);
    lowerArmRight->setup(world, x + 114.0f, y + 40.0f, 34.0f, 12.0f);
    parts.push_back(lowerArmRight);

    // build the legs
    ofxMtlBox2dBox *upperLegLeft = new ofxMtlBox2dBox();
    upperLegLeft->setPhysics(1.0f, 0.4f, 0.1f);
    upperLegLeft->setup(world, x - 16.0f, y + 170.0f, 15.0f, 44.0f);
    parts.push_back(upperLegLeft);

    ofxMtlBox2dBox *upperLegRight = new ofxMtlBox2dBox();
    upperLegRight->setPhysics(1.0f, 0.4f, 0.1f);
    upperLegRight->setup(world, x + 16.0f, y + 170.0f, 15.0f, 44.0f);
    parts.push_back(upperLegRight);

    ofxMtlBox2dBox *lowerLegLeft = new ofxMtlBox2dBox();
    lowerLegLeft->setPhysics(1.0f, 0.4f, 0.1f);
    lowerLegLeft->setup(world, x - 16.0f, y + 240.0f, 12.0f, 40.0f);
    parts.push_back(lowerLegLeft);

    ofxMtlBox2dBox *lowerLegRight = new ofxMtlBox2dBox();
    lowerLegRight->setPhysics(1.0f, 0.4f, 0.1f);
    lowerLegRight->setup(world, x + 16.0f, y + 240.0f, 12.0f, 40.0f);
    parts.push_back(lowerLegRight);

    // build the joints
    ofxMtlBox2dRevoluteJoint *head2Shoulders = new ofxMtlBox2dRevoluteJoint();
    head2Shoulders->setLimitEnabled(true);
    head2Shoulders->setLimits(-40.0, 40.0);
    head2Shoulders->setup(world, shoulders, head, ofPoint(x, y + 30.0f));
    joints.push_back(head2Shoulders);

    ofxMtlBox2dRevoluteJoint *upperArm2ShouldersLeft = new ofxMtlBox2dRevoluteJoint();
    upperArm2ShouldersLeft->setLimitEnabled(true);
    upperArm2ShouldersLeft->setLimits(-85.0, 130.0);
    upperArm2ShouldersLeft->setup(world, shoulders, upperArmLeft, ofPoint(x - 36.0f, y + 40.0f));
    joints.push_back(upperArm2ShouldersLeft);

    ofxMtlBox2dRevoluteJoint *upperArm2ShouldersRight = new ofxMtlBox2dRevoluteJoint();
    upperArm2ShouldersRight->setLimitEnabled(true);
    upperArm2ShouldersRight->setLimits(-130.0, 85.0);
    upperArm2ShouldersRight->setup(world, shoulders, upperArmRight, ofPoint(x + 36.0f, y + 40.0f));
    joints.push_back(upperArm2ShouldersRight);

    ofxMtlBox2dRevoluteJoint *upper2LowerArmLeft = new ofxMtlBox2dRevoluteJoint();
    upper2LowerArmLeft->setLimitEnabled(true);
    upper2LowerArmLeft->setLimits(-130.0, 10.0);
    upper2LowerArmLeft->setup(world, upperArmLeft, lowerArmLeft, ofPoint(x - 90.0f, y + 40.0f));
    joints.push_back(upper2LowerArmLeft);

    ofxMtlBox2dRevoluteJoint *upper2LowerArmRight = new ofxMtlBox2dRevoluteJoint();
    upper2LowerArmRight->setLimitEnabled(true);
    upper2LowerArmRight->setLimits(-10.0, 130.0);
    upper2LowerArmRight->setup(world, upperArmRight, lowerArmRight, ofPoint(x + 90.0f, y + 40.0f));
    joints.push_back(upper2LowerArmRight);

    ofxMtlBox2dRevoluteJoint *shoulders2Stomach = new ofxMtlBox2dRevoluteJoint();
    shoulders2Stomach->setLimitEnabled(true);
    shoulders2Stomach->setLimits(-15.0, 15.0);
    shoulders2Stomach->setup(world, shoulders, stomach, ofPoint(x, y + 70.0f));
    joints.push_back(shoulders2Stomach);

    ofxMtlBox2dRevoluteJoint *stomach2Hips = new ofxMtlBox2dRevoluteJoint();
    stomach2Hips->setLimitEnabled(true);
    stomach2Hips->setLimits(-15.0, 15.0);
    stomach2Hips->setup(world, stomach, hips, ofPoint(x, y + 100.0f));
    joints.push_back(stomach2Hips);

    ofxMtlBox2dRevoluteJoint *hips2upperLegLeft = new ofxMtlBox2dRevoluteJoint();
    hips2upperLegLeft->setLimitEnabled(true);
    hips2upperLegLeft->setLimits(-25.0, 45.0);
    hips2upperLegLeft->setup(world, hips, upperLegLeft, ofPoint(x - 16.0f, y + 144.0f));
    joints.push_back(hips2upperLegLeft);

    ofxMtlBox2dRevoluteJoint *hips2upperLegRight = new ofxMtlBox2dRevoluteJoint();
    hips2upperLegRight->setLimitEnabled(true);
    hips2upperLegRight->setLimits(-45.0, 25.0);
    hips2upperLegRight->setup(world, hips, upperLegRight, ofPoint(x + 16.0f, y + 144.0f));
    joints.push_back(hips2upperLegRight);

    ofxMtlBox2dRevoluteJoint *upper2LowerLegLeft = new ofxMtlBox2dRevoluteJoint();
    upper2LowerLegLeft->setLimitEnabled(true);
    upper2LowerLegLeft->setLimits(-25.0, 115.0);
    upper2LowerLegLeft->setup(world, upperLegLeft, lowerLegLeft, ofPoint(x - 16.0f, y + 210.0f));
    joints.push_back(upper2LowerLegLeft);

    ofxMtlBox2dRevoluteJoint *upper2LowerLegRight = new ofxMtlBox2dRevoluteJoint();
    upper2LowerLegRight->setLimitEnabled(true);
    upper2LowerLegRight->setLimits(-115.0, 25.0);
    upper2LowerLegRight->setup(world, upperLegRight, lowerLegRight, ofPoint(x + 16.0f, y + 210.0f));
    joints.push_back(upper2LowerLegRight);

    // build the controls
    leftArmControl = new Control(world, lowerArmLeft, ofPoint(-114.0f, -280.0f), lowerArmLeft->getPosition() - ofPoint(lowerArmLeft->getWidth() / 2, 0));
    rightArmControl = new Control(world, lowerArmRight, ofPoint(114.0f, -280.0f), lowerArmRight->getPosition() + ofPoint(lowerArmRight->getWidth() / 2, 0));
    leftLegControl = new Control(world, lowerLegLeft, ofPoint(-100.0f, -420.0f), lowerLegLeft->getPosition() + ofPoint(0, lowerLegLeft->getHeight() / 2));
    rightLegControl = new Control(world, lowerLegRight, ofPoint(100.0f, -420.0f), lowerLegRight->getPosition() + ofPoint(0, lowerLegRight->getHeight() / 2));
    headControl = new Control(world, head, ofPoint(0, -200.0f), head->getPosition());
}

//------------------------------------------------
Ragdoll::~Ragdoll()
{
    // delete all the joints and body segments
    for (int i = 0; i < joints.size(); i++) {
        delete joints[i];
    }
    joints.clear();

    for (int i = 0; i < parts.size(); i++) {
        delete parts[i];
    }
    parts.clear();

    // delete the controls
    delete leftArmControl;
    delete rightArmControl;
    delete leftLegControl;
    delete rightLegControl;
}

//------------------------------------------------
void Ragdoll::update()
{

}

//------------------------------------------------
void Ragdoll::draw()
{

}