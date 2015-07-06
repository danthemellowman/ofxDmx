#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetVerticalSync(true);
    ofSetFrameRate(60);
    //setup our directory
    dir.setup();
    //setup our client
    client.setup();
    
    //register for our directory's callbacks
    ofAddListener(dir.events.serverAnnounced, this, &ofApp::serverAnnounced);
    // not yet implemented
    //ofAddListener(dir.events.serverUpdated, this, &ofApp::serverUpdated);
    ofAddListener(dir.events.serverRetired, this, &ofApp::serverRetired);
    dirIdx = -1;
    SyphonToDMX.setName("Syphon To DMX");
    SyphonToDMX.add(lerpColor.set("Change Rate", 0.01, 0.001, 1.0));
    SyphonToDMX.add(resetPos.set("Reset", false));
    SyphonToDMX.add(numCols.set("Num Cols", 6, 1, 12));
    SyphonToDMX.add(numRows.set("Num Rows", 2, 1, 12));
    SyphonToDMX.add(channelsPerModule.set("Channels", 3, 1, 4));
    SyphonToDMX.add(port.set("port", "tty.usbserial-EN143867"));
    SyphonToDMX.add(drawSample.set("Draw Syphon ", true));
    SyphonToDMX.add(standBymode.set("Stand By Mode", 0, 0, 10));
    
    gui.setup();
    gui.add(SyphonToDMX);
    gui.setSize(250, 300);
    gui.setWidthElements(250);
    gui.loadFromFile("SyphonToDMX.xml");
    
    
    colorPoints.setClickRadius(24);
    for(int i = 0; i <  numCols; i++) {
        for(int j = 0; j < numRows; j++){
            colorPoints.add(ofVec2f(ofGetWidth()/((numCols)*2)+i*ofGetWidth()/(numCols), ofGetHeight()/((numRows)*2)+j*ofGetHeight()/(numRows)));
            dmxColors.push_back(ofColor(255, 255, 255));
        }
    }
    
    ofxXmlSettings samplerPts;
    if(samplerPts.loadFile(("sampler.xml"))){
        samplerPts.pushTag("samplerPts");
        for(int i = 0; i < colorPoints.size(); i++){
            colorPoints.get(i).position.x = samplerPts.getValue("x", 0, i);
            colorPoints.get(i).position.y =samplerPts.getValue("y", 0, i);
        }
        
        samplerPts.popTag();
    }
    
    
    
    colorPoints.enableControlEvents();
    colorPoints.enableDrawEvent();
    
    sampler.allocate(ofGetWidth(), ofGetHeight(), GL_RGB);
    sampler.begin();
    ofClear(0, 0, 0, 0);
    sampler.end();
    
    pix.allocate(sampler.getWidth(), sampler.getHeight(), 3);
    
    dmx.connect(port.get(), numRows*numCols * channelsPerModule);
    dmx.update(true); // black on startup
    
    
}
//--------------------------------------------------------------
void ofApp::update(){
    ofPushStyle();
    ofEnableAlphaBlending();
    sampler.begin();
    ofClear(0, 0, 0);
    ofSetColor(255, 255, 255);
    if(dir.isValidIndex(dirIdx)){
        client.draw(0, (sampler.getHeight()-sampler.getWidth()*client.getHeight()/client.getWidth())/2, sampler.getWidth(), sampler.getWidth()*client.getHeight()/client.getWidth());
    }else{
        float time = ofGetElapsedTimef();
        if(standBymode == 0){
            for(int i = 0; i < numCols; i++){
                for(int j = 0; j < numRows; j++){
                    c = ofColor(abs(sin(time/10*(i+1)))*255, 0, abs(sin(time/20*(i+1))*255));
                    ofSetColor(c);
                    ofRect(i*sampler.getWidth()/numCols, j*sampler.getHeight()/numRows, sampler.getWidth()/numCols, sampler.getHeight()/numRows);
                    
                }
            }
        }else if(standBymode == 1){
            for(int i = 0; i < numCols; i++){
                for(int j = 0; j < numRows; j++){
                    c = ofColor(abs(sin(time/3))*255, abs(sin(time))*255, abs(sin(time/2)*255));
                    ofSetColor(c);
                    ofRect(i*sampler.getWidth()/numCols, j*sampler.getHeight()/numRows, sampler.getWidth()/numCols, sampler.getHeight()/numRows);
                    
                }
            }
        }else if(standBymode == 2){
            for(int i = 0; i < numCols; i++){
                for(int j = 0; j < numRows; j++){
                    c = ofColor(abs(sin(time/10+(i+1)))*255, 0, abs(sin(time/10+(i+1))*255));
                    ofSetColor(c);
                    ofRect(i*sampler.getWidth()/numCols, j*sampler.getHeight()/numRows, sampler.getWidth()/numCols, sampler.getHeight()/numRows);
                    
                }
            }
        }else if(standBymode == 3){
            for(int i = 0; i < numCols; i++){
                for(int j = 0; j < numRows; j++){
                    c = ofColor(abs(sin(time/10*(j+1)))*255, 0, abs(sin(time/20*(j+1))*255));
                    ofSetColor(c);
                    ofRect(i*sampler.getWidth()/numCols, j*sampler.getHeight()/numRows, sampler.getWidth()/numCols, sampler.getHeight()/numRows);
                    
                }
            }
        }else if(standBymode == 4){
            for(int i = 0; i < numCols; i++){
                for(int j = 0; j < numRows; j++){
                    c = ofColor(abs(sin(time/100+(i+1)))*255, abs(sin(time/200+(i+1))*255), abs(sin(time/200+(i+1))*255));
                    ofSetColor(c);
                    ofRect(i*sampler.getWidth()/numCols, j*sampler.getHeight()/numRows, sampler.getWidth()/numCols, sampler.getHeight()/numRows);
                    
                }
            }
        }else if(standBymode == 5){
            for(int i = 0; i < numCols; i++){
                for(int j = 0; j < numRows; j++){
                    c = ofColor(abs(sin(time/10/(i+1)))*255, 0, abs(sin(time/20/(i+1))*255));
                    ofSetColor(c);
                    ofRect(i*sampler.getWidth()/numCols, j*sampler.getHeight()/numRows, sampler.getWidth()/numCols, sampler.getHeight()/numRows);
                    
                }
            }
        }else if(standBymode == 6){
            for(int i = 0; i < numCols; i++){
                for(int j = 0; j < numRows; j++){
                    c = ofColor(abs(sin(time/10*(i+1)))*255, 0, abs(sin(time/20*(i+1))*255));
                    ofSetColor(c);
                    ofRect(i*sampler.getWidth()/numCols, j*sampler.getHeight()/numRows, sampler.getWidth()/numCols, sampler.getHeight()/numRows);
                    
                }
            }
        }else if(standBymode == 7){
            for(int i = 0; i < numCols; i++){
                for(int j = 0; j < numRows; j++){
                    c = ofColor(abs(sin(time/10*(i+1)))*255, 0, abs(sin(time/20*(i+1))*255));
                    ofSetColor(c);
                    ofRect(i*sampler.getWidth()/numCols, j*sampler.getHeight()/numRows, sampler.getWidth()/numCols, sampler.getHeight()/numRows);
                    
                }
            }
        }else if(standBymode == 8){
            for(int i = 0; i < numCols; i++){
                for(int j = 0; j < numRows; j++){
                    c = ofColor(abs(sin(time/10*(i+1)))*255, 0, abs(sin(time/20*(i+1))*255));
                    ofSetColor(c);
                    ofRect(i*sampler.getWidth()/numCols, j*sampler.getHeight()/numRows, sampler.getWidth()/numCols, sampler.getHeight()/numRows);
                    
                }
            }
        }else if(standBymode == 9){
            for(int i = 0; i < numCols; i++){
                for(int j = 0; j < numRows; j++){
                    c = ofColor(abs(sin(time/10*(i+1)))*255, 0, abs(sin(time/20*(i+1))*255));
                    ofSetColor(c);
                    ofRect(i*sampler.getWidth()/numCols, j*sampler.getHeight()/numRows, sampler.getWidth()/numCols, sampler.getHeight()/numRows);
                    
                }
            }
        }else if(standBymode == 10){
            for(int i = 0; i < numCols; i++){
                for(int j = 0; j < numRows; j++){
                    c = ofColor(abs(sin(time/10*(i+1)))*255, 0, abs(sin(time/20*(i+1))*255));
                    ofSetColor(c);
                    ofRect(i*sampler.getWidth()/numCols, j*sampler.getHeight()/numRows, sampler.getWidth()/numCols, sampler.getHeight()/numRows);
                    
                }
            }
        }
    }
    
    sampler.end();
    ofDisableAlphaBlending();
    
    
    
    sampler.readToPixels(pix);
    
    for(int i = 0; i < colorPoints.size(); i++){
        ofVec2f pt = colorPoints.get(i).position;
        ofColor currentColor;
        for(int j = -24; j <= 24; j++){
            for(int k = -24; k <= 24; k++){
                currentColor = currentColor.lerp(pix.getColor(pt.x+j, pt.y+k), 0.5);
            }
        }
        dmxColors[i] =  dmxColors[i].lerp(currentColor, lerpColor);
    }
    ofPopStyle();
    
    int channel = 1;
    for(int module = 0; module < numCols*numRows; module++) {
        string label = "mod" + ofToString(module);
        dmx.setLevel(channel++, dmxColors[module].r);
        dmx.setLevel(channel++, dmxColors[module].g);
        dmx.setLevel(channel++, dmxColors[module].b);
    }
    if(dmx.isConnected()) {
        dmx.update();
    }
    
    if(resetPos){
        int count = 0;
        for(int i = 0; i <  numCols; i++) {
            for(int j = 0; j < numRows; j++){
                colorPoints.get(count).position.set(ofVec2f(ofGetWidth()/((numCols)*2)+i*ofGetWidth()/(numCols), ofGetHeight()/((numRows)*2)+j*ofGetHeight()/(numRows)));
                count++;
            }
        }
        resetPos = false;
    }
    
}

