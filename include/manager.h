#pragma once
#include<iostream>
#include "worker.h"

class manager : public worker
{
public:
    manager(int id, std::string name, int dId);
    virtual void showInfo();
    virtual std::string getDeptName();
};