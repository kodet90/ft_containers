#ifndef SWILMER_STACK_HPP
#define SWILMER_STACK_HPP

#include "vector.hpp"

namespace ft
{
    template <class T, class Container = ft::vector<T> >
    class stack
    {
    public:
        typedef Container container_type;
        typedef typename container_type::value_type value_type;
        typedef typename container_type::size_type size_type;
        typedef typename container_type::reference reference;
        typedef	typename container_type::const_reference const_reference;

        // constructors
        // default
        explicit stack(const container_type &cont = container_type())
            : c(cont)
        {}

        //copy
        stack(const stack &src)
            : c(src.c)
        {}

        // destructor
        ~stack() {}

        // assign operator
        stack &operator=(const stack &src)
        {
            if (this == &src)
                return *this;
            this->c = src.c;
            return *this;
        }

        // Element access
        value_type &top()
        {
            return this->c.back();
        }

        const value_type &top() const
        {
            return this->c.back();
        }

        // Capacity
        bool empty() const
        {
            return this->c.empty();
        }

        size_type size() const
        {
            return this->c.size();
        }

        // Modifiers
        void push(const value_type &value)
        {
            this->c.push_back(value);
        }

        void pop()
        {
            this->c.pop_back();
        }

    protected:
        container_type c;

        template<class U, class ContainerType>
        friend bool operator==(const stack<U, ContainerType> &lhs, const stack<U, ContainerType> &rhs);

        template<class U, class ContainerType>
        friend bool operator!=(const stack<U, ContainerType> &lhs, const stack<U, ContainerType> &rhs);

        template<class U, class ContainerType>
        friend bool operator<(const stack<U, ContainerType> &lhs, const stack<U, ContainerType> &rhs);

        template<class U, class ContainerType>
        friend bool operator<=(const stack<U, ContainerType> &lhs, const stack<U, ContainerType> &rhs);

        template<class U, class ContainerType>
        friend bool operator>(const stack<U, ContainerType> &lhs, const stack<U, ContainerType> &rhs);

        template<class U, class ContainerType>
        friend bool operator>=(const stack<U, ContainerType> &lhs, const stack<U, ContainerType> &rhs);
    };

    template<class U, class ContainerType>
    bool operator==(const stack<U, ContainerType> &lhs, const stack<U, ContainerType> &rhs)
    {
        return (lhs.c == rhs.c);
    }

    template<class U, class ContainerType>
    bool operator!=(const stack<U, ContainerType> &lhs, const stack<U, ContainerType> &rhs)
    {
        return (lhs.c != rhs.c);
    }

    template<class U, class ContainerType>
    bool operator<(const stack<U, ContainerType> &lhs, const stack<U, ContainerType> &rhs)
    {
        return (lhs.c < rhs.c);
    }

    template<class U, class ContainerType>
    bool operator<=(const stack<U, ContainerType> &lhs, const stack<U, ContainerType> &rhs)
    {
        return (lhs.c <= rhs.c);
    }

    template<class U, class ContainerType>
    bool operator>(const stack<U, ContainerType> &lhs, const stack<U, ContainerType> &rhs)
    {
        return (lhs.c > rhs.c);
    }

    template<class U, class ContainerType>
    bool operator>=(const stack<U, ContainerType> &lhs, const stack<U, ContainerType> &rhs)
    {
        return (lhs.c >= rhs.c);
    }
}

#endif //SWILMER_STACK_HPP
