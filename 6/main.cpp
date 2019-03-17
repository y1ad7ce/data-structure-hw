#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
public:
	Node(): value(0), up(NULL), left(NULL), right(NULL), down(NULL), id(NULL), \
  index(-1), Across(false), Down(false) {}
	Node(const char& v) : value(v), up(NULL), left(NULL),	\
		right(NULL), down(NULL), id(NULL), index(-1), Across(false), Down(false) {}
  Node(Node* identity, int indx): value(0), up(NULL), left(NULL), \
    right(NULL), down(NULL), id(identity), index(indx), Across(false), Down(false) {}

	char value;

	Node* up;
	Node* left;
	Node* right;
	Node* down;

	// this vector contains the beginnings of words
	vector<int> solutionLength;
	vector<char> directions;

  // id: "id pointer" to pointer Node
  Node* id;
  int index;

	// for solution board
	bool Across;
	bool Down;
};

void readDict(ifstream &dictFile, vector<string> &dictContainer) {
  string word;
  while(dictFile >> word) {
		if (word.length() > 2) {
			dictContainer.push_back(word);
		}
  }
}

void readPuzzle(ifstream &gridFile, vector < vector<char> > &puzzle, \
  vector<int> &constraints) {

  string str;
  vector<char> tempChars;
	vector<int> tempConstraints;
  while (gridFile >> str) {

    if (str[0] == '!') {
      continue;
    }

    if (str[0] == '+') {
      tempConstraints.push_back(stoi(str));
      continue;
    }

    for (size_t i = 0; i < str.length(); i++) {
      tempChars.push_back(str[i]);
    }
    puzzle.push_back(tempChars);
    tempChars.clear();
  }

	for (size_t i = 0; i < tempConstraints.size(); i++) {
		while (tempConstraints[i] + 1 > constraints.size()) {
			constraints.push_back(0);
		}
		constraints[tempConstraints[i]]++;
	}
}

void constructGrid(vector < vector<char> > &puzzle, Node* &grid) {
  // grid initialization
  // using 3 node pointers:
  // x for adding new ones
  // z goes after x and keep track of locations of x and y
  // y stays at the beginning of rows all the time.

  Node* z = grid;

  for (size_t i = 0; i < puzzle.size(); i++) {
    if (i > 0) {
      Node* y = new Node(puzzle[i][0]);
      y->up = z;
			z->down = y;
			z = y;
    } else if (puzzle.size() > 0) {
      grid->value = puzzle[0][0];
    }

    for (size_t j = 1; j < puzzle[0].size(); j++) {
      Node* x = new Node(puzzle[i][j]);
      x->left = z;
      z->right = x;
      if (i > 0) {
        x->up = z->up->right;
        z->up->right->down = x;
      }
      z = x;
    }

    for (size_t j = 1; j < puzzle[0].size(); j++) {
      z = z->left; // set back
    }
  }
}

bool stringCompare(const string str1, const string str2) {
	// str1 -> current word in puzzle
	// str2 -> word in dictionary
	// return true if str2 starts with str1 or equals to str1
	for (size_t i = 0; i < str1.length(); i++) {
		if (str1[i] != str2[i])
			return false;
	}

	return true;
}
string findInDict(const string str, const vector<string> dictionary) {
	// because the puzzle's letters are all upper-case, returned string can use
	// lower case letters in the case that word is not finished yet
	for (size_t i = 0; i < dictionary.size(); i++) {
		if (str.length() > dictionary[i].length()) {
			continue;
		}
		if (stringCompare(str, dictionary[i])) {
			if (str.length() == dictionary[i].length())
				return dictionary[i];
			else
				return "next";
		}
	}
	return "failed";
}

