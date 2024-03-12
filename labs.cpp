#include <iostream>
#include <cassert>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
namespace lab11
{
    struct list_node
    {
        double value = 0;
        list_node* next = nullptr;
    };
    struct list_t
    {
        size_t size = 0;
        list_node* head = nullptr;
    };
    list_t make_list()
    {
        return   list_t{};
    }
    list_t make_list(double value)
    {
        return list_t{ 1,new list_node{value } };
    }
    size_t size(list_t& list)
    {
        return list.size;
    }

    void clear(list_t& list)
    {
        list_node* cur = list.head;
        while (cur)
        {
            list_node* cur1 = cur;
            cur = cur->next;
            delete cur1;
        }
        list = make_list();
    }
    void print(list_t& list)
    {
        list_node* head = list.head;
        std::cout << "[";
        if (!list.head)
        {
            std::cout << "]";
            return;
        }
        while (head->next)
        {
            std::cout << head->value << ", ";
            head = head->next;
        }
        std::cout << head->value << "]";
    }
    void println(list_t& list)
    {
        print(list);
        std::cout << "\n";
    }
    void append(list_t& list, double new_value)
    {
        auto new_node = new list_node{ new_value };
        if (!list.head)
        {
            list.head = new_node;
            list.size = 1;
            return;
        }
        list_node* cur = list.head;
        while (cur->next)
            cur = cur->next;
        cur->next = new_node;
        ++list.size;
    }
    void append(list_t& list, list_t& another_list)
    {

        list_node* cur = list.head;
        list_node* a_cur = another_list.head;
        if (!a_cur) {
            return;
        }
        if (!cur)
        {
            while (a_cur) {
                append(list, a_cur->value);
                a_cur = a_cur->next;
            }
            return;
        }
        while (cur->next)
            cur = cur->next;
        while (a_cur)
        {
            auto new_node = new list_node{ a_cur->value };
            cur->next = new_node;
            a_cur = a_cur->next;
            cur = cur->next;
            ++list.size;
        }
    }
    void copy(list_t& list, list_t& another_list)
    {
        clear(list);
        append(list, another_list);
    }
    void check(list_t list, list_t list1)
    {
        print(list); //вывод содержимого списка в консоль
        std::cout << " ";
        println(list1);//вывод содержимого списка в консоль с сносом строки
    }
    void test()
    {
        list_t list1 = make_list(14);//создание списка заданным первым элементом
        list_t list2 = make_list();//создание пустого списка
        check(list1, list2);
        append(list1, 13);//Добавление в список элемента
        append(list2, list1);//Добавление к списку списка
        append(list2, 16);
        check(list1, list2);
        std::cout << "size of list: " << size(list1) << "\n";//вывод длины списка
        copy(list1, list2);//копирования значений списка с освобождением памяти
        print(list1);
        std::cout << " ";
        println(list2);
        clear(list1);//удаление списка с освобождением памяти

    }
}
namespace lab12
{

    struct list_node
    {
        double value = 0;
        list_node* next = nullptr;
    };

    struct list_t
    {
        list_node* head = nullptr;
        list_node* tail = nullptr;
        size_t size = 0;
    };

    list_t make_list(double value)
    {
        auto list = list_t{ new list_node{ value } };
        list.tail = list.head;
        list.size = 1;
        return list;
    }

    list_t make_list()
    {
        return list_t{};
    }

    void print(const list_t& list)
    {
        list_node* cur = list.head;
        while (cur)
        {
            std::cout << cur->value << ", ";
            cur = cur->next;
        }
    }
    void println(const list_t& list)
    {
        print(list);
        std::cout << '\n';
    }
    size_t size(const list_t& list)
    {
        return list.size;
    }

    void append(list_t& list, double new_value)
    {
        auto new_node = new list_node{ new_value };
        if (!list.head)
        {
            list.head = new_node;
        }
        else
        {
            list.tail->next = new_node;
        }
        list.tail = new_node;
        ++list.size;
    }
    void append(list_t& list, const list_t& another_list)
    {
        list_node* from_cur = another_list.head;

        if (!list.head && from_cur)
        {
            auto tmp_head = new list_node{ from_cur->value };

            list.head = tmp_head;
            list.tail = tmp_head;
            from_cur = from_cur->next;
        }

        while (from_cur)
        {
            auto tmp_head = new list_node{ from_cur->value };
            list.tail->next = tmp_head;
            list.tail = tmp_head;
            ++list.size;
            from_cur = from_cur->next;
        }
    }

