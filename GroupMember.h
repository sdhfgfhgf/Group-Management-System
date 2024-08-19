#pragma once
#include <iostream>
#include <string>

using namespace std;

//create an abstract class that outlines the basic features and variables that members classes should have
class GroupMember
{
public:
	virtual void show_info() = 0;

	virtual string get_depart_name() = 0;

	int Member_Num;
	string Member_Name;
	int Department_Num;
};