#include <iostream>
using namespace std;
template<class T>
struct nodeLL {
    T data;
    nodeLL *next;
};
 
template<class T>
class LinkedList {
protected:
    nodeLL<T> *head, *last;
public:
    static int count;
    LinkedList();
 
    bool isEmpty();
 
    int length();
 
    void insertLast(T &);
 
    void insert(T &);
 
    template<class U> 
    friend ostream &operator<<(ostream &os, LinkedList<U> &list);
};
template<class T>
int LinkedList<T>::count;
template<class T>
LinkedList<T>::LinkedList() {
    head = last = NULL;
    count = 0;
}
 
template<class T>
int LinkedList<T>::length() {
    return count;
}
 
template<class T>
void LinkedList<T>::insertLast(T &item) {
    nodeLL<T> *newnodeLL = new nodeLL<T>;
    newnodeLL->data = item;
    newnodeLL->next = NULL;
    if (head == NULL) {
        head = last = newnodeLL;
    } else {
        last->next = newnodeLL;
        last = newnodeLL;
    }
    count++;
}
 
///////////////// my edit /////////////////////////////////
template<class T>
void LinkedList<T>::insert(T &item) {
    insertLast(item);
}
 
template<class T>
ostream &operator<<(ostream &os, LinkedList<T> &list) {
    nodeLL<T> *p = list.head;
    while (p != NULL) {
        cout << p->data;
        p = p->next;
    }
    return os;
}