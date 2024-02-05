// 22i-2637 Gulsher Khan 22i-8791 Ahsan Faraz

#include <iostream>
using namespace std;

template <class T>
struct Qnode // Queue Node
{
    T data;
    Qnode<T> *next;
};

template <class T>
class Queue // Queue class
{

private:
    Qnode<T> *front, *rear; // front nad  rear variales of queue

public:
    Queue()
    {
        front = rear = NULL;
    }
    //  function for checking is queue is empty
    bool isEmpty()
    {
        return (front == NULL);
    }
    // function for adding a node in queue
    void enqueue(T x)
    {
        Qnode<T> *p = new Qnode<T>;
        p->data = x;
        p->next = NULL;
        if (isEmpty())
        {
            front = rear = p;
        }
        else
        {
            rear->next = p;
            rear = p;
        }
    }

    // function for dequeue a node
    T dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return 0;
        }
        else
        {
            Qnode<T> *p = front;
            T x = p->data;
            front = front->next;
            delete p;
            return x;
        }
    }
    // Displaying queue function
    void display()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
        }
        else
        {
            Qnode<T> *p = front;
            while (p != NULL)
            {
                cout << p->data << " ";
                p = p->next;
            }
            cout << endl;
        }
    }
};
