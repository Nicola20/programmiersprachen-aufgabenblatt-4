# ifndef BUW_LIST_HPP
# define BUW_LIST_HPP

#include <cstddef>
#include <assert.h>
#include <utility>
#include <algorithm>

// List.hpp
template <typename T> 
class List;

template <typename T>
struct ListNode
{   
    ListNode (T const& v, ListNode *prev, ListNode *next):
     value{v},
     prev{prev},
     next{next} {}  

    //Default Konstruktor erstellen


   T value = T(); // check ich nicht
   ListNode *prev = nullptr;
   ListNode *next = nullptr;
};

template <typename T>
class ListIterator
{
   public:
   using Self = ListIterator<T>;
   using value_type = T; 
   using pointer = T*;
   using reference = T&;
   using difference_type = ptrdiff_t;
   using iterator_category = std::bidirectional_iterator_tag;

   friend class List<T>;

   ListIterator ():
       node{nullptr} {}

   ListIterator (ListNode<T>* n):
       node{n}
       {}


   reference operator* () const {
       return node -> value; 
   } 

   pointer operator-> () const {
       //return &(node -> value);
       return *node;
   } 

   Self& operator++ () {
      node = node -> next;
      return *this;
   }  

   Self operator++ (int) {
        ListIterator old(*this);
        node = node->next;
       return old;
   } 

   //Überprüfen ob 2 Pointer auf das selbe Element verweisen
   bool operator== (Self const& x) const {
       return (node == x.node);
   }
    
   bool operator!= (Self const& x) const {
       return (node != x.node);
   } 

   Self next() const {
     if (node)
        return ListIterator (node -> next);
      else
        return ListIterator (nullptr);
   }

      Self prev() const {
     if (node)
        return ListIterator (node -> prev);
      else
        return ListIterator (nullptr);
   }



   private:
   ListNode <T>* node;
};

template <typename T>
class ListConstIterator
{
   public:
   // not implemented yet
   // do not forget about the initialiser lists !
   private:
   ListNode<T>* node;
};

/*4.7*/
template <typename T>
bool operator== (List<T> const& xs, List<T> const& ys)
{
    auto i = xs.begin();
    auto j = ys.begin();

    if(xs.size() != ys.size()) {
        return false;
    } else {
        for(unsigned int c = 0; c < xs.size(); c++){
            if(*i == *j){
                ++i;
                ++j;
            }
            else 
                return false;   
        }
    }   
    return true;
}

template <typename T>
bool operator!= (List<T> const& xs, List<T> const& ys)
{
auto i =xs.begin();
auto j =ys.begin();
//bool result = false;
  if(xs.size() != ys.size()) {
       return true;
  } else {
      while(i != nullptr) {
          if (*i != *j){
              return true;
              break;
          }
          ++i;
          ++j;
      }
  }
}


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

   //friend struct ListNode<T>;
   //friend class ListIterator<T>;

   /*Aufgabe 4.2*/
   List():  //Default Constructor
   size_{0},
   first_{nullptr},
   last_{nullptr} {}


//Copy Constructor

List(List<T> const& list):                //already implemented list
    first_{nullptr},                     //set *this on nullptr
    last_{nullptr} {
      auto i = list.begin();            //iterate through list
      while(i != nullptr){
        push_back(*i);                //push all elements into *this
        ++i;
      }
}

/*4.13*/
//Move Constructor, moves elements from one list to the other, "steals them"
    List (List<T>&& list):                    
        size_{list.size_},                 
        first_{list.first_},
        last_{list.last_} {
            list.first_ = nullptr;
            list.last_ = nullptr;
            list.size_ = 0;
    }

   bool empty() const{
       return (size_ == 0);
   }

   std::size_t size() const {
       return size_;
   }

   /*Aufgabe 4.3*/
   void push_front (T const& v) {  //neues Element am Anfang einfügen
      if(empty()){
          //std::cout<<"klappt.\n";
        ListNode<T>* tmp = new ListNode<T>{v,nullptr,nullptr};
        last_ = tmp;
        first_ = tmp;
        ++ size_;
        //std::cout<<"hey there.\n";
      } else {
          //std::cout<<"klappt.\n";
          ListNode<T>* tmp = new ListNode<T>{v,nullptr,first_};
          first_ -> prev = tmp;
          first_ = tmp;
          //first_ -> next -> prev = first_;
          ++ size_;
          //std::cout<<"hey there.\n";
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
        last_ = nullptr;
        --size_;
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
        first_ = nullptr;
        --size_;
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

/*4.4*/

void clear() {
    while(!empty()){
        pop_back();
    }
}

//Destruktor mit clear
~List() {
    clear();
} 


   //4.6
   ListIterator<T> begin() const {
       if (empty()) {
           return ListIterator<T>(nullptr);
       } else {
           return ListIterator<T>(first_);
       }
   }

   ListIterator<T> end() const {
       if(empty()) {
           return ListIterator<T>(nullptr);
       } else {
           return ListIterator<T>(last_);
       }
   }
   
//4.9

   void insert(ListIterator<T> const& pos, T const& v){
       if (pos == begin()) {
           push_front(v);
       } else if (pos == end()) {
           push_back (v);          
       } else {
          ListNode <T>* newNode = new ListNode<T>(v, pos.prev().node, pos.node);
          pos.node->prev = newNode;
          newNode->prev->next = newNode;
          ++ size_;

         }
   } 

//4.10

void reverse() {
   
   for(auto i = first_ ; i != nullptr; i = i-> prev) {
       std::swap(i -> prev, i -> next);
   }
  std::swap(first_,last_);
}

 //iterator points to element behind last element
    ListIterator <T> bend() const {        
        return ListIterator<T>();
    }

   private:
   std::size_t size_ = 0;
   ListNode <T>* first_ = nullptr;
   ListNode <T>* last_ = nullptr;

};

   //4.10

  /*
   template <typename T>
   List<T> reverse (List<T> list){
       list.reverse();
       return list;
   } */

   template<typename T>
        List<T> reverse(List<T> const& list) {  //swaps the list an returns a new list
            List<T> newList;
            for(auto a = list.begin(); a != nullptr; ++a) {
                 newList.push_front(*a);
            }
                return newList;
        } 

# endif // # define BUW_LIST_HPP