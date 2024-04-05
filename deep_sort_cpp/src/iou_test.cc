#include <iostream>
#include <cassert>
#include <cmath>
#include "iou.h"
#include "nn_metric.h"

void test_calculate_intersection_width_height() {

    // Define a bounding box
    Eigen::Vector4f bbox(1.0, 1.0, 3.0, 3.0);
    

    // Define a set of candidate bounding boxes
    Eigen::MatrixXf candidates(2, 4);
    candidates << 0.0, 0.0, 2.0, 2.0,
                  2.0, 2.0, 4.0, 4.0;

    // Call the function to test
    Eigen::MatrixXf result = calculate_intersection_width_height(bbox, candidates);

    // Define the expected result
    Eigen::MatrixXf expected_result(2, 2);
    expected_result << 1.0, 1.0,
                       2.0, 2.0;

    // Assert that the result is as expected
    if ((result - expected_result).norm() > 1e-6) {
        std::cerr << "Test failed: result is not as expected." << std::endl;
        return ;
    }

    std::cout << "Test calculate_intersection_width_height() passed: result is as expected." << std::endl;
}

void test_iou() {
    // Define a bounding box
    Eigen::Vector4f bbox(1.0, 1.0, 3.0, 3.0);
    

    // Define a set of candidate bounding boxes
    Eigen::MatrixXf candidates(2, 4);
    candidates << 0.0, 0.0, 2.0, 2.0,
                  2.0, 2.0, 4.0, 4.0;

    // Call the function to test
    Eigen::VectorXf iou_results = iou(bbox, candidates);


    assert(iou_results.size() == 2);
    char buffer[9];
    sprintf(buffer, "%.7f", iou_results[0]);
    assert(strcmp(buffer, "0.0833333") == 0);

}

void test_iou_cost() {
    // Define a set of cost tracking objects

    Eigen::Vector4f bbox(1.0, 1.0, 3.0, 3.0);
    Eigen::Vector4f bbox2(1.0, 1.0, 3.0, 3.0);
    Eigen::MatrixXf candidates(2, 4);
    candidates << 0.0, 0.0, 2.0, 2.0,
                  2.0, 2.0, 4.0, 4.0;

    std::vector<cost_tracking*> cost_trackings;
    cost_tracking* ct1 = (cost_tracking *)malloc(sizeof(cost_tracking));
    ct1->bbox = bbox;
    ct1->infiy_coast = true;
    cost_trackings.push_back(ct1);

    cost_tracking* ct2 = (cost_tracking *)malloc(sizeof(cost_tracking));
    ct2->bbox = bbox2;
    cost_trackings.push_back(ct2);

    // // Define a set of track indices
    std::vector<int> track_indices;
    track_indices.push_back(0);
    track_indices.push_back(1);

    // // Define a set of candidate indices
    std::vector<int> candidate_indices;
    candidate_indices.push_back(0);
    candidate_indices.push_back(1);

    // // Define a set of candidate bounding boxes
    // Eigen::MatrixXf candidates(2, 4);
    // candidates << 0.0, 0.0, 2.0, 2.0,
    //               2.0, 2.0, 4.0, 4.0;

    // // Call the function to test
    Eigen::MatrixXf iou_cost_results = iou_cost(cost_trackings, candidates, track_indices, candidate_indices);

    // // Define the expected result
    Eigen::MatrixXf expected_result(2, 2);
    expected_result << 0.0833333, 0.0833333,
                       0.0833333, 0.0833333;

    Eigen::Vector2f expected_inifity(1e+5, 1e+5);
    Eigen::VectorXf result_inifity2 = iou_cost_results.row(0);
    std::cout << "Expected infinity: " << expected_inifity << std::endl;
    std::cout << "Result infinity: " << result_inifity2 << std::endl;
    bool isSame = expected_inifity.isApprox(result_inifity2);
    if (isSame) {
        std::cout << "Test iou_cost() passed: result is as expected." << std::endl;
    }

    std::cout << "Result " << iou_cost_results << std::endl;
    // // Assert that the result is as expected
    if ((iou_cost_results - expected_result).norm() > 1e-6) {
        std::cerr << "Test failed: result is not as expected." << std::endl;
        return ;
    }

    

    std::cout << "Test iou_cost() passed: result is as expected." << std::endl;
}


void test_nn_distance_metric() {
    // Define a set of cost tracking objects

    // 定义两个向量
    Eigen::VectorXf vector1(3);
    vector1 << 1, 2, 3;

    Eigen::VectorXf vector2(3);
    vector2 << 4, 5, 6;

    float result = cosine_distance(vector1, vector2);

    assert(result == 0.0);

}

void test_nn_metric() {
    // nn_distance_metric_instance* instance = nn_distrance_metric_instance_new(0.0);
    // float a[2] = {1.0, 2.0};
    // float b[2] = {3.0, 4.0};
    // float result = nn_distance(instance, a, b);
    // std::cout << "Result: " << result << std::endl;
    // assert(result == 0.0);
    // nn_distance_metric_instance_free(instance);

    // test_nn_distance_metric();
}


int main() {

    // test_calculate_intersection_width_height();

    // test_iou();

    // Eigen::Vector4f bbox(1.0, 1.0, 3.0, 3.0);
    // std::cout << "bbox: " << bbox.transpose() << std::endl;

    // test_iou_cost();

    // test_nn_metric();

    return 0;
}