#include<iostream>
using namespace std;
#include"worker_Manager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"
int main(){
    WorkerManager wm;
    int choice = 0;
    while(true){
        wm.show_Menu();
        cin>>choice;
        switch(choice){
            case 0://退出
                wm.ExitSystem();
                break;
            case 1://增加
                wm.Add_Emp();
                break;
            case 2://显示
                wm.Show_Emp();
                break;
            case 3://删除
                wm.Del_Emp();
                break;
            case 4://修改
                wm.Mod_Emp();
                break;
            case 5://查找
                wm.Find_Emp();
                break;
            case 6://排序
                wm.Sort_Emp();
                break;
            case 7://清空
                wm.Clean_File();
                break;
            default:
                system("cls");//清屏
                break;
        }
    }
    system("pause");
    return 0;
}