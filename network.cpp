#include "network.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <deque>
using namespace std;

	Network::Network()
	{
		total_Users = 0;
	}

	Network::~Network()
	{
		
	}
	//parsing through the text file
	//given the number of users, repeat that many times
	//of parsing allocated info
	int Network::read_friends(const char *filename)
	{
		ifstream in_File(filename);
		if (in_File.fail())
		{
			return -1;
		}
		string temp_Line;
		string name, first_Name, last_Name;
		int id;
		int year;
		int zip;
		int initial_People;
		int friends;
		stringstream temp_Parse;

		in_File >> initial_People;
		int count = 0;
		while(count < initial_People)
		{
			in_File >> id;
			in_File.ignore();
			getline(in_File, temp_Line);
			temp_Parse << temp_Line;
			temp_Parse >> first_Name >> last_Name;
			temp_Parse.clear();
			temp_Parse.str("");
			name = first_Name + " " + last_Name;
			in_File >> year >> zip;
			in_File.ignore();
			User temp_User(id, name, year, zip);
			getline(in_File, temp_Line);
			temp_Parse << temp_Line;
			while (temp_Parse >> friends)
			{
				temp_User.addFriend(friends);
			}
			temp_Parse.clear();
			temp_Parse.str("");
			add_user(&temp_User);
			count++;
		}
		
		in_File.close();

		return 0;
	}

	//write to designated file info already saved
	int Network::write_friends(const char *filename)
	{

		ofstream out_File(filename);
		if (out_File.fail())
		{
			return -1;
		}


		out_File << total_Users << endl;
		for (int count = 0; count < total_Users; count++)
		{
			int count_Friends = 0;
			out_File << network_Users[count].getID() << endl;
			out_File << '\t' << network_Users[count].getName() << endl;
			out_File << '\t' <<network_Users[count].getYear() << endl;
			out_File << '\t' << network_Users[count].getZip() << endl;
			out_File << '\t';
			while (count_Friends < network_Users[count].getFriends().size())
			{

				out_File << (network_Users[count].getFriends())[count_Friends] << " ";
				count_Friends++;
			}
			out_File << endl;
		}
		out_File.close();
		return 0;
	}

	//add to user designated user
	void Network::add_user(User* adding)
	{
		network_Users.push_back(*adding);
		total_Users++;
	}
	//connect two users together
	int Network::add_connection(string name1, string name2)
	{
		if (get_id(name1) == -1 || get_id(name2) == -1)
		{
			return -1;
		}
		User *temp1 = &network_Users[get_id(name1)];
		User *temp2 = &network_Users[get_id(name2)];
		int temp1ID = temp1->getID();
		int temp2ID = temp2->getID();
		if(temp1->getFriend(temp2ID) == temp2ID)
		{
			return -1;
		}

		temp2->addFriend(temp1ID);
		temp1->addFriend(temp2ID);

		return 0;
	}
	//delete two friends from each other
	int Network::remove_connection(string name1, string name2)
	{
		if (get_id(name1) == -1 || get_id(name2) == -1)
		{
			return -1;
		}
		User *temp1 = &network_Users[get_id(name1)];
		User *temp2 = &network_Users[get_id(name2)];
		if(temp1->getFriend(temp2->getID()) != temp2->getID())
		{
			return -1;
		}
		temp1->deleteFriend(temp1->getFriend(temp2->getID()));
		temp2->deleteFriend(temp2->getFriend(temp1->getID()));
		return 0;
	}
	//locate user based on id
	int Network::get_id(string username) //get_id
	{
		int count = 0;
		while (count < total_Users)
		{
			if(username == network_Users[count].getName())
			{
				return count;
			}
			count++;
		}
		return -1;
	}
	//getter functions for total number of users and vector
	int Network::get_totalusers()
	{
		return total_Users;
	}



	std::vector<User>& Network::get_users()
	{
		return network_Users;
	}
	//returns a vector of predecessor values following each other
	std::vector<int> Network::shortest_path(int from, int to)
	{
		reset_depth();
		vector <int> return_path;
		if (from == -1 || to == -1)
		{
			return return_path;
		}
		bfs(from);

		User *temp = &network_Users[to];
		int tracker = temp->getID();
		if (temp->user_Depth == -1)
		{
			return return_path;
		}
		return_path.push_back(tracker);

		while (tracker != from)
		{
			temp = &network_Users[temp->user_Predecessor];
			tracker = temp->getID();
			return_path.insert(return_path.begin(), tracker);
		}



		reset_depth();
		return return_path;
	}
	//returns several vectors representing distinct groups
 	std::vector<std::vector<int> > Network::groups()
 	{
 		vector<vector<int> > disjoint;
 		if (network_Users.empty())
 		{
 			return disjoint;
 		}
 		vector<int> cumulative;

		for (int users = 0; users < total_Users; users++)
		{
			User *tempUser = &network_Users[users];
			if (tempUser->user_Depth == -1)
			{
				vector <int> temp;
				bfs(tempUser->getID());
				temp.push_back(tempUser->getID());
				tempUser->user_Depth = -2;
				for (int users2 = 0; users2 < total_Users; users2++)
				{
					User *tempUser2 = &network_Users[users2];
					if (tempUser2->user_Depth > -1)
					{
						temp.push_back(tempUser2->getID());
						tempUser2->user_Depth = -2;
					}
				}
				disjoint.push_back(temp);	
			}
		}
		reset_depth();
		return disjoint;
 	}
 	//returns a list of recommended vectors with a rating
  	std::vector<int> Network::suggest_friends(int who, int& score)
  	{
  		reset_depth();
  		vector<int> firstFriends;
  		vector<int> secondFriends;
  		vector<int> returnFriends;
  		score = -1;
  		bfs(who);
  		for (int users = 0; users < total_Users; users++)
  		{
  			User *temp = &network_Users[users];
  			if (temp->user_Depth == 1)
  			{
  				firstFriends.push_back(temp->getID());
  			}

  			if (temp->user_Depth == 2)
  			{
  				secondFriends.push_back(temp->getID());
  			}
  		}
  		
  		reset_depth();

  		for (int users = 0; users < firstFriends.size(); users++)
  		{
  			User *temp = &network_Users[firstFriends[users]];
  			bfs(temp->getID());
  			for (int users2 = 0; users2 < secondFriends.size(); users2++)
  			{
  				User *temp2 = &network_Users[secondFriends[users2]];
  				if (temp2->user_Depth == 1)
  				{
  					temp2->user_Score++;
  					if (temp2->user_Score > score)
  					{
  						score = temp2->user_Score;
  					}
  				}
  			}
  			reset_depth();
  		}


  		for (int users = 0; users < secondFriends.size(); users++)
  		{
  			User *temp = &network_Users[secondFriends[users]];
  			if (temp->user_Score == score)
  			{
  				returnFriends.push_back(temp->getID());
  			}
  		}

  		reset_score();
  		return returnFriends;

  	}
  	//breadth first search, sets predecessor and depth
   	void Network::bfs(int bvertex)
   	{
   		int depth = 0, remove = 0;
   		if (bvertex == -1)
   		{
   			return;
   		}
   		User *initial = &network_Users[bvertex];
   		initial->user_Depth = depth;
   		bfsdepth.push_back(bvertex);
   		while(!bfsdepth.empty())
   		{
   			remove = bfsdepth[0];
   			initial = &network_Users[remove];
   			depth = initial->user_Depth + 1;
   			for (int friends = 0; friends < initial->getFriends().size(); friends++)
   			{
   				int tempFriend = initial->getFriends()[friends];
   				User *temp = &network_Users[tempFriend];
   				if(temp->user_Depth == -1)
   				{
   					bfsdepth.push_back(tempFriend);
   					temp->user_Depth = depth;
   					temp->user_Predecessor = remove;
   				}

   			}

 			bfsdepth.pop_front();	

   		}

   	}
   	//resets users depth value
   	void Network::reset_depth()
   	{
   		for (int i = 0; i < total_Users; i++)
   		{
   			User* temp = &network_Users[i];
   			temp->user_Depth = -1;
   			temp->user_Predecessor = -1;
   		}
   	}
   	//resets users score value
   	void Network::reset_score()
   	{
   		for (int i = 0; i < total_Users; i++)
   		{
   			User* temp = &network_Users[i];
   			temp->user_Score = 0;
   		}
   	}