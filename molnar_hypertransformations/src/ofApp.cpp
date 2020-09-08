#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    bFill = false;
    nSquares = 6;

    bHideGui = false;
    gui.setup();
    gui.add(bFill.setup("fill", true));
    gui.add(nSquares.setup("squares", 20, 1, 50));
    gui.add(randomSeed.setup("random seed", 2, 0, 2000));
    
    padding = ofGetWindowWidth()*(1.0/nSquares);
    error = padding*0.9;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(243, 243, 243);
    ofSetColor(5, 5, 6);
    ofSetRectMode(OF_RECTMODE_CENTER);
//    ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
    
    if (bFill) {
        ofFill();
    }
    else {
        ofSetLineWidth(1);
        ofNoFill();
    }
    
    ofSeedRandom(randomSeed);
    for (int k=nSquares; k > 0; k--){
        
        if (bFill) {
            if (k%2) {
                ofSetColor(243, 243, 243);
            }
            else
            {
                ofSetColor(5, 5, 6);
            }
        }
        
        float sideSize = ofMap(k,0, nSquares, padding, ofGetWindowWidth()-padding);
        
        float xPlus = ofGetWindowWidth()*0.5 + sideSize*0.5;
        float xMinus = ofGetWindowWidth()*0.5 - sideSize*0.5;
        float yPlus = ofGetWindowHeight()*0.5 + sideSize*0.5;
        float yMinus = ofGetWindowHeight()*0.5 - sideSize*0.5;
        
        float uR[] = {xPlus, yPlus};
        float uL[] = {xMinus, yPlus};
        float lL[] = {xMinus, yMinus};
        float lR[] = {xPlus, yMinus};

        ofBeginShape();
        
        float offsetMultiplier = ofMap(k, 0, nSquares, 50, 5);
        this->drawSide(uL, lL, offsetMultiplier);
        this->drawSide(lL, lR, offsetMultiplier);
        this->drawSide(lR, uR, offsetMultiplier);
        this->drawSide(uR, uL, offsetMultiplier);

        ofEndShape(true);
        
        if(!bHideGui){
            gui.draw();
        }
    }

}

void ofApp::drawSide(float beginCorner[], float endCorner[], float offsetMultiplier) {
    ofVertex(beginCorner[0],beginCorner[1]);
    
    ofVec2f beginPt(beginCorner[0], beginCorner[1]);
    ofVec2f endPt(endCorner[0], endCorner[1]);
    ofVec2f sideVector = endPt - beginPt;
    
    // create random insertion points for control points
    int nVertices = ofRandom(0, 10);
    vector<float> offsets;
    for (int i = 0; i < nVertices; i++) {
        offsets.push_back(ofRandom(0, 1));
    }
    
    sort(offsets.begin(), offsets.end());
    ofLog() << ofToString(sideVector);
    
    for (int i = 0; i < offsets.size(); i++) {
        ofVec2f curPt = beginPt+sideVector*offsets[i];
        curPt.x += ofMap(ofNoise(i*0.5), 0, 1, 0, offsetMultiplier);
        curPt.y += ofMap(ofNoise(i*0.5), 0, 1, 0, offsetMultiplier);
        ofVertex(curPt);
    }
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        img.grabScreen(0,0,ofGetWindowWidth(),ofGetWindowHeight());
        string fileName = "hypertransformation_" + ofGetTimestampString("%y-%m-%d-%H%M") + ".jpg";
        img.save(fileName);
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
