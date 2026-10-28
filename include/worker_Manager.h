#pragma once
#include<iostream>
#include<fstream>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<memory>
#include<vector>

class WorkerManager{
public:
    WorkerManager();
    ~WorkerManager() = default;//交给vector来管

    void show_Menu();//菜单
    void ExitSystem();//退出系统
    void Add_Emp();//添加职工
    void save();//保存文件
    void init_Emp(std::ifstream& ifs);//初始化员工
    void Show_Emp();//显示职工
    void Del_Emp();//删除职工
    int IsExist(int id);/*判断职工是否存在，
        存在则返回职工所在数组中的位置，不存在则返回-1*/
    bool running()const {
        return m_running;
    }
    void Mod_Emp();//修改职工
    void Find_Emp();//查找职工
    void Sort_Emp();//排序职工
    void Clean_File();//清空文件
    void get_Valid_Input(int& dSelect);//校验输入值是否合规(1,2,3)
    void get_Valid_InputV2(int& select);//校验输入值是否合规(1,2)
    void pause_and_clear();
    static constexpr const char* kFileName = "empFile.txt";//比#define的方式更安全

private:
    std::vector<std::unique_ptr<worker>> m_EmpArray;//存放职工的容器
    bool m_running = true;
};