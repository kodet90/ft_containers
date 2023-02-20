#ifndef SWILMER_INPUT_ITERATOR_HPP
#define SWILMER_INPUT_ITERATOR_HPP

#include <type_traits>

template <class Iter>
class input_iterator
{
public:
    typedef typename std::iterator_traits<Iter>::difference_type	difference_type;
    typedef typename std::iterator_traits<Iter>::value_type			value_type;
    typedef typename std::iterator_traits<Iter>::pointer			pointer;
    typedef typename std::iterator_traits<Iter>::reference			reference;
    typedef std::input_iterator_tag								    iterator_category;

    input_iterator(pointer ptr)
        : _i(ptr)
    {}

    input_iterator(input_iterator const &src)
        : _i(src._i)
    {}

    virtual ~input_iterator() {}

    input_iterator& operator=(const input_iterator<Iter> &src)
    {
        if (this == &src)
            return *this;
        _i = src.base();
        return *this;
    }

    operator input_iterator<const value_type *>() const
    {
        return input_iterator<const value_type *>(this->_i);
    }

    // *it
    reference operator*()
    {
        return *_i;
    }

    // it->
    pointer operator->()
    {
        return _i;
    }

    // ++it
    input_iterator &operator++()
    {
        ++_i;
        return *this;
    }

    // it++
    input_iterator operator++(int)
    {
        input_iterator return_iterator(*this);
        ++_i;
        return return_iterator;
    }

    template <class T>
    bool operator==(input_iterator<T> const &rhs)
    {
        return _i == rhs._i;
    }

    template <class T>
    bool operator!=(input_iterator<T> const &rhs)
    {
        return _i != rhs._i;
    }

private:
    Iter _i;

    template <class Type>
    friend class input_iterator;
};

#endif //SWILMER_INPUT_ITERATOR_HPP
