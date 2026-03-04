#pragma once
#include <iostream>
#include <string>


class Task {
public:
    Task();
    Task(std::string);
    void load(const std::string);
};

class Knapsack : public Task {

};

class TSP : public Task {

};

class Solver {

public:
    Solver();
    void solve();
    
};