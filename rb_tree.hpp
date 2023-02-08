#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include <cstddef> // BUNU EN SON SİL
# include <iostream> // BUNU EN SON SİL
# ifndef nullptr
#  define nullptr NULL
# endif

# include <memory>
# include "utility.hpp"
//# include "type_traits.hpp"
# include "pair.hpp"
# include "rb_tree_iterator.hpp"

namespace ft
{

template<class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
class rb_tree
{
/* --------------- TYPEDEFS --------------- */
public:
    typedef T                                                       value_type;
    typedef Compare                                                 value_compare;
    typedef Alloc                                                   allocator_type;
    typedef typename Alloc::template rebind<rbt_node<T> >::other    node_allocator;
    typedef typename node_allocator::pointer                        node_pointer;
    typedef typename allocator_type::reference                      reference;
    typedef typename allocator_type::const_reference                const_reference;
    typedef typename allocator_type::pointer                        pointer;
    typedef typename allocator_type::const_pointer                  const_pointer;
    typedef typename allocator_type::size_type                      size_type;
    typedef typename allocator_type::difference_type                difference_type;
    typedef rb_tree_iterator<T, difference_type>                    iterator;
    typedef const_rb_tree_iterator<T, difference_type>              const_iterator;
    typedef ft::reverse_iterator<iterator>                          reverse_iterator;
    typedef ft::reverse_iterator<const_iterator>                    const_reverse_iterator;

/* --------------- MEMBER ATTRIBUTES --------------- */
private:
    node_pointer        m_Root;
    allocator_type      m_Value_Allocator;
    node_allocator      m_Node_Allocator;
    value_compare       m_Compare;
    size_type           m_Size;
    node_pointer        m_End;
    node_pointer        m_Nil;

/* --------------- CONSTRUCTORS AND DESTRUCTOR --------------- */
public:
    rb_tree()
        :   m_Root(nullptr), m_Value_Allocator(allocator_type()), m_Node_Allocator(node_allocator()), m_Compare(value_compare()), m_Size(0)
    {
        init_end_and_nil();
        m_Root = m_End;
    }

    rb_tree(const value_compare &comp, const allocator_type &alloc = allocator_type())
        :   m_Root(nullptr), m_Value_Allocator(alloc), m_Node_Allocator(node_allocator()), m_Compare(comp), m_Size(0)
    {
        init_end_and_nil();
        m_Root = m_End;
    }

    template<class InputIt>
    rb_tree(InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last, const value_compare &comp = value_compare(), const allocator_type &alloc = allocator_type())
        :   m_Root(nullptr), m_Value_Allocator(alloc), m_Node_Allocator(node_allocator()), m_Compare(comp), m_Size(0)
    {
        init_end_and_nil();
        m_Root = m_End;
        for (; first != last; first++)
            insert(*first);
    }

    rb_tree(const rb_tree &other)
        :   m_Root(nullptr), m_Compare(other.m_Compare)
    {
        *this = other;
    }

    rb_tree &operator=(const rb_tree &src)
    {
        if (this == &src)
            return (*this);
        m_Node_Allocator = src.m_Node_Allocator;
        m_Value_Allocator = src.m_Value_Allocator;
        m_Compare = src.m_Compare;
        if (m_Root == nullptr)
            init_end_and_nil();
        else
            clear_node(m_Root);
        if (src.m_Size == 0)
            m_Root = m_End;
        else
        {
            m_Root = copy_node(src.m_Root);
            copy_child_nodes(m_Root, src.m_Root);
        }
        m_Size = src.m_Size;
        return (*this);
    }

    ~rb_tree()
    {
        clear_node(m_Root);
        m_Value_Allocator.destroy(m_End->value);
        m_Value_Allocator.deallocate(m_End->value, 1);
        m_Node_Allocator.deallocate(m_Nil, 1);
        m_Node_Allocator.deallocate(m_End, 1);
    }

/* --------------- PRIVATE MEMBER FUNCTIONS --------------- */
private:
    void    init_end_and_nil()
    {
        m_End = m_Node_Allocator.allocate(1);
        m_Node_Allocator.construct(m_End, rbt_node<value_type>());
        m_End->value = m_Value_Allocator.allocate(1);
        m_Value_Allocator.construct(m_End->value, value_type());
        m_End->is_black = true;

        m_Nil = m_Node_Allocator.allocate(1);
        m_Node_Allocator.construct(m_Nil, rbt_node<value_type>());
        m_Nil->is_black = true;
        m_Nil->is_nil = true;
    }

