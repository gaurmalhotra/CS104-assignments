#ifndef WEBPAGE_H
#define WEBPAGE_H
#include <set>
#include <vector>
#include <string>

class Webpage{
 public:
  Webpage();
  void content_push(std::string str);
  int content_size();
  std::vector<std::string> get_content();
  void incoming_insert(std::string str);
  int incoming_size();
  std::set<std::string> get_incoming();
  void outgoing_insert(std::string str);
  int outgoing_size();
  std::set<std::string> get_outgoing();

 private:
  std::vector<std::string> content;
  std::set<std::string> incomingLinks;
  std::set<std::string> outgoingLinks;
};
#endif
