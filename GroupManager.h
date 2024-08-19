#pragma once
#include <iostream>
#include <string>
#include "GroupMember.h"

using namespace std;

//create an abstract class that inheritance GroupMember for customized features for role Group Manager
class GroupManager :public GroupMember
{
public:
	GroupManager(int Mem_Num, string Mem_Name, int Depart_Num);

	virtual void show_info();

	virtual string get_depart_name();

	virtual string get_depart_role();
};