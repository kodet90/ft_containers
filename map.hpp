#ifndef SWILMER_MAP_HPP
#define SWILMER_MAP_HPP

#include "RBtree.hpp"
#include "type_traits.hpp"
#include <stdexcept>

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key, T> > >
    class map
    {
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
		typedef Alloc allocator_type;
		typedef value_type &reference;
		typedef const value_type &const_reference;

        static_assert((is_same<typename allocator_type::value_type, value_type>::value),
                      "Allocator::value_type must be same type as value_type");

        class value_compare;

    private:
        typedef typename Alloc::template rebind<Node<value_type> >::other node_alloc;
        typedef RBtree<value_type, Node<value_type>, value_compare, node_alloc> tree_type;
        typedef Node<value_type> *node_ptr;

    public:
        typedef typename tree_type::size_type           size_type;
        typedef typename tree_type::difference_type     difference_type;
        typedef typename tree_type::pointer             pointer;
        typedef typename tree_type::const_pointer       const_pointer;
        typedef typename tree_type::iterator            iterator;
        typedef typename tree_type::const_iterator      const_iterator;
        typedef ft::reverse_iterator<iterator>          reverse_iterator;
        typedef ft::reverse_iterator<const_iterator>    const_reverse_iterator;

		class value_compare
		{
            friend class map;
            friend class RBtree<value_type, Node<value_type>, value_compare, node_alloc>;

        protected:
			value_compare(const key_compare &compare = key_compare())
				: _compare(compare) {}

		public:
			bool operator()(const value_type &x, const value_type &y) const
			{
				return _compare(x.first, y.first);
			}

		private:
			key_compare _compare;
		};

		// constructors
		// default
		explicit map(const key_compare &comp = key_compare(),
					 const allocator_type &alloc = allocator_type())
			: _allocator(alloc)
			, _key_comp(comp)
			, _value_comp(comp)
			, _tree()
			, _size(0)
		{}

		//range
		template <class input_iterator>
		map(input_iterator first, input_iterator last,
			const key_compare &comp = key_compare(),
			const allocator_type &alloc = allocator_type())
			: _allocator(alloc)
			, _key_comp(comp)
			, _value_comp(comp)
			, _tree()
			, _size(0)
		{
			insert(first, last);
		}

		//copy
		map(const map &src)
			: _allocator(src._allocator)
			, _key_comp(src._key_comp)
			, _value_comp(src._value_comp)
			, _tree()
			, _size(0)
		{
			insert(src.begin(), src.end());
		}

		// destructor
		~map()
		{
			_tree.clear();
		}

        // assign operator
		map &operator=(const map &src)
		{
			if (this == &src)
				return *this;
			clear();
			insert(src.begin(), src.end());
			return *this;
		}

		// iterators
		iterator begin()
		{
			return iterator(_tree.min(_tree.getRoot()), _tree);
		}

		const_iterator begin() const
		{
			return const_iterator(_tree.min(_tree.getRoot()), _tree);
		}

		iterator end()
		{
			return iterator(nullptr, _tree);
		}

		const_iterator end() const
		{
			return const_iterator(nullptr, _tree);
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

		// capacity
		bool empty() const
		{
			return !_size;
		}

		size_type size() const
		{
			return _size;
		}

		size_type max_size() const
		{
			return _tree.max_size();
		}

		// element access
		mapped_type &operator[](const key_type &k)
		{
			return (*((insert(ft::make_pair(k, mapped_type()))).first)).second;
		}

        mapped_type &at(const key_type &k)
        {
            typename tree_type::pointer root = _tree.getRoot();
            typename tree_type::pointer node = _tree.find(ft::make_pair(k, mapped_type()), root);
            if (!node)
                throw std::out_of_range("map::at:  key not found");
            return node->data.second;
        }

        const mapped_type &at(const key_type &k) const
        {
            typename tree_type::pointer root = _tree.getRoot();
            typename tree_type::pointer node = _tree.find(ft::make_pair(k, mapped_type()), root);
            if (!node)
                throw std::out_of_range("map::at:  key not found");
            return node->data.second;
        }

		// modifiers
		// single element
		pair<iterator, bool> insert(const value_type &val)
		{
			bool res = _tree.insert(_tree.createNode(val), _tree.getRoot());
			_size += res;
			typename tree_type::pointer node = _tree.find(val, _tree.getRoot());
			iterator iter = iterator(node, _tree);
			return pair<iterator, bool>(iter, res);
		}

		// with hint
		iterator insert(iterator position, const value_type &val)
		{
			_size += _tree.insert(_tree.createNode(val), position);
			typename tree_type::pointer node = _tree.find(val, _tree.getRoot());
			return iterator(node, _tree);
		}

		// range
		template <class input_iterator>
		void insert
        (
            input_iterator first
            , input_iterator last
            , typename ft::enable_if
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
			for (; first != last; ++first)
				this->_size += this->_tree.insert(this->_tree.createNode(*first), this->_tree.getRoot());
		}

		void erase(iterator position)
		{
			this->_size -= this->_tree.deleteNode(position);
		}

		size_type erase(const key_type &k)
		{
			node_ptr node = this->_tree.find(ft::make_pair(k, mapped_type()), this->_tree.getRoot());
			bool res = this->_tree.deleteNode(node);
			this->_size -= res;
			return res;
		}

		void erase(iterator first, iterator last)
		{
			while (first != last)
				erase(first++);
		}

		void swap(map &x)
		{
            this->_tree.swap(x._tree);
			size_type size = this->_size;
			this->_size = x._size;
			x._size = size;
		}

		void clear()
		{
			this->_tree.clear();
			this->_size = 0;
		}

		// observers
		key_compare key_comp() const
		{
			return this->_key_comp;
		}

		value_compare value_comp() const
		{
			return this->_value_comp;
		}

		// operations
		iterator find(const key_type &k)
		{
			return iterator(this->_tree.find(ft::make_pair(k, mapped_type()), this->_tree.getRoot()), this->_tree);
		}

		const_iterator find(const key_type &k) const
		{
			return const_iterator(this->_tree.find(ft::make_pair(k, mapped_type()), this->_tree.getRoot()), this->_tree);
		}

		size_type count(const key_type &k) const
		{
			if (this->_tree.find(ft::make_pair(k, mapped_type()), this->_tree.getRoot()))
				return 1;
			return 0;
		}

		iterator lower_bound(const key_type &k)
		{
			return iterator(this->_tree.lower(this->_tree.getRoot(), ft::make_pair(k, mapped_type())), this->_tree);
		}

		const_iterator lower_bound(const key_type &k) const
		{
			return const_iterator(this->_tree.lower(this->_tree.getRoot(), ft::make_pair(k, mapped_type())), this->_tree);
		}

		iterator upper_bound(const key_type &k)
		{
			return iterator(this->_tree.upper(this->_tree.getRoot(), ft::make_pair(k, mapped_type())), this->_tree);
		}

		const_iterator upper_bound(const key_type &k) const
		{
			return const_iterator(this->_tree.upper(this->_tree.getRoot(), ft::make_pair(k, mapped_type())), this->_tree);
		}

		pair<iterator, iterator> equal_range(const key_type &k)
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		pair<const_iterator,const_iterator> equal_range(const key_type &k) const
		{
			return ft::make_pair(lower_bound(k), upper_bound(k));
		}

		// allocator
		allocator_type get_allocator() const
		{
			return this->_allocator;
		}

	private:
		allocator_type _allocator;
		key_compare _key_comp;
		value_compare _value_comp;

		tree_type _tree;
		size_type _size;
	};

    template <class Key, class T, class Compare, class Alloc>
    bool operator==(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin() ) && ft::equal(rhs.begin(), rhs.end(), lhs.begin());
    }
    
    template <class Key, class T, class Compare, class Alloc>
    bool operator!=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs == rhs);
    }
    
    template <class Key, class T, class Compare, class Alloc>
    bool operator<(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());        
    }
    
    template <class Key, class T, class Compare, class Alloc>
    bool operator<=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs > rhs);
    }
    
    template <class Key, class T, class Compare, class Alloc>
    bool operator>(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return (rhs < lhs);
    }
    
    template <class Key, class T, class Compare, class Alloc>
    bool operator>=(const map<Key, T, Compare, Alloc> &lhs, const map<Key, T, Compare, Alloc> &rhs)
    {
        return !(lhs < rhs);
    }

    template <class Key, class T, class Compare, class Alloc>
    void swap(map<Key, T, Compare, Alloc> &lhs, map<Key, T, Compare, Alloc> &rhs)
    {
        lhs.swap(rhs);
    }
}

#endif //SWILMER_MAP_HPP
