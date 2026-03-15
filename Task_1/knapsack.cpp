#include "knapsack.h"

bool Knapsack::use_three_neighbournood = false;

std::vector<int> Knapsack::get_initial_solution(double &value)
{
    std::vector<int> indices(size);

    std::iota(indices.begin(), indices.end(), 0);
    
    for (size_t i = size - 1; i > 0; --i) {
        size_t j = std::rand() % (i + 1);
        std::swap(indices[i], indices[j]);
    }

    std::vector<int> solution(size, 0);
    double weight = 0;
    value = 0;

    for (size_t k = 0; k < size; ++k) {
        size_t idx = indices[k];
        double w = items[idx].first;
        double v = items[idx].second;
        
        if (weight + w <= max_weight) {
            weight += w;
            value += v;
            solution[idx] = 1;
        }
    }
    return solution;
}

std::vector<int> Knapsack::neighbour_solution(std::vector<int>& prev_solution, double &value, bool &is_permissible_)
{
    std::vector<int> new_solution = prev_solution;
    
    std::vector<int> inside, outside;
    for (size_t i = 0; i < size; ++i) {
        if (prev_solution[i] == 1) inside.push_back(i);
        else outside.push_back(i);
    }
    
    if (!outside.empty() && rand() % 2 == 0) {
        int idx = outside[rand() % outside.size()];
        if (get_value(prev_solution) + items[idx].second >= value) { 
            new_solution[idx] = 1;
            if (is_permissible(new_solution)) {
                value = get_value(new_solution);
                is_permissible_ = true;
                return new_solution;
            }
        }
    }
    
    if (!inside.empty()) {
        int idx = inside[rand() % inside.size()];
        new_solution[idx] = 0;
        value = get_value(new_solution);
        is_permissible_ = true; 
        return new_solution;
    }
    
    is_permissible_ = true;
    value = get_value(prev_solution);
    return prev_solution;
}

double Knapsack::get_value(std::vector<int>& sol)
{
    double ans = 0.0f;
    for (size_t i = 0; i < items.size(); i++){
        if (sol[i] == 1)
            ans += items[i].second;
    }
    return ans;
}

bool Knapsack::is_permissible(std::vector<int>& sol)
{
    double weight = 0.0f;
    for (size_t i = 0; i < items.size(); i++){
        if (sol[i] == 1)
            weight += items[i].first;
    }
    return weight <= this->max_weight;
}
