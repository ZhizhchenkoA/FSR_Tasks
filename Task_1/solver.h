#pragma once
#include <iostream>
#include <string>
#include <vector>


class Task {
public:
    Task();
    virtual void load();
    virtual void get_initial_solution();
};


class Solver {

public:
    Solver();
    void solve();
    
};