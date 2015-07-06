#pragma once

#include "ofMain.h"
#include "ofxSyphon.h"
#include "SelectablePoints.h"
#include "DraggablePoints.h"
#include "ofxPanel.h"
#include "ofxDmx.h"
#include "ofxXmlSettings.h"
class DMXPoint : public DraggablePoints {
public:
    void draw(ofEventArgs& args) {
        ofSetColor(0, 0, 0, 0);
        DraggablePoints::draw(args);
    }
};


class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void exit();
    
    void reset();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    
    void serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg);
    void serverUpdated(ofxSyphonServerDirectoryEventArgs &args);
    void serverRetired(ofxSyphonServerDirectoryEventArgs &arg);
    
    ofxSyphonServerDirectory dir;
    ofxSyphonClient client;
    int dirIdx;
    ofColor c;
    ofxPanel gui;
    ofParameterGroup SyphonToDMX;
    ofParameter<int> numRows;
    ofParameter<int> numCols;
    ofParameter<string> port;
    ofParameter<float> lerpColor;
    ofParameter<int> channelsPerModule;
    ofParameter<bool> resetPos;
    ofParameter<bool> drawSample;
    ofParameter<int> standBymode;
    DMXPoint colorPoints;
    ofPixels pix;
    ofFbo sampler;
    vector<ofColor> dmxColors;
    ofxDmx dmx;
};
