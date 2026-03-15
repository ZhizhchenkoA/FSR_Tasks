#include <iostream>
#include <ctime>
#include "solver.h"
#include "TSP.h"

int main() {
    int N;
    std::cin >> N;

    std::srand(time(0));

    std::vector<CityCoords> cities(N);
    for (int i = 0; i < N; ++i) {
        std::cin >> cities[i].first >> cities[i].second;
    }

    TSP::neighborhood_type = 0; 

    TSP tsp_problem(N, cities);
    Solver solver_tsp(&tsp_problem);

    double value = 0;
    std::vector<int> tour = solver_tsp.solve_multiple(value, 10);

    std::cout << -value << std::endl;

    for (size_t i = 0; i < tour.size(); ++i) {
        std::cout << tour[i] << " ";
    }
    std::cout << std::endl;

    return 0;
}