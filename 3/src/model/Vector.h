#ifndef LAB3_VECTOR_H
#define LAB3_VECTOR_H

#include <iostream>
#include <type_traits>
#include <iterator>  // Для iterator_category
#include <memory>
#include <limits>

template<typename T, bool is_const>
class VectorIterator {
private:
    using value_ptr_t = std::conditional_t<is_const, const T *, T *>;  // Тип указателя

    value_ptr_t current;  // Указатель на текущий элемент

public:
    // Конструктор по умолчанию
    VectorIterator() noexcept: current(nullptr) {}

    // Конструктор с параметром
    explicit VectorIterator(value_ptr_t ptr) noexcept: current(ptr) {}

    template<std::default_initializable U>
    friend
    class Vector;

    friend class VectorIterator<T, !is_const>;

    // Типы для std::iterator_traits
    using difference_type = std::ptrdiff_t;
    using value_type = T;
    using pointer = std::conditional_t<is_const, const T *, T *>;
    using reference = std::conditional_t<is_const, const T &, T &>;
    using iterator_category = std::random_access_iterator_tag;

    // Конструктор копирования итератора
    template<bool other_const>
    explicit VectorIterator(const VectorIterator<T, other_const> &other) noexcept
            : current(other.current) {}

    // Оператор присваивания (копирование)
    template<bool other_const>
    VectorIterator &operator=(const VectorIterator<T, other_const> &other) noexcept {
        current = other.current;
        return *this;
    }

