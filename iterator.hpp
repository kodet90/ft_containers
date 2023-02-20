#ifndef SWILMER_ITERATOR_HPP
#define SWILMER_ITERATOR_HPP

#include "iterator_traits.hpp"
#include "reverse_iterator.hpp"

namespace ft
{
    template <class Iter>
    class iterator
    {
	public:
		typedef typename iterator_traits<Iter>::difference_type		difference_type;
		typedef typename iterator_traits<Iter>::value_type			value_type;
		typedef typename iterator_traits<Iter>::pointer				pointer;
		typedef typename iterator_traits<Iter>::reference			reference;
		typedef typename iterator_traits<Iter>::iterator_category	iterator_category;

		iterator()
			: _i(nullptr)
		{}

		iterator(iterator const &src)
			: _i(src._i)
		{}

		virtual ~iterator()
		{}

		iterator &operator=(const iterator &src)
		{
			if (this == &src)
				return *this;
			_i = src._i;
			return *this;
		}

        operator iterator<const value_type *>() const
        {
            return iterator<const value_type *>(this->_i);
        }

		pointer base() const
		{
			return _i;
		}

		reference operator*() const
		{
			return *_i;
		}

		pointer operator->() const
		{
			return _i;
		}

		iterator &operator++()
		{
			++_i;
			return *this;
		}

		iterator operator++(int)
		{
			const iterator return_iterator(*this);
			++_i;
			return return_iterator;
		}

		iterator &operator--()
		{
			--_i;
			return *this;
		}

		iterator operator--(int)
		{
			iterator return_iterator(*this);
			--_i;
			return return_iterator;
		}
		iterator &operator+=(difference_type n)
		{
			_i += n;
			return *this;
		}

		iterator &operator-=(difference_type n)
		{
			_i -= n;
			return *this;
		}

		reference operator[](difference_type pos) const
		{
			return _i[pos];
		}

		template <class T>
		bool operator==(const iterator<T> &rhs) const
		{
			return _i == rhs._i;
		}

		template <class T>
		bool operator!=(const iterator<T> &rhs) const
		{
			return _i != rhs._i;
		}

		template <class T>
		bool operator<(const iterator<T> &rhs) const
		{
			return _i < rhs._i;
		}

		template <class T>
		bool operator<=(const iterator<T> &rhs) const
		{
			return _i <= rhs._i;
		}

		template <class T>
		bool operator>(const iterator<T> &rhs) const
		{
			return _i > rhs._i;
		}

		template <class T>
		bool operator>=(const iterator<T> &rhs) const
		{
			return _i >= rhs._i;
		}

		iterator operator+(difference_type n) const
		{
			return iterator(_i + n);
		}

		iterator operator-(difference_type n) const
		{
			return iterator(_i - n);
		}

		template <class T>
		difference_type operator-(const iterator<T> &rhs) const
		{
			return _i - rhs._i;
		}

	private:
		explicit iterator(pointer ptr)
            : _i(ptr)
		{}

		pointer _i;

		template <class T, class Alloc>
		friend class vector;

        template <class Type>
        friend class iterator;
    };

	template <class Iter>
	iterator<Iter> operator+(typename iterator<Iter>::difference_type n,
         iterator<Iter> &rhs)
	{
		return rhs + n;
	}
}

#endif //SWILMER_ITERATOR_HPP
