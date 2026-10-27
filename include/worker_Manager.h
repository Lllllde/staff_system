#pragma once
#include<iostream>
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
#include<fstream>
#define FILENAME "empFile.txt"
using namespace std;
class WorkerManager{
public:
    WorkerManager();
    void show_Menu();//菜单
    void ExitSystem();//退出系统
    void Add_Emp();//添加职工
    ~WorkerManager();
    void save();//保存文件
    int get_EmpNum();//统计文件中人数
    void init_Emp();//初始化员工
    void Show_Emp();//显示职工
    void Del_Emp();//删除职工
    int IsExist(int id);/*判断职工是否存在，
        存在则返回职工所在数组中的位置，不存在则返回-1*/
    void Mod_Emp();//修改职工
    void Find_Emp();//查找职工
    void Sort_Emp();//排序职工
    void Clean_File();//清空文件
    void get_Valid_Input(int& dSelect);//校验输入值是否合规(1,2,3)
    void get_Valid_InputV2(int& select);//校验输入值是否合规(1,2)
    
    bool m_FileIsEmpty;//判断文件是否为空
    int m_EmpNum;//职工人数
    worker**m_EmpArray;//职工数组指针
};