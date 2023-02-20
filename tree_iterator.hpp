#ifndef SWILMER_ITERATOR_TREE_HPP
#define SWILMER_ITERATOR_TREE_HPP

#include "reverse_iterator.hpp"
#include "type_traits.hpp"

namespace ft
{
    template <class T, class Node, class Compare, class Allocator>
    class RBtree;

    template <class T>
    struct Node;

    template <class T>
    class tree_iterator
    {
    public:
        typedef ptrdiff_t					    difference_type;
        typedef typename remove_cv<T>::type	    value_type;
        typedef T							    *pointer;
        typedef T							    &reference;
        typedef std::bidirectional_iterator_tag iterator_category;

        typedef Node<value_type>                *node_ptr;

        tree_iterator()
                : _ptr(nullptr)
                , _root(nullptr)
        {}

        template <class Compare, class Allocator>
        explicit tree_iterator(node_ptr const &node,
                               RBtree<value_type, Node<value_type>, Compare, Allocator> const &tree)
                : _ptr(node)
                , _root(tree.getRootPtr())
        {};

        tree_iterator(const tree_iterator &src)
                : _ptr(src._ptr)
                , _root(src._root)
        {}

        tree_iterator &operator=(tree_iterator const &source)
        {
            if (this == &source)
                return *this;
            this->_ptr = source._ptr;
            this->_root = source._root;
            return *this;
        }

        ~tree_iterator() {};

        operator tree_iterator<const value_type>() const
        {
            return tree_iterator<const value_type>(this->_ptr, this->_root);
        }

        operator node_ptr() const
        {
            return _ptr;
        }

        // operators
        // *it
        reference operator*() const
        {
            return this->_ptr->data;
        }

        // it->
        pointer operator->() const
        {
            return &(this->_ptr->data);
        }

        // it++
        tree_iterator operator++(int)
        {
            tree_iterator<T> tmp = *this;
            if (!this->_ptr)
                return tmp;
            if (this->_ptr->right)
            {
                this->_ptr = this->_ptr->right;
                while (this->_ptr->left)
                    this->_ptr = this->_ptr->left;
            }
            else
            {
                node_ptr parent = this->_ptr->parent;
                while (parent && this->_ptr == parent->right)
                {
                    this->_ptr = parent;
                    parent = this->_ptr->parent;
                }
                this->_ptr = parent;
            }
            return tmp;
        }

        // ++it
        tree_iterator &operator++()
        {
            if (!this->_ptr)
                return *this;
            if (this->_ptr->right)
            {
                this->_ptr = this->_ptr->right;
                while (this->_ptr->left)
                    this->_ptr = this->_ptr->left;
            }
            else
            {
                node_ptr parent = this->_ptr->parent;
                while (parent && this->_ptr == parent->right)
                {
                    this->_ptr = parent;
                    parent = this->_ptr->parent;
                }
                this->_ptr = parent;
            }
            return *this;
        }

        // it--
        tree_iterator operator--(int)
        {
            tree_iterator<T> tmp(*this);
            if (!this->_ptr)
            {
                this->_ptr = *this->_root;
                while (this->_ptr && this->_ptr->right)
                    this->_ptr = this->_ptr->right;
                return tmp;
            }
            if (this->_ptr->left)
            {
                node_ptr copy = this->_ptr->left;
                while (copy->right)
                    copy = copy->right;
                this->_ptr = copy;
            }
            else
            {
                node_ptr parent = this->_ptr->parent;
                while (parent && this->_ptr == parent->left)
                {
                    this->_ptr = parent;
                    parent = parent->parent;
                }
                this->_ptr = parent;
            }
            return tmp;
        }

        // --it
        tree_iterator &operator--()
        {
            if (!this->_ptr)
            {
                this->_ptr = *this->_root;
                while (this->_ptr && this->_ptr->right)
                    this->_ptr = this->_ptr->right;
                return *this;
            }
            if (this->_ptr && this->_ptr->left)
            {
                node_ptr copy = this->_ptr->left;
                while (copy->right)
                    copy = copy->right;
                this->_ptr = copy;
            }
            else
            {
                node_ptr parent = this->_ptr->parent;
                while (parent && this->_ptr == parent->left)
                {
                    this->_ptr = parent;
                    parent = parent->parent;
                }
                this->_ptr = parent;
            }
            return *this;
        }

    private:
        explicit tree_iterator(node_ptr const &node, node_ptr const * const &root)
            : _ptr(node)
            , _root(root)
        {}

        node_ptr _ptr;
        node_ptr const *_root;

        template <class Type>
        friend class tree_iterator;

        // relationship
        template <class Iter1, class Iter2>
        friend bool	operator==(const tree_iterator<Iter1> &left, const tree_iterator<Iter2> &right);

        template <class Iter1, class Iter2>
        friend bool	operator!=(const tree_iterator<Iter1> &left, const tree_iterator<Iter2> &right);
    };

    template <class Iter1, class Iter2>
    bool	operator==(const tree_iterator<Iter1> &left, const tree_iterator<Iter2> &right)
    {
        return (left._ptr == right._ptr);
    }

    template <class Iter1, class Iter2>
    bool	operator!=(const tree_iterator<Iter1> &left, const tree_iterator<Iter2> &right)
    {
        return !(left == right);
    }
}

#endif //SWILMER_ITERATOR_TREE_HPP
