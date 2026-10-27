#include "worker_Manager.h"
WorkerManager::WorkerManager(){//构造函数
    //1.文件不存在
    ifstream ifs;
    ifs.open(FILENAME,ios::in);//读文件

    if(!ifs.is_open()){
        cout<<"文件不存在"<<endl;
        this->m_EmpNum = 0;//初始化人数
        this->m_EmpArray = NULL;//初始化数组指针
        this->m_FileIsEmpty = true;//初始化文件是否为空
        ifs.close();
        return;
    }
    
    //2.文件存在，数据为空
    char ch;
    ifs>>ch;
    if(ifs.eof())//文件为空
    {
        cout<<"文件为空"<<endl;
        this->m_EmpNum = 0;//初始化人数
        this->m_EmpArray = NULL;//初始化数组指针
        this->m_FileIsEmpty = true;//初始化文件是否为空
        ifs.close();
        return;
    }

    //3.文件存在且不为空
    int num = get_EmpNum();
    cout<<"职工人数为"<<num<<endl;
    this->m_EmpNum = num;//职工人数
    this->m_EmpArray = new worker*[this->m_EmpNum];//开辟空间
    this->init_Emp();//将文件中数据存到数组中
    this->m_FileIsEmpty = false;//初始化文件是否为空
}
int WorkerManager::get_EmpNum()//统计文件中人数
{
    ifstream ifs;
    ifs.open(FILENAME, ios::in);//打开文件 读
    int id;
    string name;
    int dId;

    int num = 0;
    while(ifs>>id&&ifs>>name&&ifs>>dId){
        num++;
    }
    ifs.close();
    return num;
}

WorkerManager::~WorkerManager(){//析构函数
    if(this->m_EmpArray!=NULL){
        for(int i=0; i<this->m_EmpNum; i++){           
            if(this->m_EmpArray[i]!=NULL){
                delete this->m_EmpArray[i];
            }
        }
        delete[] this->m_EmpArray;
        this->m_EmpArray = NULL;
    }
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
    system("pause");
    exit(0);
}

void WorkerManager::Add_Emp(){//添加职工函数
    cout<<"添加的职工数？ "<<endl;

    int addnum = 0;//新增人数
    while (!(cin >> addnum)) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "输入有误，请输入数字！" << endl;
    }
    if(addnum>0){
       
        int NewSize = this->m_EmpNum + addnum;
         //新空间人数=已添加人数+新增人数
         
        worker**newSpace = new worker*[NewSize];//开辟新空间
        if(m_EmpArray!=NULL)//旧数据复制
        {
            for(int i=0; i<m_EmpNum; i++)
            {
                newSpace[i] = this->m_EmpArray[i];
                //在 C++ 底层，newSpace[i] 完全等价于 *(newSpace + i)。
            }
        }

        for(int i=0; i<addnum; i++){
            int id;
            string name;//部门选择
            int dSelect;

            cout<<"第"<<i+1<<"名新职工的编号？"<<endl;
            cin>>id;
            
            cout<<"第"<<i+1<<"名新职工的姓名？"<<endl;
            cin>>name;
            
            cout<<"第"<<i+1<<"名新职工的部门？"<<endl;
            cout<<"1.employee"<<endl;
            cout<<"2.manager"<<endl;
            cout<<"3.boss"<<endl;
            get_Valid_Input(dSelect);//校验输入值
            
            worker*p_worker = NULL;
            switch (dSelect)
            {
                case 1:
                    p_worker = new employee(id,name,1);
                    break;
                case 2:
                    p_worker = new manager(id,name,2);
                    break;
                case 3:
                    p_worker = new boss(id,name,3);
                    break;
            default:
                break;
            }
            newSpace[m_EmpNum+i]=p_worker;
        }
        delete[] this->m_EmpArray;//释放原有空间
        this->m_EmpArray = newSpace;//更新指针指向
        this->m_EmpNum = NewSize;//更新人数
        this->save();//保存数据到文件中
        this->m_FileIsEmpty = false;
        cout<<"成功添加"<<addnum<<"名新职工"<<endl;
    }
    else{
        cout<<"输入有误"<<endl;
    }
    system("pause");
    system("cls");
}

void WorkerManager::save(){//保存函数
    ofstream ofs;
    ofs.open(FILENAME,ios::out);
    for(int i=0; i<this->m_EmpNum; i++){
        ofs<<this->m_EmpArray[i]->m_Id<<" "
        <<this->m_EmpArray[i]->m_Name<<" "
        <<this->m_EmpArray[i]->m_DeptId<<endl;
    }
    ofs.close();
}

void WorkerManager::init_Emp(){//初始化员工
    ifstream ifs;
    ifs.open(FILENAME,ios::in);

    int id;
    string name;
    int dId;

    int index=0;
    while(ifs>>id&&ifs>>name&&ifs>>dId){
        worker*p_worker = NULL;

        if(dId==1)//普通职工
        {
            p_worker=new employee(id,name,dId);
        }
        else if(dId==2)//经理
        {
            p_worker=new manager(id,name,dId);
        }
        else if(dId==3)//
        {
            p_worker=new boss(id,name,dId);
        }
        else{
            cout<<"输入有误"<<endl;
            continue;
        }
        this->m_EmpArray[index] = p_worker;
        index++;
    }
    ifs.close();
}

void WorkerManager::Show_Emp(){//显示职工
    if(this->m_FileIsEmpty){//判断文件是否为空
        cout<<"文件为空"<<endl;
    }
    else{
        for(int i=0; i<this->m_EmpNum; i++){
            this->m_EmpArray[i]->showInfo();
        }
    }
    system("pause");
    system("cls");
}

