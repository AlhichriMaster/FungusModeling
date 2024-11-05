#pragma once
#include "ofMain.h"
#include "MushroomGenerator.h"

class ofApp : public ofBaseApp {
public:
    void setup();
    void update();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);

private:
    MushroomGenerator mushroom;
    ofEasyCam cam;
    bool wireframe;
    bool showDebug;
    MushroomGenerator::MushroomType currentType;
};