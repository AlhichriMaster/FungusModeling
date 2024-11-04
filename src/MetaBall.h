// src/MetaBall.h
#pragma once
#include "ofMain.h"

class MetaBall {
public:
    ofVec3f position;
    float radius;
    float strength;

    MetaBall(ofVec3f pos, float r, float s) : position(pos), radius(r), strength(s) {}

    float evaluate(ofVec3f point) const {
        float dist = position.distance(point);
        return strength * radius * radius / (dist * dist + 0.000001);
    }
};