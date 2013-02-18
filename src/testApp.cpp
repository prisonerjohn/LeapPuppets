#include "testApp.h"
#include <limits>

//--------------------------------------------------------------
void testApp::setup()
{	
	ofSetFrameRate(30);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);

    bDebug = true;
    bInfo = true;

    leap.open();

    // init the physics world
    world = new ofxMtlBox2dWorld();
//    world->enableMouseJoints();
    world->setGravityB2(b2Vec2(0, 9.8));

    buildTerrain();
    buildRagdoll();
}

//--------------------------------------------------------------
void testApp::update()
{
	world->update();

    simpleHands = leap.getSimpleHands();
    if (leap.isFrameNew() && simpleHands.size()) {
        for (int i = 0; i < simpleHands.size(); i++) {
            int numFingers = simpleHands[i].fingers.size();
            if (numFingers) {
                // order the fingers by x-position
                list<int> orderedIndices;
                orderedIndices.push_back(0);
                float frontX = simpleHands[i].fingers[0].pos.x;
                float backX = simpleHands[i].fingers[0].pos.x;
                for (int j = 1; j < numFingers; j++) {
                    float currX = simpleHands[i].fingers[j].pos.x;
                    if (currX < frontX) {
                        orderedIndices.push_front(j);
                        frontX = currX;
                    }
                    else {
                        orderedIndices.push_back(j);
                        backX = currX;
                    }
                }
                
                if (ragdoll) {
                    // move the ragdoll controls

                    // the first point is the left leg
                    int leftLegIndex = orderedIndices.front();
                    int leftLegID = simpleHands[i].fingers[leftLegIndex].id;
                    ofPoint leftLegPos(simpleHands[i].fingers[leftLegIndex].pos.x, simpleHands[i].fingers[leftLegIndex].pos.y * -1);
                    if (ragdoll->leftLegControl->moverID != leftLegID)
                        ragdoll->leftLegControl->grab(leftLegID, leftLegPos);
                    else {
                        ragdoll->leftLegControl->move(leftLegID, leftLegPos);
                    }

                    // the last point is the right leg
                    if (numFingers > 1) {
                        int rightLegIndex = orderedIndices.back();
                        int rightLegID = simpleHands[i].fingers[rightLegIndex].id;
                        ofPoint rightLegPos(simpleHands[i].fingers[rightLegIndex].pos.x, simpleHands[i].fingers[rightLegIndex].pos.y * -1);
                        if (ragdoll->rightLegControl->moverID != rightLegID)
                            ragdoll->rightLegControl->grab(rightLegID, rightLegPos);
                        else {
                            ragdoll->rightLegControl->move(rightLegID, rightLegPos);
                        }
                    }

                    // the second point is the left arm
                    if (numFingers > 2) {
                        int leftArmIndex = *(++orderedIndices.begin());
                        int leftArmID = simpleHands[i].fingers[leftArmIndex].id;
                        ofPoint leftArmPos(simpleHands[i].fingers[leftArmIndex].pos.x, simpleHands[i].fingers[leftArmIndex].pos.y * -1);
                        if (ragdoll->leftArmControl->moverID != leftArmID)
                            ragdoll->leftArmControl->grab(leftArmID, leftArmPos);
                        else {
                            ragdoll->leftArmControl->move(leftArmID, leftArmPos);
                        }
                    }

                    // the second to last point is the right arm
                    if (numFingers > 3) {
                        int rightArmIndex = *(++orderedIndices.rbegin());
                        int rightArmID = simpleHands[i].fingers[rightArmIndex].id;
                        ofPoint rightArmPos(simpleHands[i].fingers[rightArmIndex].pos.x, simpleHands[i].fingers[rightArmIndex].pos.y * -1);
                        if (ragdoll->rightArmControl->moverID != rightArmID)
                            ragdoll->rightArmControl->grab(rightArmID, rightArmPos);
                        else {
                            ragdoll->rightArmControl->move(rightArmID, rightArmPos);
                        }
                    }

                    // the middle point is the head, but only if all limbs are connected
                    if (numFingers > 4) {
                        int headIndex = *(++(++orderedIndices.begin()));
                        int headID = simpleHands[i].fingers[headIndex].id;
                        ofPoint headPos(simpleHands[i].fingers[headIndex].pos.x, simpleHands[i].fingers[headIndex].pos.y * -1);
                        if (ragdoll->headControl->moverID != headID)
                            ragdoll->headControl->grab(headID, headPos);
                        else {
                            ragdoll->headControl->move(headID, headPos);
                        }
                    }
                }
            }
        }
    }

    leap.markFrameAsOld();
}


//--------------------------------------------------------------
void testApp::draw() {
	
	ofSetHexColor(0xf2ab01);

    if (bDebug) {
        world->debug();
    }
    else {
        if (terrain) terrain->draw();
        if (ragdoll) ragdoll->draw();
    }

    if (bInfo) {
        string info = "";
        info += "Total Bodies: " + ofToString(world->getBodyCount()) + "\n";
        info += "Total Joints: " + ofToString(world->getJointCount()) + "\n";
        info += "FPS: " + ofToString(ofGetFrameRate()) + "\n";
        ofSetHexColor(0x444342);
        ofDrawBitmapString(info, 10, 20);
    }
}

//--------------------------------------------------------------
void testApp::keyPressed(int key)
{		
    switch (key) {
        case 9:
            ofToggleFullscreen();
            break;

        case 'i':
        case 'I':
            bInfo ^= true;
            break;

        case 'd':
        case 'D':
            bDebug ^= true;
            break;

        case 'r':
        case 'R':
            buildRagdoll();
            break;

        case 't':
        case 'T':
            buildTerrain();
            break;
    }
}

//--------------------------------------------------------------
void testApp::keyReleased(int key)
{

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y)
{
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h)
{
    buildTerrain();
}

//--------------------------------------------------------------
void testApp::buildTerrain()
{
    world->createBounds(0, 0, ofGetWidth(), ofGetHeight());

    if (terrain) delete terrain;
    terrain = new Terrain(world);
}

//--------------------------------------------------------------
void testApp::buildRagdoll()
{
    if (ragdoll) delete ragdoll;
    ragdoll = new Ragdoll(world, ofGetWidth() * 0.5f, ofGetHeight() * 0.5f);
}
