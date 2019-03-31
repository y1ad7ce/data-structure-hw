//UPDATE 3/23/2019: Commented out version of Report in SAME used wrong parameters before.
/*
A Node class is required (see the provided one in Rope.h), must have
  weight, value, left, and right members.
  You can add other members.
The Rope class must have a constructor that takes a Node*
  and uses that Node* as a root.
The Rope class must also have a function, expose_root() to return a pointer to the root Node.
  (This is poor class design, but will be necessary for us to autograde your data structure.)
*/

#include <cassert>
#include <string>
#include "Rope.h"

void StudentTests();
bool SAME(const Rope& r, const std::string& s);
void BasicTests();
Node* IndexTestRope();
Node* ConcatTestRopeLeft();
Node* ConcatTestRopeRight();

Node* tree1();
Node* tree2();

int main(){
	BasicTests();
	std::cout << "***Basic tests passed." << std::endl;
	StudentTests();
	std::cout << "***Student tests passed." << std::endl;
	return 0;
}

void StudentTests(){
	/* ADD YOUR TESTS HERE
	 * MAKE SURE TO TEST FUNCTIONS THOROUGHLY
	 * CONSIDER CORNER CASES, ETC.
	 * THESE TESTS SHOULD NOT CAUSE A CRASH.
	 */
	// assert(0 && "STUDENT TESTS NOT YET WRITTEN!");

	std::cout << "Student tests begin" << '\n';

	std::cout << "Some split test with the tree given for basic test" << '\n';

	std::cout << '\n' << "lhs.split(1,rhs):" << '\n';
	Rope r4(IndexTestRope());
	std::string s4 = "Hello my name is Simon";
	Rope r5;
	std::string s5 = s4.substr(0,1);
	std::string s6 = s4.substr(1,21);
	r4.split(1,r5);
	r4.print_strings(std::cout);
	r5.print_strings(std::cout);
	// r4.print(std::cout);
	// r1.print(std::cout);
	assert(SAME(r4,s5));
	assert(SAME(r5,s6));

	std::cout << '\n' << "lhs.split(6,rhs):" << '\n';
	Rope r3(IndexTestRope());
	Rope r2;
	s5 = s4.substr(0,6);
	s6 = s4.substr(6,16);
	r3.split(6,r2);
	r3.print_strings(std::cout);
	r2.print_strings(std::cout);
	// r3.print(std::cout);
	// r1.print(std::cout);
	assert(SAME(r3,s5));
	assert(SAME(r2,s6));

	std::cout << '\n' << "lhs.split(7,rhs):" << '\n';
	Rope r1(IndexTestRope());
	Rope r0;
	s5 = s4.substr(0,7);
	s6 = s4.substr(7,15);
	r1.split(7,r0);
	r1.print_strings(std::cout);
	r0.print_strings(std::cout);
	// r1.print(std::cout);
	// r1.print(std::cout);
	assert(SAME(r1,s5));
	assert(SAME(r0,s6));
	std::cout << "***Split tests in hw8_split_solutions.pdf passed" << std::endl;


	std::cout << '\n' << "Custom split tests, uncomment prints to see tree structures: " << '\n';

	std::cout << "Test 1: string ---> HELLO THIS IS DATA STRUCTURE HW 8 TREE" << '\n';
	std::string s1 = "HELLO THIS IS DATA STRUCTURE HW 8 TREE";
	Rope r6(tree1());
	Rope r7;
	assert(SAME(r6,s1));

	r6.split(0,r7);
	std::string s2 = s1.substr(0,0);
	std::string s3 = s1.substr(0,38);
	// r6.print(std::cout);
	// r7.print(std::cout);
	r6.print_strings(std::cout);
	r7.print_strings(std::cout);
	assert(SAME(r6,s2));
	assert(SAME(r7,s3));

	Rope r8(tree1());
	Rope r9;
	r8.split(2,r9);
	s2 = s1.substr(0,2);
	s3 = s1.substr(2,36);
	// r8.print(std::cout);
	// r9.print(std::cout);
	r8.print_strings(std::cout);
	r9.print_strings(std::cout);
	assert(SAME(r8,s2));
	assert(SAME(r9,s3));

	Rope r10(tree1());
	Rope r11;
	r10.split(12,r11);
	s2 = s1.substr(0,12);
	s3 = s1.substr(12,26);
	// r10.print(std::cout);
	// r11.print(std::cout);
	r10.print_strings(std::cout);
	r11.print_strings(std::cout);
	assert(SAME(r10,s2));
	assert(SAME(r11,s3));

	Rope r12(tree1());
	Rope r13;
	r12.split(38,r13);
	s2 = s1.substr(0,38);
	s3 = s1.substr(38,0);
	// r12.print(std::cout);
	// r13.print(std::cout);
	r12.print_strings(std::cout);
	r13.print_strings(std::cout);
	assert(SAME(r12,s2));
	assert(SAME(r13,s3));

	Rope r16(tree1());
	Rope r17;
	r16.split(37,r17);
	s2 = s1.substr(0,37);
	s3 = s1.substr(37,1);
	// r16.print(std::cout);
	// r17.print(std::cout);
	r16.print_strings(std::cout);
	r17.print_strings(std::cout);
	assert(SAME(r16,s2));
	assert(SAME(r17,s3));

	// single node tree test
	std::cout << "Single node tree test: string ---> suprise" << '\n';
	std::string s00 = "suprise";
	Rope r14(tree2());
	Rope r15;

	assert(SAME(r14,s00));
	std::cout << "single node tree constructed" << '\n';

	r14.split(2,r15);
	std::string s01 = s00.substr(0,2);
	std::string s02 = s00.substr(2,5);
	// r14.print(std::cout);
	// r15.print(std::cout);
	r14.print_strings(std::cout);
	r15.print_strings(std::cout);
	assert(SAME(r14,s01));
	assert(SAME(r15,s02));
}

