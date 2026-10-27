#include "boss.h"

boss::boss(int id, string name, int dId)
{
    this->m_Id = id;
    this->m_Name = name;
    this->m_DeptId = dId;
};
void boss::showInfo(){
    cout<<"职工编号 "<<this->m_Id
    <<"\t姓名 "<<this->m_Name
    <<"\t部门 "<<this->getDeptName()
    <<"\t职责:干大活"<<endl;
}
string boss::getDeptName(){
    return string ("老板");
}