void findWords(Node* &grid, const vector<string> &dictionary, \
	const vector<int> &constraints, vector<Node*> &words,
	string &str, Node* location, Node* newRowColumnStart, Node* wordStart, \
	bool horizontalDirect) {
	// the recursive function

	str.push_back(location->value);
	string result = findInDict(str, dictionary);
	if (horizontalDirect) { // checking horizontal words
		if (location->right != NULL) { // not the end of the row

			if (result == "failed") {
				str = "";
				location = wordStart;
				wordStart = wordStart->right;
			}
			if (result != "next" && result != "failed") {
				wordStart->solutionLength.push_back(str.length());
				wordStart->directions.push_back('h');
				words.push_back(wordStart);
			}
			findWords(grid, dictionary, constraints, words, str, \
				location->right, newRowColumnStart, wordStart, horizontalDirect);
		}
		else { // currently at the last node in this row
      if (result != "next" && result != "failed") {
        wordStart->solutionLength.push_back(str.length());
				wordStart->directions.push_back('h');
        words.push_back(wordStart);
      }
			str = "";
			if (wordStart->right != NULL && wordStart->right->right != NULL) {
				location = wordStart;
				wordStart = wordStart->right;
				findWords(grid, dictionary, constraints, words, str, \
					location->right, newRowColumnStart, wordStart, horizontalDirect);
			}
			else {
				if (newRowColumnStart->down != NULL) { // not the last row
					newRowColumnStart = newRowColumnStart->down;
					findWords(grid, dictionary, constraints, words, str, \
						newRowColumnStart, newRowColumnStart, newRowColumnStart, \
						horizontalDirect);
				}
				else { // last row
	        // going back to the beginning and start running through columns
	        location = newRowColumnStart = wordStart = grid;
					findWords(grid, dictionary, constraints, words, str, \
						location, newRowColumnStart, wordStart, false);
				}
			}
		}
	}
  else { // checking vertical words
		if (location->down != NULL) { // not the end of the column

			if (result == "failed") {
				str = "";
				location = wordStart;
				wordStart = wordStart->down;
			}
			if (result != "next" && result != "failed") {
				wordStart->solutionLength.push_back(str.length());
				wordStart->directions.push_back('v');
				words.push_back(wordStart);
			}
			findWords(grid, dictionary, constraints, words, str, \
				location->down, newRowColumnStart, wordStart, horizontalDirect);
		}
		else { // currently at the last node in this column
      if (result != "next" && result != "failed") {
        wordStart->solutionLength.push_back(str.length());
				wordStart->directions.push_back('v');
        words.push_back(wordStart);
      }
			str = "";
			if (wordStart->down != NULL && wordStart->down->down != NULL) {
				location = wordStart;
				wordStart = wordStart->down;
				findWords(grid, dictionary, constraints, words, str, \
					location->down, newRowColumnStart, wordStart, horizontalDirect);
			}
			else {
				if (newRowColumnStart->right != NULL) { // not the last column
					newRowColumnStart = newRowColumnStart->right;
					findWords(grid, dictionary, constraints, words, str, \
						newRowColumnStart, newRowColumnStart, newRowColumnStart, \
						horizontalDirect);
				}
				else { // the end of the grid
					return;
				}
			}
		}
	}
}

void identifyDuplicates(vector<Node*> &words, vector<Node*> &idPointers) {
	// find words starting from the same character in the puzzle
	// make them distinguishable pointer in the words vector
	sort( words.begin(), words.end() );
	words.erase( unique( words.begin(), words.end() ), words.end() );

	for (size_t i = 0; i < words.size(); i++) {
		if (words[i]->solutionLength.size() != 1) {
			for (size_t j = 0; j < words[i]->solutionLength.size(); j++) {
				Node* tmp = new Node(words[i], j);
				idPointers.push_back(tmp);
			}
		}
	}

	for (size_t i = 0; i < idPointers.size(); i++) {
		words.erase(remove(words.begin(), words.end(), idPointers[i]->id), words.end());
	}

	for (size_t i = 0; i < idPointers.size(); i++) {
		words.push_back(idPointers[i]);
	}
}

void unmarkNodes(Node* grid) {
	// unmark nodes
	Node* ptr = grid;
	Node* ptr4 = grid;
	while (ptr4 != NULL) {
		while (ptr != NULL) {
			ptr->Across = false;
			ptr->Down = false;
			ptr = ptr->right;
		}
		ptr4 = ptr4->down;
		ptr = ptr4;
	}
}