    list_t clone(const list_t& list)
    {
        auto new_list = make_list();
        append(new_list, list);
        return new_list;
    }

    void clear(list_t& list)
    {
        list_node* cur = list.head;
        while (cur)
        {
            auto tmp = cur;
            cur = cur->next;
            delete tmp;
        }
        list.head = nullptr;
        list.size = 0;
    }

    void copy(list_t& list, const list_t& another_list)
    {
        //auto tmp = make_list(); //безопасно относительно исключений, без утечки памяти
        //try
        //{
        //    tmp = clone(another_list);
        //}
        //catch (std::bad_alloc& ex)
        //{
        //    clear(tmp);
        //    throw ex;
        //}
        auto tmp = clone(another_list); //безопасно относительно исключений, но с утечкой памяти
        clear(list);
        list = tmp; //низкоуровневое копирование - копирует только члены структуры
    }


    void test()
    {
        list_t list;
        println(list);
        std::cout << size(list) << std::endl;

        auto l2 = make_list(15);
        auto l3 = make_list(39);
        append(l2, 37);
        append(l2, 23);
        println(l2);

        auto& list2 = list;
        copy(list, list2);

        std::cout << size(l2) << std::endl;
    }
}
namespace lab13
{

    struct list_node
    {
        double value = 0;
        list_node* next = nullptr;
    };

    struct list_t
    {
        list_node* head = nullptr;
        list_node* tail = nullptr;
        size_t size = 0;
    };
    struct list_iterator
    {
        list_node* cur;
    };
    list_iterator begin(const list_t& cont)
    {
        return list_iterator{ cont.head };
    }
    list_iterator end(const list_t& cont)
    {
        return list_iterator{ nullptr };
    }

    bool operator!=(list_iterator a, list_iterator b)
    {
        return a.cur != b.cur;
    }

    list_iterator& operator++(list_iterator& it)
    {
        it.cur = it.cur->next;
        return it;
    }
    list_iterator operator++(list_iterator& it, int) //постфиксный
    {
        list_iterator tmp = it;
        it.cur = it.cur->next;
        return tmp;
    }
    double& deref(list_iterator it)
    {
        return it.cur->value;
    }

    double& operator*(list_iterator it)
    {
        return deref(it);
    }


    list_t make_list(double value)
    {
        auto list = list_t{ new list_node{ value } };
        list.tail = list.head;
        list.size = 1;
        return list;
    }

    list_t make_list()
    {
        return list_t{};
    }

    void print(const list_t& list)
    {
        list_node* cur = list.head;
        /* while (cur)
         {
             std::cout << cur->value << ", ";
             cur = cur->next;
         }*/
        for (auto cur = begin(list), e = end(list); cur != e; ++cur)
        {
            std::cout << cur.cur->value << ", ";

        }
    }
    void println(const list_t& list)
    {
        print(list);
        std::cout << '\n';
    }
    size_t size(const list_t& list)
    {
        return list.size;
    }

    void append(list_t& list, double new_value)
    {
        auto new_node = new list_node{ new_value };
        if (!list.head)
        {
            list.head = new_node;
        }
        else
        {
            list.tail->next = new_node;
        }
        list.tail = new_node;
        ++list.size;
    }
    void append(list_t& list, const list_t& another_list)
    {
        list_node* from_cur = another_list.head;

        if (!list.head && from_cur)
        {
            auto tmp_head = new list_node{ from_cur->value };

            list.head = tmp_head;
            list.tail = tmp_head;
            from_cur = from_cur->next;
        }

        while (from_cur)
        {
            auto tmp_head = new list_node{ from_cur->value };
            list.tail->next = tmp_head;
            list.tail = tmp_head;
            ++list.size;
            from_cur = from_cur->next;
        }
    }

    list_t clone(const list_t& list)
    {
        auto new_list = make_list();
        append(new_list, list);
        return new_list;
    }

