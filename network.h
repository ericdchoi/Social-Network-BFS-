#ifndef NETWORK_H
#define NETWORK_H
#include <string>
#include "user.h"
#include <vector>
#include <deque>
class Network {
 public:
  Network();
  ~Network();
  int read_friends(const char *filename);
  int write_friends(const char *filename);
  void add_user(User* adding);
  int add_connection(std::string name1, std::string name2);
  int remove_connection(std::string name1, std::string name2);
  int get_id(std::string username);
  int get_totalusers();

  std::vector<User>& get_users();
  std::deque<int>& get_bfs();
  std::vector<int> shortest_path(int from, int to);
  std::vector<std::vector<int> > groups();
  std::vector<int> suggest_friends(int who, int& score);
  
 private:
  void reset_depth();
  void reset_score();
 	std::vector <User> network_Users;
  std::deque <int> bfsdepth;
  void bfs(int bvertex);
 	int total_Users;
 
};


#endif
