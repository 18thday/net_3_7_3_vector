#include <cassert>
#include <iostream>

template <typename T>
class Vector {
public:
    Vector() = default;
    Vector(size_t size) : raw_ptr_(new T[size == 0 ? 1 : size]), size_(0), capacity_(size == 0 ? 1 : size) {
    }

    Vector(const Vector& other) : raw_ptr_(new T[other.size_]), size_(0), capacity_(other.capacity_) {
        for (size_t i = 0; i < other.size_; ++i) {
            raw_ptr_[i] = other[i];
        }
        size_ = other.size_;
    }
    Vector& operator=(const Vector& other) {
        Vector temp(other);
        swap(temp);
        return *this;
    }

    ~Vector() {
        Clear();
    }


    T& at(int index) {
        assert(index >= 0 && index < size_);
        return raw_ptr_[index];
    }

    const T& at(int index) const {
        assert(index >= 0 && index < size_);
        return raw_ptr_[index];
    }

    size_t size() const {
        return size_;
    }

    T& operator[](size_t index) {
        return raw_ptr_[index];
    }
    const T& operator[](size_t index) const{
        return raw_ptr_[index];
    }

    void push_back(T value) {
        if (size_ == capacity_) {
            Reallocate();
        }
        raw_ptr_[size_] = value;
        ++size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    void clear() {
        size_ = 0;
    }

    void swap(Vector& other) {
        std::swap(raw_ptr_, other.raw_ptr_);
        std::swap(size_, other.size_);
        std::swap(capacity_, other.capacity_);
    }

private:
    T* raw_ptr_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;

    void Reallocate() {
        Vector temp(2 * size_);
        for (size_t i = 0; i < size_; ++i) {
            temp.push_back(raw_ptr_[i]);
        }
        swap(temp);
    }

    void Clear() {
        delete[] raw_ptr_;
        raw_ptr_ = nullptr;
        size_ = 0;
        capacity_ = 0;
    }

};

int main() {
    size_t size = 5;
    Vector<int> v(size);
    for (size_t i = 0; i < size; ++i) {
        v.push_back(i);
    }

    std::cout << "size: " << v.size() << ", capacity: " << v.capacity() << std::endl;
    std::cout << "Vector v:";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << " " << v.at(i);
    }
    std::cout << std::endl;

    v.push_back(5);
    std::cout << "\nAfter push_back\n";
    std::cout << "size: " << v.size() << ", capacity: " << v.capacity() << std::endl;
    std::cout << "Vector v:";
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << " " << v.at(i);
    }
    std::cout << std::endl;


    return 0;
}
