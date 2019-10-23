#pragma once
template <class T>
class TStack {
  T *arr;
  int size;
  int num;
public:
  TStack(int _size = 10000) {
    if (_size <= 0) throw _size;
    size = _size;
    arr = new T[size];
    num = -1;
  }
  TStack(const TStack& st) {
    size = st.size;
    arr = new T[size];
    num = st.num;
    for (int i = 0; i <= num; i++) arr[i] = st.arr[i];
  }
  TStack& operator= (const TStack& st) {
    if (this != &st){
      delete[] arr;
      size = st.size;
      arr = new T[size];
      num = st.num;
      for (int i = 0; i <= num; i++) arr[i] = st.arr[i];
    }
    return *this;
  }
  bool IsEmpty()const {
    if (num == -1) return true;
    return false;
  }
  bool IsFull()const {
    if (num == size-1) return true;
    return false;
  }
  void push(T el) {
    IsFull();
    arr[num + 1] = el;
    num++;
  }
  T pop() {
    if (num == 0) throw num;
    num--;
    return arr[num + 1];
  }
  T top() {
    IsEmpty;
    return arr[num + 1];
  }
};