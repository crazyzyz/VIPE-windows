/**
 * This file includes code originally from the DROID-SLAM repository:
 * https://github.com/princeton-vl/DROID-SLAM
 * Licensed under the BSD-3 License. See THIRD_PARTY_LICENSES.md for details.
 */

#include <torch/extension.h>
#include <vector>

namespace slam_ext {

torch::Tensor depth_filter_cuda(torch::Tensor poses, torch::Tensor disps, torch::Tensor intrinsics, torch::Tensor ix,
                                torch::Tensor thresh);

torch::Tensor frame_distance_cuda(torch::Tensor poses, torch::Tensor disps, torch::Tensor intrinsics, torch::Tensor pi,
                                  torch::Tensor pj, torch::Tensor qi, torch::Tensor qj, torch::Tensor di,
                                  const float beta);

std::vector<torch::Tensor> projmap_cuda(torch::Tensor poses, torch::Tensor disps, torch::Tensor intrinsics,
                                        torch::Tensor ii, torch::Tensor jj);

torch::Tensor iproj_cuda(torch::Tensor poses, torch::Tensor disps, torch::Tensor intrinsics);

std::vector<torch::Tensor> ba_cuda(torch::Tensor poses, torch::Tensor disps, torch::Tensor intrinsics,
                                   torch::Tensor disps_sens, torch::Tensor targets, torch::Tensor weights,
                                   torch::Tensor eta, torch::Tensor ii, torch::Tensor jj, const int t0, const int t1,
                                   const int iterations, const float lm, const float ep, const bool motion_only);

}  // namespace slam_ext

void pybind_slam_ext(py::module &m) {
    m.def("ba", &slam_ext::ba_cuda, "bundle adjustment");
    m.def("frame_distance", &slam_ext::frame_distance_cuda, "frame_distance");
    m.def("projmap", &slam_ext::projmap_cuda, "projmap");
    m.def("depth_filter", &slam_ext::depth_filter_cuda, "depth_filter");
    m.def("iproj", &slam_ext::iproj_cuda, "back projection");
}