    void clear(list_t& list)
    {
        list_node* cur = list.head;
        while (cur)
        {
            auto tmp = cur;
            cur = cur->next;
            delete tmp;
        }
        //for (auto cur = begin(list), e = end(list); cur != e; ++cur)
        //{
        //        auto tmp = cur;
        //        delete tmp.cur;
        //}
        list.head = nullptr;
        list.tail = nullptr;
        list.size = 0;
    }

    void copy(list_t& list, const list_t& another_list)
    {
        //auto tmp = make_list(); //безопасно относительно исключений, без утечки памяти
        //try
        //{
        //    tmp = clone(another_list);
        //}
        //catch (std::bad_alloc& ex)
        //{
        //    clear(tmp);
        //    throw ex;
        //}
        auto tmp = clone(another_list); //безопасно относительно исключений, но с утечкой памяти
        clear(list);
        list = tmp; //низкоуровневое копирование - копирует только члены структуры
    }

    void lab()
    {
        list_t list;
        println(list);
        std::cout << size(list) << std::endl;

        auto l2 = make_list(15);
        append(l2, 37);
        append(l2, 52);
        println(l2);
        append(list, 1);
        append(list, 2);
        println(list);
        copy(list, l2);
        println(list);

        for (auto x : list) {
            std::cout << x;
        }
        std::cout << size(l2) << std::endl;
    }
}
namespace lab21
{
    template<typename T>
    struct list_node
    {
        T value = 0;
        list_node* next = nullptr;
    };
    template<typename T>
    struct list_iterator
    {
        list_node<T>* cur;
        list_iterator(list_node<T>* node) :cur(node) {};
        bool operator!=(list_iterator b) { return this->cur != b.cur; };
        list_iterator& operator++() { cur = cur->next; return *this; };
        double& operator*() { return cur->value; };
    };
    template<typename T>
    struct list_const_iterator
    {
        const  list_node<T>* cur;

        list_const_iterator(const list_node<T>* node) :cur(node) {};
        bool operator!=(list_const_iterator<T> b) { return this->cur != b.cur; };
        list_const_iterator<T>& operator++() { cur = cur->next; return *this; };
        const T& operator*() { return cur->value; };
    };
    template<typename T>
    class list_t
    {
    private:
        list_node<T>* head = nullptr;
        list_node<T>* tail = nullptr;
        size_t size = 0;
    public:

        list_iterator<T> begin();
        list_iterator<T> end();
        list_const_iterator<T> begin() const;
        list_const_iterator<T> end() const;
        list_t<T>& operator+=(const list_t<T>& another_list);
        list_t<T>& operator+=(const T new_value);
        list_t<T> operator+(const T new_value);
        list_t<T> operator+(const list_t<T>& another_list);
        list_t<T>& operator=(const list_t<T>& another_list);
        void append(const list_t& another_list);
        void append(const T new_value);
        void clear(list_t& list);
        void swap(list_t& another_list);

        list_t()
        {
        }

        list_t(const list_t& list) {
            auto rhs_cur = list.head;
            if (rhs_cur)
            {
                head = tail = new list_node<T>{ rhs_cur->value };
                ++size;
                rhs_cur = rhs_cur->next;
            }
            while (rhs_cur)
            {
                tail = tail->next = new list_node<T>{ rhs_cur->value };
                ++size;
                rhs_cur = rhs_cur->next;
            }
        }; //конструктор копирования

        list_t(T value)
            : head(new list_node<T>{ value })
            , tail(head)
            , size(1)
        {
            //this->head;
            //head;
        }

        list_t(list_t<T>&& list) noexcept
        {
            swap(list);
        }

