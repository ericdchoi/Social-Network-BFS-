#ifndef USER_H
#define USER_H

#include <string>
#include <vector>


class User {
 public:
 	User(int id, std::string name, int year, int zip);
 	void addFriend(int id);
 	void deleteFriend(int id);
 	std::string getName();
 	int getID();
 	int getYear();
 	int getZip();
 	int getFriend(int id);
 	const std::vector<int>& getFriends();
 	int user_Depth;
 	int user_Predecessor;
 	int user_Score;

 private:
 	int findFriend(int id);
 	int user_ID;
 	std::string user_Name;
 	int user_Year;
 	int user_Zip;
 	std::vector <int> user_Friends;


};


#endif
