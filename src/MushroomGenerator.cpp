#include "MushroomGenerator.h"


const int MushroomGenerator::edgeTable[256] = {
    0x0  , 0x109, 0x203, 0x30a, 0x406, 0x50f, 0x605, 0x70c,
    0x80c, 0x905, 0xa0f, 0xb06, 0xc0a, 0xd03, 0xe09, 0xf00,
    0x190, 0x099, 0x393, 0x29a, 0x596, 0x49f, 0x795, 0x69c,
    0x99c, 0x895, 0xb9f, 0xa96, 0xd9a, 0xc93, 0xf99, 0xe90,
    0x230, 0x339, 0x033, 0x13a, 0x636, 0x73f, 0x435, 0x53c,
    0xa3c, 0xb35, 0x83f, 0x936, 0xe3a, 0xf33, 0xc39, 0xd30,
    0x3a0, 0x2a9, 0x1a3, 0x0aa, 0x7a6, 0x6af, 0x5a5, 0x4ac,
    0xbac, 0xaa5, 0x9af, 0x8a6, 0xfaa, 0xea3, 0xda9, 0xca0,
    0x460, 0x569, 0x663, 0x76a, 0x066, 0x16f, 0x265, 0x36c,
    0xc6c, 0xd65, 0xe6f, 0xf66, 0x86a, 0x963, 0xa69, 0xb60,
    0x5f0, 0x4f9, 0x7f3, 0x6fa, 0x1f6, 0x0ff, 0x3f5, 0x2fc,
    0xdfc, 0xcf5, 0xfff, 0xef6, 0x9fa, 0x8f3, 0xbf9, 0xaf0,
    0x650, 0x759, 0x453, 0x55a, 0x256, 0x35f, 0x055, 0x15c,
    0xe5c, 0xf55, 0xc5f, 0xd56, 0xa5a, 0xb53, 0x859, 0x950,
    0x7c0, 0x6c9, 0x5c3, 0x4ca, 0x3c6, 0x2cf, 0x1c5, 0x0cc,
    0xfcc, 0xec5, 0xdcf, 0xcc6, 0xbca, 0xac3, 0x9c9, 0x8c0,
    0x8c0, 0x9c9, 0xac3, 0xbca, 0xcc6, 0xdcf, 0xec5, 0xfcc,
    0x0cc, 0x1c5, 0x2cf, 0x3c6, 0x4ca, 0x5c3, 0x6c9, 0x7c0,
    0x950, 0x859, 0xb53, 0xa5a, 0xd56, 0xc5f, 0xf55, 0xe5c,
    0x15c, 0x055, 0x35f, 0x256, 0x55a, 0x453, 0x759, 0x650,
    0xaf0, 0xbf9, 0x8f3, 0x9fa, 0xef6, 0xfff, 0xcf5, 0xdfc,
    0x2fc, 0x3f5, 0x0ff, 0x1f6, 0x6fa, 0x7f3, 0x4f9, 0x5f0,
    0xb60, 0xa69, 0x963, 0x86a, 0xf66, 0xe6f, 0xd65, 0xc6c,
    0x36c, 0x265, 0x16f, 0x066, 0x76a, 0x663, 0x569, 0x460,
    0xca0, 0xda9, 0xea3, 0xfaa, 0x8a6, 0x9af, 0xaa5, 0xbac,
    0x4ac, 0x5a5, 0x6af, 0x7a6, 0x0aa, 0x1a3, 0x2a9, 0x3a0,
    0xd30, 0xc39, 0xf33, 0xe3a, 0x936, 0x83f, 0xb35, 0xa3c,
    0x53c, 0x435, 0x73f, 0x636, 0x13a, 0x033, 0x339, 0x230,
    0xe90, 0xf99, 0xc93, 0xd9a, 0xa96, 0xb9f, 0x895, 0x99c,
    0x69c, 0x795, 0x49f, 0x596, 0x29a, 0x393, 0x099, 0x190,
    0xf00, 0xe09, 0xd03, 0xc0a, 0xb06, 0xa0f, 0x905, 0x80c,
    0x70c, 0x605, 0x50f, 0x406, 0x30a, 0x203, 0x109, 0x000
};