void ofApp::exit(){
    gui.saveToFile("SyphonToDMX.xml");
    ofxXmlSettings samplerPts;
    samplerPts.addTag("samplerPts");
    samplerPts.pushTag("samplerPts");
    for(int i = 0; i < colorPoints.size(); i++){
        ofVec2f foo = colorPoints.get(i).position;
        cout<<foo<<endl;
        samplerPts.addValue("x", foo.x);
        samplerPts.addValue("y", foo.y);
    }
    samplerPts.popTag();
    samplerPts.save("sampler.xml");
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0, 0, 0);
    ofPushStyle();
    ofSetColor(255, 255, 255);
    if(drawSample)
        sampler.draw(0, 0);
    for(int i = 0; i < colorPoints.size(); i++){
        ofVec2f pt = colorPoints.get(i).position;
        
        ofSetColor(100, 100, 100);
        ofCircle(pt, 35);
        
        ofSetColor(dmxColors[i]);
        ofCircle(pt, 30);
        
        ofSetColor(255, 255, 255);
        ofDrawBitmapStringHighlight("Start Ch: "+ofToString(1+i*channelsPerModule), pt+ofVec2f(-50, 50));
    }
    ofPopStyle();
    
    ofDrawBitmapStringHighlight(ofToString(ofGetFrameRate()), ofGetWidth()-75, ofGetHeight()-10);
    
    gui.draw();
}

//these are our directory's callbacks
void ofApp::serverAnnounced(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Announced")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}

void ofApp::serverUpdated(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Updated")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}

void ofApp::serverRetired(ofxSyphonServerDirectoryEventArgs &arg)
{
    for( auto& dir : arg.servers ){
        ofLogNotice("ofxSyphonServerDirectory Server Retired")<<" Server Name: "<<dir.serverName <<" | App Name: "<<dir.appName;
    }
    dirIdx = 0;
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    //press any key to move through all available Syphon servers
    if (dir.size() > 0)
    {
        if(key == OF_KEY_LEFT){
            dirIdx--;
        }
        if(key == OF_KEY_RIGHT){
            dirIdx++;
        }
        if(dirIdx > dir.size() - 1){
            dirIdx = 0;
        }
        if(dirIdx < 0){
            dirIdx = dir.size() - 1;
        }
        client.set(dir.getDescription(dirIdx));
        string serverName = client.getServerName();
        string appName = client.getApplicationName();
        
        if(serverName == ""){
            serverName = "null";
        }
        if(appName == ""){
            appName = "null";
        }
        ofSetWindowTitle(serverName + ":" + appName);
        
    }
    else
    {
        ofSetWindowTitle("No Server");
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
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}
