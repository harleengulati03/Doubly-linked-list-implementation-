// Implementation of the list module.
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Each node in a doubly linked list is stored in this structure. The user of the
// module does not have any knowledge of nodes.
struct node { struct node *back; item x; struct node *next; };
typedef struct node node;

// A list is to be represented as a circular list. It has to contain a doubly linked list
// of item nodes and one special sentinel node that links to the two ends of the item list.
// The none field holds this sentinel node. It has a default item, must always be present for 
// a list and always sits before the first item node and after the last item node. For a list 
// that holds no item nodes the back and next fields of the sentinel node point to the sentinel 
// node itself. The current node refers to the currently selected item node in the list. If 
// the current node is the none node then no item is selected.
struct list { node *none, *current; };
typedef struct list list;

// ---------- ADD YOUR 13 FUNCTIONS HERE ----------

// FUNCTION #1: Create a new empty list and make e the default item that is
// returned by functions in case no item is selected. No item is selected in an empty list.
list *newList(item e) {
    // allocating memory on heap for new list
    list *theNewList = malloc(sizeof(list));
    // allocating memory on heap for sentinel node
    node *sentinelNode = malloc(sizeof(node));
    // none and current pointers point to sentinel node
    theNewList->none = sentinelNode;
    theNewList->current = sentinelNode;
    // initialise sentinel node with default value
    sentinelNode->x = e;
    // linking back to sentinel node
    sentinelNode->back = sentinelNode;
    // linking front to sentinel node
    sentinelNode->next = sentinelNode;
    return theNewList;
}

// FUNCTION #2: Free up the list and all the data in it. Does not have to run in O(1).
void freeList(list *xs){
    node *endNode = xs->none;
    node *currentNode = xs->current;
    // set current node to first node
    xs->current = endNode->next;
    // if node points forwards to same node it points backwards to
    // then this node is a none node
    while (currentNode->next != currentNode->back) {
        // set current node to node after current node
        xs->current = currentNode->next;
        // free it by referring to it using the back field
        free(currentNode->back);
    }
    // freeing the none node
    free(endNode);
    // freeing the list
    free(xs);
}

// FUNCTIONS #3/#4: Set the current item to the first item or to the last
// item of the list. If the list has no items the functions do nothing
// and no item is selected.

// FUNCTION #3
void first(list *xs) {
    // check case where list has no items
    // if list has no items then only node is none node
    // front and back pointer of the none node points to itself
    node *isNone = xs->none;
    if (isNone->back != isNone->next) {
        // set current node to next node
        //  as none node points forward to first node
        xs->current = isNone->next;
    }
}
// FUNCTION #4
void last(list *xs) {
    // same procedure as first to check if list has no items
    node *isNone = xs->none;
    if (isNone->back != isNone->next) {
        // set current node to back node
        // as the none node points back to the last node
        xs->current = isNone->back;
    }
}

// FUNCTION #5: Returns true if no item is selected, i.e. the 'none' position.
// Otherwise it returns false.
bool none(list *xs) {
    // if no item is selected, current pointer points to none
    if (xs->current == xs->none) {return true;}
    return false;
}

// FUNCTION #6: Move the current item one place forwards in the list and return true.
// If after is called while the last item is the current item, then no item is
// selected and true is returned. If the function is called while no item
// is selected then the function does nothing and returns false.
bool after(list *xs) {
    node *endNode = xs->none;
    node *currentNode = xs->current;
    // check if no item is selected
    if (currentNode == endNode) {return false;}
    // otherwise, moves currentNode to the next item
    // and stores this as the current item
    xs->current = currentNode->next;
    return true;
}

// FUNCTION #7: Move the current item one place backwards in the list and return true.
// If before is called while the first item is the current item, then no item is
// selected and true is returned. If the function is called while no item
// is selected then the function does nothing and returns false.
bool before(list *xs) {
    node *endNode = xs->none;
    node *currentNode = xs->current;
    // check in a similar fashion to after if no item is selected
    if (currentNode == endNode) {return false;}
    // otherwise, move currentNode to the previous item
    // and store this as the current item
    xs->current = currentNode->back;
    return true;
}

