#ifndef SWILMER_VECTOR_HPP
#define SWILMER_VECTOR_HPP

#include <algorithm>
#include <stdexcept>
#include "iterator.hpp"
#include "type_traits.hpp"

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef ft::iterator<pointer> iterator;
		typedef ft::iterator<const_pointer> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ptrdiff_t difference_type;
		typedef size_t size_type;

        static_assert((is_same<typename allocator_type::value_type, value_type>::value),
                      "Allocator::value_type must be same type as value_type");

        // constructors
		// default
		explicit vector(const allocator_type &alloc = allocator_type())
			: _allocator(alloc)
			, _capacity(0)
			, _begin(nullptr)
			, _end(nullptr)
		{}

		// fill
		explicit vector(size_type n, const_reference val = value_type(),
						const allocator_type &alloc = allocator_type())
			: _allocator(alloc)
			, _capacity(0)
			, _begin(nullptr)
			, _end(nullptr)
		{
			insert(iterator(), n, val);
		}

		// range
		template <class input_iterator>
		vector
		(
			input_iterator first
			, input_iterator last
			, const allocator_type &alloc = allocator_type()
			, typename enable_if
			<
				!is_integral
				<
					typename remove_cv<input_iterator>::type
				>::value
			>::type* = nullptr
		)
			: _allocator(alloc)
			, _capacity(0)
			, _begin(nullptr)
			, _end(nullptr)
		{
			insert(iterator(), first, last);
		}

		// copy
		vector(const vector &src)
			: _allocator(src._allocator)
			, _capacity(0)
			, _begin(nullptr)
			, _end(nullptr)
		{
			insert(iterator(), src.begin(), src.end());
		}

		// destructor
		~vector()
		{
			if (_begin)
			{
				clear();
				_allocator.deallocate(_begin, _capacity);
			}
		};

		// assign operator
		vector &operator=(const vector &src)
		{
			if (this == &src)
				return *this;
			clear();
			insert(begin(), src.begin(), src.end());
			return *this;
		}

		// Iterators
        iterator begin()
        {
            return iterator(_begin);
        }

        const_iterator begin() const
        {
            return const_iterator(_begin);
        }

        iterator end()
        {
            return iterator(_end);
        }

        const_iterator end() const
        {
            return const_iterator(_end);
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(end());
        }

        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(end());
        }

        reverse_iterator rend()
        {
            return reverse_iterator(begin());
        }

        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(begin());
        }

		// Capacity
        size_type size() const
        {
            return _end - _begin;
        }

        size_type max_size() const
        {
            return std::min<size_type>(_allocator.max_size(),
                                       std::numeric_limits<difference_type>::max());
        }

        void resize(size_type new_size, const_reference val = value_type())
        {
            size_type current_size = size();
            if (current_size < new_size)
            {
                if (new_size <= _capacity)
                {
                    construct_forward(new_size - current_size, val, _end);
                }
                else
                {
                    buffer buffer(recommend(new_size), current_size, _allocator);
                    construct_forward(new_size - current_size, val, buffer.end);
                    construct_backward(_begin, _end, buffer.begin);
                    buffer.swap(*this);
                }
            }
            else
                truncate(_begin + new_size);
        }

        size_type capacity() const
        {
            return _capacity;
        }

        bool empty() const
        {
            return _begin == _end;
        }

        void reserve(size_type new_capacity)
        {
            if (new_capacity > _capacity)
            {
                buffer buffer(new_capacity, size(), _allocator);
                construct_backward(_begin, _end, buffer.begin);
                buffer.swap(*this);
            }
        }

		// Element access
        reference operator[](size_type pos)
        {
            return _begin[pos];
        }

        const_reference operator[](size_type pos) const
        {
            return _begin[pos];
        }

        reference at(size_type pos)
        {
            if (pos >= size())
                throw std::out_of_range("vector");
            return _begin[pos];
        }

        const_reference at(size_type pos) const
        {
            if (pos >= size())
                throw std::out_of_range("vector");
            return _begin[pos];
        }

        reference front()
        {
            return *_begin;
        }

        const_reference front() const
        {
            return *_begin;
        }

        reference back()
        {
            return *(_end - 1);
        }

        const_reference back() const
        {
            return *(_end - 1);
        }

        pointer data()
        {
            return _begin;
        }

        const_pointer data() const
        {
            return _begin;
        }

        // Modifiers
		// fill
		void assign(size_type n, const_reference val)
		{
			clear();
			insert(begin(), n, val);
		}

		// range
		template <class input_iterator>
		void assign
		(
			input_iterator first
			, input_iterator last
			, typename enable_if
			<
				!is_integral
				<
					typename remove_cv<input_iterator>::type
				>::value
			>::type* = nullptr
		)
		{
			clear();
			insert(begin(), first, last);
		}

        void push_back(const_reference val)
        {
            if (size() < _capacity)
            {
                _allocator.construct(_end, val);
                ++_end;
            }
            else
            {
                buffer buffer(recommend(size() + 1), size(), _allocator);
                buffer.push_back(val);
                construct_backward(_begin, _end, buffer.begin);
                buffer.swap(*this);
            }
        }

        void pop_back()
        {
            truncate(_end - 1);
        }

		// single element
		iterator insert(iterator position, const_reference val)
		{
			pointer p = position.base();
			if (size() < _capacity)
			{
				if (p == _end)
					push_back(val);
				else
				{
					move_range(p, _end, 1);
					const_pointer pointer_val = &val;
					if (p <= pointer_val && pointer_val < _end)
						++pointer_val;
					*position = *pointer_val;
				}
			}
			else
			{
				buffer buffer(recommend(size() + 1), p - _begin, _allocator);
				pointer new_p = buffer.begin;
				buffer.push_back(val);
				construct_backward(_begin, p, buffer.begin);
				construct_forward(p, _end, buffer.end);
				buffer.swap(*this);
				p = new_p;
			}
			return iterator(p);
		}

		// fill
		void insert(iterator position, size_type n, const_reference val)
		{
			pointer p = position.base();
			if (n > 0)
			{
				if (size() + n <= _capacity)
				{
					pointer old_end = _end;
					size_type dx = _end - p;
					if (n > dx)
					{
						size_type cx = n - dx;
						construct_forward(cx, val, _end);
						n = dx;
					}
					if (n > 0)
					{
						move_range(p, old_end, n);
						const_pointer pointer_val = &val;
						if (p <= pointer_val && pointer_val < old_end)
							pointer_val += n;
						copy(n, *pointer_val, p);
					}
				}
				else
				{
					buffer buffer(recommend(size() + n), p - _begin, _allocator);
					construct_forward(n, val, buffer.end);
					construct_backward(_begin, p, buffer.begin);
					construct_forward(p, _end, buffer.end);
					buffer.swap(*this);
				}
			}
		}

		// range (input iterator)
		template <class input_iterator>
		typename enable_if
		<
			!is_integral
			<
				typename remove_cv<input_iterator>::type
			>::value
		>::type insert(iterator position, input_iterator first, input_iterator last)
		{
			_insert(position, first, last);
		}

	private:
		// range (input iterator)
		template <class input_iterator>
		typename enable_if
		<
			is_input_iterator<input_iterator>::value
				&& !is_random_access_iterator<input_iterator>::value
				&& std::is_constructible
				<
					value_type,
					typename iterator_traits<input_iterator>::reference
				>::value
		>::type _insert(iterator position, input_iterator first, input_iterator last)
		{
			pointer p = position.base();
			pointer old_end = _end;
			for (; size() < _capacity && first != last; ++_end)
				_allocator.construct(_end, *first++);
			buffer buffer(_allocator);
			if (first != last)
			{
				try
				{
					buffer.construct_at_end(first, last);
					difference_type old_size = old_end - _begin;
					difference_type offset = p - _begin;
					reserve(recommend(size() + buffer.size()));
					p = _begin + offset;
					old_end = _begin + old_size;
				}
				catch (...)
				{
					truncate(old_end);
					throw;
				}
			}
			p = std::rotate(p, old_end, _end);
			_insert(iterator(p), iterator(buffer.begin), iterator(buffer.end));
		}

		// range (random access iterator)
		template <class random_access_iterator>
		typename enable_if
		<
            is_random_access_iterator<random_access_iterator>::value
				&& std::is_constructible
				<
					value_type,
					typename iterator_traits<random_access_iterator>::reference
				>::value
		>::type _insert(iterator position, random_access_iterator first, random_access_iterator last)
		{
			pointer p = position.base();
			difference_type n = std::distance(first, last);
			if (n > 0)
			{
				if (size() + n <= _capacity)
				{
					pointer old_end = _end;
					difference_type dx = _end - p;
					if (n > dx)
					{
						construct_forward(first + dx, first + n, _end);
						n = dx;
					}
					if (n > 0)
					{
						move_range(p, old_end, n);
						copy(first, last, p);
					}
				}
				else
				{
					buffer buffer(recommend(size() + n),
								  p - _begin, _allocator);
					construct_forward(first, first + n, buffer.end);
					construct_backward(_begin, p, buffer.begin);
					construct_forward(p, _end, buffer.end);
					buffer.swap(*this);
				}
			}
		}

	public:
		// single element
		iterator erase(iterator pos)
		{
			pointer p = pos.base();
			pointer last = _end - 1;
			if (p != last)
				copy(p + 1, _end, p);
			truncate(last);
			return iterator(p);
		}

		// range
		iterator erase(iterator first, iterator last)
		{
			pointer p = first.base();
			if (first != last)
			{
				pointer l = last.base();
				if (l == _end)
					truncate(p);
				else
				{
					pointer new_end = p + (_end - l);
					copy(l, _end, p);
					truncate(new_end);
				}
			}
			return iterator(p);
		}

		void swap(vector &vec)
		{
			std::swap(vec._capacity, _capacity);
			std::swap(vec._begin, _begin);
			std::swap(vec._end, _end);
		}

        void clear()
        {
            truncate(_begin);
        }

        // Allocator
        allocator_type get_allocator() const
        {
            return _allocator;
        }

	private:
		static pointer copy_backward(pointer first, pointer last, pointer result)
		{
			if (result == last)
				return first;
			while (first != last)
				*--result = *--last;
			return result;
		}

		template <class input_iterator>
		static pointer copy
		(
			input_iterator first
			, input_iterator last
			, pointer &result
			, typename enable_if
			<
				is_input_iterator<input_iterator>::value
				&& std::is_constructible
					<
						value_type,
						typename iterator_traits<input_iterator>::reference
					>::value
			>::type* = nullptr
		)
		{
			while (first != last)
				*result++ = *first++;
			return result;
		}

		static pointer copy(pointer first, pointer last, pointer result)
		{
			if (result == first)
				return last;
			while (first != last)
				*result++ = *first++;
			return result;
		}

		static pointer copy(size_type n, const_reference val, pointer result)
		{
			while (n-- > 0)
				*result++ = val;
			return result;
		}

		void move_range(pointer from, pointer end, difference_type n)
		{
			if (n < 0)
				throw std::invalid_argument("move_range(): n < 0");
			if (n > 0) {
				construct_forward(end - n, end, _end);
				copy_backward(from, end - n, end);
			}
		}

		size_type recommend(size_type new_capacity) const
		{
			if (new_capacity > max_size())
				throw std::length_error("vector");
			if (_capacity >= max_size() / 2)
				return max_size();
			return std::max(2 * _capacity, new_capacity);
		}

		void truncate(pointer new_end)
		{
			while (_end != new_end)
				_allocator.destroy(--_end);
		}

		void construct_backward(pointer begin1, pointer end1, pointer &end2)
		{
			while (end1 != begin1)
			{
				_allocator.construct(end2 - 1, *--end1);
				--end2;
			}
		}

		template <class input_iterator>
		void construct_forward
		(
			input_iterator begin1
			, input_iterator end1
			, pointer &begin2
			, typename enable_if
			<
				is_input_iterator<input_iterator>::value
					&& std::is_constructible
					<
						value_type,
						typename iterator_traits<input_iterator>::reference
					>::value
			>::type* = nullptr
		)
		{
			while (begin1 != end1)
			{
				_allocator.construct(begin2, *begin1++);
				++begin2;
			}
		}

		void construct_forward(pointer begin1, pointer end1, pointer &begin2)
		{
			while (begin1 != end1)
			{
				_allocator.construct(begin2, *begin1++);
				++begin2;
			}
		}

		void construct_forward(size_type n, const_reference val, pointer &begin)
		{
			while (n-- > 0)
			{
				_allocator.construct(begin, val);
				++begin;
			}
		}

		struct buffer
		{
			buffer(allocator_type &allocator)
					: allocator(allocator)
					, capacity(0)
					, first(nullptr)
					, begin(nullptr)
					, end(nullptr)
			{}

			buffer(size_type capacity, size_type start, allocator_type &allocator)
				: allocator(allocator)
				, capacity(capacity)
			{
				first = capacity != 0 ? allocator.allocate(capacity) : nullptr;
				begin = end = first + start;
			}

			~buffer()
			{
				while (end != begin)
					allocator.destroy(--end);
				if (first)
					allocator.deallocate(first, capacity);
			}

			void push_back(const_reference val)
			{
				allocator.construct(end, val);
				++end;
			}

			void swap(vector &vector)
			{
				if (first != begin)
					throw std::invalid_argument
					("buffer.swap(): buffer.first != buffer.begin");
				std::swap(vector._capacity, capacity);
				std::swap(vector._begin, first);
				begin = first;
				std::swap(vector._end, end);
			}

			void swap(buffer &buffer)
			{
				if (first != begin)
					throw std::invalid_argument
					("buffer.swap(): buffer.first != buffer.begin");
				std::swap(buffer.capacity, capacity);
				std::swap(buffer.first, first);
				std::swap(buffer.begin, begin);
				std::swap(buffer.end, end);
			}

			size_type size() const
			{
				return end - begin;
			}

			template <class input_iterator>
			typename enable_if
			<
				is_input_iterator<input_iterator>::value
					&& std::is_constructible
					<
						value_type,
						typename iterator_traits<input_iterator>::reference
					>::value
			>::type construct_at_end(input_iterator first, input_iterator last)
			{
				for (; first != last; ++first)
				{
					if (size() == capacity)
					{
						size_type old_capacity = capacity;
						size_type new_capacity = std::max<size_type>(2 * old_capacity, 8);
						size_type maxsize = allocator.max_size();
						if (new_capacity > maxsize)
							new_capacity = maxsize;
						buffer buffer(new_capacity, 0, allocator);
						for (pointer p = begin; p != end; ++p, ++buffer.end)
							allocator.construct(buffer.end, *p);
						swap(buffer);
					}
					allocator.construct(end, *first);
					++end;
				}
			}

			allocator_type &allocator;
			size_type capacity;
			pointer first;
			pointer begin;
			pointer end;
		};

		allocator_type _allocator;
		size_type _capacity;
		pointer _begin;
		pointer _end;
	};

	template <class T, class Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return lhs.size() == rhs.size()
			&& ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}

	template <class T, class Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(),
											rhs.end());
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return rhs < lhs;
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs < rhs);
	}

	template <class T, class Alloc>
	void swap(vector<T, Alloc> &lhs, vector<T, Alloc> &rhs)
	{
		lhs.swap(rhs);
	}
}

#endif //SWILMER_VECTOR_HPP
