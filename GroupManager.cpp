#include <iostream>
#include "GroupManager.h"
#include <string>
using namespace std;

GroupManager::GroupManager(int Mem_Num, string Mem_Name, int Depart_Num)
{
	this->Member_Num = Mem_Num;
	this->Member_Name = Mem_Name;
	this->Department_Num = Depart_Num;
}

void GroupManager::show_info()
{
	cout << endl;
	cout << "ID: " << Member_Num
		<< "\tName: " << Member_Name
		<< "\tDepartment: " << get_depart_name() << "\n"
		<< "\tRole: " << get_depart_role()
		<< endl;
	cout << endl;
}

string GroupManager::get_depart_name()
{
	return string("Group Manager");
}

string GroupManager::get_depart_role()
{
	return string("Supervise the common members and complete tasks that handed over by the Group Leader");
}