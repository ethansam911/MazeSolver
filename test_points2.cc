// Do not change this file other than adding header files
// if needed.
// You can also comment parts of the functions, and uncomment
// as you add more functionality.
#include <points2.h>

#include <array> 
#include <iostream>
#include <string>
using namespace std;
using namespace teaching_project;

// Place stand-alone function in unnamed namespace.
namespace {
void TestPart1() {
	
    Points2<int> a, b;  // Two empty Points2 are created.
    cout << a.size() << " " << b.size() <<endl; // yields 0 0.
    const array<int, 2> a_point2{{7, 10}};
    Points2<int> d{a_point2};  // A Points2 containing (7, 10) should be created.
    cout << d << endl; // Should just print (7, 10).
    cout << "Enter a sequence of points (integer)" << "\n\n"; 
    a.ReadPoints2(); // User enters a set of points in the form:
                     // 3 7 4 3 2 1 10
                     // 3 specifies number of points. Points are the pairs
                     // (7, 4) (3, 2) and (1, 10).
    cout << "Output1: " << "\n";
    cout << a << endl;// Output should be what user entered.
    cout << "Enter a sequence of points (integer)" << "\n\n";
    b.ReadPoints2();  // Enter another sequence.
    cout << "Output2: " << endl; 
    cout << b << endl;               
    Points2<int> c{a};  // Calls copy constructor for c.
    cout << "After copy constructor1 c{a}: " << endl;
    cout << c << endl; 
    cout << a << endl; 
    a = b;  // Should call the copy assignment operator for a.
    cout << "After assignment a = b" << endl;
    cout << a << endl;
    Points2<int> e = move(c);  // Move constructor for d.
    cout << "After e = move(c) " << endl;
    cout << e << endl;
    cout << c << endl;
    cout << "After a = move(e) " << endl;
    a = move(e);  // Move assignment operator for a.
    cout << a << endl;
    cout << e << endl;
	
}  

void TestPart2() {

    Points2<double> a, b;
    cout << "Enter a sequence of points (double)" << "\n\n";
    a.ReadPoints2();  // User provides input for Points2 a.
    cout << a << endl;
    cout << "Enter a sequence of points (double)" << "\n\n";
    b.ReadPoints2();  // User provides input for Points2 b.
    cout << b << "\n\n";
    cout << "Result of a + b" << endl;
    cout << a + b << "\n\n";
    Points2<double> d = a + b;
    cout << "Result of d = a + b" << endl;
    cout << d << endl;
    cout << "Second element in a: " << endl;
    cout << a[1][0] << ", " << a[1][1] << endl;  // Should print the 2nd element.
}  

}  // namespace

int
main(int argc, char **argv) 
{
  TestPart1();
  TestPart2();
  return 0;
}
