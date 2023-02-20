#ifndef SWILMER_REVERSE_ITERATOR_HPP
#define SWILMER_REVERSE_ITERATOR_HPP

#include "iterator_traits.hpp"
#include <type_traits>

namespace ft
{
	template <class Iter>
	class reverse_iterator
	{
	public:
        typedef Iter                                                iterator_type;
		typedef typename iterator_traits<Iter>::difference_type		difference_type;
		typedef typename iterator_traits<Iter>::value_type			value_type;
		typedef typename iterator_traits<Iter>::pointer				pointer;
		typedef typename iterator_traits<Iter>::reference			reference;
		typedef typename iterator_traits<Iter>::iterator_category	iterator_category;

		reverse_iterator()
			: _i()
		{}

		explicit reverse_iterator(Iter i)
			: _i(i)
		{}

		reverse_iterator(reverse_iterator const &src)
			: _i(src._i)
		{}

		virtual ~reverse_iterator()
		{}

		reverse_iterator &operator=(const reverse_iterator &src)
		{
			if (this == &src)
				return *this;
			_i = src._i;
			return *this;
		}

        template <class Type>
        reverse_iterator(const reverse_iterator<Type> &u, typename enable_if<
                !is_same<Type, Iter>::value && std::is_convertible<Type const &, Iter>::value>::type* = nullptr)
                : _i(u.base())
        {}

		Iter base() const
		{
			return _i;
		}

		reference operator*() const
		{
			Iter i = _i;
			--i;
			return *i;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reverse_iterator &operator++()
		{
			--_i;
			return *this;
		}

		reverse_iterator operator++(int)
		{
			reverse_iterator return_iterator(*this);
			--_i;
			return return_iterator;
		}

		reverse_iterator &operator--()
		{
			++_i;
			return *this;
		}

		reverse_iterator operator--(int)
		{
			reverse_iterator return_iterator(*this);
			++_i;
			return return_iterator;
		}

		reverse_iterator &operator+=(difference_type n)
		{
			_i -= n;
			return *this;
		}

		reverse_iterator &operator-=(difference_type n)
		{
			_i += n;
			return *this;
		}

		reference operator[](difference_type pos) const
		{
			return _i[-pos - 1];
		}

		template <class T>
		bool operator==(const reverse_iterator<T> &rhs) const
		{
			return _i == rhs._i;
		}

		template <class T>
		bool operator!=(const reverse_iterator<T> &rhs) const
		{
			return !(_i == rhs._i); // _i != rhs._i
		}

		template <class T>
		bool operator<(const reverse_iterator<T> &rhs) const
		{
			return rhs._i < _i; // _i > rhs._i
		}

		template <class T>
		bool operator<=(const reverse_iterator<T> &rhs) const
		{
			return !(_i < rhs._i); // _i >= rhs._i
		}

		template <class T>
		bool operator>(const reverse_iterator<T> &rhs) const
		{
			return _i < rhs._i;
		}

		template <class T>
		bool operator>=(const reverse_iterator<T> &rhs) const
		{
			return !(rhs._i < _i); // _i <= rhs._i;
		}

		reverse_iterator operator+(difference_type n) const
		{
			return reverse_iterator(_i - n);
		}

		reverse_iterator operator-(difference_type n) const
		{
			return reverse_iterator(_i + n);
		}

		template <class T>
		difference_type operator-(const reverse_iterator<T> &rhs) const
		{
			return -(_i - rhs._i);
		}

	private:
		Iter _i;

        template <class Type>
        friend class reverse_iterator;
    };

	template <class Iter>
	reverse_iterator<Iter> operator+(typename reverse_iterator<Iter>::difference_type n,
									 reverse_iterator<Iter> &rhs)
	{
		return rhs + n;
	}
}

#endif //SWILMER_REVERSE_ITERATOR_HPP
