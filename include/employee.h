#pragma once
#include<iostream>
#include "worker.h"

class employee : public worker
{
public:
    employee(int id, std::string name, int dId);
    virtual void showInfo();
    virtual std::string getDeptName();
};