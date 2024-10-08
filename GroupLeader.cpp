#include <iostream>
#include "GroupLeader.h"
#include <string>
using namespace std;

GroupLeader::GroupLeader(int Mem_Num, string Mem_Name, int Depart_Num)
{
	this->Member_Num = Mem_Num;
	this->Member_Name = Mem_Name;
	this->Department_Num = Depart_Num;
}

void GroupLeader::show_info()
{
	cout << endl;
	cout << "ID: " << Member_Num
		<< "\tName: " << Member_Name
		<< "\tDepartment: " << get_depart_name() << "\n"
		<< "\tRole: " << get_depart_role()
		<< endl;
	cout << endl;
}

string GroupLeader::get_depart_name()
{
	return string("Group Leader");
}

string GroupLeader::get_depart_role()
{
	return string("Lead the group to the promising direction and supervise the Group Managers");
}