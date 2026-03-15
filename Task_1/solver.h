#pragma once
#include <iostream>
#include <string>
#include <vector>
#define MAX_ITERS 10000

class Task {
public:
    virtual ~Task() = default; 
    
    virtual std::vector<int> get_initial_solution(double&) = 0;
    virtual std::vector<int> neighbour_solution(std::vector<int>&, double&, bool&) = 0;
    virtual double get_value(std::vector<int>&) = 0;
    virtual bool is_permissible(std::vector<int>&) = 0;
};

class Solver {
    Task* task;
public:
    Solver(Task* task_) : task(task_) {};
    std::vector<int> solve(double& ans);
    std::vector<int> solve_multiple(double& ans, int N = 100);
};