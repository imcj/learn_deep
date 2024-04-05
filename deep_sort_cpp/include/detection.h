#include <vector>
#include "feature.h"

typedef struct detection {
    float x;

    float y;

    float w;

    float h;

    float confidence;

    feature theFeature;

} detection;

typedef std::vector<detection> detections;