#include "nn_metric.h"
#include <iostream>

float nn_distance_metric(float* a, float* b) {
    return 0.0;
}

nn_distance_metric_instance* nn_distrance_metric_instance_new(float threshold) {
    nn_distance_metric_instance* instance = (nn_distance_metric_instance*)malloc(sizeof(nn_distance_metric_instance));
    instance->threshold = threshold;
    instance->metric = nn_distance_metric;
    return instance;
}

void nn_distance_metric_instance_free(nn_distance_metric_instance* instance) {
    free(instance);
}

float nn_distance_metric_distance(nn_distance_metric_instance* instance, float* a, float* b) {
    std::cout << "hello" << std::endl;
    return instance->metric(a, b);
}

float nn_distance(nn_distance_metric_instance* instance, float* a, float* b) {
    return nn_distance_metric_distance(instance, a, b);
}

double cosine_distance(const Eigen::VectorXf& a, const Eigen::VectorXf& b) {
    double dot_product = a.dot(b);

    double norm_A = a.norm();
    double norm_B = b.norm();
    double similarity = dot_product / (norm_A * norm_B);

    std::cout << "Similarity: " << similarity << std::endl;

    return 1 - similarity;
}