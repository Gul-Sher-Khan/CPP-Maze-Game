// 22i-2637 Gulsher Khan 22i-8791 Ahsan Faraz

// class template
template <class T>
class listNode // list node
{
public:
    listNode<T> *next;
    listNode<T> *prev;
    T data;
};

template <class T>
class list
{
public:
    listNode<T> *head;
    listNode<T> *tail;
    int count;

    list()
    {
        head = NULL;
        tail = NULL;
        count = 0;
    }
    // Function for adding node in the list
    void add(T data)
    {
        listNode<T> *node = new listNode<T>();
        node->data = data;
        node->next = NULL;
        node->prev = NULL;

        if (head == NULL)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }

        count++;
    }
    // Function to remove node from list
    void remove(listNode<T> *node)
    {
        if (node->prev != NULL)
        {
            node->prev->next = node->next;
        }
        else
        {
            head = node->next;
        }

        if (node->next != NULL)
        {
            node->next->prev = node->prev;
        }
        else
        {
            tail = node->prev;
        }

        delete node;
        count--;
    }
    // function to found data
    bool contains(T data)
    {
        listNode<T> *node = head;
        while (node != NULL)
        {
            if (node->data == data)
            {
                return true;
            }

            node = node->next;
        }

        return false;
    }

    void clear()
    {
        listNode<T> *node = head;
        while (node != NULL)
        {
            listNode<T> *next = node->next;
            delete node;
            node = next;
        }

        head = NULL;
        tail = NULL;
        count = 0;
    }

    listNode<T> *get(int index)
    {
        listNode<T> *node = head;
        for (int i = 0; i < index; i++)
        {
            node = node->next;
        }

        return node;
    }
};