//Used to compare a string and a rope that should be the same.
//You can uncomment the .report assert to test report on the whole string
bool SAME(const Rope& r, const std::string& s){
	/*std::cout << "Comparing string \"" << s << "\" to Rope:" << std::endl;
	r.print(std::cout);*/
	// std::cout << "rope size: " << r.size() << '\n';
	// std::cout << "string size: " << (int)s.length() << '\n';
	assert(r.size() == (int)s.length() && "ERROR: ROPE SIZE DOES NOT MATCH STRING SIZE");
	char c;
	for(unsigned int i=0; i<s.size(); i++){
		// r.index(i,c);
		// std::cout << "1---> " << c << '\n';
		// std::cout << "2---> " << s[i] << '\n';
		assert(r.index(i,c) && c == s[i] && "MISMATCH BETWEEN A CHARACTER IN ROPE AND STRING USING INDEX");
	}
	/*
	std::string s2;
	assert(r.report(0,s.length()-1,s2) && s2 == s && "MISMATCH BETWEEN ROPE.REPORT(0,length-1) AND STRING");
	*/
	return true;
}

void BasicTests(){
	Rope r1(IndexTestRope());
	std::string s1 = "Hello my name is Simon";
	std::string rs1;

	r1.print(std::cout);
	r1.print_strings(std::cout);
	assert(SAME(r1,s1));
	std::cout << "***Index test passed." << std::endl;
	assert(r1.report(0,s1.length()-1,rs1) && rs1 == s1);
	std::cout << "***Basic report test passed." << std::endl;

	//Concat test
	Rope r2(ConcatTestRopeLeft());
	Rope r3(ConcatTestRopeRight());
	std::string s2 = "Hello my ";
	std::string s3 = "name i";

	assert(SAME(r2,s2));
	assert(SAME(r3,s3));
	std::cout << "***More index tests passed." << std::endl;

	r2.concat(r3);
	s2 += s3;
	assert(SAME(r2, s2));
	std::cout << "***Concatenation test passed" << std::endl;

	// Split test
	Rope r4(IndexTestRope()); //Wikipedia split @ 11
	std::string s4 = "Hello my name is Simon";
	Rope r5;
	std::string s5 = s4.substr(0,11);
	std::string s6 = s4.substr(11,11);
	r4.split(11,r5);
	r4.print_strings(std::cout);
	r5.print_strings(std::cout);
	assert(SAME(r4,s5));
	assert(SAME(r5,s6));
	std::cout << "***Split test passed" << std::endl;

	//Copy & Assignment tests
	Rope r9(IndexTestRope());
	Rope r10(r9);
	std::string rs2;
	assert(r10.expose_root() != r9.expose_root());
 	assert(r10.size() == r9.size());
	assert(r10.report(0,r10.size()-1,rs1) && r9.report(0,r9.size()-1,rs2) && rs1 == rs2);
	std::cout << "***Copy test passed" << std::endl;
	Rope r11;
	r11 = r9;
	assert(r11.expose_root() != r9.expose_root());
 	assert(r11.size() == r9.size());
	assert(r11.report(0,r11.size()-1,rs1) && r9.report(0,r9.size()-1,rs2) && rs1 == rs2);
	std::cout << "***Assignment test passed" << std::endl;
}

