// 22i-2637 Gulsher Khan 22i-8791 Ahsan Faraz

template <typename T>
class vector // class Vector
{
private:
    T *data;
    int size;

public:
    vector(int size = 0) // default constructor
    {
        this->size = size;
        this->data = new T[size]();
    }

    vector(int size, const T &initial_value) // parameterized constructor
    {
        this->size = size;
        this->data = new T[size];
        for (int i = 0; i < size; ++i)
        {
            this->data[i] = initial_value;
        }
    }

    ~vector() // destructor
    {
        delete[] this->data;
    }
    // getters
    int getSize() const
    {
        return this->size;
    }

    T *getData() const
    {
        return this->data;
    }
    // push an element in vector
    void push(const T &value)
    {
        T *temp = new T[size + 1];
        for (int i = 0; i < size; ++i)
        {
            temp[i] = this->data[i];
        }
        temp[size] = value;
        delete[] this->data;
        this->data = temp;
        ++size;
    }
    // pop/delete an element from vector
    void pop()
    {
        T *temp = new T[size - 1];
        for (int i = 0; i < size - 1; ++i)
        {
            temp[i] = this->data[i];
        }
        delete[] this->data;
        this->data = temp;
        --size;
    }
    // operator overloading
    T &operator[](int index)
    {
        return this->data[index];
    }

    vector(const vector &other)
    {
        this->size = other.size;
        this->data = new T[size];
        for (int i = 0; i < size; ++i)
        {
            this->data[i] = other.data[i];
        }
    }
    // operator overloading
    vector &operator=(const vector &other)
    {
        if (this != &other)
        {
            delete[] this->data;
            this->size = other.size;
            this->data = new T[size];
            for (int i = 0; i < size; ++i)
            {
                this->data[i] = other.data[i];
            }
        }
        return *this;
    }
    void resize(int size)
    {
        T *temp = new T[size];
        for (int i = 0; i < size; ++i)
        {
            temp[i] = this->data[i];
        }
        delete[] this->data;
        this->data = temp;
        this->size = size;
    }

    void reverse()
    {
        T *temp = new T[size];
        for (int i = 0; i < size; ++i)
        {
            temp[i] = this->data[size - i - 1];
        }
        delete[] this->data;
        this->data = temp;
    }
};