    pointer create_value(const value_type &value)
    {
        pointer new_value = m_Value_Allocator.allocate(1);
        m_Value_Allocator.construct(new_value, value);
        return (new_value);
    }

    node_pointer    copy_node(node_pointer other)
    {
        node_pointer new_node = m_Node_Allocator.allocate(1);
        m_Node_Allocator.construct(new_node, rbt_node<value_type>());
        new_node->is_black = other->is_black;
        new_node->is_nil = other->is_nil;
        if (other->value)
        {
            new_node->value = m_Value_Allocator.allocate(1);
            m_Value_Allocator.construct(new_node->value, *other->value);
        }
        return (new_node);
    }

    void    copy_child_nodes(node_pointer node, node_pointer other)
    {
        if (other->left->is_nil)
            node->left = m_Nil;
        else
        {
            node->left = copy_node(other->left);
            node->left->parent = node;
            copy_child_nodes(node->left, other->left);
        }

        if (other->right->is_nil)
            node->right = m_Nil;
        else if (other->right->right == nullptr)
        {
            node->right = m_End;
            m_End->parent = node;
        }
        else
        {
            node->right = copy_node(other->right);
            node->right->parent = node;
            copy_child_nodes(node->right, other->right);
        }
    }

    bool    is_nil(node_pointer node) const
    {
        return (node == m_Nil || node == m_End);
    }

    node_pointer    search(const value_type &value, node_pointer node) const
    {
        if (node == nullptr || is_nil(node))
            return (nullptr);
        if (m_Compare(value, *node->value))
            return (search(value, node->left));
        else if (m_Compare(*node->value, value))
            return (search(value, node->right));
        return (node);
    }

    node_pointer    tree_min(node_pointer node) const
    {
        while (node != nullptr && !is_nil(node->left))
            node = node->left;
        return (node);
    }

    node_pointer    tree_max(node_pointer node) const
    {
        while (node != nullptr && !is_nil(node->right))
            node = node->right;
        return (node);
    }

    void    rotate_right(node_pointer x)
    {
        node_pointer y = x->left;
        x->left = y->right;
        if (!is_nil(y->right))
            y->right->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            m_Root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->right = x;
        x->parent = y;
    }

    void    rotate_left(node_pointer x)
    {
        node_pointer y = x->right;
        x->right = y->left;
        if (!is_nil(y->left))
            y->left->parent = x;
        y->parent = x->parent;
        if (x->parent == nullptr)
            m_Root = y;
        else if (x == x->parent->left)
            x->parent->left = y;
        else
            x->parent->right = y;
        y->left = x;
        x->parent = y;
    }

    void    free_node(node_pointer node)
    {
        m_Value_Allocator.destroy(node->value);
        m_Value_Allocator.deallocate(node->value, 1);
        m_Node_Allocator.deallocate(node, 1);
    }

    void    clear_node(node_pointer node)
    {
        if (node != nullptr && !is_nil(node))
        {
            clear_node(node->right);
            clear_node(node->left);
            free_node(node);
        }
    }

    void    transplant(node_pointer u, node_pointer v)
    {
        if (u->parent == nullptr)
            m_Root = v;
        else if (u == u->parent->left)
            u->parent->left = v;
        else
            u->parent->right = v;
        v->parent = u->parent;
    }

    node_pointer    insert_into_tree(node_pointer node, node_pointer root)
    {
        if (m_Root == m_End)
            m_Root = node;
        else
            insert_into_tree_2(node, root);
        return (node);
    }

    node_pointer    insert_into_tree_2(node_pointer node, node_pointer root)
    {
        if (m_Compare(*node->value, *root->value))
        {
            if (!is_nil(root->left))
                return (insert_into_tree_2(node, root->left));
            root->left = node;
        }
        else
        {
            if (!is_nil(root->right))
                return (insert_into_tree_2(node, root->right));
            root->right = node;
        }
        node->parent = root;
        return (node);
    }

    void    insert_fixup(node_pointer node)
    {
        if (node == m_Root || node->parent == m_Root)
        {
            m_Root->is_black = true;
            return;
        }

        while (node != m_Root && !node->parent->is_black)
        {
            if (node->parent == node->parent->parent->left)
            {
                node_pointer uncle = node->parent->parent->right;
                if (!uncle->is_black)
                {
                    node->parent->is_black = true;
                    uncle->is_black = true;
                    node->parent->parent->is_black = false;
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->right)
                    {
                        node = node->parent;
                        rotate_left(node);
                    }
                    node->parent->is_black = true;
                    node->parent->parent->is_black = false;
                    rotate_right(node->parent->parent);
                }
            }
            else
            {
                node_pointer uncle = node->parent->parent->left;
                if (!uncle->is_black)
                {
                    node->parent->is_black = true;
                    uncle->is_black = true;
                    node->parent->parent->is_black = false;
                    node = node->parent->parent;
                }
                else
                {
                    if (node == node->parent->left)
                    {
                        node = node->parent;
                        rotate_right(node);
                    }
                    node->parent->is_black = true;
                    node->parent->parent->is_black = false;
                    rotate_left(node->parent->parent);
                }
            }
        }
        m_Root->is_black = true;
    }

