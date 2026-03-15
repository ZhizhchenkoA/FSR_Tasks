#pragma once
#include "solver.h"
#include <vector>
#include <utility>
#include <cmath>

using CityCoords = std::pair<double, double>; // {x, y}

class TSP : public Task {
    size_t n_cities;
    std::vector<CityCoords> cities;
    
    std::vector<std::vector<double>> dist_matrix;
    
  
    
    double euclidean_distance(size_t i, size_t j) const;
    double calculate_tour_length(const std::vector<int>& tour) const;
    std::vector<int> apply_2opt(const std::vector<int>& tour) const;
    std::vector<int> apply_3opt(const std::vector<int>& tour) const;
    
public:
      static int neighborhood_type; // 0 = 2-opt, 1 = 3-opt
    TSP(size_t n, std::vector<CityCoords> coords);
    
    virtual std::vector<int> get_initial_solution(double&) override;
    virtual std::vector<int> neighbour_solution(std::vector<int>&, double&, bool&) override;
    virtual double get_value(std::vector<int>&) override;
    virtual bool is_permissible(std::vector<int>&) override;
    
    
};