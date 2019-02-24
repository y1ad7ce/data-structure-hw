// =======================================================
//
// IMPORTANT NOTE: Do not modify this file
//     (except to uncomment the provided test cases
//     and add your test cases where specified)
//
// =======================================================

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cassert>
#include <vector>
#include "table.h"


// helper testing functions
void SimpleTest();
void StudentTests();
void BatchTest(const char* filename, int num);
void ExtraCreditTests();


int main(int argc, char* argv[]) {
  if (argc == 1) {
    SimpleTest();
     std::cout << "Simple test completed." << std::endl;
    StudentTests();
    std::cout << "Student tests completed." << std::endl;

    //
    // uncomment if you have implemented the extra credit features
    //
    ExtraCreditTests();
    //

 } else {
    if (argc != 3) {
      std::cerr << "Usage: " << argv[0] << " <filename> <num_iters>" << std::endl;
      exit(1);
    }
    BatchTest(argv[1],atoi(argv[2]));
    std::cout << "Batch test completed." << std::endl;
  }
}



void SimpleTest() {

  // create a table with dimensions 2x5, where all entries are '.'
  Table<char> t(2,5,'.');
  assert (t.get(0,0) == '.');
  assert (t.get(1,4) == '.');
  assert (t.get(1,2) == '.');
  assert (t.numRows() == 2);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "constructor test completed" << std::endl;

  // intialize the values in the table
  t.set(0,0,'a');
  t.set(0,1,'b');
  t.set(0,2,'c');
  t.set(0,3,'d');
  t.set(0,4,'e');
  t.set(1,0,'f');
  t.set(1,1,'g');
  t.set(1,2,'h');
  t.set(1,3,'i');
  t.set(1,4,'j');
  assert (t.get(0,0) == 'a');
  assert (t.get(1,2) == 'h');
  assert (t.get(1,4) == 'j');
  t.print();
  std::cout << "set & get tests completed" << std::endl;

  // =======================================================
  //
  //     UNCOMMENT THE SECTIONS BELOW AS YOU
  //        COMPLETE THE IMPLEMENTATION
  //
  // =======================================================


  // add a row
  std::vector<char> new_row;
  new_row.push_back('A');
  new_row.push_back('B');
  new_row.push_back('C');
  new_row.push_back('D');
  new_row.push_back('E');
  t.push_back_row(new_row);
  assert (t.numRows() == 3);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "add row test completed" << std::endl;



  // remove a column
  t.pop_back_column();
  assert (t.numRows() == 3);
  assert (t.numColumns() == 4);
  t.print();
  std::cout << "remove column test completed" << std::endl;



  // add a column
  std::vector<char> new_col;
  new_col.push_back('X');
  new_col.push_back('Y');
  new_col.push_back('Z');
  t.push_back_column(new_col);
  assert (t.numRows() == 3);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "add column test completed" << std::endl;



  // remove a row
  t.pop_back_row();
  assert (t.numRows() == 2);
  assert (t.numColumns() == 5);
  t.print();
  std::cout << "remove row test completed" << std::endl;



  // example of the copy constructor
  Table<char> another(t);
  // the structures initially look the same
  assert (t.numRows() == another.numRows());
  assert (t.numColumns() == another.numColumns());
  for (unsigned  i = 0; i < t.numRows(); i++) {
    for (unsigned  j = 0; j < t.numColumns(); j++) {
      assert (t.get(i,j) == another.get(i,j));
    }
  }
  // but future edits show they are different!
  another.set(1,2,'Q');
  assert (t.get(1,2) != another.get(1,2));
  std::vector<char> new_row2;
  new_row2.push_back('A');
  new_row2.push_back('B');
  new_row2.push_back('C');
  new_row2.push_back('D');
  new_row2.push_back('E');
  another.push_back_row(new_row2);
  assert (t.numRows()+1 == another.numRows());
  assert (t.numColumns() == another.numColumns());
  t.print();
  another.print();
  std::cout << "copy constructor test completed" << std::endl;

  // example of the assignment operator
  t = another;
  // again the structures look the same
  assert (t.numRows() == another.numRows());
  assert (t.numColumns() == another.numColumns());
  for (unsigned  i = 0; i < t.numRows(); i++) {
    for (unsigned  j = 0; j < t.numColumns(); j++) {
      assert (t.get(i,j) == another.get(i,j));
    }
  }
  std::cout << "assignment operator test completed" << std::endl;


  // Note: The Table destructor is implicitly called for the
  //   stack-allocated variables 't' and 'another' when we leave the
  //   function and it goes out of scope.

}

