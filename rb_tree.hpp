#ifndef RB_TREE_HPP
# define RB_TREE_HPP

# include <cstddef> // BUNU EN SON SİL
# ifndef nullptr
#  define nullptr NULL
# endif

# include <memory>
# include "utils.hpp"
# include "pair.hpp"

template<typename T>
struct rbt_node
{
/* --------------- TYPEDEFS --------------- */
	typedef T		    value_type;
    typedef rbt_node *  pointer;   

/* --------------- MEMBER ATTRIBUTES --------------- */
	value_type  *value;
    pointer     parent;
    pointer     left;
    pointer     right;
    bool        is_black;
    bool        is_nil;

/* --------------- CONSTRUCTORS --------------- */
	rbt_node(value_type *val = 0)
		:	value(val), parent(nullptr), left(nullptr), right(nullptr), is_black(false), is_nil(false)
	{
	}

	rbt_node(const rbt_node &other)
		:	value(other.val), parent(other.parent), left(other.left), right(other.right), is_black(other.is_black), is_nil(other.is_nil)
	{
	}

    rbt_node &operator=(const rbt_node &other)
    {
        value = other.value;
        parent = other.parent;
        left = other.left;
        right = other.right;
        is_black = other.is_black;
        is_nil = other.is_nil;
        return (*this);
    }
};

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

/* --------------- MEMBER ATTRIBUTES --------------- */
private:
    allocator_type      m_Value_Allocator;
    node_allocator      m_Node_Allocator;
    value_compare       m_Compare;
    node_pointer        m_Root;
    node_pointer        m_End;
    node_pointer        m_Nil;
    size_type           m_Size;

/* --------------- CONSTRUCTORS AND DESTRUCTOR --------------- */
public:
    rb_tree()
        :   m_Root(nullptr), m_Value_Allocator(allocator_type()), m_Node_Allocator(node_allocator()), m_Compare(value_compare()), m_Size(0)
    {
        init_end_and_nil();
        m_Root = m_End;
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
                insert_fixup_2(node, true);
            else
                insert_fixup_2(node, false);
        }

        m_Root->is_black = true;
    }

    void    insert_fixup_2(node_pointer node, bool rotate_to_right)
    {
        node_pointer uncle;
        void (*main_rotate)(node_pointer);
        void (*second_rotate)(node_pointer);
        node_pointer left_or_right;

        if (rotate_to_right)
        {
            uncle = node->parent->parent->right;
            main_rotate = rotate_right;
            second_rotate = rotate_left;
            left_or_right = node->parent->right;
        }
        else
        {
            uncle = node->parent->parent->left;
            main_rotate = rotate_left;
            second_rotate = rotate_right;
            left_or_right = node->parent->left;
        }

        if (!uncle->is_black)
        {
            node->parent->is_black = true;
            uncle->is_black = true;
            node->parent->parent->is_black = false;
            node = node->parent->parent;
        }
        else
        {
            if (node == left_or_right)
            {
                node = node->parent;
                second_rotate(node);
            }
            node->parent->is_black = true;
            node->parent->parent->is_black = false;
            main_rotate(node->parent->parent);
        }
    }

    void    fix_end_node()
    {
        node_pointer node = tree_max(m_Root);
        node->right = m_End;
        m_End->parent = node;
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

    const_iterator    find(const value_type &value)
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
        insert(value);
    }

    template<class InputIt>
    void    insert(InputIt first, typename ft::enable_if<!ft::is_integral<InputIt>::value, InputIt>::type last)
    {
        for (; first != last; first++)
            insert(*first);
    }
};

#endif