
#include <vector>
#include <stdlib.h>
#include "detection.h"
#include "track.h"

#define max_iou_distance 0.7
#define max_age 30
#define n_init 3

typedef struct tracker {
    std::vector<track> tracks;

    int next_id;
} tracker;

tracker* tracker_new();

void tracker_predict(tracker* tracker);

void update(tracker* tracker, detections detections);

void tracker_free(tracker* tracker);