        ~list_t() //destructor
        {
            clear(*this);
            // std::cout << "dtor" << std::endl;
        }

    };
    template<typename T>
    void list_t<T>::swap(list_t<T>& list) {
        std::swap(head, list.head);
        std::swap(tail, list.tail);
        std::swap(size, list.size);
    }
    template<typename T>
    list_iterator<T> list_t<T>::begin()
    {
        return list_iterator<T>(head);
    }
    template<typename T>
    list_iterator<T> list_t<T>::end()
    {
        return list_iterator<T>(nullptr);
    }
    //list_const_iterator list_t::cbegin()
    //{
    //    return list_const_iterator(head);
    //}
    //list_const_iterator list_t::cend()
    //{
    //    return list_const_iterator(nullptr);
    //}
    //list_const_iterator list_t::cbegin() const
    //{
    //    return list_const_iterator(head);
    //}
    //list_const_iterator list_t::cend() const
    //{
    //    return list_const_iterator(nullptr);
    //}
    template<typename T>
    list_const_iterator<T> list_t<T>::begin() const
    {
        return list_const_iterator<T>(head);
    }
    template<typename T>
    list_const_iterator<T> list_t<T>::end() const
    {
        return list_const_iterator<T>(nullptr);
    }
    template<typename T>
    void list_t<T>::clear(list_t<T>& list)
    {
        list_node<T>* cur = list.head;
        while (cur)
        {
            auto tmp = cur;
            cur = cur->next;
            delete tmp;
        }
        list.head = nullptr;
        list.size = 0;
    }
    template<typename T>
    void list_t<T>::append(T new_value)
    {
        auto new_node = new list_node<T>{ new_value };
        if (!head)
        {
            head = new_node;
        }
        else
        {
            tail->next = new_node;
        }
        tail = new_node;
        ++size;
    }
    template<typename T>
    void list_t<T>::append(const list_t<T>& another_list)//TODO реализовать аппенд через форыч
    {
        auto tmp(another_list);

        if (!head)
        {
            head = tmp.head;
        }
        else
        {
            tail->next = tmp.head;
        }
        tail = tmp.tail;
        size += tmp.size;

        tmp.head = nullptr;
        tmp.tail = nullptr;
        tmp.size = 0;

    }
    template<typename T>
    list_t<T>& list_t<T>::operator=(const list_t<T>& another_list)
    {
        auto tmp(another_list);
        swap(tmp);
        return *this;
    }
    template<typename T>
    list_t<T>& list_t<T>:: operator+=(const T new_value)
    {
        this->append(new_value);
        return *this;
    }
    template<typename T>
    list_t<T>& list_t<T>::operator+=(const list_t<T>& another_list)
    {
        this->append(another_list);
        return *this;

    }
    template<typename T>
    list_t<T> list_t<T>::operator+(const T new_value)
    {
        auto tmp(*this);
        tmp.append(new_value);
        return tmp;
    }
    template<typename T>
    list_t<T> list_t<T>::operator+(const list_t<T>& another_list)
    {
        auto tmp(*this);
        tmp.append(another_list);
        return tmp;
    }
    template<typename T>
    list_iterator<T> begin(list_t<T>& list)
    {
        return list.begin();
    }
    template<typename T>
    list_iterator<T> end(list_t<T>& list)
    {
        return list.end();
    }


