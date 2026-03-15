#include "TSP.h"
#include <cstdlib>
#include <algorithm>
#include <numeric>

int TSP::neighborhood_type = 0; 

TSP::TSP(size_t n, std::vector<CityCoords> coords) 
    : n_cities(n), cities(std::move(coords)) {
    
    dist_matrix.resize(n_cities, std::vector<double>(n_cities, 0.0));
    for (size_t i = 0; i < n_cities; ++i) {
        for (size_t j = i + 1; j < n_cities; ++j) {
            double d = euclidean_distance(i, j);
            dist_matrix[i][j] = d;
            dist_matrix[j][i] = d;
        }
    }
}

double TSP::euclidean_distance(size_t i, size_t j) const {
    double dx = cities[i].first - cities[j].first;
    double dy = cities[i].second - cities[j].second;
    return std::sqrt(dx * dx + dy * dy);
}

double TSP::calculate_tour_length(const std::vector<int>& tour) const {
    if (tour.size() != n_cities) return 1e18;
    
    double length = 0.0;
    for (size_t i = 0; i < n_cities; ++i) {
        size_t from = tour[i];
        size_t to = tour[(i + 1) % n_cities];
        length += dist_matrix[from][to];
    }
    return length;
}

std::vector<int> TSP::apply_2opt(const std::vector<int>& tour) const {
    std::vector<int> new_tour = tour;
    

    
    size_t i = std::rand() % n_cities, j;
    do {
        j = std::rand() % n_cities;
    } while (j == i);

    if (i > j) std::swap(i, j);
    

    std::reverse(new_tour.begin() + i, new_tour.begin() + j + 1);
    
    return new_tour;
}

std::vector<int> TSP::apply_3opt(const std::vector<int>& tour) const {
    std::vector<int> new_tour;
    
    if (n_cities < 6) {
        return apply_2opt(tour);
    }
    
    size_t a = std::rand() % n_cities;
    size_t b = std::rand() % n_cities;
    size_t c = std::rand() % n_cities;
    
    while (b == a) b = std::rand() % n_cities;
    while (c == a || c == b) c = std::rand() % n_cities;
    
    if (a > b) std::swap(a, b);
    if (b > c) std::swap(b, c);
    if (a > b) std::swap(a, b);
    
    int reconnection = std::rand() % 8;
    
    new_tour.reserve(n_cities);
    
    switch (reconnection) {
        case 0:
            // 2-opt
            new_tour = tour;
            std::reverse(new_tour.begin() + a, new_tour.begin() + b);
            break;
            
        case 1:

            new_tour.insert(new_tour.end(), tour.begin(), tour.begin() + a);          
            new_tour.insert(new_tour.end(), tour.rbegin() + (n_cities - c),  tour.rbegin() + (n_cities - b));             // [b, c) reversed
            new_tour.insert(new_tour.end(), tour.begin() + a, tour.begin() + b);       
            new_tour.insert(new_tour.end(), tour.begin() + c, tour.end());             
            break;
            
        case 2:
            new_tour.insert(new_tour.end(), tour.rbegin() + (n_cities - b),  tour.rbegin() + (n_cities - a));            
            new_tour.insert(new_tour.end(), tour.begin(), tour.begin() + a);          
            new_tour.insert(new_tour.end(), tour.begin() + b, tour.begin() + c);       
            new_tour.insert(new_tour.end(), tour.begin() + c, tour.end());            
            break;
            
        case 3:
            new_tour.insert(new_tour.end(), tour.begin() + a, tour.begin() + b);    
            new_tour.insert(new_tour.end(), tour.begin() + b, tour.begin() + c);       
            new_tour.insert(new_tour.end(), tour.begin(), tour.begin() + a);           
            new_tour.insert(new_tour.end(), tour.begin() + c, tour.end());             
            break;
            
        case 4:
            new_tour.insert(new_tour.end(), tour.begin(), tour.begin() + a);          
            new_tour.insert(new_tour.end(), tour.rbegin() + (n_cities - b), tour.rbegin() + (n_cities - a));           
            new_tour.insert(new_tour.end(), tour.begin() + b, tour.begin() + c);    
            new_tour.insert(new_tour.end(), tour.begin() + c, tour.end());            
            break;
            
        case 5:
        
            new_tour.insert(new_tour.end(), tour.begin(), tour.begin() + a);          
            new_tour.insert(new_tour.end(), tour.begin() + b, tour.begin() + c);      
            new_tour.insert(new_tour.end(), tour.rbegin() + (n_cities - b),  tour.rbegin() + (n_cities - a));            
            new_tour.insert(new_tour.end(), tour.begin() + c, tour.end());           
            break;
            
        case 6:
            new_tour.insert(new_tour.end(), tour.begin() + b, tour.begin() + c); 
            new_tour.insert(new_tour.end(), tour.begin() + a, tour.begin() + b);     
            new_tour.insert(new_tour.end(), tour.begin(), tour.begin() + a);        
            new_tour.insert(new_tour.end(), tour.begin() + c, tour.end());          
            break;
            
        case 7:
            new_tour.insert(new_tour.end(), tour.rbegin() + (n_cities - a), tour.rend()); 
            new_tour.insert(new_tour.end(), tour.begin() + a, tour.begin() + b);   
            new_tour.insert(new_tour.end(), tour.begin() + b, tour.begin() + c);      
            new_tour.insert(new_tour.end(), tour.begin() + c, tour.end());             
            break;
    }

    if (new_tour.size() != n_cities) {
        return apply_2opt(tour); 
    }
    
    return new_tour;
}

std::vector<int> TSP::get_initial_solution(double& value) {
    std::vector<int> tour(n_cities);
    std::iota(tour.begin(), tour.end(), 0);
    
    for (size_t i = n_cities - 1; i > 0; --i) {
        size_t j = std::rand() % (i + 1);
        std::swap(tour[i], tour[j]);
    }
    
    value = -calculate_tour_length(tour);
    return tour;
}

std::vector<int> TSP::neighbour_solution(std::vector<int>& prev_tour, double& value, bool& is_permissible_) {
    std::vector<int> new_tour;
    
    if (TSP::neighborhood_type == 0) {
        new_tour = apply_2opt(prev_tour);
    } else {
        new_tour = apply_3opt(prev_tour);
    }
    
    is_permissible_ = true;
    value = -calculate_tour_length(new_tour);
    
    return new_tour;
}

double TSP::get_value(std::vector<int>& tour) {
    return -calculate_tour_length(tour);
}

bool TSP::is_permissible(std::vector<int>& tour) {
    if (tour.size() != n_cities) return false;
    
    std::vector<bool> visited(n_cities, false);
    for (int city : tour) {
        if (city < 0 || city >= static_cast<int>(n_cities)) return false;
        if (visited[city]) return false;
        visited[city] = true;
    }
    return true;
}