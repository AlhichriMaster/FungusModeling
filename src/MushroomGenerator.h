#pragma once
#include "ofMain.h"
#include "MetaBall.h"

class MushroomGenerator {
public:
    void setup();
    void update();
    void draw();
    void generateMushroom(ofVec3f position, float scale);
    void drawDebug() const;

private:
    std::vector<MetaBall> metaballs;
    ofMesh mesh;
    ofShader shader;

    void generateImplicitSurface();
    void marchingCubes();
    float evaluateFieldAt(ofVec3f point) const;
    void addSurfaceDetail();
    void generateNormals();
};