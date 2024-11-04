// src/ofApp.cpp
#include "ofApp.h"

void ofApp::setup() {
    ofSetFrameRate(60);
    ofEnableDepthTest();
    ofSetLogLevel(OF_LOG_NOTICE);  // Enable logging

    ofLogNotice() << "Starting application setup";

    wireframe = false;
    showDebug = true;

    // Set up camera for better initial view
    cam.setDistance(15);
    cam.setNearClip(0.1);
    cam.setFarClip(1000);
    cam.setPosition(10, 10, 10);
    cam.lookAt(ofVec3f(0, 0, 0));

    mushroom.setup();
    mushroom.generateMushroom(ofVec3f(0, 0, 0), 2.0f);

    ofLogNotice() << "Application setup complete";
}

void ofApp::update() {
    mushroom.update();
}

void ofApp::draw() {
    ofBackground(40);

    // Simple directional lighting
    ofEnableLighting();
    ofLight light;
    light.setDirectional();
    light.setPosition(10, 10, 10);
    light.enable();

    cam.begin();

    // Draw coordinate system
    ofDrawAxis(10);

    // Draw ground grid
    ofPushStyle();
    ofSetColor(128);
    ofDrawGrid(10, 1, false, false, true, false);
    ofPopStyle();

    // Always show debug for now
    mushroom.drawDebug();

    // Draw the mesh
    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }

    mushroom.draw();

    if (wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    cam.end();

    // Draw debug info
    ofSetColor(255);
    stringstream info;
    info << "FPS: " << ofGetFrameRate() << endl;
    info << "Camera distance: " << cam.getDistance() << endl;
    info << "Camera position: " << cam.getPosition() << endl;
    info << "Press 'w' to toggle wireframe" << endl;
    info << "Press 'd' to toggle debug view" << endl;
    info << "Click to generate new mushroom" << endl;
    info << "Left mouse: Rotate" << endl;
    info << "Middle mouse: Pan" << endl;
    info << "Right mouse: Zoom" << endl;

    ofDrawBitmapString(info.str(), 10, 20);
}


void ofApp::keyPressed(int key) {
    if (key == 'w') {
        wireframe = !wireframe;
    }
    else if (key == 'd') {
        showDebug = !showDebug;
    }
}

void ofApp::mousePressed(int x, int y, int button) {
    float scale = ofRandom(1.0, 3.0);
    mushroom.generateMushroom(ofVec3f(0, 0, 0), scale);
}