void WorkerManager::Del_Emp()//删除职工
{
    if(this->m_FileIsEmpty){
        cout<<"文件不存在或记录为空"<<endl;
    }
    else{
        cout<<"要删除的职工编号是？"<<endl;
        int id=0;
        cin>>id;
        
        int index=this->IsExist(id);
        if(index!=-1){//说明职工存在
            delete this->m_EmpArray[index];
            for(int i=index; i<this->m_EmpNum-1; i++){
                //数组前移
                this->m_EmpArray[i]=this->m_EmpArray[i+1];
            }
            this->m_EmpArray[this->m_EmpNum - 1] = NULL;
            this->m_EmpNum--;//更新当前职工人数
            this->save();
            cout<<"删除成功"<<endl;
        }
        else{
            cout<<"未找到该职工，删除失败"<<endl;
        }
    }
    system("pause");
    system("cls");
}

int WorkerManager::IsExist(int id)//判断职工是否存在，存在则返回职工所在数组中的位置，不存在则返回-1//
{
    int index=-1;
    for(int i=0; i<this->m_EmpNum; i++){
        if(this->m_EmpArray[i]->m_Id== id){//找到职工
            index=i;//记录职工编号
            break;
        }
    }
    return index;//返回职工编号
}

void WorkerManager::Mod_Emp()//修改职工
{
    if(this->m_FileIsEmpty){
        cout<<"文件不存在或文件为空"<<endl;
    }
    else{
        int id;
        cout<<"要修改的职工编号？"<<endl;
        cin>>id;
        int ret = this->IsExist(id);
        if(ret!=-1){
            delete this->m_EmpArray[ret];
            
            int newId=0;
            string newName=" ";
            int dSelect = 0;

            cout<<"查找到"<<id<<"号职工，请输入新职工号"<<endl;
            cin>>newId;

            cout<<"请输入新姓名"<<endl;
            cin>>newName;
            
            cout<<"请输入新部门"<<endl;
            cout<<"1.employee"<<endl;
            cout<<"2.manager"<<endl;
            cout<<"3.boss"<<endl;
            get_Valid_Input(dSelect);//校验输入值
            worker*p_worker=NULL;
            switch(dSelect){
                case 1:
                    p_worker=new employee(newId,newName,dSelect);
                    break;
                case 2:
                    p_worker=new manager(newId,newName,dSelect);
                    break;
                case 3:
                    p_worker=new boss(newId,newName,dSelect);
                    break;
                default:
                    break;
            }
            this->m_EmpArray[ret] = p_worker;
            cout<<"修改成功"<<endl;
            this->save();
        }
        else{
            cout<<"查无此人，修改失败"<<endl;
        }
    }
    system("pause");//摁任意键清屏
    system("cls");
}

void WorkerManager::Find_Emp()//查找职工
{
    if(this->m_FileIsEmpty){
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
            for(int i=0; i<this->m_EmpNum; i++){
                if(this->m_EmpArray[i]->m_Name==name){
                    cout<<"查找成功，职工编号为"
                    <<this->m_EmpArray[i]->m_Id
                    <<"的职工信息如下"<<endl;
                    this->m_EmpArray[i]->showInfo();
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
    system("pause");//摁任意键清屏
    system("cls");
}

void WorkerManager::Sort_Emp(){//排序职工
    if(this->m_FileIsEmpty){
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
        
        for(int i=0; i<this->m_EmpNum; i++){
            int MinOrMax=i;
            for(int j=i+1; j<this->m_EmpNum; j++){
                if(select==1){//升序
                    if(this->m_EmpArray[MinOrMax]->m_Id > this->m_EmpArray[j]->m_Id)
                    {
                        MinOrMax = j;
                    }
                }
                else if(select==2){//降序
                    if(this->m_EmpArray[MinOrMax]->m_Id < this->m_EmpArray[j]->m_Id)
                    {
                        MinOrMax = j;
                    }
                }
            }
            //判断初始时认定的最值是否为最值，不是则交换
            if(i!=MinOrMax){
                worker*temp = this->m_EmpArray[i];
                this->m_EmpArray[i]=this->m_EmpArray[MinOrMax];
                this->m_EmpArray[MinOrMax]=temp;
            }
        }
        cout<<"排序成功，结果如下"<<endl;
        this->save();
        this->Show_Emp();
    }
}

void WorkerManager::Clean_File()//清空文件
{
    if(this->m_FileIsEmpty){
        cout << "当前文件已空，无需清空" << endl;
        system("pause");
        system("cls");
        return; // 直接返回，不执行后面的清空
    }
    cout<<"确定清空？"<<endl;
    cout<<"1.确定"<<endl;
    cout<<"2.返回"<<endl;

    int select=0;
    cin>>select;
    if(select==1){//清空文件
        ofstream ofs(FILENAME,ios::trunc);//删除文件后重新创建
        ofs.close();

        if(this->m_EmpArray!=NULL){
            for(int i=0; i<this->m_EmpNum; i++){//删除堆区的每个职工对象
                delete this->m_EmpArray[i];
                this->m_EmpArray[i] = NULL;
            }
            delete []this->m_EmpArray;//删除堆区数组指针
            this->m_EmpArray = NULL;
            this->m_EmpNum = 0;
            this->m_FileIsEmpty = true;
        }
        cout<<"清空成功"<<endl;
    }
    system("pause");
    system("cls");
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