void StudentTests() {

  // =======================================================
  //
  // YOU SHOULD ADD YOUR OWN TEST CASES HERE
  //
  // be sure to rigorously test:
  //   * tables that store types other than char
  //   * copy constructor
  //   * assignment operator
  //   * destructor
  //   * invalid requests (comment out for final submission)
  //
  // =======================================================
  Table<double> x(4,7,3.14);
  std::cout << "\n(4, 7) table x of double value 3.14 has been created.\n";
  assert (x.numRows() == 4);
  assert (x.numColumns() == 7);
  x.print();

  std::cout << "\nTrying to set (1,2) to 1.22 and (3,5) to 3.58:\n";
  x.set(1,2,1.22);
  x.set(3,5,3.58);
  assert (x.get(1,2) == 1.22);
  assert (x.get(3,5) == 3.58);
  x.print();


  std::cout << "\nSome error test results should show below: \n";
  std::cout << "Trying to set values of the location outsdie the table.\n";
  x.set(4,7,4.21); // ERROR
  x.set(7,5,4.51); // ERROR
  x.print();

  Table<double> y(x);
  assert (x.numRows() == y.numRows());
  assert (x.numColumns() == y.numColumns());
  for (unsigned  i = 0; i < x.numRows(); i++) {
    for (unsigned  j = 0; j < x.numColumns(); j++) {
      assert (x.get(i,j) == y.get(i,j));
    }
  }
  std::cout << "Table y created by copy constructor and values confirmed:\n";
  y.print();

  y.pop_back_row();
  y.pop_back_row();
  y.pop_back_row();
  y.pop_back_row();
  std::cout << "All rows in table y removed using pop back row." << '\n';
  y.print();
  std::cout << "And try pop back row once more." << '\n';
  y.pop_back_row();
  y.print();

  Table<double> z;
  z = y;
  std::cout << "Table z created and assigned values of y." << '\n';
  assert (z.numRows() == y.numRows());
  assert (z.numColumns() == y.numColumns());
  z.print();

  z = x;
  assert (x.numRows() == z.numRows());
  assert (x.numColumns() == z.numColumns());
  for (unsigned  i = 0; i < x.numRows(); i++) {
    for (unsigned  j = 0; j < x.numColumns(); j++) {
      assert (x.get(i,j) == z.get(i,j));
    }
  }
  std::cout << "Set z equals to x. Values confirmed correct." << '\n';
  z.print();

  z.pop_back_column();
  z.pop_back_column();
  z.pop_back_column();
  z.pop_back_column();
  z.pop_back_column();
  z.pop_back_column();
  z.pop_back_column();
  assert (z.numRows() == 0);
  assert (z.numColumns() == 0);
  std::cout << "All columns in z removed using pop back column." << '\n';
  z.print();

  std::cout << "And try pop back column once more." << '\n';
  y.pop_back_column();
  y.print();

  std::vector<double> container;
  for (size_t i = 0; i < 5; i++) {
    container.push_back(3.14*i);
  }
  std::cout << "Container vector created:" << '\n';
  std::cout << "Container ---> {";
  for (size_t i = 0; i < container.size(); i++) {
    std::cout << container[i]; if (i != container.size()-1) std::cout << ", ";
  }
  std::cout << "}" << '\n';
  std::cout << "As of now, x contains some values, and y and z are empty.\n\n";

  z.push_back_row(container);
  z.push_back_row(container);
  z.push_back_row(container);
  std::cout << "Rows pushed back to an empty table z:" << '\n';
  z.print();
  assert (z.get(0,0) == 0);
  assert (z.get(0,1) == 3.14);
  assert (z.get(1,0) == 0);
  assert (z.get(1,4) == 12.56);
  assert (z.get(2,1) == 3.14);
  assert (z.get(2,2) == 6.28);
  assert (z.get(2,3) == 9.42);
  std::cout << "Confirmed values added correctly.\n";
  z.print();

  std::cout << "Try keep adding rows until number of rows equals to number of columns." << '\n';
  z.push_back_row(container);
  z.push_back_row(container);
  assert (z.numRows() == z.numColumns());
  z.print();

  std::cout << "Now we can try to add the vector as column. Format may not be perfect." << '\n';
  z.push_back_column(container);
  z.push_back_column(container);
  z.push_back_column(container);
  assert (z.get(0,0) == 0);
  assert (z.get(0,1) == 3.14);
  assert (z.get(0,7) == 0);
  assert (z.get(1,4) == 12.56);
  assert (z.get(2,6) == 6.28);
  assert (z.get(3,6) == 9.42);
  assert (z.get(4,5) == 12.56);
  std::cout << "Columns added correctly." << '\n';
  z.print();

  z = y;
  assert (z.numRows() == 0);
  assert (z.numColumns() == 0);
  std::cout << "Reset table z and make it equal to y, an empty table." << '\n';
  z.print();

  std::cout << "This time, same process, push back column first then row." << '\n';
  z.push_back_column(container);
  z.push_back_column(container);
  z.push_back_column(container);
  z.push_back_column(container);
  z.push_back_column(container);
  std::cout << "First add 5 columns to the empty table." << '\n';
  z.print();

  z.push_back_row(container);
  z.push_back_row(container);
  z.push_back_row(container);
  std::cout << "Then add 3 rows to it." << '\n';
  assert (z.get(0,0) == 0);
  assert (z.get(1,1) == 3.14);
  assert (z.get(3,0) == 9.42);
  assert (z.get(4,2) == 12.56);
  assert (z.get(5,2) == 6.28);
  assert (z.get(6,3) == 9.42);
  assert (z.get(7,4) == 12.56);
  std::cout << "Values confirmed." << '\n';
  z.print();

  std::cout << "Now let's test push back rows and columns:" << '\n';

  std::cout << "First start with a table with values, x." << '\n';
  x.print();

  std::cout << "Pop two columns so we can add it to z as rows." << '\n';
  x.pop_back_column();
  x.pop_back_column();
  x.print();

  z.push_back_rows(x);
  assert (z.get(7,4) == 12.56);
  assert (z.get(11,4) == 3.14);
  assert (z.get(9,2) == 1.22);
  std::cout << "Push back rows done correctly" << '\n';
  z.print();

  std::cout << "x hasn't changed: " << '\n';
  x.print();

  y = x;
  assert (y.get(1,2) == 1.22);
  assert (y.get(2,2) == 3.14);
  std::cout << "table y: " << '\n';
  y.print();

  std::cout << "x's values assigned to y, now let's test push back columns." << '\n';
  std::cout << "Make x's values same as z, then push back columns: " << '\n';
  x = z;
  std::cout << "table x: " << '\n';
  x.print();
  std::cout << "table z: " << '\n';
  z.print();

  z.push_back_columns(x);
  assert (z.get(9,2) == 1.22);
  assert (z.get(9,7) == 1.22);
  std::cout << "Push back columns works." << '\n';
  z.print();

  std::cout << "x hasn't changed: " << '\n';
  x.print();

  x.pop_back_column();
  x.pop_back_column();
  x.pop_back_column();
  x.pop_back_column();
  x.pop_back_column();

  std::cout << "x is now an empty table, all columns removed." << '\n';
  assert (x.numRows() == 0);
  assert (x.numColumns() == 0);
  x.print();

  std::cout << "y now looks like this: " << '\n';
  y.print();

  std::cout << "Test for push back rows columns for empty table." << '\n';
  std::cout << "Push back rows from y." << '\n';
  x.push_back_rows(y);
  assert (x.get(1,2) == 1.22);
  std::cout << "Push back rows for empty table works." << '\n';
  x.print();

  x.pop_back_row();
  x.pop_back_row();
  x.pop_back_row();
  x.pop_back_row();
  assert (x.numRows() == 0);
  assert (x.numColumns() == 0);
  std::cout << "x cleared by pop back row. Next, try push back columns. Note that some values in y will change." << '\n';
  x.print();

  y.set(2,1,9.98);
  x.push_back_columns(y);
  assert (x.get(1,2) == 1.22);
  assert (x.get(2,1) == 9.98);
  std::cout << "Values confirmed correct." << '\n';
  x.print();
}


