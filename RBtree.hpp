#ifndef SWILMER_RBTREE_HPP
#define SWILMER_RBTREE_HPP

#include <iomanip>
#include "type_traits.hpp"
#include "tree_iterator.hpp"

namespace ft
{
    enum RBTreeColors
    {
        Black,
        Red,
    };

    template <class T>
    struct Node
    {
        Node(const T &data = T())
            : data(data)
            , left(nullptr)
            , right(nullptr)
            , parent(nullptr)
            , colour(Black)
        {}

        T data;
        Node* left;
        Node* right;
        Node* parent;
        bool colour;
    };

    template <class T, class Node, class Compare, class Allocator = std::allocator<Node> >
    class RBtree
    {
    public:
        typedef T                                           value_type;
        typedef Allocator                                   allocator_type;
        typedef typename allocator_type::size_type          size_type;
        typedef typename allocator_type::difference_type    difference_type;
        typedef typename allocator_type::pointer            pointer;
        typedef typename allocator_type::const_pointer      const_pointer;
        typedef tree_iterator<value_type>                   iterator;
        typedef tree_iterator<const value_type>             const_iterator;

        RBtree()
                : _root(nullptr)
                , _allocator(Allocator())
        {}

        ~RBtree() {}

        pointer createNode(const T &value = T())
        {
            pointer node = this->_allocator.allocate(1);
            this->_allocator.construct(node, value);
            return node;
        }

        void destroyNode(pointer node)
        {
            if (!node)
                return ;
            this->_allocator.destroy(node);
            this->_allocator.deallocate(node, 1);
        }

        pointer getRoot() const
        {
            return this->_root;
        }

        const pointer *getRootPtr() const
        {
            return &this->_root;
        }

        size_t max_size() const
        {
            return this->_allocator.max_size();
        }

        pointer min(pointer node) const
        {
            if (node)
            {
                while (node->left)
                    node = node->left;
            }
            return node;
        }

        pointer max(pointer node) const
        {
            if (node)
            {
                while (node->right)
                    node = node->right;
            }
            return node;
        }

        pointer find(T value, pointer node) const
        {
            if (node)
            {
                if (_comparator(node->data, value))
                    return find(value, node->right);
                else if (_comparator(value, node->data))
                    return find(value, node->left);
            }
            return node;
        }

        void rotateLeft(pointer node)
        {
            pointer rightChild = node->right;

            node->right = rightChild->left;
            if (rightChild->left)
                rightChild->left->parent = node;

            rightChild->parent = node->parent;
            if (!node->parent)
                _root = rightChild;
            else if (node == node->parent->left)
                node->parent->left = rightChild;
            else
                node->parent->right = rightChild;

            rightChild->left = node;
            node->parent = rightChild;
        }

        void rotateRight(pointer node)
        {
            pointer leftChild = node->left;

            node->left = leftChild->right;
            if (leftChild->right)
                leftChild->right->parent = node;

            leftChild->parent = node->parent;
            if (!node->parent)
                _root = leftChild;
            else if (node == node->parent->right)
                node->parent->right = leftChild;
            else
                node->parent->left = leftChild;

            leftChild->right = node;
            node->parent = leftChild;
        }

        void balanceTree(pointer node)
        {
            pointer parent = nullptr;
            pointer grandParent = nullptr;
            pointer uncle = nullptr;

            if (node)
                parent = node->parent;
            if (parent)
                grandParent = parent->parent;
            while (parent && grandParent && parent->colour == Red)
            {
                if (parent == grandParent->left)
                {
                    uncle = grandParent->right;
                    if (uncle && uncle->colour == Red)
                    {
                        parent->colour = Black;
                        uncle->colour = Black;
                        grandParent->colour = Red;
                        node = grandParent;
                    }
                    else if (!uncle || uncle->colour == Black)
                    {
                        if (node == parent->right)
                        {
                            node = parent;
                            rotateLeft(node);
                        }
                        else
                        {
                            parent->colour = Black;
                            grandParent->colour = Red;
                            rotateRight(grandParent);
                        }
                    }
                }
                else
                {
                    uncle = grandParent->left;
                    if (uncle && uncle->colour == Red)
                    {
                        parent->colour = Black;
                        uncle->colour = Black;
                        grandParent->colour = Red;
                        node = grandParent;
                    }
                    else if (!uncle || uncle->colour == Black)
                    {
                        if (node == parent->left)
                        {
                            node = parent;
                            rotateRight(node);
                        }
                        else
                        {
                            parent->colour = Black;
                            grandParent->colour = Red;
                            rotateLeft(grandParent);
                        }
                    }
                }
                parent = nullptr;
                grandParent = nullptr;
                uncle = nullptr;

                if (node)
                    parent = node->parent;
                if (parent)
                    grandParent = parent->parent;
            }
            _root->colour = Black;
        }

        bool insert(pointer node, pointer hint = nullptr)
        {
            if (!_root)
            {
                _root = node;
                return true;
            }

            if (!hint)
                hint = max(_root);
            while (hint->parent && _comparator(node->data, hint->data) == _comparator(node->data, hint->parent->data))
                hint = hint->parent;
            pointer traverse = hint;

            while (true)
            {
                if (!_comparator(traverse->data, node->data)
                    && !_comparator(node->data, traverse->data))
                {
                    if (traverse != node)
                        destroyNode(node);
                    return false;
                }
                else if (_comparator(node->data, traverse->data))
                {
                    if (traverse->left)
                        traverse = traverse->left;
                    else
                    {
                        traverse->left = node;
                        node->parent = traverse;
                        break;
                    }
                }
                else
                {
                    if (traverse->right)
                        traverse = traverse->right;
                    else
                    {
                        traverse->right = node;
                        node->parent = traverse;
                        break;
                    }
                }
            }

            node->colour = Red;
            balanceTree(node);
            return true;
        }

