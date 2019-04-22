#ifndef _MOVIE_H
#define _MOVIE_H

#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class movie {
public:
  movie();
  movie(string tt, string y, string tm, string g, string a, string r);

  // print for search results
  void print(std::ostream& out, const map<string, string>& actors) const;

  vector<string> getAllStringKeys() const;

private:
  string title, year, time, gList, aList, rList;
  vector<vector<string> > choices;
};

void combine(vector<vector<string> > &comb, vector<vector<string> > array, \
  int i, vector<string> accum);

vector<string> split(const string& str, const string& delim);

#endif