    void    fix_end_node()
    {
        node_pointer node = tree_max(m_Root);
        node->right = m_End;
        m_End->parent = node;
    }

    void    erase_fixup(node_pointer x)
    {
        node_pointer brother;
        while (x != m_Root && x != m_Nil && x->is_black)
        {
            if (x == x->parent->left)
            {
                brother = x->parent->right;
                if (!brother->is_black)
                {
                    brother->is_black = true;
                    x->parent->is_black = false;
                    rotate_left(x->parent);
                    brother = x->parent->right;
                }
                if (brother->left->is_black && brother->right->is_black)
                {
                    brother->is_black = false;
                    x = x->parent;
                }
                else
                {
                    if (brother->right->is_black)
                    {
                        brother->left->is_black = true;
                        brother->is_black = false;
                        rotate_right(brother);
                        brother = x->parent->right;
                    }
                    brother->is_black = x->parent->is_black;
                    x->parent->is_black = true;
                    brother->right->is_black = true;
                    rotate_left(x->parent);
                    x = m_Root;
                }
            }
            else
            {
                brother = x->parent->left;
                if (!brother->is_black)
                {
                    brother->is_black = true;
                    x->parent->is_black = false;
                    rotate_right(x->parent);
                    brother = x->parent->left;
                }
                if (brother->right->is_black && brother->left->is_black)
                {
                    brother->is_black = false;
                    x = x->parent;
                }
                else
                {
                    if (brother->left->is_black)
                    {
                        brother->right->is_black = true;
                        brother->is_black = false;
                        rotate_left(brother);
                        brother = x->parent->left;
                    }
                    brother->is_black = x->parent->is_black;
                    x->parent->is_black = true;
                    brother->left->is_black = true;
                    rotate_right(x->parent);
                    x = m_Root;
                }
            }
        }
    }

/* --------------- PUBLIC MEMBER FUNCTIONS --------------- */
public:
    iterator    find(const value_type &value)
    {
        node_pointer res = search(value, m_Root);
        if (res == nullptr)
            return (end());
        return (iterator(res));
    }

    const_iterator    find(const value_type &value) const
    {
        node_pointer res = search(value, m_Root);
        if (res == nullptr)
            return (end());
        return (const_iterator(res));
    }

    ft::pair<iterator, bool>    insert(const value_type &value)
    {
        node_pointer find_val = search(value, m_Root);
        if (find_val)
            return (ft::make_pair(iterator(find_val), false));
        node_pointer new_node = m_Node_Allocator.allocate(1);
        m_Node_Allocator.construct(new_node, rbt_node<value_type>(create_value(value)));
        new_node->left = m_Nil;
        new_node->right = m_Nil;
        insert_into_tree(new_node, m_Root);
        insert_fixup(new_node);
        m_Size++;
        fix_end_node();
        return (ft::make_pair(iterator(new_node), true));
    }

    iterator    insert(iterator position, const value_type &value) // BURASI OLMAZSA HALLEDERİZ
    {
        (void)position;
        return (insert(value).first);
    }

    template<class InputIt>
    void    insert(InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last)
    {
        for (; first != last; first++)
            insert(*first);
    }

    void erase(iterator pos)
    {
        node_pointer x;
        node_pointer y = pos.node();
        node_pointer for_free = y;
        bool is_y_black = y->is_black;

        if (is_nil(y->left))
        {
            x = y->right;
            transplant(y, y->right);
        }
        else if (is_nil(y->right))
        {
            x = y->left;
            transplant(y, y->left);
        }
        else
        {
            node_pointer z = y;
            y = tree_min(z->right);
            is_y_black = y->is_black;
            x = y->right;
            if (y->parent != z)
            {
                transplant(y, y->right);
                y->right = z->right;
                z->right->parent = y;
            }
            transplant(z, y);
            y->left = z->left;
            y->left->parent = y;
            y->is_black = z->is_black;
        }
        free_node(for_free);
        if (is_y_black)
            erase_fixup(x);
        m_Size--;
        m_Nil->parent = nullptr;
        if (m_Size == 0)
            m_Root = m_End;
        else
        {
            if (m_Size != 1)
                x = tree_max(m_Root);
            else
                x = m_Root;
            x->right = m_End;
            m_End->parent = x;
        }
    }

