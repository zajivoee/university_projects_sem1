#include <iostream>

class Array {
public:
<<<<<<< HEAD
    Array(std::ostream& ostream);
    Array(const Array& array);
    Array(size_t size, std::ostream& ostream = std::cout, int defaultValue = 0);
    ~Array();

    size_t Size() const;
    size_t Capacity() const;
    void Reserve(size_t newCapacity);
    void Resize(size_t newSize);
    void PushBack(int value = 0);
    void PopBack();

    const int& operator[](const size_t i) const;
    int& operator[](const size_t i);
    explicit operator bool() const;

    bool operator<(const Array& it) const;
    bool operator>(const Array& it) const;
    bool operator!=(const Array& it) const;
    bool operator==(const Array& it) const;
    bool operator<=(const Array& it) const;
    bool operator>=(const Array& it) const;

    Array& operator<<(const int value);
    Array& operator<<(const Array& it);
=======
    Array(std::ostream& ostream)
        : Ostream_(ostream) {
        size_ = 0;
        capacity_ = 2;
        data_ = new int[capacity_];
        Ostream_.clear();
        Ostream_ << "Constructed. " << (*this);
    }

    Array(const Array& array) 
        : Ostream_(array.Ostream_) {
        size_ = array.size_;
        capacity_ = array.capacity_;
        data_ = new int[array.capacity_];
        for (size_t i = 0; i < this->size_; ++i) {
            this->data_[i] = array[i];
        }
        Ostream_.clear();
        Ostream_ << "Constructed from another Array. " << (*this);
    }

    Array(size_t size, std::ostream& ostream = std::cout, int defaultValue = 0)
        : Ostream_(ostream) {
        size_ = size;
        capacity_ = 2 * size;
        data_ = new int[capacity_];
        for (size_t i = 0; i < size; ++i) {
            this->data_[i] = defaultValue;
        }
        Ostream_.clear();
        ostream << "Constructed with default. " << (*this);
    }

    ~Array() {
        delete[] data_;
        Ostream_.clear();
        Ostream_ << "Destructed " << this->size_ << std::endl;
    }

    size_t Size() const {
        return size_;
    }

    size_t Capacity() const {
        return capacity_;
    }

    void Reserve(size_t newCapacity) {
        if (this->capacity_ >= newCapacity) {
            return;
        }
        capacity_ = newCapacity;
        int* NewData = new int[capacity_];
        for (size_t i = 0; i < this->size_; ++i) {
            NewData[i] = data_[i];
        }
        delete[] data_;
        data_ = NewData;
    }

    void Resize(size_t newSize) {
        if (newSize >= this->capacity_) {
            this->Reserve(newSize);
            for (size_t i = this->size_; i < newSize; ++i) {
                (*this)[i] = 0;
            }
        }
        this->size_ = newSize;
    }

    void PushBack(int value = 0) {
        this->data_[this->size_] = value;
        this->size_ += 1;
        if (size_ == capacity_){
            this->Reserve(capacity_*2);
        }
    }

    void PopBack() {
        --size_;
    }

    const int& operator[](const size_t i) const {
        return const_cast<Array*>(this)->operator[](i);
    }

    int& operator[](const size_t i) {
        return data_[i];
    }

    explicit operator bool() const {
        if (size_ != 0) {
            return true;
        }
        return false;
    }

    bool operator <(const Array& it) const {
        for (size_t i = 0; i < std::min(this->size_, it.Size()); ++i) {
            return (*this)[i] < it[i];
        }
        return (this->size_ < it.Size());
    }

     bool operator >(const Array& it) const {
        for (size_t i = 0; i < std::min(this->size_, it.Size()); ++i) {
            return (*this)[i] > it[i];
        }
        return (this->size_ > it.Size());
    }

    bool operator!=(const Array& it) const{
        for (size_t i = 0; i < std::min(this->size_, it.Size()); ++i) {
            return (*this)[i] != it[i];
        }
        return this->size_ != it.Size();
    }

    bool operator==(const Array& it) const{
        for (size_t i = 0; i < std::min(this->size_, it.Size()); ++i) {
            return (*this)[i] == it[i];
        }
        return this->size_ == it.Size();
    }

    bool operator <=(const Array& it) const {
        for (size_t i = 0; i < std::min(this->size_, it.Size()); ++i) {
            return (*this)[i] <= it[i];
        }
        return (this->size_ <= it.Size());
    }

     bool operator >=(const Array& it) const {
        for (size_t i = 0; i < std::min(this->size_, it.Size()); ++i) {
            return (*this)[i] >= it[i];
        }
        return (this->size_ >= it.Size());
    }

    Array& operator<<(const int value) {
        PushBack(value);
        return *this;
    }

    Array& operator<<(const Array& it) {
        if (this->capacity_ <= this->size_ + it.Size()) {
            Reserve((this->size_ + it.Size()) * 2);
        }
        for (size_t i = this->size_; i < this->size_ + it.Size(); ++i) {
            data_[i] = it[i-this->size_];
        }
        this->size_ += it.Size();
        return *this;
    }
>>>>>>> d84f149 (array 1st commit)

    friend std::ostream& operator<<(std::ostream& ostream, const Array& array);

private:
<<<<<<< HEAD
    std::ostream& Ostream_;
    // ...
};

=======
    size_t size_, capacity_;
    int *data_;
    std::ostream& Ostream_;
    void CopyData(int* source, int* destination) {
        for (size_t i = 0; i < size_; ++i) {
            destination[i] = source[i];
        }
    }
};

std::ostream& operator<<(std::ostream& ostream, const Array& array) {
    ostream.clear();
    ostream << "Result Array's capacity is " << array.Capacity() << " and size is " << array.Size();
    if (array.Size() > 0){
        ostream << ", elements are: ";
        for (size_t i = 0; i < array.Size() - 1; ++i) {
            ostream << array[i] << ", ";
        }
        ostream << array[array.Size() - 1];
    }
    return ostream;
}
>>>>>>> d84f149 (array 1st commit)
