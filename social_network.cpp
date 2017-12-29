#include "network.h"
#include "user.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
using namespace std;

int main(int argc, char ** argv)
{
	Network main;
	int zip = 0, year, input;
	string temp_Line, first_Name1, last_Name1, full_Name1;
	string first_Name2, last_Name2, full_Name2;
	stringstream temp_Stream;

	main.read_friends(argv[1]);
	//list of inputs
	cout << "1. Add a user" << '\n' << "2. Add friend connection" << endl;
	cout << "3. Remove friend connection" << '\n' << "4. Print users" << endl;
	cout << "5. List friends" << '\n' << "6. Write to file" << endl;
	cout << "7. Short path to friend" << '\n' << "8. Set of friends" << endl;
	cout << "9. Suggested friends" << '\n' << "Pick any other char to exit" << endl;
	//while the number is tsill through 1-9
	cin >> input;
	while (input > 0 && input < 10)
	{
		//parsing the string for input info
		if (input == 1)
		{
			getline(cin, temp_Line);
			temp_Stream << temp_Line;
			temp_Stream >> first_Name1 >> last_Name1 >> year >> zip;
			full_Name1 = first_Name1 + " " + last_Name1;
			User temporary_User(main.get_totalusers(), full_Name1, year, zip);
			temp_Stream.clear();
			main.add_user(&temporary_User);
			cin >> input;
		}
		//adding connection from two parsed names
		else if (input == 2)
		{
			getline(cin, temp_Line);
			temp_Stream << temp_Line;
			temp_Stream >> first_Name1 >> last_Name1 >> first_Name2 >> last_Name2;
			full_Name1 = first_Name1 + " " + last_Name1;
			full_Name2 = first_Name2 + " " + last_Name2;
			main.add_connection(full_Name1, full_Name2);
			temp_Stream.clear();
			cin >> input;
		}
		//deleting connection from two parsed names
		else if (input == 3)
		{
			getline(cin, temp_Line);
			temp_Stream << temp_Line;
			temp_Stream >> first_Name1 >> last_Name1 >> first_Name2 >> last_Name2;
			full_Name1 = first_Name1 + " " + last_Name1;
			full_Name2 = first_Name2 + " " + last_Name2;

			main.remove_connection(full_Name1, full_Name2);
			temp_Stream.clear();
			cin >> input;
		}
		//prints out list of users at the time
		else if (input == 4)
		{
			cout << left << setw(10) << "ID" << setw(20) <<"Name";
			cout << setw(10) << "Year" << setw(10) << "Zip" << endl;
			for (int i = 0; i < 50; i++)
			{
			cout << "=";
			}

			cout << endl;
			for (int user = 0; user < main.get_totalusers(); user++)
			{
				User temp = main.get_users()[user];
				cout << setw(10) << temp.getID() << setw(20) << temp.getName() << setw(10);
				cout << temp.getYear() << setw(10) << temp.getZip() << endl;
			}
			cin >> input;
		}
		//printing out the list of friends of specified user
		else if (input == 5)
		{
			getline(cin, temp_Line);
			temp_Stream << temp_Line;
			temp_Stream >> first_Name1 >> last_Name1;
			full_Name1 = first_Name1 + " " + last_Name1;
			temp_Stream.clear();
			int temp1ID = main.get_id(full_Name1);
			if (temp1ID == -1)
			{
				cin >> input;
				continue;
			}
			User *temp1 = &(main.get_users()[temp1ID]);

			cout << left << setw(10) << "ID" << setw(20) << "Name";
			cout << setw(10) << "Year" << setw(10) << "Zip" << endl;

			for (int i = 0; i < 50; i++)
			{
				cout << "=";
			}

			cout << endl;
			int friendo = 0;
			while (friendo < temp1->getFriends().size())
			{
				stringstream print_ID;
				int temp2ID = (temp1->getFriends())[friendo];
				if (temp2ID == -1)
				{
					cin >> input;
					continue;
				}

				User *temp2 = &(main.get_users()[temp2ID]);
				print_ID << temp2->getID() << ".";
				cout << setw(10) << print_ID.str() << setw(20) << temp2->getName() << setw(10);
				cout << temp2->getYear() << setw(10) << temp2->getZip() << endl;
				friendo++;
			}
			cin >> input;
		}
		//outputting information into designated file
		else if (input == 6)
		{
			cin >> temp_Line;
			const char *temp_Char = temp_Line.c_str();
			main.write_friends(temp_Char);
			cin >> input;
		}
		//output shortest distance from inputted users
		else if (input == 7)
		{
			getline(cin, temp_Line);
			temp_Stream << temp_Line;
			temp_Stream >> first_Name1 >> last_Name1 >> first_Name2 >> last_Name2;
			temp_Stream.clear();
			full_Name1 = first_Name1 + " " + last_Name1;
			full_Name2 = first_Name2 + " " + last_Name2;
			int temp1ID = main.get_id(full_Name1);
			int temp2ID = main.get_id(full_Name2);

			vector <int> test = main.shortest_path(temp1ID, temp2ID);
			if (test.size() == 0)
			{
				cout << "None" << endl;
				cin >> input;
				continue;
			}

			if (test.size() == 1)
			{
				cout << "Distance: " << 0 << endl;
			}
			else
			{
				cout << "Distance: " << test.size() << endl;
			}

			for (int i = 0; i < test.size() - 1; i++)
			{
				cout << main.get_users()[test[i]].getName() << " -> ";
			}
			cout << main.get_users()[test[test.size()-1]].getName() << endl;
			cin >> input;
		}
		//output the disjoint sets
		else if (input == 8)
		{
			vector <vector<int> > carrier = main.groups();
			for (int pigeons = 0; pigeons < carrier.size(); pigeons++)
			{
				cout << "Set " << (pigeons+1) << " => ";
				vector <int> doves = carrier[pigeons];
				for (int meh = 0; meh < doves.size() - 1; meh++)
				{
					cout << main.get_users()[doves[meh]].getName() << ", ";
				}
				cout << main.get_users()[doves[doves.size()-1]].getName();
				cout << endl;
			}
			cin >> input;
		}
		//output a suggest friends based on mutual friends
		else if (input == 9)
		{
			int score = -1;
			getline(cin, temp_Line);
			temp_Stream << temp_Line;
			temp_Stream >> first_Name1 >> last_Name1;
			full_Name1 = first_Name1 + " " + last_Name1;
			temp_Stream.clear();
			int temp1ID = main.get_id(full_Name1);
			if (temp1ID == -1)
			{
				cin >> input;
				continue;
			}
			vector<int> suggest = main.suggest_friends(temp1ID, score);

			if (suggest.size() == 0)
			{
				cout << "None " << endl;
				cin >> input;
			}

			cout << "The suggest friend(s) is/are: " << endl;
			for (int users = 0; users < suggest.size(); users++)
			{
				cout << main.get_users()[suggest[users]].getName() << '\t';
				cout << "Score: " << score << endl;
			}

			cin >> input;
		}

	}
	return 0;
}