    // Префиксный инкремент
    VectorIterator &operator++() noexcept {
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
    VectorIterator &operator--() noexcept {
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
    bool operator==(const VectorIterator<T, other_const> &o) const noexcept {
        return current == o.current;
    }

    // Оператор неравенства
    template<bool other_const>
    bool operator!=(const VectorIterator<T, other_const> &o) const noexcept {
        return !(*this == o);
    }

    VectorIterator &operator+=(difference_type n) noexcept {
        current += n;
        return *this;
    }

    VectorIterator operator+(difference_type n) const noexcept {
        return VectorIterator(current + n);
    }

    friend VectorIterator operator+(difference_type n, const VectorIterator &it) noexcept {
        return VectorIterator(it.current + n);
    }

    VectorIterator &operator-=(difference_type n) noexcept {
        current -= n;
        return *this;
    }

    VectorIterator operator-(difference_type n) const noexcept {
        return VectorIterator(current - n);
    }

    difference_type operator-(const VectorIterator &other) const noexcept {
        return current - other.current;
    }

    reference operator[](difference_type n) const noexcept {
        return *(current + n);
    }

    template<bool other_const>
    bool operator<(const VectorIterator<T, other_const> &o) const noexcept {
        return current < o.current;
    }

    template<bool other_const>
    bool operator<=(const VectorIterator<T, other_const> &o) const noexcept {
        return current <= o.current;
    }

    template<bool other_const>
    bool operator>(const VectorIterator<T, other_const> &o) const noexcept {
        return current > o.current;
    }

    template<bool other_const>
    bool operator>=(const VectorIterator<T, other_const> &o) const noexcept {
        return current >= o.current;
    }
};

template<std::default_initializable T>
class Vector {
private:
    T *data;
    size_t vector_size;
    size_t vector_capacity;

    void reallocate(size_t new_capacity) {
        T *new_data = new T[new_capacity];
        for (size_t i = 0; i < vector_size; ++i) {
            new_data[i] = std::move(data[i]);
        }
        delete[] data;
        data = new_data;
        vector_capacity = new_capacity;
    }

public:
    typedef T value_type;
    typedef T &reference;
    typedef const T &const_reference;
    typedef std::ptrdiff_t difference_type;
    typedef size_t size_type;

    Vector() noexcept(std::is_nothrow_default_constructible_v<T>)
            : data(nullptr), vector_size(0), vector_capacity(0) {}

    Vector(const Vector &o) requires std::copy_constructible<T>
            : Vector() {
        insert(end(), o.begin(), o.end());
    }

    Vector(Vector &&o) noexcept(std::is_nothrow_default_constructible_v<T>)
            : Vector() {
        swap(o);
    }

    Vector(size_type n, const T &t) requires std::copy_constructible<T>
            : Vector() {
        insert(end(), n, t);
    }

    template<std::input_iterator It>
    Vector(It i, It j) requires std::constructible_from<T, std::iter_reference_t<It>>
            : Vector() {
        insert(end(), i, j);
    }

    Vector(std::initializer_list<T> il) requires std::move_constructible<T>
            : Vector() {
        insert(end(), il.begin(), il.end());
    }

    Vector &operator=(const Vector &o) requires std::copy_constructible<T> {
        if (this == &o) {
            return *this;
        }
        clear();
        insert(end(), o.begin(), o.end());
        return *this;
    }

    Vector &operator=(Vector &&o) noexcept {
        swap(o);
        return *this;
    }

    Vector &operator=(std::initializer_list<T> il) requires std::move_constructible<T> {
        clear();
        insert(end(), il.begin(), il.end());
        return *this;
    }

    bool operator==(const Vector &o) const {
        return vector_size == o.vector_size &&
               std::equal(begin(), end(), o.begin(), o.end());
    }

    reference front() {
        return data[0];
    }

    const_reference front() const {
        return data[0];
    }

    reference back() {
        return data[vector_size - 1];
    }

    const_reference back() const {
        return data[vector_size - 1];
    }

    template<typename... Args>
    void emplace_front(Args &&... args) requires std::constructible_from<T, Args...> {
        emplace(begin(), std::forward<Args>(args)...);
    }

    void push_front(const T &t) requires std::copy_constructible<T> {
        insert(begin(), t);
    }

    void push_front(T &&t) requires std::move_constructible<T> {
        insert(begin(), std::move(t));
    }

    template<typename... Args>
    void emplace_back(Args &&... args) requires std::constructible_from<T, Args...> {
        emplace(end(), std::forward<Args>(args)...);
    }

    void push_back(const T &t) requires std::copy_constructible<T> {
        insert(end(), t);
    }

    void push_back(T &&t) requires std::move_constructible<T> {
        insert(end(), std::move(t));
    }

    void pop_front() noexcept {
        erase(begin());
    }

    void pop_back() noexcept {
        erase(--end());
    }

    reference at(size_type index) {
        if (index >= vector_size) {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return data[index];
    }

    const_reference at(size_type index) const {
        if (index >= vector_size) {
            throw std::out_of_range("Vector::at: index out of range");
        }
        return data[index];
    }

    ~Vector() {
        clear();
    }

    // Возврат текущего размера
    [[nodiscard]] size_t size() const noexcept {
        return vector_size;
    }

    [[nodiscard]] size_type max_size() const noexcept {
        return std::numeric_limits<size_type>::max();
    }

    [[nodiscard]] bool empty() const noexcept {
        return vector_size == 0;
    }

    void swap(Vector &other) noexcept {
        std::swap(data, other.data);
        std::swap(vector_size, other.vector_size);
        std::swap(vector_capacity, other.vector_capacity);
    }

    // Возврат текущей емкости
    [[nodiscard]] size_t capacity() const noexcept {
        return vector_capacity;
    }

    // Добавление элемента
    void push_back(const T &value) {
        if (vector_size == vector_capacity) {
            if (vector_capacity) {
                reallocate(vector_capacity * 2);
            } else {
                reallocate(1);
            }
        }
        data[vector_size++] = value;
    }

    // Доступ к элементу по индексу
    T &operator[](size_t index) {
        return data[index];
    }

    const T &operator[](size_t index) const {
        return data[index];
    }

    using iterator = VectorIterator<T, false>;
    using const_iterator = VectorIterator<T, true>;

    iterator begin() noexcept {
        return iterator(data);
    }

    iterator end() noexcept {
        return iterator(data + vector_size);
    }

    const_iterator begin() const noexcept {
        return const_iterator(data);
    }

    const_iterator end() const noexcept {
        return const_iterator(data + vector_size);
    }

    template<typename... Args>
    iterator emplace(const_iterator p, Args &&... args)requires std::constructible_from<T, Args...> {
        size_t pos = p - begin();
        if (vector_size == vector_capacity) {
            if (vector_capacity) {
                reallocate(vector_capacity * 2);
            } else {
                reallocate(1);
            }
        }
        // Сдвигаем элементы вправо
        for (size_t i = vector_size; i > pos; --i) {
            data[i] = std::move(data[i - 1]);
        }
        // Конструируем новый элемент
        data[pos] = T(std::forward<Args>(args)...);
        ++vector_size;
        return iterator(data + pos);
    }

    // Вставка копии значения
    iterator insert(const_iterator p, const T &t)requires std::copy_constructible<T> {
        return emplace(p, t);
    }

    // Вставка значения перемещением
    iterator insert(const_iterator p, T &&t)requires std::move_constructible<T> {
        return emplace(p, std::move(t));
    }

    // Вставка n копий значения
    iterator insert(const_iterator p, size_type n, const T &t)requires std::copy_constructible<T> {
        if (n == 0) {
            return iterator(const_cast<T *>(p));
        }
        size_t pos = p - begin();
        if (vector_size + n > vector_capacity) {
            reallocate(std::max(vector_capacity * 2, vector_size + n));
        }
        // Сдвигаем элементы вправо
        for (size_t i = vector_size + n - 1; i >= pos + n; --i) {
            data[i] = std::move(data[i - n]);
        }
        // Вставляем копии значения
        for (size_t i = 0; i < n; ++i) {
            data[pos + i] = t;
        }
        vector_size += n;
        return iterator(data + pos);
    }

    // Вставка элементов из диапазона [i, j)
    template<std::input_iterator It>
    iterator insert(const_iterator p, It i, It j)requires std::copy_constructible<T> {
        size_t n = std::distance(i, j);
        size_t pos = p - begin();
        if (n == 0) {
            return iterator(const_cast<T *>(p));
        }
        if (vector_size + n > vector_capacity) {
            reallocate(std::max(vector_capacity * 2, vector_size + n));
        }
        // Сдвигаем элементы вправо
        for (size_t k = vector_size + n - 1; k >= pos + n; --k) {
            data[k] = std::move(data[k - n]);
        }
        // Вставляем элементы из диапазона
        size_t idx = pos;
        try {
            for (auto it = i; it != j; ++it) {
                new(&data[idx]) T(*it);
                ++idx;
            }
        } catch (...) {
            // Уничтожаем элементы, начиная с последнего успешного
            while (idx > pos) {
                data[idx--].~T();
            }
            throw;
        }
        vector_size += n;
        return iterator(data + pos);
    }

    // Вставка элементов из списка инициализации
    iterator insert(const_iterator p, std::initializer_list<T> il)requires std::move_constructible<T> {
        return insert(p, il.begin(), il.end());
    }

    // Удаление одного элемента
    iterator erase(const_iterator pos) noexcept {
        size_t goal = pos - begin();
        if (goal >= vector_size) {
            return end();
        }

        for (size_t i = goal; i < vector_size - 1; ++i) {
            data[i] = std::move(data[i + 1]);
        }

        --vector_size;
        return begin() + goal;
    }

// Удаление элементов в диапазоне [first, last)
    iterator erase(const_iterator first, const_iterator last) noexcept {
        size_t start = first - begin();
        size_t end = last - begin();

        if (start >= vector_size || start >= end) {
            return this->end();
        }

        size_t num_to_delete = end - start;

        for (size_t i = start; i < vector_size - num_to_delete; ++i) {
            data[i] = std::move(data[i + num_to_delete]);
        }

        vector_size -= num_to_delete;
        return begin() + start;
    }

// Удаление всех элементов
    void clear() noexcept {
        for (size_t i = 0; i < vector_size; ++i) {
            data[i].~T();
        }
        vector_size = 0;
    }

    template<std::forward_iterator It>
    void assign(It i, It j) requires std::copy_constructible<T> {
        if (empty()) {
            insert(end(), i, j);
            return;
        }
        Vector temp;
        temp.insert(temp.end(), i, j);
        swap(temp);
    }

    void assign(std::initializer_list<T> il) requires std::copy_constructible<T> {
        if (empty()) {
            insert(end(), il.begin(), il.end());
            return;
        }
        Vector temp;
        temp.insert(temp.end(), il.begin(), il.end());
        swap(temp);
    }


};


#endif //LAB3_VECTOR_H
