// Zach Duncan

#ifndef _TLIST_HPP
#define _TLIST_HPP

////////////////////////////CLASS TList DEFINITIONS/////////////////////////////
// Default Constructor
template <typename T>
TList<T>::TList() : first( 0 ), last ( 0 )     //Set first, last, size to 0
{
    size = 0;
}

// Constructor w/ two parameters
template <typename T>
TList< T >::TList(T val, int num)
{
    size = 0;                                  //Set size to 0 for InsertBack
                                               //func to work properly
    for (int i = 0; i < num; i++)              //Insert new node at back of list
      InsertBack(val);                         //num times, with value val
}

// Destructor
template <typename T>
TList<T>::~TList()
{
    if (size == 0)                //If size is (and therefore no memory is
      return;                     //currently dynamically allocated), good to go
    Clear();                      //Otherwise, call Clear function
}

// Copy Constructor
template <typename T>
TList<T>::TList(const TList& L)
{
    size = 0;                     //Initialize these to start for InsertBack to
    first = 0;                    //work properly
    last = 0;

    if (L.size == 0)              //If no nodes in list to copy, return
      return;

    TListIterator<T> t = L.GetIterator();    //Get iterator for Tlist<T> L

    while (t.HasNext())                 //While there is a next node
    {
      InsertBack((t.ptr)->data);        //Insert that node's data into new list
      t = t.Next();                     //Then, advance iterator to next node
    }
    InsertBack((t.ptr)->data);          //Insert last node
}

// Copy Assignment operator
template <typename T>
TList<T>& TList<T>::operator=(const TList& L)
{
    if (this != &L) // No need to copy an object from itself
    {
      Clear();
      if (L.size == 0)              //If no nodes in list to copy, return
        return *this;

      TListIterator<T> t = L.GetIterator();    //Get iterator for Tlist<T> L

      while (t.HasNext())                 //While there is a next node
      {
        InsertBack((t.ptr)->data);        //Insert that node's data into new list
        t = t.Next();                     //Then, advance iterator to next node
      }
      InsertBack((t.ptr)->data);          //Insert last node
    }
    return *this;
}

// Move Constructor
template <typename T>
TList<T>::TList(TList&& L)
{
    std::swap(size, L.size);              //Swap size
    std::swap(first, L.first);            //Swap first pointers
    std::swap(last, L.last);              //Swap last pointers
}

// Move Assignment Operator
template <typename T>
TList<T>& TList<T>::operator=(TList&& L)
{
    std::swap(size, L.size);              //Swap size
    std::swap(first, L.first);            //Swap first pointers
    std::swap(last, L.last);              //Swap last pointers
    return *this;                         //Return list by reference
}

// checks to see whether list is empty
template <typename T>
bool TList<T>::IsEmpty() const
{
    if(size == 0)                           //If size is zero
      return true;                          //List is empty
    else                                    //Else, it is not
      return false;
}

// clear out list, reset to empty
template <typename T>
void TList<T>::Clear()
{
    if (size == 0)           //If list is already cleared
      return;
    else if (size == 1)      //If needing to clear a list of only one node
    {
      DeleteNode(first);     //Delete first (which also last)
      size = 0;              //List is empty
    }
    else
    {
      //Iterate through list using iterator, delete nodes
      TListIterator<T> t = GetIterator();

      while (t.HasNext() == true)           //Traverse through linked list
      {
        Node<T>* next = t.ptr->next;        //Store next ptr
        DeleteNode(t.ptr);                  //Delete node
        t.ptr = next;                       //Update iterator to next
        size--;                             //Decrement size
      }
      delete t.ptr;              //Delete last node
      size--;                    //Size should decrement to zero
    }

    first = nullptr;             //Set first pointer to null
    last = nullptr;              //Set last pointer to null
}

//return the size of the list
template <typename T>
int TList<T>::GetSize() const
{
    return size;
}

// insert data d as first element
template <typename T>
void TList<T>::InsertFront(const T& d)
{
    Node<T>* ptr = GetNewNode(d); //Dynmaically allocate a new node
                                  //Right now, prev = next = nullptr
    if (IsEmpty())                //If d is first node in list
      InsertFirst(ptr);
    else                          //Else if node is being added to a list
    {
      size++;                     //Increment size of TList

      //Update new node's pointers, first and last of TList<T>
      Node<T>* temp = first;      //Pointer to current first node stored in temp
      ptr->prev = nullptr;           //Set new node's previous to null
      first = ptr;                //Tlist's first points to new node
      ptr->next = temp;              //Set new node's next to previous first node

      //Then, update previous first pointer's prev
      (ptr->next)->prev = ptr;
    }
}