    size_type   erase(const value_type &value)
    {
        node_pointer res = search(value, m_Root);
        if (res)
            erase(iterator(res));
        return (res != nullptr);
    }

    void    erase(iterator first, iterator last)
    {
        while (first != last)
            erase(first++);
    }

    iterator    begin()
    {
        /*if (m_Size == 0)
            return (iterator(m_End));
        else
            return (iterator(tree_min(m_Root)));*/
        return (iterator(m_Size == 0 ? m_End : iterator(tree_min(m_Root))));
    }

    const_iterator    begin() const
    {
        /*if (m_Size == 0)
            return (const_iterator(m_End));
        else
            return (const_iterator(tree_min(m_Root)));*/
        return (const_iterator(m_Size == 0 ? m_End : const_iterator(tree_min(m_Root))));
    }

    iterator    end()
    {
        return(iterator(m_End));
    }

    const_iterator    end() const
    {
        return(const_iterator(m_End));
    }

    reverse_iterator    rbegin()
    {
        return (reverse_iterator(end()));
    }

    const_reverse_iterator    rbegin() const
    {
        return (const_reverse_iterator(end()));
    }

    reverse_iterator    rend()
    {
        return (reverse_iterator(begin()));
    }

    const_reverse_iterator    rend() const
    {
        return (const_reverse_iterator(begin()));
    }

    size_type   size() const
    {
        return (m_Size);
    }

    size_type   max_size() const
    {
        return (m_Node_Allocator.max_size());
    }

    bool    empty() const
    {
        return (m_Size == 0);
    }

    value_compare   value_comp() const
    {
        return (m_Compare);
    }

    void    clear()
    {
        clear_node(m_Root);
        m_Root = m_End;
        m_End->parent = nullptr;
        m_Size = 0;
    }

    size_type   count(const value_type &value)
    {
        return (find(value) != end());
    }

    size_type   count(const value_type &value) const
    {
        return (find(value) != end());
    }

    iterator    lower_bound(const value_type &value)
    {
        node_pointer node = m_Root;
        node_pointer pos = m_End;

        while (!is_nil(node))
        {
            if (!m_Compare(*(node->value), value))
            {
                pos = node;
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }

        return (iterator(pos));
    }

    const_iterator    lower_bound(const value_type &value) const
    {
        node_pointer node = m_Root;
        node_pointer pos = m_End;

        while (!is_nil(node))
        {
            if (!m_Compare(*(node->value), value))
            {
                pos = node;
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }

        return (const_iterator(pos));
    }

    iterator upper_bound(const value_type& value)
    {
        node_pointer node = m_Root;
        node_pointer pos = m_End;

        while (!is_nil(node))
        {
            if (m_Compare(value, *(node->value)))
            {
                pos = node;
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }

        return (iterator(pos));
    }

    const_iterator upper_bound(const value_type& value) const
    {
        node_pointer node = m_Root;
        node_pointer pos = m_End;

        while (!is_nil(node))
        {
            if (m_Compare(value, *(node->value)))
            {
                pos = node;
                node = node->left;
            }
            else
            {
                node = node->right;
            }
        }

        return (const_iterator(pos));
    }

    ft::pair<iterator, iterator>    equal_range(const value_type &value)
    {
        return (ft::make_pair(lower_bound(value), upper_bound(value)));
    }

    ft::pair<const_iterator, const_iterator>    equal_range(const value_type &value) const
    {
        return (ft::make_pair(lower_bound(value), upper_bound(value)));
    }

    allocator_type  get_allocator() const
    {
        return (m_Value_Allocator);
    }

    void    swap(rb_tree &other)
    {
        std::swap(m_Root, other.m_Root);
        std::swap(m_Nil, other.m_Nil);
        std::swap(m_End, other.m_End);
        std::swap(m_Size, other.m_Size);
        std::swap(m_Node_Allocator, other.m_Node_Allocator);
        std::swap(m_Value_Allocator, other.m_Value_Allocator);
        std::swap(m_Compare, other.m_Compare);
    }
};

template<class T, class Compare, class Alloc>
bool    operator<(const rb_tree<T, Compare, Alloc> &lhs, const rb_tree<T, Compare, Alloc> &rhs)
{
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template<class T, class Compare, class Alloc>
bool    operator==(const rb_tree<T, Compare, Alloc> &lhs, const rb_tree<T, Compare, Alloc> &rhs)
{
    return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
}

}

#endif