void ExtraCreditTests() {

  // =======================================================
  //
  //            UNCOMMENT THIS SECTION IF YOU
  //      COMPLETE THE EXTRA CREDIT IMPLEMENTATION
  //
  // =======================================================


  Table<char> x(2,5,'x');
  assert (x.numRows() == 2);
  assert (x.numColumns() == 5);
  x.set(0,0,'.');
  x.set(1,4,'X');
  x.print();

  Table<char> y(4,5,'y');
  y.set(0,0,'.');
  y.set(3,4,'Y');
  x.push_back_rows(y);
  assert (x.numRows() == 6);
  assert (x.numColumns() == 5);
  x.print();

  Table<char> z(6,2,'z');
  z.set(0,0,'.');
  z.set(5,1,'Z');
  x.push_back_columns(z);
  assert (x.numRows() == 6);
  assert (x.numColumns() == 7);
  x.print();

  assert (x.get(0,0) == '.');
  assert (x.get(1,0) == 'x');
  assert (x.get(0,1) == 'x');
  assert (x.get(1,4) == 'X');

  assert (x.get(2,0) == '.');
  assert (x.get(2,1) == 'y');
  assert (x.get(3,0) == 'y');
  assert (x.get(5,4) == 'Y');

  assert (x.get(0,5) == '.');
  assert (x.get(1,5) == 'z');
  assert (x.get(0,6) == 'z');
  assert (x.get(5,6) == 'Z');

  std::cout << "extra credit tests completed" << std::endl;

}



