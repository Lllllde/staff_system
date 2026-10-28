#include "worker_Manager.h"
#include<algorithm>
#include<limits>
#include<cstdlib>
using namespace std;
WorkerManager::WorkerManager(){//构造函数
    std::ifstream ifs(kFileName);
    if(!ifs.is_open()){
        std::cout<<"文件不存在"<<std::endl;
        return;
    }
    init_Emp(ifs);
}
void WorkerManager::show_Menu(){//展示菜单函数
    cout << "*******************************" << endl;
cout << "********  欢迎使用职工管理系统！  ********" << endl;
cout << "***********  0.退出管理程序  ***********" << endl;
cout << "***********  1.增加职工信息  ***********" << endl;
cout << "***********  2.显示职工信息  ***********" << endl;
cout << "***********  3.删除离职职工  ***********" << endl;
cout << "***********  4.修改职工信息  ***********" << endl;
cout << "***********  5.查找职工信息  ***********" << endl;
cout << "***********  6.按照编号排序  ***********" << endl;
cout << "***********  7.清空所有文档  ***********" << endl;
    cout << "*******************************" << endl;
cout << endl; // 最后留个空行，或者用 cout << endl;
}

void WorkerManager::ExitSystem(){//退出系统函数
    m_running = false;
}

void WorkerManager::pause_and_clear(){
    std::cout<<"按回车键继续..."<<std::flush;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
    std::cin.get();
    std::system("cls");
}

void WorkerManager::Add_Emp(){//添加职工函数
    std::cout<<"添加的职工数？ "<<std::endl;
    int addnum = 0;//新增人数
    while (!(cin >> addnum)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n');
        std::cout << "输入有误，请输入数字！" << std::endl;
    }
    for(int i=0; i<addnum; i++){
        int id,dSelect;
        std::string name;//部门选择
        std::cout<<"第"<<i+1<<"名新职工的编号？"<<std::endl;
        std::cin>>id;
        std::cout<<"第"<<i+1<<"名新职工的姓名？"<<std::endl;
        std::cin>>name;
        std::cout<<"第"<<i+1<<"名新职工的部门？"<<std::endl;
        std::cout<<"1.employee   2.manager   3.boss"<<std::endl;

        get_Valid_Input(dSelect);//校验输入值
        switch (dSelect)
        {
            case 1:
                m_EmpArray.push_back(std::make_unique<employee>(id,name,1));
                break;
            case 2:
                m_EmpArray.push_back(std::make_unique<manager>(id,name,2));
                break;
            case 3:
                m_EmpArray.push_back(std::make_unique<boss>(id,name,3));
                break;
            default:
                break;
        }
    }
    save();   
    pause_and_clear();
}

void WorkerManager::save(){//保存函数
    std::ofstream ofs(kFileName,std::ios::out);
    for(const auto&p:m_EmpArray){
        ofs<<p->m_Id<<" "<<p->m_Name<<" "<<p->m_DeptId<<"\n";
    }
}

void WorkerManager::init_Emp(std::ifstream& ifs){//初始化员工
    int id,dId;
    std::string name;
    while(ifs>>id>>name>>dId){
        switch(dId){
            case 1:
                m_EmpArray.push_back(std::make_unique<employee>(id,name,dId));
                break;
            case 2:
                m_EmpArray.push_back(std::make_unique<manager>(id,name,dId));
                break;
            case 3:
                m_EmpArray.push_back(std::make_unique<boss>(id,name,dId));
                break;
            default:std::cout<<"部门编号非法，跳过 id="<<id<<std::endl;
        }
    }
}

void WorkerManager::Show_Emp(){//显示职工
    if(m_EmpArray.empty()){//判断文件是否为空
        std::cout<<"记录为空"<<std::endl;
    }
    else{
        for(const auto& p:m_EmpArray){
            p->showInfo();
        }
    }
    pause_and_clear();
}

void WorkerManager::Del_Emp()//删除职工
{
    if(m_EmpArray.empty()){
        cout<<"文件不存在或记录为空"<<endl;
    }
    else{
        cout<<"要删除的职工编号是？"<<endl;
        int id=0;
        std::cin>>id;
        
        int index=IsExist(id);
        if(index!=-1){//说明职工存在
            m_EmpArray.erase(m_EmpArray.begin()+index);
            this->save();
            std::cout<<"删除成功"<<std::endl;
        }
        else{
            cout<<"未找到该职工，删除失败"<<endl;
        }
    }
    pause_and_clear();
}

int WorkerManager::IsExist(int id){//判断职工是否存在，存在则返回职工所在数组中的位置，不存在则返回-1//
    for(std::size_t i=0; i<this->m_EmpArray.size(); i++){
        if(m_EmpArray[i]->m_Id== id){//找到职工
            return static_cast<int>(i); 
        }
    }
    return -1;//返回职工编号
}