// insert data d as last element
template <typename T>
void TList<T>::InsertBack(const T& d)
{
    Node<T>* ptr = GetNewNode(d); //Dynmaically allocate a new node

    if (IsEmpty())                //If d is first node in list
      InsertFirst(ptr);
    else                          //Else if node is being added to a list
    {
      size++;                     //Increment size of TList

      Node<T>* temp = last;       //Pointer to current first node stored in temp
      ptr->next = nullptr;        //Set new node's previous to null
      last = ptr;                 //Tlist's first points to new node
      ptr->prev = temp;           //Set new node's next to previous first node

      //Then, update previous first pointer's prev
      (ptr->prev)->next = ptr;
    }
}

// helper function to InsertFront and InsertBack
// do not call outside of these two functions
template <typename T>
void TList<T>::InsertFirst(Node<T>* ptr)
{
    size = 1;
    first = ptr;
    last = ptr;
}

// helper function for Inserts
// used for dynamic memory allocation
template <typename T>
Node<T>* TList<T>::GetNewNode(const T& d)
{
    Node<T>* n = new Node<T>(d);     //Create new node<T>
                                     //Right now, d.prev = d.next = nullptr
    return n;
}

// helper function for Inserts
// used for dynamic memory deallocation
template <typename T>
void TList<T>::DeleteNode(Node<T>* ptr)
{
    delete ptr;
}

// remove first element of list
template <typename T>
void TList<T>::RemoveFront()
{
    if (size == 0)                    //If nothing to remove, return
      return;

    Node<T>* temp = first->next;      //temp Node pointer to second node
    DeleteNode(first);                //delete first Node
    first = temp;                     //second node is now first
    first->prev = nullptr;            //This node's prev pointer is now null
    size--;                           //Decrement size

    if (size == 0)
      last = nullptr;                 //First already set equal to null
}

//remove last element of list
template <typename T>
void TList<T>::RemoveBack()
{
    if (size == 0)                    //If nothing to remove, return
      return;

    Node<T>* temp = last->prev;       //temp Node pointer to second to last node
    DeleteNode(last);                 //delete last Node
    last = temp;                      //second to last Node is now last
    last->next = nullptr;             //It's next pointer is now null
    size--;                           //Decrement size

    if (size == 0)
      first = nullptr;                //Last already set equal to null
}

// return first element of list
template <typename T>
T& TList<T>::GetFirst() const
{
    return (first->data);
}

// return last element of list
template <typename T>
T& TList<T>::GetLast() const
{
    return (last->data);
}

// return iterator to first item
template <typename T>
TListIterator<T> TList<T>::GetIterator() const
{
    TListIterator<T> i;                   //Get an iterator
    i.ptr = first;                        //Update its pointer to first
    return i;                             //Return that iterator
}

// return iterator to last item
template <typename T>
TListIterator<T> TList<T>::GetIteratorEnd() const
{
    TListIterator<T> i;                   //Get an iterator
    i.ptr = last;                         //Update its pointer to last
    return i;                             //Return that iterator
}

// insert data element d just before item at pos position
template <typename T>
void TList<T>::Insert(TListIterator<T> pos, const T& d)
{
    Node<T>* ptr = GetNewNode(d);         //Allocate new node

    if (size == 0)                        //If empty list
    {
      InsertFirst(ptr);                   //Call InsertFirst
      return;                             //End function here
    }
    else if (pos.ptr == nullptr)          //If iterator not pointing to anything
    {
      InsertBack(d);                      //Then, insert data in the back of list
      return;
    }
    else if (pos.ptr == first)            //If iterator pointing to first
    {
      InsertFront(d);                     //Just call InsertFront
      return;
    }
    else                                  //If populated with 1+ Nodes already
    {                                     //pos.ptr is current node ptr
      Node<T>* temp = pos.ptr;            //Store current node ptr in temp
      Node<T>* temp2 = (pos.ptr)->prev;   //Store prev node ptr in temp2
      //INSERT NEW NODE IN BETWEEN temp AND temp2
      ptr->next =  temp;                  //Set prev and next for new node
      ptr->prev = temp2;
      temp2->next = ptr;                  //Update prev for temp2 node
      temp->prev = ptr;                   //Update next for temp2 node

      size++;                             //Increment size
    }
    return;
}