    template<typename T>
    list_const_iterator<T> begin(const list_t<T>& list)
    {
        return list.begin();
    }
    template<typename T>
    list_const_iterator<T> end(const list_t<T>& list)
    {
        return list.end();
    }
    template<typename T>
    void print(const list_t<T>& list)
    {
        //auto& list_ = const_cast<list_t&>(list);
        //forfor(auto x  : list_)
        for (auto x : list)
        {
            //std::cout << a.cur->value << " ";
            std::cout << x << " ";
        }
    }
    template<typename T>
    void println(const list_t<T>& list)
    {
        print(list);
        std::cout << std::endl;
    }
    template<typename T>
    std::ostream& operator<<(std::ostream& out, const list_t<T>& list) {
        for (auto& x : list)
        {
            out << x << " ";
        }
        return out;
    }
    void lab2_test()
    {
        list_t<double> list{ 1.2 };
        list.append(2);
        list.append(3);
        list += 2;
        list_t<double> list2{ 57 };
        list2.append(12);
        list2.append(31);
        println(list);
        println(list2);
        list.append(list2);
        list += list2;
        auto a = list + list2;
        println(list);
        println(list2);
        list.swap(list2);
        println(list);
        println(list2);
        println(a);
        list = a;
        println(list);
        std::cout << list;
    }

}
namespace lab3
{
    template<typename T>
    class dyn_array
    {
    public:
        dyn_array();
        dyn_array(size_t size);
        dyn_array(size_t size, T value);
        dyn_array(std::initializer_list<T> init);
        dyn_array(const dyn_array<T>& rhs);
        dyn_array(dyn_array<T>&& rhs) noexcept;
        ~dyn_array();
        dyn_array<T>& operator=(const dyn_array<T>& rhs);
        dyn_array<T>& operator=(dyn_array<T>&& rhs) noexcept;
    public:
        void swap(dyn_array<T>& rhs) noexcept;
        void clear();
        size_t size() const;
        T& operator[](size_t ind);
        const T& operator[](size_t ind) const;
    private:
        T* _data = nullptr;
        size_t _size = 0;
    };
    template<typename T>
    dyn_array<T>::dyn_array()
    {
    }
    template<typename T>
    dyn_array<T>::dyn_array(size_t size)
        :_data(new T[size]),
        _size(size)
    {
    }
    template<typename T>
    dyn_array<T>::dyn_array(size_t size, T value)
        : _data(new T[size]),
        _size(size)
    {
        std::fill_n(_data, _size, value);
    }
    template<typename T>
    dyn_array<T>::dyn_array(std::initializer_list<T> init)
        :_data(new T[init.size()]),
        _size(init.size())
    {
        std::copy(init.begin(), init.end(), _data);
    }
    template<typename T>
    dyn_array<T>::dyn_array(const dyn_array<T>& rhs)
        :_data(new T[rhs.size()]),
        _size(rhs.size())
    {
        std::copy(rhs._data, rhs._data + rhs._size, _data);
    }
    template<typename T>
    dyn_array<T>::dyn_array(dyn_array<T>&& rhs) noexcept

    {
        swap(rhs);
    }
    template<typename T>
    dyn_array<T>::~dyn_array()
    {
        std::cout << "dtor " << size() << std::endl;
        clear();
    }
    template<typename T>
    dyn_array<T>& dyn_array<T>::operator=(const dyn_array<T>& rhs)
    {
        //if (this != &rhs)
        //{
        //    clear();
        //    _data = new T[rhs._size];
        //    _size = rhs._size;
        //    std::copy(rhs._data, rhs._data + rhs._size, _data);
        //}
        auto temp(rhs);
        swap(temp);
        return *this;
    }
    template<typename T>
    dyn_array<T>& dyn_array<T>::operator=(dyn_array<T>&& rhs) noexcept
    {
        //if (this != &rhs) {
        //    clear();
        //    _data = rhs._data;
        //    _size = rhs._size;
        //    rhs._data = nullptr;
        //    rhs._size = 0;
        //}
        swap(rhs);
        return *this;
    }

    template<typename T>
    void dyn_array<T>::swap(dyn_array<T>& rhs) noexcept
    {
        std::swap(_data, rhs._data);
        std::swap(_size, rhs._size);
    }
    template<typename T>
    size_t dyn_array<T>::size() const
    {
        return _size;
    }
    template<typename T>
    T& dyn_array<T>::operator[](size_t ind)
    {
        assert(ind < _size);
        return _data[ind];
    }
    template<typename T>
    const T& dyn_array<T>::operator[](size_t ind) const
    {
        assert(ind < _size);
        return _data[ind];
    }
    template<typename T>
    void dyn_array<T>::clear()
    {
        delete[] _data;
        _data = nullptr;
        _size = 0;
    }

    template<typename T>
    std::ostream& operator<<(std::ostream& out, const dyn_array<T>& arr)
    {
        for (int i = 0; i < arr.size(); ++i)
        {
            out << arr[i] << " ";
        }
        return out;
    }

