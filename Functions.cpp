#include <iostream>
#include <string>
#include <fstream>
#include "Functions.h"
#include "GroupMember.h"
#include "CommonMember.h"
#include "GroupManager.h"
#include "GroupLeader.h"
#define FILENAME "GroupMembers.txt"

using namespace std;

//if the file failed to open, reset the member numbers counter, array pointer and turn the Empty file indicator to true
void Functions::FileOpenError()
{
	this->m_Num_of_Member = 0;
	this->m_MemArray = NULL;
	this->m_is_FileEmpty = true;
}


Functions::Functions()
{
	ifstream ifs(FILENAME, ios::in); //open the txt file first

	if (!ifs.is_open()) //check and notify the user if the program couldn't locate the file and reset the variables and pointers
	{
		cout << " * The file does not exist * " << endl;
		ifs.close();
		FileOpenError();
		return;
	}

	char ch;
	ifs >> ch;
	if (ifs.eof()) // check and notify the user if the file is located but empty and reset the variables and pointers
	{
		cout << " * The file is empty * " << endl;
		ifs.close();
		FileOpenError();
		return;
	}

	int num = this->getMemNum(); //store the return value of getMemNum() function to a int variable

	//greet the user and display how many numbers currently in the group
	cout << "========== Welcome to use Group Management System ==========" << endl;
	cout << "============ There are " << num << " members in the group ==============" << endl;
	cout << "============================================================" << endl;

	//initialize the variables and create an array in heap for future use
	this->m_Num_of_Member = num;
	this->m_MemArray = new GroupMember * [this->m_Num_of_Member];
	//read and store the data from the file into the array
	this->read();
}

void Functions::Show_Menu()
{
	//display the menu
	cout << "==================== 0.Exit the program ====================" << endl;
	cout << "================= 1.Add Group Member Info ==================" << endl;
	cout << "=============== 2.Display Group Member Info ================" << endl;
	cout << "=============== 3.Delete Group Member Info =================" << endl;
	cout << "=============== 4. Modify Group Member Info ================" << endl;
	cout << "=============== 5. Search Group Member Info ================" << endl;
	cout << "==================== 6. Sort by number =====================" << endl;
	cout << "==================== 7. Clear All Info =====================" << endl;
	cout << "============================================================" << endl;
}

void Functions::Exit_Sys()
{
	//exiting the system
	system("cls");
	cout << "=================== Thank you for using! ===================" << endl;
	exit(0);
}

void Functions::Notify_Empty()
{
	//this is a frequently used function which notify the users when the program couldn't locate te file
	//or the file is empty
	system("cls");
	cout << "******** No Data ********" << endl;
	cout << "*** Returning to Menu ***" << endl;
	system("pause");
	system("cls");
}

