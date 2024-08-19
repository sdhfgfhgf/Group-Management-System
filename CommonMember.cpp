#include <iostream>
#include "CommonMember.h"
#include <string>
using namespace std;

ComMember::ComMember(int Mem_Num, string Mem_Name, int Depart_Num)
{
	this->Member_Num = Mem_Num;
	this->Member_Name = Mem_Name;
	this->Department_Num = Depart_Num;
}

void ComMember::show_info()
{
	cout << endl;
	cout << "ID: " << Member_Num
		<< "\tName: " << Member_Name
		<< "\tDepartment: " << get_depart_name() << "\n"
		<< "\tRole: " << get_depart_role()
		<< endl;
	cout << endl;
}

string ComMember::get_depart_name()
{
	return string("Common Member");
}

string ComMember::get_depart_role()
{
	return string("Complete tasks that handed over by the Group Leader");
}