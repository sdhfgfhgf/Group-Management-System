#pragma once
#include <iostream>
#include <string>
#include "GroupMember.h"
using namespace std;


class Functions
{
public:
	Functions();

	void Show_Menu();

	void Notify_Empty();

	void Exit_Sys();

	int m_Num_of_Member;

	GroupMember** m_MemArray;

	void AddMembers();

	void save();

	bool m_is_FileEmpty;

	void FileOpenError();

	int getMemNum();

	void read();

	void Show_mem();

	void Del_mem();

	int IsExist(int id);

	void Modify_mem();

	void Search_mem();

	void Sort_mem();

	void Clean_file();

	~Functions();

};