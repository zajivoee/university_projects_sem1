#include <iostream>

template<typename T>
class Array {
public:
    Array(std::ostream& ostream)
        : Ostream_(ostream) {
        size_ = 0;
        capacity_ = 2;
        data_ = new T[capacity_];
        Ostream_.clear();
        Ostream_ << " Constructed. " << (*this);
    }

    Array(const Array<T>& array) 
        : Ostream_(array.Ostream_) {
        size_ = array.size_;
        capacity_ = array.capacity_;
        data_ = new T[array.capacity_];
        for (size_t i = 0; i < this->size_; ++i) {
            this->data_[i] = array[i];
        }
        Ostream_.clear();
        Ostream_ << " Constructed from another Array. " << (*this);
    }
    
    Array(size_t size, std::ostream& ostream = std::cout, T defaultValue = T()) 
        : Ostream_(ostream) {
        size_ = size;
        capacity_ = 2 * size;
        data_ = new T[capacity_];
        for (size_t i = 0; i < size; ++i) {
            this->data_[i] = defaultValue;
        }
        Ostream_.clear();
        ostream << " Constructed with default. " << (*this);
    }

    ~Array() {
        delete[] data_;
        Ostream_.clear();
        Ostream_ << " Destructed " << this->size_ << std::endl;
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
        T* NewData = new T[capacity_];
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

    void PushBack(T value = 0) {
        this->data_[this->size_] = value;
        this->size_ += 1;
        if (size_ == capacity_){
            this->Reserve(capacity_*2);
        }
    }

    void PopBack() {
        --size_;
    }

    const T& operator [](const size_t i) const {
        return const_cast<Array*>(this)->operator[](i);
    }

    T& operator [](const size_t i) {
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
            if (this->data_[i] != it[i]) {
                return (*this)[i] < it[i];
            }
        }
        return this->size_ < it.Size();
    }

    bool operator >(const Array& it) const {
        for (size_t i = 0; i < std::min(this->size_, it.Size()); ++i) {
            if (this->data_[i] != it[i]) {
                return (*this)[i] > it[i];
            }
        }
        return this->size_ > it.Size();
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

    Array<T>& operator <<(const T& value) {
        PushBack(value);
        return *this;
    }

    Array<T>& operator <<(const Array<T>& it) {
        if (this->capacity_ <= this->size_ + it.Size()) {
            Reserve((this->size_ + it.Size()) * 2);
        }
        for (size_t i = this->size_; i < this->size_ + it.Size(); ++i) {
            data_[i] = it[i-this->size_];
        }
        this->size_ += it.Size();
        return *this;
    }

    bool Insert(size_t pos, const T& value) {
        if (pos > this->size_){
            return false;
        }
        for (size_t i = size_; i > pos; --i){
            this->data_[i] = this->data_[i - 1];
        }
        this->data_[pos] = value;
        ++size_;
        return true;
    }

    bool Erase(size_t pos) {
        if (pos > this->size_){
            return false;
        }
        for (size_t i = pos; i < size_ - 1; ++i) {
            this->data_[i] = this->data_[i + 1];
        }
        --size_;
        return true;
    }

private:
    size_t size_, capacity_;
    T *data_;
    std::ostream& Ostream_;

};

template<typename T>
std::ostream& operator <<(std::ostream& ostream, const Array<T>& array) {
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