// FUNCTION #8: Get the current item. If get is called and no item is selected
// then the default item is returned.
item get(list *xs) {
    node *currentNode = xs->current;
    // return current item
    // note "no item" case is accounted for here
    // because item in the none pointer is set to the default item anyways
    return currentNode -> x;
}

// FUNCTION #9: Set the current item and return true. If set is called while no
// item is selected then the function does nothing and returns false.
bool set(list *xs, item x) {
    node *endNode = xs->none;
    node *currentNode = xs->current;
    // check if no item is selected
    if (endNode == currentNode) {return false;}
    // otherwise, sets item to the parameter provided by set
    currentNode->x = x;
    return true;
}

// FUNCTION #10: Inserts an item after the current item and makes it the current item.
// If insertAfter is called while no item is selected then
// the function inserts the item at the beginning of the list
// before the first item.
void insertAfter(list *xs, item x){
    node *beforeIN = xs->current;
    node *afterIN = beforeIN->next;
    // allocate memory on heap for insertion node
    node *insertionNode = malloc(sizeof(node));
    // set value of x to value passed in
    insertionNode->x = x;
    // beforeIN currently points to afterIN
    // it needs to point to insertionNode
    beforeIN->next = insertionNode;
    // afterIN points back to beforeIN
    // it needs to point to insertionNode
    afterIN->back = insertionNode;
    // front and back pointers of insertion node set
    insertionNode->next = afterIN;
    insertionNode->back = beforeIN;
    // set current value of pointer to the insertion node
    xs->current = insertionNode;
}

// FUNCTION #11: Inserts an item before the current item and makes it the current item.
// If insertAfter is called while no item is selected then the function inserts
// the item at the end of the list after the last item.
void insertBefore(list *xs, item x){
    node *afterIN = xs->current;
    node *beforeIN = afterIN->back;
    // allocate memory on heap for insertion node
    node *insertionNode = malloc(sizeof(node));
    // set value of x to value passed in
    insertionNode->x = x;
    // afterIN points back to beforeIN
    // it needs to point back to insertionNode
    afterIN-> back = insertionNode;
    // beforeIN points forward to afterIN
    // it needs to point forward to insertionNode
    beforeIN->next = insertionNode;
    // front and back pointers of insertion node set
    insertionNode->back = beforeIN;
    insertionNode->next = afterIN;
    // set current value of pointer to  insertion node
    xs->current = insertionNode;
}

// FUNCTION #12: Delete the current item and make its successor the current item, then
// return true. If deleteToAfter is called while the last item is the current item then
// the last item is deleted, no item is selected, and true is returned.
// If deleteToAfter is called while no item is selected then the
// function does nothing and returns false.
bool deleteToAfter(list *xs){
    node *currentItem = xs->current;
    node *predecessor = currentItem->back;
    node *successor = currentItem->next;
    // first check if no item selected
    if (currentItem == xs->none) {return false;}
    // make item before current node point to item after current node
    predecessor->next = successor;
    // make item after current node point to item before current node
    successor->back = predecessor;
    // set current pointer to successor node
    xs->current = successor;
    // remove current item from heap
    free(currentItem);
    return true;
}

// FUNCTION #13: Delete the current item and make its predecessor the current item, then
// return true. If deleteToBefore is called while the first item is the current item then
// the first item is deleted, no item is selected, and true is returned.
// If deleteToBefore is called while no item is selected then the
// function does nothing and returns false.
bool deleteToBefore(list *xs){
    node *currentItem = xs->current;
    node *predecessor = currentItem->back;
    node *successor = currentItem->next;
    // first check if no item selected
    if (currentItem == xs->none) {return false;}
    // make item before current node point to item after the current node
    predecessor->next = successor;
    // make item after current node point to item before the current node
    successor->back = predecessor;
    // set current pointer to predecessor node
    xs->current = predecessor;
    // remove current item from the heap
    free(currentItem);
    return true;
}

// Test the list module, using int as the item type. Strings are used as
// 'pictograms' to describe lists. Single digits represent items and the '|' symbol
// in front of a digit indicates that this is the current item. If the '|' symbol
// is at the end of the string then 'none' of the items is selected. The strings
// "|37", "3|7", "37|" represent a list of two items, with the current position
// at the first item, the last item, and a situation where 'none' of the items
// is selected.