bool checkSolution(Node* grid, const vector<Node*> &solution, \
	bool finalOutput, vector<Node*> &output) {
	// this function validates one solution

	// check substrings
	int len;
	Node* check_loc_1; //
	Node* check_loc_2;
	Node* check_loc_3;
	char d1;
	char d2;
	for (size_t i = 0; i < solution.size(); i++) {
		if (solution[i]->solutionLength.size() == 0) {
			check_loc_1 = solution[i]->id;
			d1 = solution[i]->id->directions[solution[i]->index];
			len = solution[i]->id->solutionLength[solution[i]->index];
		} else {
			check_loc_1 = solution[i];
			d1 = solution[i]->directions[0];
			len = solution[i]->solutionLength[0];
		}
		for (size_t j = 0; j < solution.size(); j++) {
			if (j == i) {
				continue;
			}
			check_loc_3 = check_loc_1;

			if (solution[j]->solutionLength.size() == 0) {
				check_loc_2 = solution[j]->id;
				d2 = solution[j]->id->directions[solution[j]->index];
			} else {
				check_loc_2 = solution[j];
				d2 = solution[j]->directions[0];
			}

			for (size_t k = 0; k < len; k++) {
				if (check_loc_3 == check_loc_2 && d1 == d2) {
					return false;
				}

				if (d1 == 'h') {
					check_loc_3 = check_loc_3->right;
				} else {
					check_loc_3 = check_loc_3->down;
				}
			}
		}
	}

	// mark words' nodes so words in board are represented with directions
	// get prepared for the validation
	Node* ptr;
	for (size_t i = 0; i < solution.size(); i++) {
		ptr = solution[i];
		if (solution[i]->solutionLength.size() > 0) {
			for (int j = 0; j < solution[i]->solutionLength[0]; j++) {
				if (solution[i]->directions[0] == 'h') {
					ptr->Across = true;
					ptr = ptr->right;
				}
				else {
					ptr->Down = true;
					ptr = ptr->down;
				}
			}
		}
		else { // idPointers
			ptr = solution[i]->id;
			for (int j = 0; j < solution[i]->id->solutionLength[solution[i]->index]; j++) {
				if (solution[i]->id->directions[solution[i]->index] == 'h') {
					ptr->Across = true;
					ptr = ptr->right;
				}
				else {
					ptr->Down = true;
					ptr = ptr->down;
				}
			}
		}
	}

	// validation
	// get all the words nodes on board (convert idpointers to pointers on board)
	vector<Node*> solutionLocation = solution;
	for (size_t i = 0; i < solutionLocation.size(); i++) {
		if (solutionLocation[i]->solutionLength.size() == 0) {
			solutionLocation[i] = solutionLocation[i]->id;
		}
	}
	sort( solutionLocation.begin(), solutionLocation.end() );
	solutionLocation.erase( unique( solutionLocation.begin(), solutionLocation.end() ), solutionLocation.end() );

	// validation: checking words' surroundings
	Node* ptr3 = grid;
	Node* ptr2 = grid;
	Node* ptr4 = NULL;
	// while loops will go through the entire board
	// nodes will be unmarked in either case, valid or invalid
	while (ptr3 != NULL) { // incrementing rows
		while (ptr2 != NULL) { // incrementing columns

			if (ptr2->Across && ptr2->Down) {
				if (ptr2->down != NULL) {
					if (ptr2->down->Across && !ptr2->down->Down) {
						output.clear();
						unmarkNodes(grid);
						return false;
					}
				}
				if (ptr2->right != NULL) {
					if (!ptr2->right->Across && ptr2->right->Down) {
						output.clear();
						unmarkNodes(grid);
						return false;
					}
				}
			}

			if (ptr2->Across && !ptr2->Down) {
					// words below
					if (ptr2->down != NULL && (ptr2->down->Across || ptr2->down->Down)) {
						// creating "new a word"
						output.clear();
						unmarkNodes(grid);
						return false;
					}
					// words on the right
					if (ptr2->right != NULL) {
						if (find(solutionLocation.begin(), \
						solutionLocation.end(), ptr2->right) != solutionLocation.end()) {
							// next to a beginning of another word
							for (size_t i = 0; i < ptr2->right->directions.size(); i++) {
								if (ptr2->right->directions[i] == 'h') {
									// words in line and connected
									output.clear();
									unmarkNodes(grid);
									return false;
								}
							}
						}
						if (ptr2->right->Down && !ptr2->right->Across) {
							// Across word next to a down word, no intersection
							output.clear();
							unmarkNodes(grid);
							return false;
						}
					}
				}

			if (!ptr2->Across && ptr2->Down) {
					// words on the right
					if (ptr2->right != NULL && (ptr2->right->Across || ptr2->right->Down)) {
						output.clear();
						unmarkNodes(grid);
						return false;
					}
					// words below
					if (ptr2->down != NULL) {
						if (find(solutionLocation.begin(), \
						solutionLocation.end(), ptr2->down) != solutionLocation.end()) {
							// words below is a new word
							for (size_t i = 0; i < ptr2->down->directions.size(); i++) {
								if (ptr2->down->directions[i] == 'd') {
									// words in one column, connected
									output.clear();
									unmarkNodes(grid);
									return false;
								}
							}
						}
						if (ptr2->down->Across && !ptr2->down->Down) {
							// words "turn"
							output.clear();
							unmarkNodes(grid);
							return false;
						}
					}
				}

			if (ptr2->Across || ptr2->Down) {
				// output this word's character if it's marked, otherwise NULL
				if (finalOutput)
					output.push_back(ptr2);
			} else {
				if (finalOutput)
					output.push_back(ptr4);
			}

			ptr2 = ptr2->right;
		}
		ptr3 = ptr3->down;
		ptr2 = ptr3;
	}

	unmarkNodes(grid);
	return true;
}

