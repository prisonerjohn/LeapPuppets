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

//    minX = minY = std::numeric_limits<int>::max();
//    maxX = maxY = std::numeric_limits<int>::min();
    minX = -200;
    maxX =  200;
    minY =   30;
    maxY =  400;

    leap.open();

    // init the physics world
    world = new ofxMtlBox2dWorld();
    world->enableMouseJoints();
    world->setGravityB2(b2Vec2(0, 9.8));

    buildTerrain();
    buildRagdoll();

//    
//	// first we add just a few circles
//	for (int i = 0; i < 8; i++) {
//		ofxBox2dCircle circle;
//		circle.setPhysics(3.0, 0.53, 0.1);
//		circle.setup(box2d.getWorld(), ofGetWidth()/2, 100+(i*20), 20);
//		circles.push_back(circle);
//	}
//	
//	// now connect each circle with a joint
//	for (int i=1; i<circles.size(); i++) {
//		
//		ofxBox2dJoint joint;
//		
//		// if this is the first point connect to the top anchor.
//		if(i == 0) {
////			joint.setup(box2d.getWorld(), anchor.body, circles[i].body);		
//		}
//		else {
//			joint.setup(box2d.getWorld(), circles[i-1].body, circles[i].body);
//		}
//		
//		joint.setLength(25);
//		joints.push_back(joint);
//	}
}

//--------------------------------------------------------------
void testApp::update()
{
	world->update();

    simpleHands = leap.getSimpleHands();
    if (leap.isFrameNew() && simpleHands.size()) {
//        leap.setMappingX(-230, 230, 0, 7);
//		leap.setMappingY(90, 490, -1, 1);
//        leap.setMappingZ(-150, 150, -200, 200);

//        leap.setMappingX(-200, 200, -ofGetWidth()/2, ofGetWidth()/2);
//		leap.setMappingY(30, 400, -ofGetHeight()/2, ofGetHeight()/2);
//        leap.setMappingZ(-150, 150, -200, 200);

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

                    // the first point is the left arm
                    int leftArmID = simpleHands[i].fingers[0].id;
                    ofPoint leftArmPos(simpleHands[i].fingers[0].pos.x, simpleHands[i].fingers[0].pos.y * -1);
                    if (ragdoll->leftArmControl->moverID != leftArmID)
                        ragdoll->leftArmControl->grab(leftArmID, leftArmPos);
                    else {
                        ragdoll->leftArmControl->move(leftArmID, leftArmPos);
                    }

                    // the last point is the right arm
                    if (numFingers > 1) {
                        int rightArmID = simpleHands[i].fingers[numFingers - 1].id;
                        ofPoint rightArmPos(simpleHands[i].fingers[numFingers - 1].pos.x, simpleHands[i].fingers[numFingers - 1].pos.y * -1);
                        if (ragdoll->rightArmControl->moverID != rightArmID)
                            ragdoll->rightArmControl->grab(rightArmID, rightArmPos);
                        else {
                            ragdoll->rightArmControl->move(rightArmID, rightArmPos);
                        }
                    }

                    // the second point is the left leg
                    if (numFingers > 2) {
                        int leftLegID = simpleHands[i].fingers[1].id;
                        ofPoint leftLegPos(simpleHands[i].fingers[1].pos.x, simpleHands[i].fingers[1].pos.y * -1);
                        if (ragdoll->leftLegControl->moverID != leftLegID)
                            ragdoll->leftLegControl->grab(leftLegID, leftLegPos);
                        else {
                            ragdoll->leftLegControl->move(leftLegID, leftLegPos);
                        }
                    }

                    // the second to last point is the right leg
                    if (numFingers > 3) {
                        int rightLegID = simpleHands[i].fingers[numFingers - 2].id;
                        ofPoint rightLegPos(simpleHands[i].fingers[numFingers - 2].pos.x, simpleHands[i].fingers[numFingers - 2].pos.y * -1);
                        if (ragdoll->rightLegControl->moverID != rightLegID)
                            ragdoll->rightLegControl->grab(rightLegID, rightLegPos);
                        else {
                            ragdoll->rightLegControl->move(rightLegID, rightLegPos);
                        }
                    }

                    // the middle point is the head, but only if all limbs are connected
                    if (numFingers > 4) {
                        int headID = simpleHands[i].fingers[2].id;
                        ofPoint headPos(simpleHands[i].fingers[2].pos.x, simpleHands[i].fingers[2].pos.y * -1);
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
void testApp::mouseMoved(int x, int y )
{
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button)
{
//    drawing.addVertex(x, y);
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button)
{
//    buildTerrain();
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button)
{
//    drawing.setClosed(false);
//	drawing.simplify();
//
//	polyLine.addVertexes(drawing);
//	polyLine.simplify();
//	polyLine.setPhysics(0.0, 0.5, 0.5);
//	polyLine.create(box2d.getWorld());
//
//	drawing.clear();

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