void Functions::AddMembers()
{
	//adding group members
	system("cls");

	int Add_num_mem;
	cout << "How many members do you want to add?" << endl;
	cin >> Add_num_mem;

	system("cls");

	//check if the input of the user is appropriate before proceeding
	if (Add_num_mem > 0)
	{
		//define a new size for the new array that the program going to create
		int newSize = this->m_Num_of_Member + Add_num_mem;

		//create a new array to store both new data and previous data using the new size + 4 to prevent memory overflow
		GroupMember ** newSapce = new GroupMember* [newSize + 4];

		//check if there's any data stored previously
		if (this->m_MemArray != NULL)
		{
			//transfer the data from old array to the newly created array
			for (int i = 0; i < this->m_Num_of_Member; i++)
			{
				newSapce[i] = this->m_MemArray[i];
			}
		}

		//start to input the new data
		for (int j = 0; j < (Add_num_mem); j++)
		{
			//initialize variables to store the user input
			int id;
			string name;
			int depart_sel;

			cout << "Please enter the ID number of the Group Member " << j + 1 << ": " << endl;
			cin >> id;
			system("cls");

			//check if the ID that user entered is existed or not use IsExit(int) function
			//then store the return value using an int variable
			int ret = this->IsExist(id);

			//check the return value before proceeding
			if (ret == -1)
			{
				cout << "Please enter the name of the Group Member " << j + 1 << " (FirstName_LastName): " << endl;
				cin >> name;

				//use clear() and ignore() function to prevent the error that caused by wrong data type
				cin.clear();
				cin.ignore();
				system("cls");

				cout << "Please select the role of the Group Member " << j + 1 << ": " << endl;
				cout << "1.Common Member" << endl;
				cout << "2.Group Manager" << endl;
				cout << "3.Group Leader" << endl;
				cin >> depart_sel;
				system("cls");

				//initialize a NULL pointer for recording the role/department
				GroupMember* Groupmem = NULL;

				//create corresponding objects to store the role/department info
				switch (depart_sel)
				{
				case 1:
					Groupmem = new ComMember(id, name, depart_sel);
					break;
				case 2:
					Groupmem = new GroupManager(id, name, depart_sel);
					break;
				case 3:
					Groupmem = new GroupLeader(id, name, depart_sel);
					break;
				default:
					break;
				}

				//import the information to the newly created array
				newSapce[m_Num_of_Member + j] = Groupmem;

				//turn the File Empty indicator to false since the file is no longer empty
				this->m_is_FileEmpty = false;
			}
			else
			{
				//notify the user that the ID is existed and go back to let user enter again
				j--;
				system("cls");
				cout << " * The ID you entered is already existd, please enter a different one * " << endl;
				system("pause");
				system("cls");
			}
		}
		//release the old array in heap
		delete[] this->m_MemArray;
		//define the newly created array as the main array for containing all the information
		this->m_MemArray = newSapce;
		//update the number of members indicator
		this->m_Num_of_Member = newSize;

		system("cls");

		//save the information into the txt file
		this->save();

		//notify the user that the info has been added
		cout << "Successfully added " << Add_num_mem << " new group members" << endl;

		//pause here, if user click any key the program returns to the menu
		system("pause");

		system("cls");
	}
	else
	{
		//notify the users if they input an inappropriate value for the selection and resart the function to let them enter again
		system("cls");
		cout << " * Inappropriate Value * " << endl;
		system("pause");
		system("cls");
		AddMembers();
	}
}

void Functions::save()
{
	//open the file with the status of writing
	ofstream ofs;
	ofs.open(FILENAME, ios::out);

	//write the data from the array into the file
	for (int i = 0; i < this->m_Num_of_Member; i++)
	{
		ofs << this->m_MemArray[i]->Member_Num << " " 
			<< this->m_MemArray[i]->Member_Name << " " 
			<< this->m_MemArray[i]->Department_Num << endl;
	}

	//close the file
	ofs.close();
}

int Functions::getMemNum()
{
	//open the file with the status of reading
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//initialize variables for storing different kinds of info
	int id;
	string name;
	int depart;
	int num(0);

	//count number of sets of data in the file and record the number
	while (ifs >> id && ifs >> name && ifs >> depart)
	{
		num++;
	}

	//return the value
	return num;
	ifs.close();
}

void Functions::read()
{
	//open the file with the status of reading
	ifstream ifs;
	ifs.open(FILENAME, ios::in);

	//initialize variables for storing different kinds of info
	int id;
	string name;
	int depart;
	int index = 0;

	//read in various sets of data in the file and create corresponding objects to store the role/department info
	while (ifs >> id && ifs >> name && ifs >> depart)
	{
		GroupMember* group_mem = NULL;
		if (depart == 1)
		{
			group_mem = new ComMember(id, name, depart);
		}
		else if (depart == 2)
		{
			group_mem = new GroupManager(id, name, depart);
		}
		else if (depart == 3)
		{
			group_mem = new GroupLeader(id, name, depart);
		}
		
		//input the data from the file into the array
		this->m_MemArray[index] = group_mem;
		index++;
	}

	//close the file when done
	ifs.close();

}

void Functions::Show_mem()
{
	//check if the file is empty and show all information if the file is not empty using show_info() function
	system("cls");
	if (this->m_is_FileEmpty)
	{
		this->Notify_Empty();
	}
	else
	{
		for (int i = 0; i < this->m_Num_of_Member; i++)
		{
			this->m_MemArray[i]->show_info();

		}
		system("pause");
		system("cls");
	}
}

