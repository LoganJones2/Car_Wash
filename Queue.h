#ifndef _QUEUE
#define _QUEUE

template <class T>
#define SIZE 10

class Queue{
  public:
    Queue();
    bool push(T);
    bool pop();
    bool is_empty();
    bool is_full();
    T get_front();
    T get_back();
    int get_size();
    
  private:
    T arr[SIZE];
    int front, back, count;
};

#endif