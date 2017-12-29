#include "user.h"
#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

	User::User(int id, string name, int year, int zip)
	{
		user_ID = id;
		user_Name = name;
		user_Year = year;
		user_Zip = zip;
		user_Depth = -1;
		user_Predecessor = -1;
		user_Score = 0;
	}
	//max of list 100 add users
	void User::addFriend(int id)
	{
		if (user_Friends.size() > 100)
		{
			return;
		}
		user_Friends.push_back(id);
	}

	//search through for user and erase from vector
	void User::deleteFriend(int id)
	{
		int deletion = findFriend(id);
		if (deletion == -1)
		{
			return;
		}
		user_Friends.erase(user_Friends.begin() + deletion);
	}

	//getter functions
	string User::getName()
	{
		return user_Name;
	}

 	int User::getID()
 	{
 		return user_ID;
 	}

 	int User::getYear()
 	{
 		return user_Year;
 	}
 	int User::getZip()
 	{
 		return user_Zip;
 	}

 	//getter function for the vector itself
 	const vector<int>& User::getFriends()
 	{
 		return user_Friends;
 	}

 	//locating index of friend public function
 	int User::getFriend(int id)
 	{
	 		int location = findFriend(id);
	 		if (location == -1)
	 		{
	 			return -1;
	 		}
	 		return user_Friends[location];
 	}

 	//locating index of friend private function
 	int User::findFriend(int id)
 	{
 		for (int i = 0; i < user_Friends.size(); i++)
 		{
 			if (user_Friends[i] == id)
 			{
 				return i;
 			}
 		}
 		return -1;
 	}

 	// void User::suggestion_score()
 	 // {

 	// }

 	// void User::set_member(int newDepth)
 	// {
 	// 	user_Depth = newDepth;
 	// }

 	// void User::set_predecessor(int newPredecessor)
 	// {
 	// 	user_Predecessor = newPredecessor;
 	// }

 	// int User::return_member()
 	// {
 	// 	return user_Depth;
 	// }

 	// int User::return_predecessor()
 	// {
 	// 	return user_Predecessor;
 	// }