    template<typename T>
    dyn_array<T>& operator+=(dyn_array<T>& lhs, const dyn_array<T>& rhs)
    {
        assert(lhs.size() == rhs.size());

        for (size_t i = 0; i < lhs.size(); ++i)
        {
            lhs[i] += rhs[i];
        }
        return lhs;
    }
    template<typename T>
    dyn_array<T>&& operator+=(dyn_array<T>&& lhs, const dyn_array<T>& rhs)
    {
        assert(lhs.size() == rhs.size());
        return std::move(lhs += rhs);
    }
    template<typename T>
    dyn_array<T> operator+(const dyn_array<T>& lhs, dyn_array<T>&& rhs)
    {
        assert(lhs.size() == rhs.size());


        return std::move(rhs) += lhs;
    }
    template<typename T>
    dyn_array<T> operator+(const dyn_array<T>& lhs, const dyn_array<T>& rhs)
    {

        assert(lhs.size() == rhs.size());

        //dyn_array<T> result(lhs.size);
        //for (size_t i = 0; i < lhs.size(); ++i)
        //{
        //    result[i] = lhs[i] + rhs[i];
        //}
        //return result;
        return lhs + dyn_array<T>(rhs);

    }
    template<typename T>
    dyn_array<T> operator+(dyn_array<T>&& lhs, const dyn_array<T>& rhs)
    {
        return rhs + std::move(lhs);
    }
    template<typename T>
    dyn_array<T> operator+(dyn_array<T>&& lhs, dyn_array<T>&& rhs)
    {
        return lhs + std::move(rhs);
    }

    template<typename T>
    dyn_array<T>& operator*=(dyn_array<T>& lhs, T val)
    {
        for (size_t i = 0; i < lhs.size(); ++i)
        {
            lhs[i] *= val;
        }
        return lhs;
    }
    template<typename T>
    dyn_array<T>&& operator*=(dyn_array<T>&& lhs, T val)
    {
        //for (size_t i = 0; i < lhs.size(); ++i)
        //{
        //    lhs[i] *= val;
        //}??
        return std::move(lhs *= val);
    }
    template<typename T>
    dyn_array<T> operator*(const dyn_array<T>& lhs, T val)
    {

        return dyn_array<T>(lhs) *= val;
    }
    template<typename T>
    dyn_array<T> operator*(T val, const dyn_array<T>& rhs)
    {
        return dyn_array<T>(rhs) * val;
    }
    template<typename T>
    dyn_array<T> operator*(dyn_array<T>&& lhs, T val)
    {

        return  std::move(lhs) *= val;
    }
    template<typename T>
    dyn_array<T> operator*(T val, dyn_array<T>&& rhs)
    {
        return std::move(rhs) *= val;

    }


    void test_dyn_array()
    {
        using T = double;
        {
            dyn_array<T> arr;
            std::cout << "arr = " << arr << std::endl;
        }
        {
            dyn_array<T> arr(10, 3);
            std::cout << "arr(10, 3) = " << arr << std::endl;
        }
        dyn_array<T> arr2{ 1, 2, 3, 4 };
        std::cout << "arr2{ 1,2,3,4 } = " << arr2 << std::endl;
        dyn_array<T> arr3 = arr2;
        std::cout << "arr3 = arr2 = " << arr3 << std::endl;
        for (size_t i = 0, e = arr3.size(); i < e; ++i)
            arr3[i] = 2 * i + 1;
        std::cout << "{arr3[i] = 2 * i + 1} = " << arr3 << std::endl;
        std::cout << "dyn_array{ 3,4,5,6,7 } = " << dyn_array<T>{ 3, 4, 5, 6, 7 } << std::endl;
        arr3 = dyn_array<T>{ 3,4,5,6,7 };
        std::cout << "arr3 = dyn_array{ 3,4,5,6,7 } = " << arr3 << std::endl;
        arr3.clear();
        std::cout << "arr3.clear() =  " << arr3 << std::endl;
        arr3 = { 1,4 };
        std::cout << "arr3 = { 1,4 } = " << arr3 << std::endl;

    }

    void test_dyn_array_arithmetic()
    {
        using T = double;
        auto endl = '\n';
        dyn_array<T> a{ 1, 2, 3, 4 };
        dyn_array<T> b(4, 10.0);
        std::cout << "a=" << a << endl;
        std::cout << "b=" << b << endl;
        std::cout << a + b + dyn_array<T>{ -1, -1, -1, -1 } << endl;
        std::cout << dyn_array<T>(4, 10) + dyn_array<T>{ -1, -1, -1, -1 } << endl;
        std::cout << dyn_array<T>{ 1, 2, 3 }*4.0 << endl;
        std::cout << 2.0 * (dyn_array<T>{ 1, 2, 3, 4 } *4.0 + 3.0 * a) << endl;
        std::cout << "complete" << endl;
    }

