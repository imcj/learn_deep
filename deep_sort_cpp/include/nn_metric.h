#include <Eigen/Dense>
#include "feature.h"
#include "track.h"

typedef struct nn_distance_metric_instance {
    
    float threshold;

    float (*metric)(float* a, float* b);

} nn_distance_metric_instance;

/**
 * create a new instance of a distance metric
*/

nn_distance_metric_instance* nn_distrance_metric_instance_new(float threshold);

double cosine_distance(const Eigen::VectorXf& a, const Eigen::VectorXf& b);

void partial_fit(nn_distance_metric_instance* instance, features the_features, targets the_targets);

float nn_distance(nn_distance_metric_instance* instance, float* a, float* b);

void nn_distance_metric_instance_free(nn_distance_metric_instance* instance);