void Functions::Del_mem()
{
	//check is the file is empty, start choosing members to delete if the file is not empty
	if (this->m_is_FileEmpty)
	{
		this->Notify_Empty();
	}
	else
	{
		cout << "Please enter the ID of the Group member when you ready to continue: " << endl;
		this->Show_mem();
		int id = 0;
		cout << "Please enter the ID here: " << endl;
		cin >> id;

		//check if the ID input is valid and can be found in the data
		int index = this->IsExist(id);
		if (index != -1)
		{
			//delete the element in the array using left shift method
			for (int i = index; i < this->m_Num_of_Member - 1; i++)
			{
				this->m_MemArray[i] = this->m_MemArray[i + 1];
			}

			//decrease the number of members by one
			this->m_Num_of_Member--;
			//apply the change to the file
			this->save();

			//notify the user
			cout << "Group member ID " << id << " has been deleted" << endl;
		}
		else
		{
			cout << "Couldn't find the group member" << endl;
		}
		system("pause");
		system("cls");
	}
}

int Functions::IsExist(int id)
{
	//this is a frequently used function for checking if an ID is existed in the data or not
	int index = -1;

	for (int i = 0; i < this->m_Num_of_Member; i++)
	{
		if (this->m_MemArray[i]->Member_Num == id)
		{
			index = i;

			break;
		}
	}

	return index;
}

void Functions::Modify_mem()
{
	system("cls");
	if (this->m_is_FileEmpty)
	{
		this->Notify_Empty();
	}
	else
	{
		cout << "Please enter the ID number of the group member: " << endl;
		int id;
		cin >> id;
		system("cls");
		int ret = this->IsExist(id);
		//check if the ID is existed, if existed continue
		if (ret != -1)
		{
			int newID = 0;
			string newName = " ";
			int newDepart = 0;

			cout << "Group member ID " << id << " has been found, please enter the new ID number: " << endl;
			cin >> newID;
			system("cls");
			//check if the new ID is occupied
			int ret2 = this->IsExist(newID);

			//if not, continue
			if (ret2 == -1)
			{
				delete this->m_MemArray[ret];
				cout << "Please enter the new name: " << endl;
				cin >> newName;
				system("cls");

				cout << "Please enter the new role" << endl;
				cout << "1.Common Member" << endl;
				cout << "2.Group Manager" << endl;
				cout << "3.Group Leader" << endl;
				cin >> newDepart;
				system("cls");

				GroupMember* groupmember = NULL;
				switch (newDepart)
				{
				case 1:
					groupmember = new ComMember(newID, newName, newDepart);
					break;
				case 2:
					groupmember = new GroupManager(newID, newName, newDepart);
					break;
				case 3:
					groupmember = new GroupLeader(newID, newName, newDepart);
					break;
				default:
					break;
				}

				//record the info to the array
				this->m_MemArray[ret] = groupmember;
				cout << "The member info has been successfully modified" << endl;
				//update the info to the file
				this->save();
			}
			else
			{
				//notify the user that the ID is existed and go back to let user enter again
				system("cls");
				cout << " * The ID you entered is already existd, please enter a different one * " << endl;
				system("pause");
				system("cls");
				this->Modify_mem();
			}
		}
		else
		{
			cout << " ** Couldn't find the member ** " << endl;
			cout << " *****  Returning to Menu ***** " << endl;
		}

		system("pause");
		system("cls");
	}
}

void Functions::Search_mem()
{
	system("cls");
	if (this->m_is_FileEmpty)
	{
		this->Notify_Empty();
	}
	else
	{
		cout << "Please choose one of the searching method: 1.ID | 2.Name" << endl;
		int choice;
		cin >> choice;

		if (choice == 1)
		{
			cout << "Please enter the ID number of the group member: " << endl;
			int id;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret != -1)
			{
				system("cls");
				cout << "Here is the info of this group member: " << endl;
				this->m_MemArray[ret]->show_info();
				system("pause");
				system("cls");
			}
			else
			{
				system("cls");
				cout << " * Couldn't find this group member * " << endl;
				system("pause");
				system("cls");
			}
		}
		else if (choice == 2)
		{
			cout << "Please enter the name of the group member (FirstName_LastName): " << endl;
			string name;
			cin >> name;

			bool locate = false;

			for (int i = 0; i < m_Num_of_Member; i++)
			{
				if (this->m_MemArray[i]->Member_Name == name)
				{
					locate = true;
					system("cls");
					cout << "Here is the info of this group member: " << endl;
					this->m_MemArray[i]->show_info();
					system("pause");
					system("cls");
				}
			}
			if (locate == false)
			{
				system("cls");
				cout << " * Couldn't find this group member * " << endl;
				system("pause");
				system("cls");
			}
		}
		else
		{
			system("cls");
			cout << " * Inappropriate Value * " << endl;
			system("pause");
			system("cls");
			Search_mem();
		}
	}
}

