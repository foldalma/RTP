#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    bFill = false;
    nSquares = 6;

    bHideGui = false;
    gui.setup();
    gui.add(bFill.setup("fill", true));
    
    padding = ofGetWindowWidth()*(1.0/nSquares);
    error = padding*0.9;
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(255, 255, 255);
    ofSetColor(0);
    ofSetRectMode(OF_RECTMODE_CENTER);
//    ofEnableBlendMode(OF_BLENDMODE_SUBTRACT);
    
    if (bFill) {
        ofFill();
    }
    else {
        ofSetLineWidth(1);
        ofNoFill();
    }
    
    
    ofSeedRandom(mouseX);
    for (int k=0; k < nSquares; k++){
        
        if (bFill) {
            if (k%4) {
                ofSetColor(0);
            }
            else
            {
                ofSetColor(0);
            }
        }
    
        float sideSize = ofMap(k,0, nSquares, padding, ofGetWindowWidth()-padding);
        
        float xPlus = ofGetWindowWidth()*0.5 + sideSize*0.5;
        float xMinus = ofGetWindowWidth()*0.5 - sideSize*0.5;
        float yPlus = ofGetWindowHeight()*0.5 + sideSize*0.5;
        float yMinus = ofGetWindowHeight()*0.5 - sideSize*0.5;

        if (!k%2) {
            ofBeginShape();
            
            ofVertex(xPlus,yPlus);
            if (ofRandom(0,1) < 0.95){
                ofCurveVertex(xPlus-sideSize*ofRandom(0.2, 0.8),yPlus+ofMap(ofNoise(k*0.5, k*0.5), 0, 1, -error, error));
            }
            
            ofVertex(xMinus,yPlus);
            ofLog() << "error: " << error;
            if (ofRandom(0,1) < 0.95){
                ofCurveVertex(xMinus+ofMap(ofNoise(k*0.1, k*0.1), 0, 1, -error, error),yPlus-sideSize*ofRandom(0.2, 0.8));
            }
            
            ofVertex(xMinus,yMinus);
            if (ofRandom(0,1) < 0.95){
                ofCurveVertex(xMinus+sideSize*ofRandom(0.2, 0.8),yMinus-ofMap(ofNoise(k*0.5, k*0.5), 0, 1, -error, error));
            }
            
            ofVertex(xPlus,yMinus);
            if (ofRandom(0,1) < 0.95){
                ofCurveVertex(xPlus+ofMap(ofNoise(k*0.5, k*0.5), 0, 1, -error, error),yMinus+sideSize*ofRandom(0.2, 0.8));
            }
            
            ofVertex(xPlus,yPlus);
            if (ofRandom(0,1) < 0.95){
                ofCurveVertex(xPlus-sideSize*ofRandom(0.2, 0.8),yPlus+ofMap(ofNoise(k*0.5, k*0.5), 0, 1, -error, error));
            }
        }
        

        if (k%2) {
            ofVertex(xPlus,yMinus);
            if (ofRandom(0,1) < 0.95){
                ofCurveVertex(xPlus+ofMap(ofNoise(k*0.1, k*0.1), 0, 1, -error, error),yMinus+sideSize*ofRandom(0.2, 0.8));
            }
            ofVertex(xMinus,yMinus);
            if (ofRandom(0,1) < 0.95){
                ofCurveVertex(xMinus+sideSize*ofRandom(0.2, 0.8),yMinus-ofMap(ofNoise(k*0.5, k*0.5), 0, 1, -error, error));
            }
            ofVertex(xMinus,yPlus);
            ofLog() << "error: " << error;
            if (ofRandom(0,1) < 0.95){
                ofCurveVertex(xMinus+ofMap(ofNoise(k*0.5, k*0.5), 0, 1, -error, error),yPlus-sideSize*ofRandom(0.2, 0.8));
            }
            ofVertex(xPlus,yPlus);
            if (ofRandom(0,1) < 0.95){
                ofCurveVertex(xPlus-sideSize*ofRandom(0.2, 0.8),yPlus+ofMap(ofNoise(k*0.5, k*0.5), 0, 1, -error, error));
            }
            
            ofVertex(xPlus,yMinus);
            if (ofRandom(0,1) < 0.95){
                ofCurveVertex(xPlus+ofMap(ofNoise(k*0.5, k*0.5), 0, 1, -error, error),yMinus+sideSize*ofRandom(0.2, 0.8));
            }
            
            ofEndShape();
        }
        
        
        if(!bHideGui){
            gui.draw();
        }
//
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