// Build a list from a pictogram, with -1 as the default item.
list *build(char *s) {
  list *xs = malloc(sizeof(list));
    int n = strlen(s);
    node *nodes[n];
    for (int i = 0; i < n; i++) nodes[i] = malloc(sizeof(node));
    for (int i = 0; i < n; i++) nodes[i]->next = nodes[(i + 1) % n];
    for (int i = 1; i < n + 1; i++) nodes[i % n]->back = nodes[i - 1];
    xs->none = nodes[0];
    xs->none->x = -1;
    node *p = xs->none->next;
    for (int i = 0; i < strlen(s); i++) {
      if (s[i] == '|') xs->current = p;
      else {
        p->x = s[i] - '0';
        p = p->next;
      }
    }
  return xs;
}

// Destroy a list which was created with the build function and which matches a
// pictogram.
void destroy(list *xs, char *s) {
  int n = strlen(s);
  node *nodes[n];
  nodes[0] = xs->none;
  for (int i = 1; i < n; i++) nodes[i] = nodes[i-1]->next;
  for (int i = 0; i < n; i++) free(nodes[i]);
  free(xs);
}

// Check that a list matches a pictogram.
bool match(list *xs, char *s) {
  int n = strlen(s);
  node *nodes[n];
  nodes[0] = xs->none;
  for (int i = 1; i < n; i++) nodes[i] = nodes[i - 1]->next;
  if (nodes[n - 1]->next != xs->none) return false;
    for (int i = 1; i < n; i++) {
      if (nodes[i]->back != nodes[i - 1]) return false;
    }
  node *p = xs->none->next;
  for (int i = 0; i < strlen(s); i++) {
    if (s[i] == '|') {
      if (p != xs->current) return false;
    }
    else {
      if (p->x != s[i] - '0') return false;
      p = p->next;
    }
  }
  return true;
}

// Use constants to say which function to call.
enum { First, Last, None, After, Before, Get, Set, InsertAfter, InsertBefore, DeleteToAfter, DeleteToBefore};
typedef int function;

// A replacement for the library assert function.
void assert(int line, bool b) {
  if (b) return;
  printf("The test on line %d fails.\n", line);
  exit(1);
}

// Call a given function with a possible integer argument, returning a possible
// integer or boolean result (or -1).

int call(function f, list *xs, int arg) {
  int result = -1;
  switch (f) {
    case None: result = none(xs); break;
    case First: first(xs); break;
    case Last: last(xs); break;
    case After: result = after(xs); break;
    case Before: result = before(xs); break;
    case Get: result = get(xs); break;
    case Set: result = set(xs, arg); break;
    case InsertAfter: insertAfter(xs, arg); break;
    case InsertBefore: insertBefore(xs, arg); break;
    case DeleteToBefore: result = deleteToBefore(xs); break;
    case DeleteToAfter: result = deleteToAfter(xs); break;
    default: assert(__LINE__, false);
  }
  return result;
}

// Check that a given function does the right thing. The 'in' value is passed to
// the function or is -1. The 'out' value is the expected result, or -1.
bool check(function f, int in, char *before, char *after, int out) {
  list *xs = build(before);
  int result = call(f, xs, in);
  //check circular list structure
  assert(__LINE__, (xs->none == xs->none->next->back));
  assert(__LINE__, (xs->none == xs->none->back->next));
  //check correct workings of the function
  bool ok = (match(xs, after) && (result == out));
  destroy(xs, after);
  return ok;
}

// Test newList, and call freeList. The test for freeList is that the memory
// leak detector in the -fsanitize=address or -fsanitize=leak compiler option
// reports no problems.
void testNewList() {
    list *xs = newList(-1);
    //check circular list structure
    assert(__LINE__, (xs->none == xs->none->next));
    assert(__LINE__, (xs->none == xs->none->back));
    //check that an empty list is produced with a sentinel correctly
    assert(__LINE__, match(xs, "|"));
    freeList(xs);
}

