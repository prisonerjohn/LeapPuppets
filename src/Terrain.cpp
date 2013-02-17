//
//  Terrain.cpp
//  Caterpillar
//
//  Created by Elie Zananiri on 2013-02-14.
//
//

#include "Terrain.h"

//--------------------------------------------------------------
const int Terrain::kMinStep = 10;
const int Terrain::kMaxStep = 50;
const int Terrain::kMaxHeight = 50;

//--------------------------------------------------------------
Terrain::Terrain(ofxMtlBox2dWorld *world)
{
//    polyLine = new ofxBox2dPolygon();
//    polyLine->setClosed(true);

    // build the jagged terrain top edge
    int lineX = 0;
    while (lineX < ofGetWidth()) {
        points.push_back(ofPoint(lineX, ofRandom(ofGetHeight() - kMaxHeight, ofGetHeight())));
        lineX += ofRandom(kMinStep, kMaxStep);
    }

    // complete the polygon
    points.push_back(ofPoint(ofGetWidth(), ofRandom(ofGetHeight() - 50, ofGetHeight())));
    points.push_back(ofPoint(ofGetWidth(), ofGetHeight()));
    points.push_back(ofPoint(0, ofGetHeight()));
//
//    polyLine->simplify();
//	polyLine->setPhysics(0.0, 0.5, 0.5);
//	polyLine->create(physics->getWorld());

    polygon = new ofxMtlBox2dPolygon();
    polygon->setPhysics(3.0, 0.53, 0.1);
    polygon->setup(world, points);
}

//--------------------------------------------------------------
Terrain::~Terrain()
{
    delete polygon;
    points.clear();
}

//--------------------------------------------------------------
void Terrain::update()
{

}

//--------------------------------------------------------------
void Terrain::draw()
{
    ofFill();

    ofSetColor(0, 0, 200);
    ofBeginShape();
    {
        for (int i = 0; i < points.size(); i++) {
            ofVertex(points[i]);
        }
    }
    ofEndShape();
}