void push_B_to_A(vector<Node*> &a, vector<Node*> &b) {
	// push all elements of b to a
  for (size_t i = 0; i < b.size(); i++) {
    a.push_back(b[i]);
  }
}

void push_B_to_A_2(vector< vector<Node*> > &a, vector< vector<Node*> > b) {
	// push all elements of b to a
  for (size_t i = 0; i < b.size(); i++) {
    a.push_back(b[i]);
  }
}

void combination(vector<Node*> &words, int n, int m, vector<int> &constraints_, \
	const int M, vector<Node*> &container, vector< vector<Node*> > &combinations, \
	Node* grid, vector<Node*> &output) {
	// make combinations using given constraints and words found in the puzzle
  for(int i=n; i>=m; i--) {
    constraints_[m-1] = i - 1;
    if (m > 1)
      combination(words, i-1, m-1, constraints_, M, container, combinations, \
				grid, output);
    else { // m == 1
      for(int j=M-1; j>=0; j--)
        container.push_back(words[constraints_[j]]);
			if (checkSolution(grid, container, false, output)) {
				// words in container will be pushed back only if they are combined valid
				combinations.push_back(container);
			}
			container.clear();
    }
  }
}

void combinations_make_solutions(Node* grid, vector<vector<Node*> > &solutions, \
	vector<vector<vector<Node*> > > &allCombo, int i, vector<Node*> accum, \
	vector<Node*> &output) {
	// using the combinations made to find solutions
	if (i == allCombo.size()) {
		solutions.push_back(accum);
	}
	else {
		for (size_t j = 0; j < allCombo[i].size(); j++) {
			vector<Node*> tmp(accum);
			push_B_to_A(tmp, allCombo[i][j]);
			if (checkSolution(grid, tmp, false, output)) {
				// this branch of recursions will terminate if combination created is alread invalid for puzzle
				combinations_make_solutions(grid, solutions, allCombo, i+1, tmp, output);
			}
		}
	}
}