//Also used for split() test
Node* IndexTestRope(){
	Node* ret = new Node;
	ret->weight = 22;
	ret->left = new Node;
	ret->left->parent = ret;
	ret->left->weight = 9;
	ret->left->left = new Node;
	ret->left->left->parent = ret->left;
	ret->left->left->weight = 6;
	ret->left->right = new Node;
	ret->left->right->parent =	ret->left;
	ret->left->right->weight = 6;
	ret->left->left->left = new Node;
	ret->left->left->left->parent = ret->left->left;
	ret->left->left->left->weight = 6;
	ret->left->left->left->value = "Hello ";
	ret->left->left->right = new Node;
	ret->left->left->right->parent = ret->left->left;
	ret->left->left->right->weight = 3;
	ret->left->left->right->value = "my ";
	ret->left->right->left = new Node;
	ret->left->right->left->parent = ret->left->right;
	ret->left->right->left->weight = 2;
	ret->left->right->right = new Node;
	ret->left->right->right->parent = ret->left->right;
	ret->left->right->right->weight = 1;
	ret->left->right->left->left = new Node;
	ret->left->right->left->right = new Node;
	ret->left->right->left->left->parent = ret->left->right->left;
	ret->left->right->left->left->weight = 2;
	ret->left->right->left->left->value = "na";
	ret->left->right->left->right->parent = ret->left->right->left;
	ret->left->right->left->right->weight = 4;
	ret->left->right->left->right->value = "me i";
	ret->left->right->right->left = new Node;
	ret->left->right->right->left->parent = ret->left->right->right;
	ret->left->right->right->left->weight = 1;
	ret->left->right->right->left->value = "s";
	ret->left->right->right->right = new Node;
	ret->left->right->right->right->parent = ret->left->right->right;
	ret->left->right->right->right->weight = 6;
	ret->left->right->right->right->value = " Simon";
	return ret;
}

Node* ConcatTestRopeLeft(){
	Node* ret = new Node;
	ret->weight = 6;
	ret->left = new Node;
	ret->right = new Node;
	ret->left->parent = ret;
	ret->left->weight = 6;
	ret->left->value = "Hello ";
	ret->right->parent = ret;
	ret->right->weight = 3;
	ret->right->value = "my ";
	return ret;
}

Node* ConcatTestRopeRight(){
	Node* ret = new Node;
	ret->weight = 2;
	ret->left = new Node;
	ret->right = new Node;
	ret->left->parent = ret;
	ret->left->weight = 2;
	ret->left->value = "na";
	ret->right->parent = ret;
	ret->right->weight = 4;
	ret->right->value = "me i";
	return ret;
}