void Functions::Sort_mem()
{
	system("cls");
	if (this->m_is_FileEmpty)
	{
		this->Notify_Empty();
	}
	else
	{
		cout << "Please choose a sorting method: " << endl;
		cout << "1.ID Ascending order" << endl;
		cout << "2.ID Descending order" << endl;
		int choice;
		cin >> choice;

		if (choice == 1)
		{
			for (int i = 0; i < this->m_Num_of_Member; i++)
			{
				int MinValue = i;

				//using selection sorting method
				for (int j = i + 1; j < this->m_Num_of_Member; j++)
				{
					if (this->m_MemArray[MinValue]->Member_Num > this->m_MemArray[j]->Member_Num)
					{
						MinValue = j;
					}
				}

				if (i != MinValue)
				{
					GroupMember* temp = this->m_MemArray[i];
					this->m_MemArray[i] = this->m_MemArray[MinValue];
					this->m_MemArray[MinValue] = temp;
				}
			}

			system("cls");
			cout << "The data is successfully sorted by Ascending order" << endl;
			this->save();
			this->Show_mem();
		}
		else if (choice == 2)
		{
			for (int i = 0; i < this->m_Num_of_Member; i++)
			{
				int MaxValue = i;
				for (int j = i + 1; j < this->m_Num_of_Member; j++)
				{
					//using selection sorting method
					if (this->m_MemArray[MaxValue]->Member_Num < this->m_MemArray[j]->Member_Num)
					{
						MaxValue = j;
					}
				}

				if (i != MaxValue)
				{
					GroupMember* temp = this->m_MemArray[i];
					this->m_MemArray[i] = this->m_MemArray[MaxValue];
					this->m_MemArray[MaxValue] = temp;
				}
			}

			system("cls");
			cout << "The data is successfully sorted by Descending order" << endl;
			this->save();
			this->Show_mem();
		}
		else
		{
			system("cls");
			cout << " * Inappropriate Value * " << endl;
			system("pause");
			system("cls");
			Sort_mem();
		}
		
	}

}

void Functions::Clean_file()
{
	if (this->m_is_FileEmpty)
	{
		this->Notify_Empty();
	}
	else
	{
		system("cls");
		cout << "Do you confirm to Clear All Data? (1.Yes | 2.No, return to Menu)" << endl;
		int choice;
		cin >> choice;
		if (choice == 1)
		{
			ofstream ofs;
			ofs.open(FILENAME, ios::trunc);
			ofs.close();

			if (this->m_MemArray != NULL)
			{
				//first release every element in the array and set the pointers to NULL
				for (int i = 0; i < this->m_Num_of_Member; i++)
				{
					delete this->m_MemArray[i];
					this->m_MemArray[i] = NULL;
				}

				//then delete the array pointer
				delete[] this->m_MemArray;
				//set the pointer to NULL
				this->m_MemArray = NULL;
				//reset the member counter
				this->m_Num_of_Member = 0;
				//set the file status to empty
				this->m_is_FileEmpty = true;
			}

			cout << "Successfully cleared all data!" << endl;
			system("pause");
			system("cls");
		}
		else
		{
			system("cls");
			cout << "*** Returning to Menu ***" << endl;
			system("pause");
			system("cls");
		}
	}
}

Functions::~Functions()
{
	if (this->m_MemArray != NULL)
	{
		delete[] this->m_MemArray;
		this->m_MemArray = NULL;
	}
}