// Batch test will repeatedly load & process a file with Table
// operations.  If the program's working memory does not grow when the
// program is run many, many times on a large test case, the data
// structure is probably free of memory leaks.
void BatchTest(const char* filename, int iters) {

  if (iters <= 0) {
    std::cerr << "ERROR: iters should be > 0" << std::endl;
    exit(1);
  }

  while (iters > 0) {
    iters--;

    // open the file stream for reading
    std::ifstream istr(filename);
    if (!istr) {
      std::cerr << "ERROR: cannot open file " << filename << std::endl;
      exit(1);
    }

    std::string token;
    char c;
    int i,j,num;

    // create the initial table
    istr >> token >> i >> j >> c;
    assert (token == "create");
    // note: here we explicitly allocate memory for the Table object
    Table<char> *table = new Table<char>(i,j,c);

    // read in and perform various operations on the array
    while (istr >> token) {
      if (token == "set") {
        istr >> i >> j >> c;
        table->set(i,j,c);
      } else if (token == "get") {
        istr >> i >> j >> c;
        char c2 = table->get(i,j);
        assert (c == c2);
      } else if (token == "push_back_row") {
        istr >> num;
        std::vector<char> tmp(num);
        for (int i = 0; i < num; i++)
          istr >> tmp[i];
        table->push_back_row(tmp);
      } else if (token == "push_back_column") {
        istr >> num;
        std::vector<char> tmp(num);
        for (int i = 0; i < num; i++)
          istr >> tmp[i];
        table->push_back_column(tmp);
      } else if (token == "pop_back_row") {
        table->pop_back_row();
      } else if (token == "pop_back_column") {
        table->pop_back_column();
      } else {
        std::cerr << "ERROR: unknown token " << token << std::endl;
        exit(1);
      }
    }

    if (iters == 0)
      table->print();

    // Because the Table memory was allocated explicitly (using new)
    // we need to explicitly deallocate the memory (using delete)
    delete table;
  }
}
