#include "manager.h"
using namespace std;

manager::manager(int id, string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
};
void manager::showInfo(){
    cout<<"职工编号 "<<this->m_Id
    <<"\t姓名 "<<this->m_Name
    <<"\t部门 "<<this->getDeptName()
    <<"\t职责:干活"<<endl;
}
string manager::getDeptName(){
    return string ("经理");
}