void findSolutions(Node* &grid, const vector<Node*> &words, \
	vector<int> constraints, vector< vector<Node*> > &solutions) {

	vector<Node*> output;
	unsigned int sum = 0;
	for (size_t i = 0; i < constraints.size(); i++) {
		sum += constraints[i];
	}

  // if number of words found in puzzle equals to the total of constrains
	if (sum == words.size()) {
		if (checkSolution(grid, words, true, output))
			solutions.push_back(output);
		return;
	}

  // number of words found less than constraints
  else if (sum > words.size()) {
    return;
  }

  // number of words found more than constraints
  vector<Node*> tmp;
  vector<Node*> container;
  vector<Node*> commonWords; // common words in all all solutions
  vector< vector<Node*> > comboOneConstraintLen; // combinations of one constraint length

  // structure: {combinations of all constraints
  //							[combinations of one constraint
  //								(one combination of one constraint length)]}
  vector<vector<vector<Node*> > > allCombinations;

  for (size_t i = 3; i < constraints.size(); i++) {
    // constraints[3] is the number of constraints of word length 3
    if (constraints[i] == 0)
      continue;

    // first put all the words of length of i into vector tmp
    for (size_t j = 0; j < words.size(); j++) {
      if (words[j]->solutionLength.size() == 1) {
        if (words[j]->solutionLength[0] == i) {
          tmp.push_back(words[j]);
        }
      }
      else if (words[j]->id->solutionLength[words[j]->index] == i) {
        tmp.push_back(words[j]);
      }
    }


    // do some checking and make combinations
    if (tmp.size() < constraints[i]) {
      // not enough words for the number of constraints
      return; // no solution
    }
    else if (tmp.size() == constraints[i]) {
      // exact number of words for that length of constraints
      for (size_t l = 0; l < tmp.size(); l++) {
        commonWords.push_back(tmp[l]);
      }
    }
    else {
      // more words than constraints
      vector<int> indexes(constraints[i], 0);
      combination(tmp, tmp.size(), constraints[i], indexes, constraints[i], \
        container, comboOneConstraintLen, grid, output);
			allCombinations.push_back(comboOneConstraintLen);

      container.clear();
      comboOneConstraintLen.clear();
      indexes.clear();
    }

    tmp.clear();
  }

	// first check the common set of words
	if (!checkSolution(grid, commonWords, false, output)) {
		return; // no solution, conflict in common words set
	}
  comboOneConstraintLen.push_back(commonWords);
  allCombinations.push_back(comboOneConstraintLen);

	vector< vector<Node*> > solutions_temp;
	vector<Node*> oneSolution;
	combinations_make_solutions(grid, solutions, allCombinations, 0, oneSolution, \
	output);

	output.clear();
	for (size_t i = 0; i < solutions.size(); i++) {
		if (checkSolution(grid, solutions[i], true, output)) {
			solutions_temp.push_back(output);
			output.clear();
		}
	}
	solutions = solutions_temp;
}

void printOutput(vector< vector<Node*> > &solutions, int height, int width, \
string solution_mode, string output_mode) {

	int num;
	if (solutions.size() > 0) {
		if (solution_mode == "one_solution")
			num = 1;
		else
			num = solutions.size();
	} else {
		num = 0;
	}
	std::cout << "Number of solution(s): " << num << '\n';

	if (output_mode == "count_only") {
		return;
	}

	for (size_t k = 0; k < num; k++) {
		std::cout << "Board:" << '\n';
		for (size_t i = 0; i < solutions[k].size(); i++) {
			if (solutions[k][i] == NULL) {
				std::cout << "#";
			} else {
				std::cout << solutions[k][i]->value;
			}
			if (i > 0 && (i+1) % width == 0) {
				std::cout << '\n';
			}
		}
	}

}

void clearHeap(Node* &grid, int height, int width, vector<Node*> &idPointers) {
	Node* tmp;
	for (int i = 0; i < height; i++) {
	  for (int j = 0; j < width; j++) {
	    tmp = grid;
	    if (i % 2 == 0) {
	      if (j == width - 1) {
	        grid = grid -> down;
	        delete tmp;
	        continue;
	      }
	      grid = grid -> right;
	    }
	    else {
	      if (j == width - 1) {
	        grid = grid -> down;
	        delete tmp;
	        continue;
	      }
	      grid = grid -> left;
	    }
	    if (tmp->id != NULL)
	      delete tmp->id;
	    delete tmp;
	  }
	}

	for (int i = idPointers.size()-1; i >= 0; i--) {
		idPointers[i]->id = NULL; // avoid freeing freed memory
		delete idPointers[i];
	}
}

