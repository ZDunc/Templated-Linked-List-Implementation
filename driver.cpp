// Zach Duncan

#include <iostream>
#include <string>

#include "tlist.h"

using namespace std;

template <typename T>
void PrintList(const TList<T>& L, string label)
{
   cout << label << " size is: " << L.GetSize() << "\n"
        << label << " = ";
   L.Print(cout);
   cout << "\n\n";
}

int main()
{

  //Test for All Functions

  //Default Constructor
   TList<double> L1, L2;    //double list
   TList<string> L3;        //string list
   TList<char> L4;          //char list

   //Constructor with Parameters
   TList<double> L5;
   TList<string> L6;
   TList<char> L7;

   cout << "\nLet's populate some of these doubly linked lists!\n";
   for (int i = 0; i < 10; i++)
      L1.InsertFront(i * 2.12);
   PrintList(L1, "L1");

   for (int i = 0; i < 10; i++)
      L4.InsertBack((char) 97 + i);   //97 is ASCII code for 'a'
   PrintList(L4, "L4");

   //Copy, Assignment, Move, Move Assignment
   cout << "Copy Constructor Testing\n";
   TList<char> L8 = L4;
   PrintList(L8, "L8");

   cout << "Assignment Operator Testing\n";
   L2 = L1;
   PrintList(L2, "L2");

   L2 = L5;
   PrintList(L2, "L2");

   cout << "Enough of that. Repopulating L2 with new data.\n";
   for (int i = 0; i < 10; i++)
      L2.InsertFront(i * 8.88);
   PrintList(L2, "L2");

   cout << "Move Constructor Testing. TList<double> L9 = L2 + L1\n"
           "(Also an addition overload test)";
   TList<double> L9 = L2 + L1;
   PrintList(L9, "L9");

   cout << "Move Assignment Operator Testing. L5 = L2 + L1\n";
   L5 = L2 + L1;
   PrintList(L5, "L5");

   //IsEmpty()
   cout << "That was super fun. Now, IsEmpty() Testing\n";
   if (L3.IsEmpty())
      cout << "We have determined that L3 is currently empty.\n";
   if (! L3.IsEmpty())
      cout << "And this code will never print.\n";

   if (! L5.IsEmpty())
      cout << "L5 is not empty. We literally just move assigned data into it.\n\n";

   //Clear()
   cout << "Now testing Clear(). Will first add one string into L3 and two "
           "strings into L6\n";

   L3.InsertFront("Hello");
   L6.InsertBack("Hello");
   L6.InsertBack("Bob");

   cout << "Printing L3\n";
   PrintList(L3, "L3");

   cout << "Printing L6\n";
   PrintList(L6, "L6");

   cout << "Now clearing L3 and L6. Also L9 just for fun. They now print:\n";
   L3.Clear();
   L6.Clear();
   L9.Clear();

   PrintList(L3, "L3");
   PrintList(L6, "L6");
   PrintList(L9, "L9");

   cout << "Testing GetSize()\n";
   cout << "L4 has " << L4.GetSize() << " characters in its list.\n";
   cout << "L9 has " << L9.GetSize() << " doubles in its list.\n\n";

   cout << "Testing GetFirst(), GetLast()\n";
   cout << "L4's last char is " << L4.GetLast() << ".\n";
   cout << "L1's first double is " << L1.GetFirst() << ".\n\n";

   cout << "Time for some TListIterator Testing. Reprinting L1 and L4\n";
   PrintList(L1, "L1");
   PrintList(L4, "L4");

   TListIterator<char> c;
   TListIterator<double> d = L1.GetIterator();

   c = L4.GetIteratorEnd();

   if (c.HasNext())
    cout << "Iterator c is NOT at the end of L4's doubly linked list.\n";
   else
    cout << "Iterator c is at the end of L4's doubly linked list.\n";

    if (d.HasPrevious())
     cout << "Iterator d is NOT at the beginning of L1's doubly linked list.\n\n";
    else
     cout << "Iterator d is at the beginning of L1's doubly linked list.\n\n";

    cout << "Advancing iterator d three list items forward and "
            "iterator c five items backward. Retrieving data.\n\n";

    for (int i = 0; i < 3; i++)
      d.Next();
    for (int i = 0; i < 4; i++)
      c.Previous();

    cout << "Iterator c pointing to data entry '" << c.GetData() << "'\n";
    cout << "Iterator d pointing to data entry " << d.GetData() << "\n\n";

    cout << "Finally, this test program explores lots of intertwined testing of "
            "InsertFront, InsertBack, RemoveFront, RemoveBack, Insert (iterator-"
            "based), Remove (iterator-based), and more.\n\n";

    cout << "Test 1\n";
    PrintList(L4, "L4");
    L4.InsertFront('I');
    L4.InsertFront('H');
    L4.Insert(c, 'a');
    c.Previous();
    c.Previous();
    L4.Insert(c, 'a');
    PrintList(L4, "L4");

    cout << "Test 2\n";
    PrintList(L1, "L1");
    d = L1.Remove(d);
    d = L1.Remove(d);
    L1.InsertFront(3.14);
    L1.InsertBack(123874653.99998);
    d = L1.Remove(d);
    d = L1.Remove(d);
    PrintList(L1, "L1");

    cout << "Test 3\n";
    for (int i = 0; i < 12; i++)
       L7.InsertBack((char) 105 + i);   //97 is ASCII code for 'i'
    PrintList(L7, "L7");
    for (int i = 0; i < 3; i++)
       L7.RemoveFront();   //97 is ASCII code for 'i'
    TListIterator<char> c2 = L7.GetIterator();
    c2 = L7.Remove(c2);
    c2 = L7.Remove(c2);
    L7.Insert(c2, 'z');
    L7.Insert(c2, 'a');
    L7.Insert(c2, 'c');
    L7.Insert(c2, 'h');
    PrintList(L7, "L7");

    cout << "Test 4\n";
    L4 = L4 + L7;
    PrintList(L4, "L4");
    L4.RemoveFront();
    L4.RemoveBack();
    L4.RemoveFront();
    c = L4.GetIterator();
    for (int i = 0; i < 10; i++)
      c.Next();
    L4.Insert(c, '!');
    L4.InsertBack('!');
    L4.InsertFront('!');
    PrintList(L4, "L4");

    cout << "Test 5\n";
    PrintList(L5, "L5");
    L5.RemoveBack();
    L5.RemoveBack();
    L5.RemoveFront();
    L5.RemoveBack();
    L5.RemoveFront();
    L5.InsertFront(3.14);
    L5.InsertBack(3.14);
    PrintList(L5, "L5");

    //Test 5 Continued
    TListIterator<double> d2 = L5.GetIterator();
    for (int i = 6; i < 0; i++)
      d2.Next();
    d2 = L5.Remove(d2);
    d2 = L5.Remove(d2);
    L5.Insert(d2, 3.14);
    L5.Insert(d2, 3.14);
    L5.Insert(d2, 48097.11);
    d2.Next();
    d2.Next();
    d2.Next();
    d2 = L5.Remove(d2);
    d2 = L5.Remove(d2);
    PrintList(L5, "L5");

    cout << "Test 6\n";
    PrintList(L1, "L1");
    L1.RemoveBack();
    L1.RemoveBack();
    L1.RemoveFront();
    L1.RemoveFront();
    L1.RemoveFront();
    L1.InsertFront(1.1);
    L1.InsertBack(1.1);
    L1.InsertFront(1.2);
    L1.InsertBack(1.2);
    PrintList(L1, "L1");

    cout << "Test 7\n";
    for (int i = 0; i < 12; i++)
      L8.InsertBack((char) 97 + i);   //97 is ASCII code for 'a'
    PrintList(L8, "L8");
    L8.RemoveBack();
    L8.RemoveFront();
    L8.RemoveBack();
    L8.RemoveFront();
    L8.InsertBack('B');
    L8.InsertBack('Y');
    L8.InsertBack('E');
    PrintList(L8, "L8");

    //Continued Test 7
    L8.RemoveBack();
    L8.RemoveBack();
    L8.RemoveBack();
    L8.InsertBack('?');
    PrintList(L8, "L8");

    cout << "END OF TESTING\n\n";

   return 0;
}
