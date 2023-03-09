#define LISTA_H
#ifndef LISTA_H
#define LISTA_H

#include <ostream>
#include <vector>
#include <string>

#include <iostream>

template<class T>
class Lista {
public:
    Lista();
    Lista(const Lista& other);
    Lista(Lista&& other);
    Lista<T>& operator=(const Lista& other);
    Lista<T>& operator=(Lista&& other);
    ~Lista();

    T& operator[](int index);
    const T& operator[](int index) const;

    template<class U>
    friend std::ostream& operator<<(std::ostream& os, const Lista<U>& list);

    int getDim() const;
    void insert(int index, const T& value);
    void adauga(const T& value);
    void pop_back();
    void push_front(const T& value);
    void pop_front();
    void sterge(int index);
    void clear();
    bool isEmpty() const;

private:
    int capacity = 10;
    int size = 0;
    T* data = nullptr;

    friend void test_list();
};

template<class T>
inline Lista<T>::Lista()
    : capacity(10), size(0), data(new T[capacity]) {};

template<class T>
inline Lista<T>::Lista(const Lista& other)
    : size(other.size), capacity(other.capacity), data(new T[other.capacity]) {
    for (int i = 0; i < other.size; i++)
        this->data[i] = other.data[i];
}

template<class T>
inline Lista<T>::Lista(Lista&& other)
    : data(other.data), size(other.size), capacity(other.capacity) {
    other.capacity = 10;
    other.size = 0;
    other.data = nullptr;
}

template<class T>
inline Lista<T>& Lista<T>::operator=(const Lista& other)  {
    if (this != &other) {
        delete[] this->data;
        this->size = other.size;
        this->data = new T[other.size];
        for (int i = 0; i < other.size; i++) {
            this->data[i] = other.data[i];
        }
    }
    return *this;
}

template<class T>
inline Lista<T>& Lista<T>::operator=(Lista&& other) {
    if (this != &other) {
        this->data = other.data;
        this->size = other.size;
        this->capacity = other.capacity;

        other.capacity = 10;
        other.size = 0;
        other.data = nullptr;
    }
    return *this;
}

template<class T>
inline Lista<T>::~Lista() {
    this->clear();
}

template<class T>
inline T& Lista<T>::operator[](int index) {
    return this->data[index];
}

template<class T>
inline const T& Lista<T>::operator[](int index) const {
    return this->data[index];
}

template<class U>
inline std::ostream& operator<<(std::ostream& os, const Lista<U>& list) {
    os << "Lista(s=" << list.size << ", c=" << list.capacity << ")=[";
    for (int i = 0; i < list.size; i++) {
        os << list.data[i] << ",";
    }
    os << "]";
    return os;
}

template<class T>
inline int Lista<T>::getDim() const {
    return size;
}

template<class T>
inline void Lista<T>::insert(int index, const T& value) {
    if (data == nullptr)
        data = new T[capacity];

    if (index < 0 || index > this->size)
        throw "Index out of range";
    if (this->size == this->capacity) {
        this->capacity *= 2;
        T* newData = new T[this->capacity];
        for (int i = 0; i < this->size; i++) {
            newData[i] = this->data[i];
        }
        delete[] this->data;
        this->data = newData;
    }
    for (int i = this->size; i > index; i--) {
        this->data[i] = this->data[i - 1];
    }
    this->data[index] = value;
    this->size++;
}

template<class T>
inline void Lista<T>::adauga(const T& value) {
    this->insert(this->size, value);
}

template<class T>
inline void Lista<T>::pop_back() {
    if (size > 0)
        size--;
}

template<class T>
inline void Lista<T>::push_front(const T& value) {
    this->insert(0, value);
}

template<class T>
inline void Lista<T>::pop_front() {
    if (size > 0)
        this->sterge(0);
}

template<class T>
inline void Lista<T>::sterge(int index) {
    if (index < 0 || index >= this->size) {
        throw "index gresit";
    }
    for (int i = index; i < this->size - 1; i++) {
        this->data[i] = this->data[i + 1];
    }
    this->size--;
}

template<class T>
inline void Lista<T>::clear() {
    if (this->data)
        delete[] this->data;

    this->capacity = 10;
    this->size = 0;
    this->data = nullptr;
}

template<class T>
inline bool Lista<T>::isEmpty() const {
    return this->size == 0;
}


#endif // LISTA_H

//#define VECTOR
#ifndef VECTOR
#define VECTOR

#include <vector>

template<class T>
class Lista {
private:
    std::vector<T> data;

public:
    T& operator[](int index) {
        return this->data[index];
    }

    const T& operator[](int index) const {
        return this->data[index];
    }

    int getDim() const {
        return this->data.size();
    }

    void adauga(const T& value) {
        this->data.push_back(value);
    }

    void sterge(int index) {
        this->data.erase(this->data.begin() + index);
    }
};

#endif