const int MushroomGenerator::triTable[256][16] = {
    {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 1, 9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {1, 8, 3, 9, 8, 1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    // ... (rest of triangle table - you would paste all 256 entries here)
    // For testing, we can start with just a few entries
    {1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1},
    {0, 8, 3, 1, 2, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1}
};

void MushroomGenerator::setup() {
    shader.load("shaders/mushroom");
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    ofLogNotice() << "MushroomGenerator setup complete";
}

void MushroomGenerator::generateMushroom(ofVec3f position, float scale, MushroomType type) {
    metaballs.clear();
    mesh.clear();
    currentType = type;

    metaballs.push_back(MetaBall(
        position + ofVec3f(0, scale * 2.0f, 0),
        scale * 1.5f,
        1.5f
    ));

    metaballs.push_back(MetaBall(
        position + ofVec3f(0, scale * 1.0f, 0),
        scale * 0.5f,
        1.2f
    ));

    metaballs.push_back(MetaBall(
        position + ofVec3f(0, 0, 0),
        scale * 0.5f,
        1.2f
    ));

    marchingCubes();
}

float MushroomGenerator::evaluateFieldAt(ofVec3f point) const {
    float field = 0;
    float maxInfluence = 0;

    for (const auto& ball : metaballs) {
        float dist = point.distance(ball.position);
        if (dist < ball.radius * 2.0f) {
            float influence = ball.evaluate(point);
            field += influence;
            maxInfluence = std::max(maxInfluence, influence);
        }
    }

    return field;
}

void MushroomGenerator::update() {
    if (metaballs.empty()) return;

    time += ofGetLastFrameTime() * growthSpeed;
    float growthFactor = isGrowing ? ofClamp(time, 0, 1) : 1.0f;

    for (size_t i = 0; i < metaballs.size(); i++) {
        if (i >= originalPositions.size() || i >= originalRadii.size()) {
            ofLogError() << "Index out of range in originalPositions or originalRadii";
            break;
        }

        float wobble = sin(time * 2 + i) * wobbleAmount;
        ofVec3f wobbleOffset(wobble, 0, wobble);

        metaballs[i].position = originalPositions[i] + wobbleOffset;
        float targetRadius = originalRadii[i];

        if (i == 0) {
            targetRadius *= (1.0f + sin(time * 3) * 0.1f * capExpansion);
        }

        metaballs[i].radius = targetRadius * growthFactor;
    }

    marchingCubes();
}

std::vector<MushroomGenerator::Triangle> MushroomGenerator::polygonizeCell(const GridCell& cell, float isolevel) {
    std::vector<Triangle> triangles;
    int cubeindex = 0;

    for (int i = 0; i < 8; i++) {
        if (cell.val[i] > isolevel) cubeindex |= (1 << i);
    }

    if (cubeindex < 0 || cubeindex >= 256) {
        ofLogError() << "cubeindex out of range: " << cubeindex;
        return triangles;
    }

    if (edgeTable[cubeindex] == 0) return triangles;

    ofVec3f vertlist[12];
    ofVec3f normlist[12];

    if (edgeTable[cubeindex] & 1) { vertlist[0] = interpolateVertex(cell.p[0], cell.p[1], cell.val[0], cell.val[1], isolevel); normlist[0] = interpolateNormal(cell.n[0], cell.n[1], cell.val[0], cell.val[1], isolevel); }
    if (edgeTable[cubeindex] & 2) { vertlist[1] = interpolateVertex(cell.p[1], cell.p[2], cell.val[1], cell.val[2], isolevel); normlist[1] = interpolateNormal(cell.n[1], cell.n[2], cell.val[1], cell.val[2], isolevel); }
    if (edgeTable[cubeindex] & 4) { vertlist[2] = interpolateVertex(cell.p[2], cell.p[3], cell.val[2], cell.val[3], isolevel); normlist[2] = interpolateNormal(cell.n[2], cell.n[3], cell.val[2], cell.val[3], isolevel); }
    if (edgeTable[cubeindex] & 8) { vertlist[3] = interpolateVertex(cell.p[3], cell.p[0], cell.val[3], cell.val[0], isolevel); normlist[3] = interpolateNormal(cell.n[3], cell.n[0], cell.val[3], cell.val[0], isolevel); }
    if (edgeTable[cubeindex] & 16) { vertlist[4] = interpolateVertex(cell.p[4], cell.p[5], cell.val[4], cell.val[5], isolevel); normlist[4] = interpolateNormal(cell.n[4], cell.n[5], cell.val[4], cell.val[5], isolevel); }
    if (edgeTable[cubeindex] & 32) { vertlist[5] = interpolateVertex(cell.p[5], cell.p[6], cell.val[5], cell.val[6], isolevel); normlist[5] = interpolateNormal(cell.n[5], cell.n[6], cell.val[5], cell.val[6], isolevel); }
    if (edgeTable[cubeindex] & 64) { vertlist[6] = interpolateVertex(cell.p[6], cell.p[7], cell.val[6], cell.val[7], isolevel); normlist[6] = interpolateNormal(cell.n[6], cell.n[7], cell.val[6], cell.val[7], isolevel); }
    if (edgeTable[cubeindex] & 128) { vertlist[7] = interpolateVertex(cell.p[7], cell.p[4], cell.val[7], cell.val[4], isolevel); normlist[7] = interpolateNormal(cell.n[7], cell.n[4], cell.val[7], cell.val[4], isolevel); }
    if (edgeTable[cubeindex] & 256) { vertlist[8] = interpolateVertex(cell.p[0], cell.p[4], cell.val[0], cell.val[4], isolevel); normlist[8] = interpolateNormal(cell.n[0], cell.n[4], cell.val[0], cell.val[4], isolevel); }
    if (edgeTable[cubeindex] & 512) { vertlist[9] = interpolateVertex(cell.p[1], cell.p[5], cell.val[1], cell.val[5], isolevel); normlist[9] = interpolateNormal(cell.n[1], cell.n[5], cell.val[1], cell.val[5], isolevel); }
    if (edgeTable[cubeindex] & 1024) { vertlist[10] = interpolateVertex(cell.p[2], cell.p[6], cell.val[2], cell.val[6], isolevel); normlist[10] = interpolateNormal(cell.n[2], cell.n[6], cell.val[2], cell.val[6], isolevel); }
    if (edgeTable[cubeindex] & 2048) { vertlist[11] = interpolateVertex(cell.p[3], cell.p[7], cell.val[3], cell.val[7], isolevel); normlist[11] = interpolateNormal(cell.n[3], cell.n[7], cell.val[3], cell.val[7], isolevel); }

    for (int i = 0; triTable[cubeindex][i] != -1; i += 3) {
        if (i + 2 >= 16) break;
        Triangle tri;
        for (int j = 0; j < 3; j++) {
            int vertIndex = triTable[cubeindex][i + j];
            if (vertIndex == -1 || vertIndex >= 12) break;
            tri.p[j] = vertlist[vertIndex];
            tri.n[j] = normlist[vertIndex];
        }
        triangles.push_back(tri);
    }

    return triangles;
}

void MushroomGenerator::marchingCubes() {
    mesh.clear();
    float resolution = 0.3f;
    float threshold = 0.5f;

    ofVec3f minBound = metaballs[0].position - ofVec3f(metaballs[0].radius * 2.0f);
    ofVec3f maxBound = metaballs[0].position + ofVec3f(metaballs[0].radius * 2.0f);

    for (size_t i = 1; i < metaballs.size(); i++) {
        const MetaBall& ball = metaballs[i];
        ofVec3f min = ball.position - ofVec3f(ball.radius * 2.0f);
        ofVec3f max = ball.position + ofVec3f(ball.radius * 2.0f);

        minBound.x = std::min(minBound.x, min.x);
        minBound.y = std::min(minBound.y, min.y);
        minBound.z = std::min(minBound.z, min.z);

        maxBound.x = std::max(maxBound.x, max.x);
        maxBound.y = std::max(maxBound.y, max.y);
        maxBound.z = std::max(maxBound.z, max.z);
    }

    minBound -= ofVec3f(resolution);
    maxBound += ofVec3f(resolution);

    int nx = ceil((maxBound.x - minBound.x) / resolution);
    int ny = ceil((maxBound.y - minBound.y) / resolution);
    int nz = ceil((maxBound.z - minBound.z) / resolution);

    for (int i = 0; i < nx - 1; i++) {
        for (int j = 0; j < ny - 1; j++) {
            for (int k = 0; k < nz - 1; k++) {
                int idx = i + j * nx + k * nx * ny;
                int nextRow = idx + nx;
                int nextSlice = idx + nx * ny;

                if (idx < mesh.getNumVertices() && nextRow < mesh.getNumVertices() && nextSlice < mesh.getNumVertices()) {
                    if (idx + 1 < mesh.getNumVertices()) mesh.addTriangle(idx, idx + 1, nextRow);
                    if (nextRow + 1 < mesh.getNumVertices()) mesh.addTriangle(nextRow, idx + 1, nextRow + 1);
                    if (nextSlice < mesh.getNumVertices()) mesh.addTriangle(idx, nextRow, nextSlice);
                    if (nextSlice + nx < mesh.getNumVertices()) mesh.addTriangle(nextRow, nextSlice + nx, nextSlice);
                }
            }
        }
    }
}

void MushroomGenerator::generateNormals() {
    mesh.clearNormals();

    if (mesh.getNumVertices() == 0) {
        ofLogError() << "Mesh has no vertices in generateNormals";
        return;
    }

    for (const auto& vertex : mesh.getVertices()) {
        ofVec3f normal(0, 0, 0);
        float epsilon = 0.01f;

        float dx = evaluateFieldAt(vertex + ofVec3f(epsilon, 0, 0)) -
            evaluateFieldAt(vertex - ofVec3f(epsilon, 0, 0));
        float dy = evaluateFieldAt(vertex + ofVec3f(0, epsilon, 0)) -
            evaluateFieldAt(vertex - ofVec3f(0, epsilon, 0));
        float dz = evaluateFieldAt(vertex + ofVec3f(0, 0, epsilon)) -
            evaluateFieldAt(vertex - ofVec3f(0, 0, epsilon));

        normal.set(dx, dy, dz);
        normal.normalize();

        mesh.addNormal(normal);
    }
}


ofVec3f MushroomGenerator::interpolateVertex(ofVec3f p1, ofVec3f p2, float valp1, float valp2, float isolevel) {
    if (abs(isolevel - valp1) < 0.00001f) return p1;
    if (abs(isolevel - valp2) < 0.00001f) return p2;
    if (abs(valp1 - valp2) < 0.00001f) return p1;

    float mu = (isolevel - valp1) / (valp2 - valp1);
    return p1 + (p2 - p1) * mu;
}

ofVec3f MushroomGenerator::interpolateNormal(const ofVec3f& n1, const ofVec3f& n2, float valp1, float valp2, float isolevel) {
    float mu = (isolevel - valp1) / (valp2 - valp1);
    return (n1 + (n2 - n1) * mu).normalize();
}











void MushroomGenerator::draw() {
    if (mesh.getNumVertices() == 0) return;

    ofPushMatrix();
    ofPushStyle();

    ofEnableLighting();

    // Set up material
    ofMaterial material;
    material.setAmbientColor(ofColor(50));
    material.setDiffuseColor(ofColor(200));
    material.setSpecularColor(ofColor(255));
    material.setShininess(120);
    material.begin();

    // Add lighting
    ofLight light;
    light.setPosition(200, 200, 200);
    light.enable();

    // Draw mesh
    mesh.draw();

    material.end();
    ofDisableLighting();

    ofPopStyle();
    ofPopMatrix();
}

void MushroomGenerator::drawWireframe() {
    ofPushStyle();
    ofSetColor(255, 255, 255, 50);
    mesh.drawWireframe();
    ofPopStyle();
}

void MushroomGenerator::drawDebug() const {
    for (const auto& ball : metaballs) {
        ofPushStyle();

        // Draw metaball center
        ofSetColor(255, 0, 0);
        ofDrawSphere(ball.position, 0.1f);

        // Draw influence radius
        ofNoFill();
        ofSetColor(255, 255, 0, 100);
        ofDrawSphere(ball.position, ball.radius);

        // Draw axes
        float axisLength = ball.radius * 0.5f;
        ofSetLineWidth(2);

        ofSetColor(255, 0, 0); // X
        ofDrawLine(ball.position, ball.position + ofVec3f(axisLength, 0, 0));

        ofSetColor(0, 255, 0); // Y
        ofDrawLine(ball.position, ball.position + ofVec3f(0, axisLength, 0));

        ofSetColor(0, 0, 255); // Z
        ofDrawLine(ball.position, ball.position + ofVec3f(0, 0, axisLength));

        ofPopStyle();
    }
}