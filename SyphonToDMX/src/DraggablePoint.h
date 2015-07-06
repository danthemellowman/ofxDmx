#pragma once

class DraggablePoint {
public:
    ofVec2f position, positionStart;
    bool selected, dragging, hit;
    
    DraggablePoint()
    :selected(false)
    ,dragging(false)
    ,hit(false) {
    }
    bool isHit(ofVec2f v, float clickRadiusSquared) {
        bool curHit = position.distanceSquared(v) < clickRadiusSquared;
        if(curHit) {
            hit = true;
            cout << "hit" << endl;
        }
        return curHit;
    }
    void draw(float clickRadiusSquared) {
        float r = sqrt(clickRadiusSquared);
        ofPushStyle();
        ofNoFill();
        ofSetLineWidth(2);
        if(selected) {
            ofSetColor(ofColor::yellow);
            ofCircle(position, r + 4);
        }
        ofPopStyle();
        ofPushStyle();
        ofFill();
        ofCircle(position, r);
        ofPopStyle();
    }
};