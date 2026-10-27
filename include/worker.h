#pragma once
#include<iostream>
using namespace std;
#include<string>

class worker
{

public:
    virtual void showInfo() = 0;
    virtual string getDeptName() = 0;
    int m_Id;//职工编号
    string m_Name;//职工姓名
    int m_DeptId;//职工部门编号

};