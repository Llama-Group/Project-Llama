
//  Copyright © 2016 Project Llama. All rights reserved.
//
//  Licensed under the Apache License,Version 2.0 (the "License");
//  you may not use this file except in compliance with the License.
//  You may obtain a copy of the License at:
//
//  http://www.apache.org/licenses/LICENSE-2.0
//
//  Unless required by applicable law or agreed to in writing,software
//  distributed under the License is distributed on an "AS IS" BASIS,
//  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,either express or implied.
//  See the License for the specific language governing permissions and
//  limitations under the License.
//

#ifndef LLAMA_CPP_SRC_ML_KMEANS_H_
#define LLAMA_CPP_SRC_ML_KMEANS_H_

#include <RNG/MersenneTwister.h>

#include <float.h>
#include <time.h>

#include <algorithm>
#include <functional>
#include <map>
#include <vector>
#include <utility>

namespace alpaca {
namespace ML {
    /**
     *  @brief K-means algorithm
     *
     *  @param k        Number of clusters
     *  @param min_diff Minimum difference
     *  @param data     Data to cluster
     *  @param center   Custom center calcualation
     *  @param distance Custom distance calculation
     */
    template <class _Element>
    std::vector<_Element> kmeans(ssize_t k, double min_diff, const std::vector<_Element>& data,
       const std::function<_Element(const std::vector<std::pair<_Element, uint32_t>>& data)>& center,
       const std::function<double(const _Element& first, const _Element& second)>& distance);

    /**
     *  @brief K-means algorithm
     *
     *  @param k        Number of clusters
     *  @param min_diff Minimum difference
     *  @param data     Data (with count) to cluster
     *  @param center   Custom center calcualation
     *  @param distance Custom distance calculation
     */
    template <class _Element>
    std::vector<_Element> kmeans(ssize_t k, double min_diff, const std::vector<std::pair<_Element,
       uint32_t>>& data,
       const std::function<_Element(
           const std::vector<std::pair<_Element, uint32_t>>& data)>& center,
           const std::function<double(const _Element& first,
           const _Element& second)>& distance);

    template <class _Element>
    std::vector<_Element> kmeans(ssize_t k, double min_diff, const std::vector<_Element>& data,
       const std::function<_Element(const std::vector<std::pair<_Element, uint32_t>>& data)>& center,
       const std::function<double(const _Element& first, const _Element& second)>& distance) {
        using ElementCount  = std::pair<_Element, uint32_t>;
        std::vector<ElementCount> elements;
        std::for_each(data.cbegin(), data.cend(), [&](const _Element& element) {
            elements.emplace_back(element, 1);
        });
        return kmeans<_Element>(k, min_diff, elements, center, distance);
    }

    template <class _Element>
    std::vector<_Element> kmeans(ssize_t k, double min_diff, const std::vector<std::pair<_Element,
       uint32_t>>& data,
       const std::function<_Element(const std::vector<std::pair<_Element, uint32_t>>& data)>& center,
       const std::function<double(const _Element& first, const _Element& second)>& distance) {
        using ElementCount  = std::pair<_Element, uint32_t>;
        using Cluster       = std::vector<_Element>;
        using ClusterPoint  = std::map<uint32_t, std::vector<ElementCount>>;

        Cluster clusters;
        alpaca::RNG::MersenneTwister mt(static_cast<uint32_t>(time(NULL)));
        uint32_t randmax = static_cast<uint32_t>(data.size());

        for (uint32_t i = 0; i < k; i++) {
            auto iter = data.cbegin();
            for (uint32_t t = 0; t < mt.rand() % randmax; t++, iter++) {}
            clusters.emplace_back(iter->first);
        }

        while (1) {
            ClusterPoint points;

            std::for_each(data.cbegin(), data.cend(), [&](const std::pair<_Element, uint32_t>& point) {
                double smallestDistance = DBL_MAX;
                double dis;
                uint32_t smallestIndex;
                for (uint32_t i = 0; i < k; i++) {
                    dis = distance(point.first, clusters[i]);

                    if (dis < smallestDistance) {
                        smallestDistance = dis;
                        smallestIndex = i;
                    }
                }
                points[smallestIndex].emplace_back(point);
            });

            double diff = 0;
            for (uint32_t i = 0; i < k; i++) {
                _Element oldCenter = clusters[i];
                _Element newCenter = center(points[i]);
                clusters[i] = newCenter;
                double dis = distance(oldCenter, newCenter);
                diff = std::max(diff, dis);
            }

            if (diff < min_diff) {
                break;
            }
        }
        return clusters;
    }
}  // namespace ML
}  // namespace alpaca

#endif  // LLAMA_CPP_SRC_ML_KMEANS_H_
