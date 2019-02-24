#include <typeinfo>

template <class T>
class Table {

public:
  // CONSTRUCTORS, ASSIGNMNENT OPERATOR, & DESTRUCTOR
  Table() { this->create(); }
  Table(unsigned int rowNum, unsigned int colNum, T val) { this->create(rowNum, colNum, val); }
  Table(const Table& v) { copy(v); }
  Table& operator=(const Table& v);
  ~Table();

  // ACCESSORS
	T get(unsigned int row, unsigned int col) const;
  unsigned int numRows() const { return rows; }
  unsigned int numColumns() const { return cols; }
  void print() const;

  // MODIFIERS
	void set(unsigned int row, unsigned int col, T newValue);
	void push_back_row(std::vector<T> v);
	void push_back_column(std::vector<T> v);
	void pop_back_row();
	void pop_back_column();

  void push_back_rows(Table<T>& v);
  void push_back_columns(Table<T>& v);

private:
  // PRIVATE MEMBER FUNCTIONS
  void create();
  void create(unsigned int rowNum, unsigned int colNum, const T& val);
  void copy(const Table<T>& v);

  // REPRESENTATION
  T** table; // Pointer to first location in the allocated table 2D array
	unsigned int rows, cols; // Numbers of rows and columns
};

// Create an empty table.
template <class T>
void Table<T>::create() {
  // No memory allocated yet
  table = NULL;
  rows = cols = 0;
}

// Create a table and assign initial value to each location
template <class T>
void Table<T>::create(unsigned int rowNum, unsigned int colNum, const T& val) {
  rows = rowNum;
  cols = colNum;
  table = new T *[rowNum];
  for (size_t i = 0; i < rowNum; i++) {
    table[i] = new T [colNum];
    for (size_t j = 0; j < colNum; j++) {
      table[i][j] = val;
    }
  }
}

// Create the table as a copy of the given table
template <class T>
void Table<T>::copy(const Table<T>& v) {
  // Some values assignments for memeber variables
  this -> rows = v.rows;
  this -> cols = v.cols;
  // Create a table of same size
  this -> table = new T *[this -> rows];
  for (size_t i = 0; i < this -> rows; i++) {
    this -> table[i] = new T[cols];
  }
  // Copy the data in the table
  for (size_t i = 0; i < this -> rows; i++) {
    for (size_t j = 0; j < this -> cols; j++) {
      this -> table[i][j] = v.get(i, j);
    }
  }
}

// Assign one table to another, avoiding duplicate copying
template <class T>
Table<T>& Table<T>::operator=(const Table<T>& v) {
  if (this != &v) { // Copy if it's not = to itself
    this -> ~Table();
    this -> copy(v);
  }
  return *this;
}

template <class T>
Table<T>::~Table() {
  // delete the 2D array
  for (size_t i = 0; i < rows; i++) {
    delete [] table[i];
  }
  delete [] table;
}

template <class T>
T Table<T>::get(unsigned int row, unsigned int col) const {
  // This function gets the value of a specific location in the table
  if (row < rows && col < cols) {
    return table[row][col];
  } else {
    std::cerr << "Error: Trying to get the value of (" << row << ", " << col << \
     "), but it is outside of the table." << std::endl;
    exit(1);
  }
}

template <class T>
void Table<T>::print() const {
  // This function prints the information of the table
  std::cout << "table: " << rows << " rows, " << cols  << " cols" << '\n';
  for (size_t i = 0; i < rows; i++) {
    for (size_t j = 0; j < cols; j++) {
      std::cout << table[i][j] << ' ';
    }
    std::cout << '\n';
  }
  std::cout << std::endl;
}

template <class T>
void Table<T>::set(unsigned int row, unsigned int col, T newValue) {
  // This function sets a new value to a location in the table
  if (row >= rows || col >= cols) {
    if (typeid(newValue) != typeid(table[row][col])) {
      std::cerr << "Error: Trying to set a value of incorrect type in the table." << std::endl;
      return;
    }
    std::cerr << "Error: Trying to get the value of (" << row << ", " << col << \
     "), but is outside of the table." << std::endl;
    return;
  }
  table[row][col] = newValue;
}

template <class T>
void copyTableData(T** &tOld, T** &tNew, int rowNum, int colNum) {
  // Helper function copies table data from table [0, 0] to [rowNum-1, colNum-1]
  for (size_t i = 0; i < rowNum; i++) {
    for (size_t j = 0; j < colNum; j++) {
      tNew[i][j] = tOld[i][j];
    }
  }
}

