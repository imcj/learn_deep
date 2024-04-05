#include "iou.h"
#include <iostream>

Eigen::MatrixXf calculate_intersection_width_height(Eigen::Vector4f bbox, Eigen::MatrixXf candidates) {
    Eigen::Vector2f top_left = bbox.head(2);
    Eigen::Vector2f bottom_right = top_left + bbox.tail(2);

    Eigen::MatrixXf candicates_top_left = candidates.leftCols(2);
    Eigen::MatrixXf candicates_bottom_right = candicates_top_left + candidates.rightCols(2);

    // std::cout << "top_left: "  << std::endl << top_left << std::endl;
    // std::cout << "bottom_right: "  << std::endl << bottom_right << std::endl;
    // std::cout << "candicates_top_left: "  << std::endl << candicates_top_left << std::endl;
    // std::cout << "candicates_bottom_right: "  << std::endl << candicates_bottom_right << std::endl;


    Eigen::MatrixXf top_left_intersection = top_left.transpose().replicate(candicates_top_left.rows(), 1).cwiseMax(candicates_top_left);
    Eigen::MatrixXf bottom_right_intersection = bottom_right.transpose().replicate(candicates_bottom_right.rows(), 1).cwiseMin(candicates_bottom_right);

    // std::cout << "top_left_intersection: "  << std::endl << top_left_intersection << std::endl;
    // std::cout << "bottom_right_intersection: " << std::endl << bottom_right_intersection << std::endl;


    Eigen::MatrixXf intersection_width_height = (bottom_right_intersection - top_left_intersection).cwiseMax(0);
    // std::cout << "intersection_width_height: " << std::endl << intersection_width_height << std::endl;

    return intersection_width_height;
}

/**
 * @brief Calculate the width and height of the intersection of a bounding box with a set of candidates.
 * 
 * calculate_area_intersection: [[1, 1], [2, 2]]
 * 
 * return: [1, 4]
 * 
 * @param calculate_area_intersection A Nx2 matrix where each row contains the width and height of the intersection of the bbox with the corresponding candidate.
 * @return Returns a vector of length N containing the area of the intersection of the bbox with each candidate.
 *
*/
inline Eigen::VectorXf calculate_area_intersection(Eigen::MatrixXf intersection_width_height) {
    return intersection_width_height.rowwise().prod();
}

Eigen::VectorXf iou(Eigen::Vector4f bbox, Eigen::MatrixXf candidates) {

    // Calculate the width and height of the intersection of the bbox with all candidates
    // [[1, 1], [2, 2]] is the intersection of bbox with candidates
    Eigen::MatrixXf intersection_width_height = calculate_intersection_width_height(bbox, candidates);
    
    // Calculate the area of the intersection, the area of the candidates, and the area of the bbox
    // [1, 4] is the area of the intersection
    Eigen::VectorXf area_intersection = calculate_area_intersection(intersection_width_height);

    // [4， 16] is the area of the candidates
    // input: candidates: [[0, 0, 2, 2], [2, 2, 4, 4]]
    // rightCols(2) is the width and height of the candidates, pick the last 2 columns
    // rowwise().prod() is the area of the candidates
    Eigen::VectorXf area_candidates = candidates.rightCols(2).rowwise().prod();

    // [9, 9] is the area of the bbox
    // bbox.tail(2) is the width and height of the bbox, [3, 3] is the width and height of the bbox, 9 is the area of the bbox
    // input: bbox: [1, 1, 3, 3]
    Eigen::VectorXf area_bbox = Eigen::VectorXf::Constant(area_candidates.size(), bbox.tail(2).prod());

    // std::cout << "area_intersection: " << area_intersection.transpose() << std::endl;
    // std::cout << "area bbox:" << area_bbox.transpose() << std::endl;
    // std::cout << "area_candidates:" << area_candidates.transpose() << std::endl;
    // std::cout << "add area_condidates and bbox:" << (area_bbox + area_candidates).transpose() << std::endl;
    // std::cout << "substrct : " << (area_bbox + area_candidates - area_intersection).transpose() << std::endl;

    // this is the formula of iou, area_intersection / (area_bbox + area_candidates - area_intersection)
    Eigen::VectorXf iou = area_intersection.cwiseQuotient(
        (area_bbox + area_candidates - area_intersection)
    );

    // iou [0.0833333, 0.0833333]

    // std::cout << "iou: " << iou.transpose() << std::endl;
    return iou;
}


Eigen::MatrixXf iou_cost(std::vector<cost_tracking*> cost_trackings, Eigen::MatrixXf candidates, std::vector<int> track_indices, std::vector<int> candidate_indices) {
    Eigen::MatrixXf iou_cost_matrix(cost_trackings.size(), candidates.rows());
    for (int i = 0; i < track_indices.size(); i++) {
        int track_index = track_indices[i];
        cost_tracking* cost_tracking = cost_trackings[track_index];

        if (cost_tracking->infiy_coast) {
            iou_cost_matrix.row(i).setConstant(1e+5);
            continue;
        }

        Eigen::VectorXf results = iou(cost_tracking->bbox, candidates);
        std::cout << "results: " << results.transpose() << std::endl;

        iou_cost_matrix.row(i) = 1.0 - results.transpose().array();
    }
    return iou_cost_matrix;
}