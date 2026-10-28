#pragma once
#include<iostream>
#include "worker.h"

class boss : public worker
{
public:
    boss(int id, std::string name, int dId);
    virtual void showInfo();
    virtual std::string getDeptName();
};