// remove data item at position pos. Return iterator to the item
//  that comes after the one being deleted
template <typename T>
TListIterator<T> TList<T>::Remove(TListIterator<T> pos)
{
    if (size == 0 || size == 1)           //If list will be cleared
    {
      Clear();
      pos.ptr = nullptr;                  //Update pos.ptr to nullptr for return
    }
    else if (pos.ptr == first)            //If iterator is pointing to first
    {
      RemoveFront();
      pos.ptr = first;                    //Will update ptr to new first
    }
    else if (pos.ptr == last)             //If iterator is pointing to last
    {
      RemoveBack();
      pos.ptr = nullptr;                  //Will update ptr to new last
    }
    else
    {
      Node<T>* temp = (pos.ptr)->prev;    //Store next node ptr in temp
      Node<T>* temp2 = (pos.ptr)->next;   //Store prev node ptr in temp2

      DeleteNode(pos.ptr);                //DELETE NODE
      temp->next = temp2;                 //Update temp's next ptr
      temp2->prev = temp;                 //Update temp2's prev ptr
      size--;                             //Decrement size;

      pos.ptr = temp2;                    //Return the Node AFTER the Node
    }                                     //just deleted
    return pos;
}

// print list contents in order, separated by given delimiter
template <typename T>
void TList<T>::Print(std::ostream& os, char delim) const
{
    if (size == 0)                       //If nothing to print
    {
      os << "EMPTY LIST";
      return;
    }


    //Iterate through list to print
    TListIterator<T> t = GetIterator();

    while (t.HasNext() == true)           //Traverse through linked list
    {
      os << (t.ptr)->data << delim;
      t = t.Next();                       //Update iterator to next
    }
      os << (t.ptr)->data;                //Print last node
    }

////////////////////////STAND ALONE FUNCTION DEFINITIONS////////////////////////
// stand-alone function for concatenating two TList objects
template <typename T>
TList<T> operator+(const TList<T>& t1, const TList<T>& t2)
{
    TList<T> t3 = t1;                       //Copy list t1 into into new list t3
    TListIterator<T> t = t2.GetIterator();  //Get an interator to t2

    while (t.HasNext())                     //If t2 has a next Node
    {
      T tdata = t.GetData();                //Copy the data in that Node
      t3.InsertBack(tdata);                 //Insert it at end of list t3
      t.Next();                             //Advance iterator to next Node
    }
    //Insert last node
    T tdata = t.GetData();
    t3.InsertBack(tdata);

    return t3;                              //Then, return list t3
}

////////////////////////CLASS TListIterator DEFINITIONS/////////////////////////
// Default constructor
template <typename T>
TListIterator<T>::TListIterator()
{
    ptr = nullptr;                          //Set ptr to null, to initialize
}                                           //with TList<T>'s GetIterator()

// Next item available?
template <typename T>
bool TListIterator<T>::HasNext() const
{
    if(ptr->next == nullptr)                //If there is not a next Node
      return false;                         //Return false
    else
      return true;                          //Else, return true
}

// Previous item available?
template <typename T>
bool TListIterator<T>::HasPrevious() const
{
  if(ptr->prev == nullptr)                  //If there is not a previous Node
    return false;                           //Return false
  else
    return true;                            //Else, return true
}

// Advance to next item
template <typename T>
TListIterator<T> TListIterator<T>::Next()
{
    if (! HasNext())                        //If there is not a next Node
      ptr = nullptr;                        //iterator pointer is now null
    else
      ptr = ptr->next;                      //Else, point to next Node

    return *this;                           //Return the iterator
}

// Move to previous item
template <typename T>
TListIterator<T> TListIterator<T>::Previous()
{
    if (! HasPrevious())                    //If there is not a prev Node
      ptr = nullptr;                        //iterator pointer is now null
    else
      ptr = ptr->prev;                      //Else, point to prev Node

  return *this;                             //Return the iterator
}

// Return data element of current node
template< typename T >
T& TListIterator<T>::GetData() const
{
    return ptr->data;                        //Return data element at Node ptr
}

#endif