template <class T>
void Table<T>::push_back_row(std::vector<T> v) {
  // This function pushes back a new row to the table
  if (v.size() != cols && cols != 0) {
    // Size confirmed so this value can be used below
    std::cerr << "Invalid Request: Incorrect size of vector being pushed back to the table as a new row." << std::endl;
    return;
  }

  // New table for the new size
  T** newTable = new T *[rows+1];
  for (size_t i = 0; i < rows+1; i++) {
    newTable[i] = new T [v.size()]; // "v.size()" ready for empty table cases, same applied below
  }

  // Copy needed existing data
  copyTableData(table, newTable, rows, cols);

  // Put in the new row
  for (size_t i = 0; i < v.size(); i++) {
    newTable[rows][i] = v[i];
  }

  // Finish up and set variables to correct values
  this -> ~Table();
  table = newTable;
  rows++;
  // if started with empty table, cols should be changed
  if (cols == 0) { cols = v.size(); }
}

template <class T>
void Table<T>::push_back_column(std::vector<T> v) {
  // This function pushes back a new column to the table
  if (v.size() != rows && rows != 0) {
    // Size confirmed so this value can be used below
    std::cerr << "Invalid Request: Incorrect size of vector being pushed back to the table as a new column." << std::endl;
    return;
  }

  // New table for the new size
  T** newTable = new T *[v.size()];
  for (size_t i = 0; i < v.size(); i++) {
    newTable[i] = new T [cols+1];
    newTable[i][cols] = v[i];
  }

  // Copy needed existing data
  copyTableData(table, newTable, rows, cols);

  // Set variables to correct values.
  this -> ~Table();
  table = newTable;
  cols++;
  // if started with empty table, rows should be changed
  if (rows == 0) { rows = v.size(); }
}

template <class T>
void Table<T>::pop_back_row() {
  // This function pops the last row of the table
  if (rows == 0) {
    std::cerr << "Invalid Request: Cannot pop a row from an empty table." << std::endl;
    return;
  }
  if (rows == 1) { // if it's the last row left, reset table.
    this -> ~Table();
    table = new T *[0];
    rows = 0;
    cols = 0;
  } else {
  // New table for the new size
  T** newTable = new T *[rows-1];
  for (size_t i = 0; i < rows-1; i++) {
    newTable[i] = new T [cols];
  }
  // Copy needed existing data
  copyTableData(table, newTable, rows-1, cols);
  // Set variables to correct values
  this -> ~Table();
  table = newTable;
  rows--;
  }
}

template <class T>
void Table<T>::pop_back_column() {
  // This function pops the last column of the table
  if (cols == 0) {
    std::cerr << "Invalid Request: Cannot pop a column from an empty table." << std::endl;
    return;
  }
  if (cols == 1) { // if it's the last column left, reset table.
    this -> ~Table();
    table = new T *[0];
    cols = 0;
    rows = 0;
  } else {
  // New table for the new size
  T** newTable = new T *[rows];
  for (size_t i = 0; i < rows; i++) {
      newTable[i] = new T [cols-1];
  }
  // Copy needed existing data
  copyTableData(table, newTable, rows, cols-1);
  // Finish up and set variables to correct values.
  this -> ~Table();
  table = newTable;
  cols--;
  }
}

// Extra credit work
template <class T>
void Table<T>::push_back_rows(Table<T>& v) {
  // This function pushes back new rows to the table from another table
  if (cols != v.numColumns() && cols != 0) {
    std::cerr << "Invalid Request: Unmatched column number for push back rows." << std::endl;
  }
  T** newTable = new T *[rows+v.numRows()];
  for (size_t i = 0; i < rows+v.numRows(); i++) {
    // newTable[i] = new T [cols];
    *(newTable+i) = new T [v.numColumns()];
  }
  copyTableData(table, newTable, rows, cols);
  for (size_t i = 0; i < v.numRows(); i++) {
    for (size_t j = 0; j < v.numColumns(); j++) {
      // newTable[i+rows][j] = v.get(i, j);
      *(*(newTable+i+rows)+j) = v.get(i, j);
    }
  }
  this -> ~Table();
  table = newTable;
  rows += v.numRows();
  if (cols == 0) { cols = v.numColumns(); }
}

template <class T>
void Table<T>::push_back_columns(Table<T>& v) {
  // This function pushes back a new columns to the table from another table
  if (rows != v.numRows() && rows != 0) {
    std::cerr << "Invalid Request: Unmatched row number for push back columns." << std::endl;
  }
  T** newTable = new T *[v.numRows()];
  for (size_t i = 0; i < v.numRows(); i++) {
    // newTable[i] = new T [cols+v.numColumns()];
    *(newTable+i) = new T [cols+v.numColumns()];
    for (size_t j = 0; j < v.numColumns(); j++) {
      // newTable[i][j+cols] = v.get(i, j);
      *(*(newTable+i)+j+cols) = v.get(i, j);
    }
  }
  copyTableData(table, newTable, rows, cols);
  this -> ~Table();
  table = newTable;
  cols += v.numColumns();
  if (rows == 0) { rows = v.numRows(); }
}
