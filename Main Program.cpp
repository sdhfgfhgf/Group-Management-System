#include <iostream>
#include <string>
#include <fstream>
#include "Functions.h"
#include "CommonMember.h"

using namespace std;


int main()
{
	int choice;

	while (true)
	{
		Functions func;
		func.Show_Menu();

		cout << "Please Enter Your Choice: " << endl;
		cin >> choice;

		switch (choice)
		{
		case 0:
			func.Exit_Sys();
			break;
		case 1:
			func.AddMembers();
			break;
		case 2:
			func.Show_mem();
			break;
		case 3:
			func.Del_mem();
			break;
		case 4:
			func.Modify_mem();
			break;
		case 5:
			func.Search_mem();
			break;
		case 6:
			func.Sort_mem();
			break;
		case 7:
			func.Clean_file();
			break;
		default:
			system("cls");
			break;
		}

	}

	system("pause");

	return 0;
}