// my trees
Node* tree1() {

	Node* rootN = new Node();
	rootN->left = new Node();
	rootN->left->left = new Node();
	rootN->left->left->right = new Node();
	rootN->left->left->right->left = new Node();
	rootN->left->left->left = new Node();
	rootN->left->left->left->right = new Node();

	rootN->left->right = new Node();
	rootN->left->right->left = new Node();
	rootN->left->right->left->left = new Node();
	rootN->left->right->left->right = new Node();
	rootN->left->right->left->right->left = new Node();

	rootN->left->right->right = new Node();
	rootN->left->right->right->left = new Node();
	rootN->left->right->right->left->right = new Node();
	rootN->left->right->right->right = new Node();

	rootN->right = new Node();
	rootN->right->left = new Node();
	rootN->right->left->left = new Node();
	rootN->right->left->left->right = new Node();
	rootN->right->left->right = new Node();
	rootN->right->left->right->right = new Node();

	rootN->right->right = new Node();
	rootN->right->right->left = new Node();
	rootN->right->right->left->left = new Node();
	rootN->right->right->left->left->right = new Node();
	rootN->right->right->left->right = new Node();

	rootN->right->right->right = new Node();
	rootN->right->right->right->left = new Node();
	rootN->right->right->right->right = new Node();
	rootN->right->right->right->right->left = new Node();


	rootN->left->left->left->right->value = "HE";
	rootN->left->left->right->left->value = "LLO";

	rootN->left->right->left->left->value = " ";
	rootN->left->right->left->right->left->value = "THIS ";
	rootN->left->right->right->left->right->value = "I";
	rootN->left->right->right->right->value = "S ";

	rootN->right->left->left->right->value = "DATA ";
	rootN->right->left->right->right->value = "STRUCTURE";

	rootN->right->right->left->left->right->value = " HW";
	rootN->right->right->left->right->value = " 8";
	rootN->right->right->right->left->value = " TRE";
	rootN->right->right->right->right->left->value = "E";


	rootN->weight = 14;
	rootN->left->weight = 5;
	rootN->left->left->weight = 2;
	rootN->left->left->right->weight = 3;
	rootN->left->left->right->left->weight = 3;
	rootN->left->left->left->weight = 0;
	rootN->left->left->left->right->weight = 2;

	rootN->left->right->weight = 6;
	rootN->left->right->left->weight = 1;
	rootN->left->right->left->left->weight = 1;
	rootN->left->right->left->right->weight = 5;
	rootN->left->right->left->right->left->weight = 5;

	rootN->left->right->right->weight = 1;
	rootN->left->right->right->left->weight = 0;
	rootN->left->right->right->left->right->weight = 1;
	rootN->left->right->right->right->weight = 2;

	rootN->right->weight = 14;
	rootN->right->left->weight = 5;
	rootN->right->left->left->weight =0;
	rootN->right->left->left->right->weight =5;
	rootN->right->left->right->weight = 0;
	rootN->right->left->right->right->weight = 9;

	rootN->right->right->weight = 5;
	rootN->right->right->left->weight = 3;
	rootN->right->right->left->left->weight = 0;
	rootN->right->right->left->left->right->weight = 3;
	rootN->right->right->left->right->weight = 2;

	rootN->right->right->right->weight = 4;
	rootN->right->right->right->left->weight = 4;
	rootN->right->right->right->right->weight = 1;
	rootN->right->right->right->right->left->weight = 1;


	rootN->left->parent = rootN;
	rootN->left->left->parent = rootN->left;
	rootN->left->left->right->parent = rootN->left->left;
	rootN->left->left->right->left->parent = rootN->left->left->right;
	rootN->left->left->left->parent = rootN->left->left;
	rootN->left->left->left->right->parent = rootN->left->left->left;

	rootN->left->right->parent = rootN->left;
	rootN->left->right->left->parent = rootN->left->right;
	rootN->left->right->left->left->parent = rootN->left->right->left;
	rootN->left->right->left->right->parent = rootN->left->right->left;
	rootN->left->right->left->right->left->parent = rootN->left->right->left->right;

	rootN->left->right->right->parent = rootN->left->right;
	rootN->left->right->right->left->parent = rootN->left->right->right;
	rootN->left->right->right->left->right->parent = rootN->left->right->right->left;
	rootN->left->right->right->right->parent = rootN->left->right->right;

	rootN->right->parent = rootN;
	rootN->right->left->parent = rootN->right;
	rootN->right->left->left->parent = rootN->right->left;
	rootN->right->left->left->right->parent = rootN->right->left->left;
	rootN->right->left->right->parent = rootN->right->left;
	rootN->right->left->right->right->parent = rootN->right->left->right;

	rootN->right->right->parent = rootN->right;
	rootN->right->right->left->parent = rootN->right->right;
	rootN->right->right->left->left->parent = rootN->right->right->left;
	rootN->right->right->left->left->right->parent = rootN->right->right->left->left;
	rootN->right->right->left->right->parent = rootN->right->right->left;

	rootN->right->right->right->parent = rootN->right->right;
	rootN->right->right->right->left->parent = rootN->right->right->right;
	rootN->right->right->right->right->parent = rootN->right->right->right;
	rootN->right->right->right->right->left->parent = rootN->right->right->right->right;

	return rootN;
}

Node* tree2() {
	Node* rootN = new Node();
	rootN->weight = 7;
	rootN->value = "suprise";

	return rootN;
}