    void test_dyn_array_string_arithmetic()
    {
        using T = std::string;
        auto endl = '\n';
        dyn_array<T> a{ "q", "w", "r", "y" };
        dyn_array<T> b(4, "e");
        std::cout << "a=" << a << endl;
        std::cout << "b=" << b << endl;
        std::cout << a + (b + dyn_array<T>{ "a", "b", "c", "d" }) << endl;
        //std::cout << "-----" << std::endl;
        std::cout << dyn_array<T>(4, "e") + dyn_array<T>{ "s", "t", "u", "v" } << endl;
        std::cout << "complete" << endl;
    }
}
namespace lab4
{
    struct student {
        std::string surname;
        std::string name;
        double mark;
    };

    void test() {

        auto print = [](const auto& students)
        {
            for (const auto& s : students)
            {
                std::cout << s.surname << " " << s.name << " " << s.mark << "\n";
            }
        };

        std::vector<student> students;
        std::ifstream file("students.txt");
        //std::string surname, name;
        //double mark;
        student s;
        while (file >> s.surname >> s.name >> s.mark)
        {
            students.push_back(std::move(s));
        }

        std::sort(students.begin(), students.end(), [](const student& s1, const student& s2) { return s1.mark > s2.mark; });
        std::cout << "Sorted by marks:\n";
        print(students);

        std::cout << "Enter new student's surname, name and mark: ";
        std::cin >> s.surname >> s.name >> s.mark;
        //students.emplace_back(surname, name, mark);
        students.push_back(std::move(s));
        std::cout << "\nUpdated list:\n";
        print(students);

        std::vector<student> a_students;
        std::copy_if(students.begin(), students.end(), std::back_inserter(a_students), [](const student& s) {return std::toupper(s.name[0]) == 'A'; });
        std::cout << "\nStudents whose names start with 'A':\n";
        print(a_students);

        auto longest_surname_student = std::max_element(students.begin(), students.end(), [](const student& s1, const student& s2)
            {
                return s1.surname.length() < s2.surname.length();
            });
        std::cout << "\nStudent with longest surname: " << longest_surname_student->surname << " " << longest_surname_student->name << " " << longest_surname_student->mark << "\n";


    }
}
namespace lab5
{
    struct gun_state {
        double x;
        double angle;

    };
    std::ostream& operator<<(std::ostream& out, const gun_state& gun)
    {
        out << "x = " << gun.x << " angle = " << gun.angle << std::endl;
        return out;
    }
    struct gun_command {
        double arg;
        gun_command(double val) :arg(val) {}
        virtual void operator()(gun_state& gun) {  }
    };
    struct move_command : public gun_command
    {
        move_command(double val) : gun_command(val) {}
        void  operator()(gun_state& gun)override {
            gun.x += this->arg;
        }
    };
    struct rotate_command : public gun_command
    {
        rotate_command(double val) : gun_command(val) {}

        void operator()(gun_state& gun)override {
            gun.angle = this->arg;

        }
    };
    std::vector<gun_command*> read_commands(std::string filename)
    {
        std::ifstream file(filename);
        std::vector<gun_command*> commands;
        std::string c;
        double arg;
        gun_state gun{ 2,0 };
        while (file >> c >> arg) {
            if (c == "move") {

                commands.push_back(new move_command(arg));
            }
            if (c == "look_at") {
                commands.push_back(new rotate_command(arg));
            }
        }
        return commands;
    }
    void fire(std::vector<gun_command*> commands, gun_state& gun)
    {
        for (auto& c : commands) {
            (*c)(gun);
            std::cout << gun;
        }
    }
    void test()
    {
        gun_state gun{ 2,0 };
        auto commands = read_commands("commands.txt");
        fire(commands, gun);
    }
}

int main()
{
    extern int x;
    extern void func();
    func();
    std::cout << x;
    //lab3::test_dyn_array_arithmetic();
    //lab3::test_dyn_array_string_arithmetic();
    //lab5::test();
}