void WorkerManager::Mod_Emp()//修改职工
{
    if(m_EmpArray.empty()){
        cout<<"文件不存在或文件为空"<<endl;
    }
    else{
        int id;
        cout<<"要修改的职工编号？"<<endl;
        cin>>id;
        int ret = this->IsExist(id);
        if(ret!=-1){
            int newId=0;
            string newName=" ";
            int dSelect = 0;
            cout<<"查找到"<<id<<"号职工，请输入新职工号"<<endl;
            cin>>newId;
            cout<<"请输入新姓名"<<endl;
            cin>>newName;
            cout<<"请输入新部门"<<endl;
            cout<<"1.employee   2.manager   3.boss"<<endl;
            get_Valid_Input(dSelect);//校验输入值
            std::unique_ptr<worker>p;
            switch(dSelect){
                case 1:
                    p = std::make_unique<employee>(newId,newName,dSelect);
                    break;
                case 2:
                    p = std::make_unique<manager>(newId,newName,dSelect);
                    break;
                case 3:
                    p = std::make_unique<boss>(newId,newName,dSelect);
                    break;
                default:
                    break;
            }
            m_EmpArray[ret] = std::move(p);
            cout<<"修改成功"<<endl;
            this->save();
        }
        else{
            cout<<"查无此人，修改失败"<<endl;
        }
    }
    pause_and_clear();
}

void WorkerManager::Find_Emp()//查找职工
{
    if(m_EmpArray.empty()){
        cout<<"文件不存在或文件为空"<<endl;
    }
    else{
        cout<<"请输入查找方式"<<endl;
        cout<<"1.编号"<<endl;
        cout<<"2.姓名"<<endl;
        int select = 0;
        get_Valid_InputV2(select);
        if(select==1){//编号查找
            int id=0;
            cout<<"编号为？"<<endl;
            cin>>id;
            int ret=this->IsExist(id);
            if(ret!=-1){
                cout<<"查找成功，信息如下"<<endl;
                this->m_EmpArray[ret]->showInfo();
            }
            else{
                cout<<"查无此人"<<endl;
            }
        }
        else if(select==2){//姓名查找
            string name=" ";
            cout<<"姓名为？"<<endl;
            cin>>name;
            bool flag=false;
            for(std::size_t i=0; i<m_EmpArray.size(); i++){
                if(this->m_EmpArray[i]->m_Name==name){
                    std::cout<<"查找成功，职工编号为"<<
                    m_EmpArray[i]->m_Id<<"的职工信息如下"<<std::endl;
                    m_EmpArray[i]->showInfo();
                    flag = true;//修改flag值
                }
            }
            if(flag==false){
                cout<<"查无此人"<<endl;
            }

        }
        else{//输入的select不是1或2
            cout<<"输入有误"<<endl;
        }
    }
    pause_and_clear();
}

void WorkerManager::Sort_Emp(){//排序职工
    if(m_EmpArray.empty()){
        cout<<"文件不存在或文件为空"<<endl;
        system("pause");
        system("cls");
    }
    else{
        cout<<"排序方式？"<<endl;
        cout<<"1.按职工编号升序"<<endl;
        cout<<"2.按职工编号降序"<<endl;

        int select=0;
        get_Valid_InputV2(select);//校验输入值
        bool asc = (select == 1);
        std::sort(m_EmpArray.begin(),m_EmpArray.end(),
        [asc](const auto&a,const auto&b){
            return asc ? a->m_Id<b->m_Id : a->m_Id>b->m_Id;
        });
        std::cout<<"排序成功，结果如下"<<std::endl;
        this->save();
        this->Show_Emp();
    }
}

void WorkerManager::Clean_File()//清空文件
{
    if(m_EmpArray.empty()){
        cout << "当前文件已空，无需清空" << endl;
        system("pause");
        system("cls");
        return; // 直接返回，不执行后面的清空
    }
    cout<<"确定清空？"<<endl;
    cout<<"1.确定  2.返回"<<endl;

    int select=0;
    std::cin>>select;
    if(select==1){//清空文件
        std::ofstream ofs(kFileName,std::ios::trunc);//删除文件后重新创建
        ofs.close();
        m_EmpArray.clear();
        std::cout<<"清空成功"<<std::endl;
    }
   pause_and_clear();
}

void WorkerManager::get_Valid_Input(int& dSelect){//校验输入值是否合规(1,2,3)
    bool validInput = false;//输入校验
    while (!validInput) {
        if(cin>>dSelect){
            if (dSelect >= 1 && dSelect <= 3) {
                validInput = true;
            }
            else {
                cout << "输入错误，请重新输入！" << endl;
            }
        }
        else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "输入有误，请重新输入！" << endl;
        }
    }
}

void WorkerManager::get_Valid_InputV2(int& select){//校验输入值是否合规(1,2)
    bool validInput = false;//输入校验
    while (!validInput) {
        if(cin>>select){
            if (select==1||select==2){
                validInput = true;
            }
            else{
                cout << "输入错误，请重新输入！" << endl;
            }
        }
        else{
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "输入有误，请重新输入！" << endl;
        }
    }
}
