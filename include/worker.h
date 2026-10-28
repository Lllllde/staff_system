#pragma once
#include<iostream>
#include<string>

class worker
{
public:
    virtual void showInfo() = 0;
    virtual std::string getDeptName() = 0;
    virtual ~worker()=default;
    int m_Id=0;//职工编号
    std::string m_Name;//职工姓名
    int m_DeptId=0;//职工部门编号

};