        void clearNode(pointer node)
        {
            if (!node)
                return ;
            clearNode(node->left);
            node->left = nullptr;
            clearNode(node->right);
            node->right = nullptr;
            if (node->parent && node == node->parent->left)
                node->parent->left = nullptr;
            else if (node->parent && node == node->parent->right)
                node->parent->right = nullptr;
            destroyNode(node);
        }

        void clear()
        {
            clearNode(_root);
            _root = nullptr;
        }

        void transplant(pointer u, pointer v)
        {
            if (u && !u->parent)
                this->_root = v;
            else if (u && u->parent && u == u->parent->left)
                u->parent->left = v;
            else if (u && u->parent && u == u->parent->right)
                u->parent->right = v;
            if (!v)
                return ;
            v->parent = u->parent;
        }

        void deleteBalance(pointer node)
        {
            pointer tmp = nullptr;
            while (node != this->_root && node->colour == Black)
            {
                if (node == node->parent->left)
                {
                    tmp = node->parent->right;
                    if (tmp && tmp->colour == Red)
                    {
                        tmp->colour = Black;
                        node->parent->colour = Red;
                        rotateLeft(node->parent);
                        tmp = node->parent->right;
                    }
                    if ((!tmp->left || tmp->left->colour == Black)
                        && (!tmp->right || tmp->right->colour == Black))
                    {
                        tmp->colour = Red;
                        node = node->parent;
                    }
                    else
                    {
                        if (!tmp->right || tmp->right->colour == Black)
                        {
                            tmp->left->colour = Black;
                            tmp->colour = Red;
                            rotateRight(tmp);
                            tmp = node->parent->right;
                        }
                        tmp->colour = node->parent->colour;
                        node->parent->colour = Black;
                        tmp->right->colour = Black;
                        rotateLeft(node->parent);
                        node = this->_root;
                    }
                }
                else
                {
                    tmp = node->parent->left;
                    if (tmp && tmp->colour == Red)
                    {
                        tmp->colour = Black;
                        node->parent->colour = Red;
                        rotateRight(node->parent);
                        tmp = node->parent->left;
                    }
                    if ((!tmp->right || tmp->right->colour == Black)
                        && (!tmp->left || tmp->left->colour == Black))
                    {
                        tmp->colour = Red;
                        node = node->parent;
                    }
                    else
                    {
                        if (!tmp->left || tmp->left->colour == Black)
                        {
                            tmp->right->colour = Black;
                            tmp->colour = Red;
                            rotateLeft(tmp);
                            tmp = node->parent->left;
                        }
                        tmp->colour = node->parent->colour;
                        node->parent->colour = Black;
                        tmp->left->colour = Black;
                        rotateRight(node->parent);
                        node = this->_root;
                    }
                }
            }
            node->colour = Black;
        }

        bool deleteNode(pointer node)
        {
            bool flag = false;
            if (!node)
                return false;
            pointer tmp = node;
            pointer x = nullptr;
            int tmpTrueColor = tmp->colour;

            if (!node->left)
            {
                x = node->right;
                if (!x)
                {
                    x = createNode();
                    flag = true;
                }
                transplant(node, x);
            }
            else if (!node->right)
            {
                x = node->left;
                transplant(node, x);
            }
            else
            {
                tmp = min(node->right);

                tmpTrueColor = tmp->colour;
                x = tmp->right;

                if (!x)
                {
                    x = createNode();
                    flag = true;
                    tmp->right = x;
                    x->parent = tmp;
                }
                if (tmp->parent != node)
                {
                    transplant(tmp, x);
                    tmp->right = node->right;
                    tmp->right->parent = tmp;
                }
                transplant(node, tmp);
                tmp->left = node->left;
                tmp->left->parent = tmp;
                tmp->colour = node->colour;
            }
            if (tmpTrueColor == Black)
                deleteBalance(x);
            if (flag)
            {
                if (x == this->_root)
                    this->_root = nullptr;
                else if (x == x->parent->right)
                    x->parent->right = nullptr;
                else if (x == x->parent->left)
                    x->parent->left = nullptr;
                destroyNode(x);
            }
            destroyNode(node);
            return true;
        }

        pointer lower(pointer node, const T &data) const
        {
            pointer tmp = nullptr;
            while (node)
            {
                if (this->_comparator(node->data, data))
                    node = node->right;
                else
                {
                    if (node->left)
                    {
                        tmp = lower(node->left, data);
                        if (tmp)
                            node = tmp;
                        break ;
                    }
                    else
                        break ;
                }
            }
            return node;
        }

        pointer upper(pointer node, const T &data) const
        {
            pointer tmp = nullptr;
            while (node)
            {
                if (!this->_comparator(data, node->data))
                    node = node->right;
                else
                {
                    if (node->left)
                    {
                        tmp = upper(node->left, data);
                        if (tmp)
                            node = tmp;
                        break ;
                    }
                    else
                        break ;
                }
            }
            return node;
        }

        void swap(RBtree &src)
        {
            pointer tmp = this->_root;
            this->_root = src._root;
            src._root = tmp;
        }

    private:
        RBtree(const RBtree &src)
        {
            (void)src;
        }

        RBtree &operator=(const RBtree &src)
        {
            (void)src;
        }

        pointer _root;
        Allocator _allocator;
        Compare _comparator;
    };
}

#endif //SWILMER_RBTREE_HPP
