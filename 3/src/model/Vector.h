#ifndef LAB3_VECTOR_H
#define LAB3_VECTOR_H

#include <iostream>
#include <type_traits>
#include <iterator>  // Для iterator_category

template<typename T>
class Vector {
private:
    T* data;
    size_t size;
    size_t capacity;

public:
    Vector() : data(nullptr), size(0), capacity(0) {}

    ~Vector() {
        delete[] data;
    }
};

template<typename T, bool is_const>
class VectorIterator {
private:
    using value_ptr_t = std::conditional_t<is_const, const T *, T *>;  // Тип указателя

    value_ptr_t current;  // Указатель на текущий элемент

public:
    // Конструктор по умолчанию
    VectorIterator() noexcept : current(nullptr) {}

    // Конструктор с параметром
    explicit VectorIterator(value_ptr_t ptr) noexcept : current(ptr) {}

    template<typename U>
    friend class Vector;

    friend class VectorIterator<T, !is_const>;

    // Типы для std::iterator_traits
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = std::conditional_t<is_const, const T *, T *>;
    using reference = std::conditional_t<is_const, const T &, T &>;
    using iterator_category = std::random_access_iterator_tag;

    // Конструктор копирования итератора
    template<bool other_const>
    explicit VectorIterator(VectorIterator<T, other_const>& other) noexcept
            : current(other.current) {}

    // Оператор присваивания (копирование)
    template<bool other_const>
    VectorIterator& operator=(const VectorIterator<T, other_const>& other) noexcept {
        current = other.current;
        return *this;
    }

    // Префиксный инкремент
    VectorIterator& operator++() noexcept {
        ++current;
        return *this;
    }

    // Постфиксный инкремент
    VectorIterator operator++(int) noexcept {
        VectorIterator temp(*this);
        ++current;
        return temp;
    }

    // Префиксный декремент
    VectorIterator& operator--() noexcept {
        --current;
        return *this;
    }

    // Постфиксный декремент
    VectorIterator operator--(int) noexcept {
        VectorIterator temp(*this);
        --current;
        return temp;
    }

    // Оператор разыменования
    reference operator*() const noexcept {
        return *current;
    }

    // Оператор доступа к членам через ->
    pointer operator->() const noexcept {
        return current;
    }

    // Оператор равенства
    template<bool other_const>
    bool operator==(const VectorIterator<T, other_const>& o) const noexcept {
        return current == o.current;
    }

    // Оператор неравенства
    template<bool other_const>
    bool operator!=(const VectorIterator<T, other_const>& o) const noexcept {
        return !(*this == o);
    }

    VectorIterator& operator+=(difference_type n) noexcept {
        current += n;
        return *this;
    }

    VectorIterator operator+(difference_type n) const noexcept {
        return VectorIterator(current + n);
    }

    friend VectorIterator operator+(difference_type n, const VectorIterator& it) noexcept {
        return VectorIterator(it.current + n);
    }

    VectorIterator& operator-=(difference_type n) noexcept {
        current -= n;
        return *this;
    }

    VectorIterator operator-(difference_type n) const noexcept {
        return VectorIterator(current - n);
    }

    difference_type operator-(const VectorIterator& other) const noexcept {
        return current - other.current;
    }

    reference operator[](difference_type n) const noexcept {
        return *(current + n);
    }

    template<bool other_const>
    bool operator<(const VectorIterator<T, other_const>& o) const noexcept {
        return current < o.current;
    }

    template<bool other_const>
    bool operator<=(const VectorIterator<T, other_const>& o) const noexcept {
        return current <= o.current;
    }

    template<bool other_const>
    bool operator>(const VectorIterator<T, other_const>& o) const noexcept {
        return current > o.current;
    }

    template<bool other_const>
    bool operator>=(const VectorIterator<T, other_const>& o) const noexcept {
        return current >= o.current;
    }
};

#endif //LAB3_VECTOR_H
