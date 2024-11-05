#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofEnableDepthTest();

    wireframe = false;
    showDebug = true;
    currentType = MushroomGenerator::BASIC;

    // Set up camera
    cam.setDistance(10);
    cam.setNearClip(0.1);
    cam.setFarClip(1000);
    cam.setPosition(5, 5, 5);
    cam.lookAt(ofVec3f(0, 0, 0));

    // Initialize mushroom
    mushroom.setup();
    mushroom.generateMushroom(ofVec3f(0, 0, 0), 1.0f, currentType);
}

void ofApp::update() {
    mushroom.update();
}

void ofApp::draw() {
    ofBackground(40);

    cam.begin();

    // Draw coordinate system
    ofDrawAxis(10);

    // Draw grid
    ofPushStyle();
    ofSetColor(128);
    ofDrawGrid(10, 1, false, false, true, false);
    ofPopStyle();

    // Draw mushroom
    mushroom.draw();

    if (wireframe) {
        mushroom.drawWireframe();
    }

    if (showDebug) {
        mushroom.drawDebug();
    }

    cam.end();

    // Draw UI
    ofSetColor(255);
    string info = "FPS: " + ofToString(ofGetFrameRate(), 1) + "\n";
    info += "Press 'w' to toggle wireframe\n";
    info += "Press 'd' to toggle debug view\n";
    info += "Press '1-3' to change mushroom type\n";
    info += "Click to generate new mushroom";
    ofDrawBitmapString(info, 10, 20);
}

void ofApp::keyPressed(int key) {
    switch (key) {
    case 'w':
        wireframe = !wireframe;
        break;
    case 'd':
        showDebug = !showDebug;
        break;
    case '1':
        currentType = MushroomGenerator::BASIC;
        mushroom.generateMushroom(ofVec3f(0, 0, 0), 1.0f, currentType);
        break;
    case '2':
        currentType = MushroomGenerator::AMANITA_MUSCARIA;
        mushroom.generateMushroom(ofVec3f(0, 0, 0), 1.0f, currentType);
        break;
    case '3':
        currentType = MushroomGenerator::GOLDEN_TEACHER;
        mushroom.generateMushroom(ofVec3f(0, 0, 0), 1.0f, currentType);
        break;
    }
}

void ofApp::mousePressed(int x, int y, int button) {
    float scale = ofRandom(0.5f, 1.5f);
    mushroom.generateMushroom(ofVec3f(0, 0, 0), scale, currentType);
}