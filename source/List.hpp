# ifndef BUW_LIST_HPP
# define BUW_LIST_HPP

# include <cstddef>
#include <assert.h>
#include <utility>

// List.hpp
template <typename T> 
class List;

template <typename T>
struct ListNode
{   /*
    ListNode (T const& v, ListNode prev, ListNode next ) :
     value{v},
     prev{prev},
     next{next} {}  */

    //Default Konstruktor erstellen


   T value = T(); // check ich nicht
   ListNode *prev = nullptr;
   ListNode *next = nullptr;
};

template <typename T>
class ListIterator
{
   public :
   // not implemented yet
   // do not forget about the initialiser lists !
   private :
   ListNode <T>* node;
};

template <typename T>
class ListConstIterator
{
   public :
   // not implemented yet
   // do not forget about the initialiser lists !
   private :
   ListNode <T>* node;
};

template <typename T>
class List
{
   public:
   using value_type = T;
   using pointer = T*;
   using const_ponter = T const*;
   using reference = T&;
   using const_reference = T const&;
   using iterator = ListIterator <T>;
   using const_iterator = ListConstIterator <T>;

   friend struct ListNode<T>;

   /*Aufgabe 4.2*/
   List():  //Default Constructor
   size_{0},
   first_{nullptr},
   last_{nullptr} {}

   bool empty() const{
       return (size_ == 0);
   }

   std::size_t size() const {
       return size_;
   }

   /*Aufgabe 4.3*/
   void push_front (T const& v) {  //neues Element am Anfang einfügen
      if(empty()){
        first_ = new ListNode<T>{v,nullptr,nullptr};  
        last_ = first_;
        ++ size_;
      } else {
          first_ = new ListNode<T>{v,nullptr,first_};
          first_ -> next -> prev = first_;
          ++ size_;
        }
   }

    void push_back(T const& v) {  //neues Element am Ende einfügen 
    if (empty()) {
      last_ = new ListNode<T>{v, nullptr, nullptr};
      first_ = last_;
    } else  {
      last_ = new ListNode<T>{v, last_, nullptr};
      last_ -> prev -> next = last_;
    }

    ++ size_;
}

 void pop_front()  //erstes Element aus Liste löschen
 {
     if (empty()) {
      std::cout<<"The list does not contain any elements. \n";
 }  
 if (size() == 1) {
     assert(first_ != nullptr);
        delete first_;
        first_=nullptr;
     } 
     if (size() > 1) {
         assert (first_ != nullptr);
             delete first_;
             first_ = first_ -> next;
             -- size_;
     }
 }

  void pop_back()  //leztes Element aus Liste löschen
 {
     if (empty()) {
      std::cout<<"The list does not contain any elements. \n";
     }  
     if (size() == 1) {
     assert(last_ != nullptr);
        delete last_;
        last_=nullptr;
     } 
    if (size() > 1) {
         assert (last_ != nullptr);
             delete last_;
             last_ = last_ -> prev;
             -- size_;
     }
 }


T& front() {
    return first_ -> value;
}

T& back() {
    return last_ -> value;
}
// not implemented yet
// do not forget about the initialiser list !
   private:
   std::size_t size_ = 0;
   ListNode <T>* first_ = nullptr;
   ListNode <T>* last_ = nullptr;

};
# endif // # define BUW_LIST_HPP