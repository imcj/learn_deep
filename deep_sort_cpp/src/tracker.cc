#include "tracker.h"

tracker* tracker_new() {
    tracker* t = (tracker*)malloc(sizeof(tracker));
    t->next_id = 1;
    return t;
}

void tracker_predict(tracker* tracker) {
    for (int i = 0; i < tracker->tracks.size(); i++) {
        track* t = &tracker->tracks[i];
        // t->predict();
    }
}

void update(tracker* tracker, detections detections) {

}

void tracker_free(tracker* tracker) {
    free(tracker);
}