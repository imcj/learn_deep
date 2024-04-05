#include <Eigen/Dense>
#include <vector>

typedef struct cost_tracking {

    Eigen::Vector4f bbox;

    bool infiy_coast;

} cost_tracking;

/**
 * Calculate the width and height of the intersection of a bounding box with a set of candidates.
 * 
 * @param bbox A bounding box represented as a 4D vector (x, y, width, height).
 * @param candidates A set of candidate bounding boxes represented as a Nx4 matrix.
 * 
 * @return Returns a Nx2 matrix where each row contains the width and height of the intersection of the bbox with the corresponding candidate.
 * 
 * Example:
 * bbox: [1, 1, 3, 3]
 * candidates: [[0, 0, 2, 2], [2, 2, 4, 4]]
 * return: [[1, 1], [2, 2]]
 * 
 * [1, 1] is the width and height of the intersection of bbox with the first candidate.
 * [2, 2] is the width and height of the intersection of bbox with the second candidate.
 */
Eigen::MatrixXf calculate_intersection_width_height(Eigen::Vector4f bbox, Eigen::MatrixXf candidates);

/**
 * Calculate the intersection over union of a bounding box with a set of candidates.
 * 
 * @param bbox A bounding box represented as a 4D vector (x, y, width, height).
 * @param candidates A set of candidate bounding boxes represented as a Nx4 matrix.
 * 
 * @return Returns a vector of length N containing the intersection over union of the bbox with each candidate.
 * The intersection over union is defined as the area of the intersection divided by the area of the union
 * of the bounding box and the candidate.
 * 
 * Example:
 * bbox: [1, 1, 3, 3]
 * candidates: [[0, 0, 2, 2], [2, 2, 4, 4]]
 * return: [0.0833333, 0.0833333]
 */
Eigen::VectorXf iou(Eigen::Vector4f bbox, Eigen::MatrixXf candidates);


Eigen::MatrixXf iou_cost(std::vector<cost_tracking*> cost_trackings, Eigen::MatrixXf candidates, std::vector<int> track_indices, std::vector<int> candidate_indices);

