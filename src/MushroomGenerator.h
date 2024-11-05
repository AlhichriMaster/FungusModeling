#pragma once
#include "ofMain.h"
#include "MetaBall.h"

class MushroomGenerator {
public:
    enum MushroomType {
        AMANITA_MUSCARIA,  // Red with white spots
        GOLDEN_TEACHER,    // Golden brown
        BASIC             // Simple shape
    };

    void setup();
    void update();
    void draw();
    void drawWireframe();
    void drawDebug() const;
    void generateMushroom(ofVec3f position, float scale, MushroomType type = BASIC);

    // Parameters
    void setGrowthSpeed(float speed) { growthSpeed = speed; }
    void setWobbleAmount(float amount) { wobbleAmount = amount; }
    void setCapExpansion(float expansion) { capExpansion = expansion; }

private:
    struct GridCell {
        ofVec3f p[8];     // Vertices
        float val[8];     // Field values
        ofVec3f n[8];     // Normals
    };

    struct Triangle {
        ofVec3f p[3];     // Positions
        ofVec3f n[3];     // Normals
    };

    std::vector<MetaBall> metaballs;
    ofMesh mesh;
    ofShader shader;
    MushroomType currentType;

    // Core functions
    void marchingCubes();
    float evaluateFieldAt(ofVec3f point) const;
    ofVec3f calculateNormalAt(const ofVec3f& point) const;
    std::vector<Triangle> polygonizeCell(const GridCell& cell, float isolevel);
    ofVec3f interpolateVertex(ofVec3f p1, ofVec3f p2, float valp1, float valp2, float isolevel);
    ofVec3f interpolateNormal(const ofVec3f& n1, const ofVec3f& n2, float valp1, float valp2, float isolevel);
    void generateNormals();

    // Animation parameters
    float growthSpeed = 1.0f;
    float wobbleAmount = 0.2f;
    float capExpansion = 1.0f;
    float time = 0.0f;
    bool isGrowing = true;

    std::vector<ofVec3f> originalPositions;
    std::vector<float> originalRadii;

    // Lookup tables
    static const int edgeTable[256];
    static const int triTable[256][16];
};