#include "employee.h"
using namespace std;

employee::employee(int id, string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
};
void employee::showInfo(){
    cout<<"职工编号 "<<this->m_Id
    <<"\t姓名 "<<this->m_Name
    <<"\t部门 "<<this->getDeptName()
    <<"\t职责:干小活"<<endl;
}
string employee::getDeptName(){
    return string ("员工");
}