#pragma once
#include <iostream>
#include "GroupMember.h"
using namespace std;

//create an abstract class that inheritance GroupMember for customized features for role Common Member
class ComMember :public GroupMember
{
public:

	ComMember(int Mem_Num, string Mem_Name,int Depart_Num);

	virtual void show_info();

	virtual string get_depart_name();

	virtual string get_depart_role();
};