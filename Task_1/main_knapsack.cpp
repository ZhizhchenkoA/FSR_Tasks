#include <iostream>
#include <ctime>
#include "solver.h"
#include "knapsack.h"

int main() {
    int N;
    double max_weight;
    std::cin >> N >> max_weight;

    srand(time(0));
    std::vector<KnapsackItems> items(N);
    for (size_t i = 0; i < N; i++)
        std::cin >> items[i].second >> items[i].first ;
    Knapsack knapsack_problem(N, max_weight, items);

    std::vector<int> ans(N);
    double value = 0;
    Solver solver_knapsack(&knapsack_problem);
    ans = solver_knapsack.solve_multiple(value);
    std::cout << value << std::endl;
    for (size_t i = 0; i < N; i++)
        std::cout << ans[i] << " ";
    std::cout << std::endl;
    return 0;
}