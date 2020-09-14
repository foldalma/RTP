#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    sampleRate = 44100;
    channels = 2;
    ofSetFrameRate(60);
    
    fbo.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    
    fileName = "whitney_experiments";
    fileExt = ".mp4";
    
    vidRecorder.setVideoCodec("mpeg4");
    vidRecorder.setVideoBitrate("800k");
    vidRecorder.setAudioCodec("mp3");
    vidRecorder.setAudioBitrate("192k");
    
    ofAddListener(vidRecorder.outputFileCompleteEvent, this, &ofApp::recordingComplete);
    
    ofSetWindowShape(ofGetWidth(), ofGetHeight());
    bRecording = false;
    
    post.init(ofGetWidth(), ofGetHeight());
    post.createPass<BloomPass>();
}

void ofApp::exit() {
    ofRemoveListener(vidRecorder.outputFileCompleteEvent, this, &ofApp::recordingComplete);
    vidRecorder.close();
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if(bRecording){
        fbo.readToPixels(recordPixels);
        bool success = vidRecorder.addFrame(recordPixels);
        if (!success) {
            ofLogWarning("This frame was not added!");
        }
    }

    // Check if the video recorder encountered any error while writing video frame or audio smaples.
    if (vidRecorder.hasVideoError()) {
        ofLogWarning("The video recorder failed to write some frames!");
    }

    if (vidRecorder.hasAudioError()) {
        ofLogWarning("The video recorder failed to write some audio samples!");
    }

}

void ofApp::recordingComplete(ofxVideoRecorderOutputFileCompleteEventArgs& args){
    cout << "The recoded video file is now complete." << endl;
}

//--------------------------------------------------------------
void ofApp::draw(){
    
    fbo.begin();
    post.begin();
    ofBackground(5);
    
    float minSize = 0.4;
    float maxSize = 0.6;
    
    int numCircles = 50;
    for (int i = 0; i < numCircles; i++) {
        ofSetColor(0, 0, 255);
        float xorig = ofMap(i*10, 0, numCircles*10,ofGetWidth()*minSize, ofGetWidth()*maxSize);
        float yorig = ofMap(i*10, 0, numCircles*10,ofGetHeight()*minSize, ofGetHeight()*maxSize);
        float radius = 100 + 60 * sin(ofGetElapsedTimef()*0.01);
//        float radius = 100;
        float angle = 2*ofGetElapsedTimef()*ofMap(i, 0, numCircles, 0.45,1.20);
        float x1 = xorig + radius * cos(angle*0.1);
        float y1 = yorig + radius * sin(angle*0.2);
        ofDrawCircle(x1,y1, 2);
        
        ofSetColor(255, 255, 255);
        float x2orig = ofMap(i*10, 0, numCircles*10,ofGetWidth()*minSize*1.1, ofGetWidth()*maxSize*1.1);
        float y2orig = ofMap(i*10, 0, numCircles*10,ofGetWidth()*minSize*1.1, ofGetWidth()*maxSize*1.1);
        float radius2 = 100 + 50 * sin(ofGetElapsedTimef()*0.015);
//        float radius2 = 150;
        float x2 = x2orig + radius2 * cos(angle*0.2);
        float y2 = y2orig + radius2 * sin(angle*0.17);
        ofDrawCircle(x2,y2, 2);
        
        
        ofMesh mesh;
        mesh.setMode(OF_PRIMITIVE_LINES);
        mesh.enableColors();
        mesh.enableIndices();
        
        mesh.addVertex(ofVec3f(x1, y1, 0));
        mesh.addColor(ofFloatColor(0.0,0.0,1.0));
        mesh.addVertex(ofVec3f(x2, y2, 0));
        mesh.addColor(ofFloatColor(1.0,1.0,1.0));
        
        mesh.addIndex(0);
        mesh.addIndex(1);
        mesh.draw();
//        ofDrawLine(x1, y1, x2, y2);
    }
    
    post.end();
    fbo.end();
    fbo.draw(0,0);
    
//    if(bRecording){
//        ofSetColor(255, 0, 0);
//        ofDrawCircle(ofGetWidth() - 20, 20, 5);
//    }
    
    counter += 0.001;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='r'){
        bRecording = !bRecording;
        
        if(bRecording && !vidRecorder.isInitialized()) {
//            vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, vidGrabber.getWidth(), vidGrabber.getHeight(), 30, sampleRate, channels);
          vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, fbo.getWidth(), fbo.getHeight(), 30); // no audio
//            vidRecorder.setup(fileName+ofGetTimestampString()+fileExt, 0,0,0, sampleRate, channels); // no video
//          vidRecorder.setupCustomOutput(vidGrabber.getWidth(), vidGrabber.getHeight(), 30, sampleRate, channels, "-vcodec mpeg4 -b 1600k -acodec mp2 -ab 128k -f mpegts udp://localhost:1234"); // for custom ffmpeg output string (streaming, etc)

            // Start recording
            vidRecorder.start();
        }
        else if(!bRecording && vidRecorder.isInitialized()) {
            vidRecorder.setPaused(true);
        }
        else if(bRecording && vidRecorder.isInitialized()) {
            vidRecorder.setPaused(false);
        }
    }
    if(key=='c'){
        bRecording = false;
        vidRecorder.close();
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