// Test the various functions.
void testFirst() {
    assert(__LINE__, check(First, -1, "|", "|", -1));
    assert(__LINE__, check(First, -1, "|37", "|37", -1));
    assert(__LINE__, check(First, -1, "3|7", "|37", -1));
    assert(__LINE__, check(First, -1, "37|", "|37", -1));
}


void testLast() {
    assert(__LINE__, check(Last, -1, "|", "|", -1));
    assert(__LINE__, check(Last, -1, "|37", "3|7", -1));
    assert(__LINE__, check(Last, -1, "3|7", "3|7", -1));
    assert(__LINE__, check(Last, -1, "37|", "3|7", -1));
}


void testNone() {
    assert(__LINE__, check(None, -1, "|", "|", true));
    assert(__LINE__, check(None, -1, "|37", "|37", false));
    assert(__LINE__, check(None, -1, "3|7", "3|7", false));
    assert(__LINE__, check(None, -1, "37|", "37|", true));
}


void testAfter() {
    assert(__LINE__, check(After, -1, "|", "|", false));
    assert(__LINE__, check(After, -1, "|37", "3|7", true));
    assert(__LINE__, check(After, -1, "3|7", "37|", true));
    assert(__LINE__, check(After, -1, "37|", "37|", false));
}

void testBefore() {
    assert(__LINE__, check(Before, -1, "|", "|", false));
    assert(__LINE__, check(Before, -1, "|37", "37|", true));
    assert(__LINE__, check(Before, -1, "3|7", "|37", true));
    assert(__LINE__, check(Before, -1, "37|", "37|", false));
}


void testGet() {
    assert(__LINE__, check(Get, -1, "|", "|", -1));
    assert(__LINE__, check(Get, -1, "|37", "|37", 3));
    assert(__LINE__, check(Get, -1, "3|7", "3|7", 7));
    assert(__LINE__, check(Get, -1, "37|", "37|", -1));
}


void testSet() {
    assert(__LINE__, check(Set, 5, "|", "|", false));
    assert(__LINE__, check(Set, 5, "|37", "|57", true));
    assert(__LINE__, check(Set, 5, "3|7", "3|5", true));
    assert(__LINE__, check(Set, 5, "37|", "37|", false));
}


void testInsertAfter() {
    assert(__LINE__, check(InsertAfter, 5, "|", "|5", -1));
    assert(__LINE__, check(InsertAfter, 5, "|37", "3|57", -1));
    assert(__LINE__, check(InsertAfter, 5, "3|7", "37|5", -1));
    assert(__LINE__, check(InsertAfter, 5, "37|", "|537", -1));
}


void testInsertBefore() {
    assert(__LINE__, check(InsertBefore, 5, "|", "|5", -1));
    assert(__LINE__, check(InsertBefore, 5, "|37", "|537", -1));
    assert(__LINE__, check(InsertBefore, 5, "3|7", "3|57", -1));
    assert(__LINE__, check(InsertBefore, 5, "37|", "37|5", -1));
}


void testDeleteToAfter() {
    assert(__LINE__, check(DeleteToAfter, -1, "|", "|", false));
    assert(__LINE__, check(DeleteToAfter, -1, "|37", "|7", true));
    assert(__LINE__, check(DeleteToAfter, -1, "3|7", "3|", true));
    assert(__LINE__, check(DeleteToAfter, -1, "37|", "37|", false));
    assert(__LINE__, check(DeleteToAfter, -1, "|5", "|", true));
}


void testDeleteToBefore() {
    assert(__LINE__, check(DeleteToBefore, -1, "|", "|", false));
    assert(__LINE__, check(DeleteToBefore, -1, "|37", "7|", true));
    assert(__LINE__, check(DeleteToBefore, -1, "3|7", "|3", true));
    assert(__LINE__, check(DeleteToBefore, -1, "37|", "37|", false));
    assert(__LINE__, check(DeleteToBefore, -1, "|5", "|", true));
}

int main() {
    testNewList();
    testFirst();
    testLast();
    testNone();
    testAfter();
    testBefore();
    testGet();
    testSet();
    testInsertAfter();
    testInsertBefore();
    testDeleteToAfter();
    testDeleteToBefore();
    printf("List module tests run OK.\n");
    return 0;
}
