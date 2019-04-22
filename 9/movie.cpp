#include "movie.h"

movie::movie(string tt, string y, string tm, string g, string a, string r) {
  title = tt;
  year = y;
  time = tm;
  gList = g;
  aList = a;
  rList = r;


  // make a template choices 2D vector ready for generating 64 keys combinations
  vector<string> _strs;

  _strs.push_back("?");
  for (size_t i = 0; i < 3; i++)
    choices.push_back(_strs);

  _strs[0] = "0"; // reset value

  for (size_t i = 0; i < 3; i++)
    choices.push_back(_strs);

  choices[0].push_back(title);
  choices[1].push_back(year);
  choices[2].push_back(time);
  choices[3].push_back(gList);
  choices[4].push_back(aList);
  choices[5].push_back(rList);
}

void movie::print(std::ostream& out, const map<string, string>& actors) const {

  vector<string> ids = split(aList, " ");
  vector<string> roles = split(rList, " ");


  out << title << '\n';
  out << year << '\n';
  out << time << '\n';
  out << gList << '\n';
  out << aList[0];
  for (size_t i = 1; i < ids.size(); i++) {
    out << " " << actors.find(ids[i])->second;
    out << " " << "(" << roles[i] << ")";
  }
  out << endl;
  // out << rList << '\n';
}

vector<string> movie::getAllStringKeys() const {
  // get 64 combinations of keys
  string str = "";
  vector<string> allKeys;

  vector<vector<string> > combinations;
  vector<string> container;

  combine(combinations, choices, 0, container);

  for (size_t i = 0; i < combinations.size(); i++) {
    for (size_t j = 0; j < combinations[i].size(); j++) {
      str += combinations[i][j];
    }
    allKeys.push_back(str);
    str = "";
  }

  return allKeys;
}

// Reference: https://stackoverflow.com/questions/8620030/generate-all-combination-of-elements-in-2d-vector
void combine(vector<vector<string> > &comb, vector<vector<string> > array, \
  int i, vector<string> accum) {

  if (i == array.size()) { // done, no more rows
    comb.push_back(accum); // assuming comb is global
  }
  else {
    vector<string> row = array[i];
    for(int j = 0; j < row.size(); ++j) {
      vector<string> tmp(accum);
      tmp.push_back(row[j]);
      combine(comb, array,i+1,tmp);
    }
  }
}

vector<string> split(const string& str, const string& delim) {
  // Reference: https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
  vector<string> tokens;
  size_t prev = 0, pos = 0;
  do
  {
      pos = str.find(delim, prev);
      if (pos == string::npos) pos = str.length();
      string token = str.substr(prev, pos-prev);
      if (!token.empty()) tokens.push_back(token);
      prev = pos + delim.length();
  }
  while (pos < str.length() && prev < str.length());
  return tokens;
}
