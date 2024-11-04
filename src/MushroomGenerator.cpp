#include "MushroomGenerator.h"

void MushroomGenerator::setup() {
    shader.load("shaders/mushroom");
    mesh.setMode(OF_PRIMITIVE_POINTS);  // Changed to points for initial debugging
    ofLogNotice() << "MushroomGenerator setup complete";
}

void MushroomGenerator::generateMushroom(ofVec3f position, float scale) {
    metaballs.clear();
    mesh.clear();

    ofLogNotice() << "Generating mushroom at position: " << position << " with scale: " << scale;

    // Add metaballs with more extreme values for testing
    metaballs.push_back(MetaBall(position + ofVec3f(0, scale * 2, 0), scale * 2.0f, 2.0f));  // Larger cap
    metaballs.push_back(MetaBall(position + ofVec3f(0, scale * 1.0, 0), scale * 0.8f, 2.0f)); // Thicker stem
    metaballs.push_back(MetaBall(position, scale * 0.8f, 2.0f));  // Larger base

    ofLogNotice() << "Added " << metaballs.size() << " metaballs";

    marchingCubes();
    generateNormals();  // Now implemented
}

void MushroomGenerator::generateNormals() {
    // Clear existing normals
    mesh.clearNormals();

    // For points, just use simple up-facing normals
    for (size_t i = 0; i < mesh.getVertices().size(); i++) {
        mesh.addNormal(ofVec3f(0, 1, 0));
    }

    ofLogNotice() << "Generated " << mesh.getNumNormals() << " normals";
}

void MushroomGenerator::update() {
    // Empty update function - no dynamic behavior yet
    // Can be used later for animation or dynamic effects
}

float MushroomGenerator::evaluateFieldAt(ofVec3f point) const {
    float field = 0;
    for (const auto& ball : metaballs) {
        field += ball.evaluate(point);
    }
    return field;
}

void MushroomGenerator::marchingCubes() {
    float resolution = 0.5f;  // Increased for initial testing
    float threshold = 0.5f;
    int pointCount = 0;

    // Sample space limits
    float xMin = -5, xMax = 5;
    float yMin = 0, yMax = 10;
    float zMin = -5, zMax = 5;

    ofLogNotice() << "Starting marching cubes with resolution: " << resolution;

    for (float x = xMin; x <= xMax; x += resolution) {
        for (float y = yMin; y <= yMax; y += resolution) {
            for (float z = zMin; z <= zMax; z += resolution) {
                ofVec3f point(x, y, z);
                float value = evaluateFieldAt(point);

                if (value > threshold) {
                    mesh.addVertex(point);
                    mesh.addColor(ofColor(255, 0, 0));  // Bright red for visibility
                    pointCount++;
                }
            }
        }
    }

    ofLogNotice() << "Generated " << pointCount << " points";
}

void MushroomGenerator::draw() {
    ofPushMatrix();
    ofPushStyle();

    // Draw the mesh
    if (mesh.getNumVertices() > 0) {
        glPointSize(5.0);  // Make points larger
        mesh.draw();
    }
    else {
        ofLogWarning() << "No vertices in mesh to draw";
    }

    ofPopStyle();
    ofPopMatrix();
}

void MushroomGenerator::drawDebug() const {
    // Draw metaball centers with larger spheres
    for (const auto& ball : metaballs) {
        // Center point
        ofSetColor(255, 0, 0);
        ofDrawSphere(ball.position, 0.2);  // Larger sphere

        // Influence radius
        ofSetColor(255, 255, 0, 100);
        ofNoFill();
        ofDrawSphere(ball.position, ball.radius);
        ofFill();

        // Axes for scale reference
        ofSetColor(255, 0, 0);
        ofDrawLine(ball.position - ofVec3f(ball.radius, 0, 0),
            ball.position + ofVec3f(ball.radius, 0, 0));
        ofSetColor(0, 255, 0);
        ofDrawLine(ball.position - ofVec3f(0, ball.radius, 0),
            ball.position + ofVec3f(0, ball.radius, 0));
        ofSetColor(0, 0, 255);
        ofDrawLine(ball.position - ofVec3f(0, 0, ball.radius),
            ball.position + ofVec3f(0, 0, ball.radius));
    }

    // Draw sampling bounds
    ofSetColor(0, 255, 0, 100);
    ofNoFill();
    ofDrawBox(ofVec3f(0, 5, 0), 10, 10, 10);
    ofFill();
}