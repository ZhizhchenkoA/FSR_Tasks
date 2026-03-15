#include "solver.h"

std::vector<int> Solver::solve(double& ans)
{
    double best_value;
    std::vector<int> solution = task->get_initial_solution(best_value);

    std::vector<int> new_solution;
    int n = 0;
    bool is_permissible;
    double new_value;
    while (n < MAX_ITERS) {
        new_solution = task->neighbour_solution(solution, new_value, is_permissible);
        if (is_permissible && new_value > best_value){
            solution = new_solution;
            best_value = new_value;
            n = 0;
        }else {
            n++;
        }

    }
    ans = best_value;
    return solution;
}

std::vector<int> Solver::solve_multiple(double& ans, int N)
{
    ans = 0.0f;
    std::vector<int> solution = this->solve(ans);
    for (int i = 0; i < N; i++){
        double new_ans = 0;
        std::vector<int> new_solution = this->solve(new_ans);
        if (new_ans >= ans){
            ans = new_ans;
            solution = new_solution;
        }
    }
    return solution;
}