// some functions for debugging
void debuggPrintInitializations(Node* ptr, vector < vector<char> >puzzle, \
	vector<int> constraints, vector<string> dictionary) {
	std::cout << "Puzzle: " << '\n';
  for (size_t i = 0; i < puzzle.size(); i++) {
    if (i != 0) {
      ptr = ptr->down;
    }
    Node* a = ptr;
    for (size_t j = 0; j < puzzle[0].size(); j++) {
      if (j != 0) {
        a = a->right;
      }
      std::cout << a->value;
    }
    std::cout << '\n';
  }

	std::cout << endl << "Constraints: " << '\n';
	for (size_t i = 0; i < constraints.size(); i++) {
		std::cout << constraints[i] << '\n';
	}

	std::cout << endl << "Dictionary: " << dictionary.size() << " words" << '\n';
	for (size_t i = 0; i < dictionary.size(); i++) {
		std::cout << dictionary[i] << '\n';
	}
	std::cout << '\n';
}
void debuggPrintWords(const vector<Node*> &words) {
	Node* ptr;
	std::cout << "Words found in puzzle: " << words.size() << '\n';
	for (size_t i = 0; i < words.size(); i++) {
		ptr = words[i];
		if (words[i]->solutionLength.size() == 1) {
			for (int j = 0; j < words[i]->solutionLength[0]; j++) {
				std::cout << ptr->value;
				if (words[i]->directions[0] == 'h')
					ptr = ptr->right;
				else
					ptr = ptr->down;
			} std::cout << '\n';
		}
		else {
			ptr = words[i]->id;

			for (int j = 0; j < words[i]->id->solutionLength[words[i]->index]; j++) {
				std::cout << ptr->value;
				if (words[i]->id->directions[words[i]->index] == 'h')
					ptr = ptr->right;
				else
					ptr = ptr->down;
			} std::cout << '\n';
		}
	}
}

int main(int argc, char* argv[]) {
  ifstream dictFile(argv[1]);
  ifstream gridFile(argv[2]);
  istringstream solutionMode(argv[3]);
  istringstream outputMode(argv[4]);
	string solution_mode, output_mode;
	solutionMode >> solution_mode;
	outputMode >> output_mode;

	if (!dictFile.good()) {
		std::cerr << "Cannot open the dictionary file" << '\n';
		return 0;
	}
	if (!gridFile.good()) {
		std::cerr << "Cannot open the dictionary file" << '\n';
		return 0;
	}

	if (solution_mode != "one_solution" && solution_mode != "all_solutions") {
		std::cerr << "Wrong solution mode" << '\n';
		return 0;
	}
	if (output_mode != "count_only" && output_mode != "print_boards") {
		std::cerr << "Wrong output mode" << '\n';
		return 0;
	}

  vector<string> dictionary;
  readDict(dictFile, dictionary);

  vector < vector<char> > puzzle;
  Node* grid = new Node();
  vector<int> constraints;
  readPuzzle(gridFile, puzzle, constraints);
	constructGrid(puzzle, grid);
	// debuggPrintInitializations(grid, puzzle, constraints, dictionary);

	vector<Node*> words;
	string str = "";
	findWords(grid, dictionary, constraints, words, \
		str, grid, grid, grid, true);
	vector<Node*> idPointers;
	identifyDuplicates(words, idPointers);
	// debuggPrintWords(words);

	vector< vector<Node*> > solutions;
	findSolutions(grid, words, constraints, solutions);
	printOutput(solutions, puzzle.size(), puzzle[0].size(), \
		solution_mode, output_mode);

	clearHeap(grid, puzzle.size(), puzzle[0].size(), idPointers);
}
