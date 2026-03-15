#pragma once
#include "solver.h"
#include <vector>
#include <utility>
#include <random>
#include <algorithm>

using KnapsackItems = std::pair<double, double>; // {weight, value}

class Knapsack : public Task {
    size_t size;
    double max_weight;
    std::vector<KnapsackItems> items;


    double sum_weight;
    double sum_value;
    static bool use_three_neighbournood;
public:
    Knapsack(size_t size_, double max_weight_, std::vector<KnapsackItems> items_) : 
                                            size(size_), max_weight(max_weight_), items(items_) {};
    virtual std::vector<int> get_initial_solution(double&) override;
    virtual std::vector<int> neighbour_solution(std::vector<int>&, double&, bool&) override;

    virtual double get_value(std::vector<int>&) override;
    virtual bool is_permissible(std::vector<int>&) override;
};

