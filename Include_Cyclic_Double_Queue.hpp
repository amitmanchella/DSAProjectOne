#pragma once
#include "cstring"
#include "sstream"
#include "string"
#include "iostream"

namespace cs251
{
    template<typename T>
    class cyclic_double_queue
    {
    public:
        /**
         * \brief The constructor with settings.
         * \param initialCapacity Preset initial capacity of the array.
         * \param increaseFactor Preset increase factor for expanding the array.
         * \param decreaseFactor Preset decrease factor for shrinking the array.
         */
        cyclic_double_queue(size_t initialCapacity = 7, size_t increaseFactor = 2, size_t decreaseFactor = 2);
        /**
         * \brief The default destructor. You should make sure no memory leaks happens after the queue is destroyed.
         */
        ~cyclic_double_queue();
        /**
         * \brief Push the item at the front of the queue.
         * \param item The item to be added.
         */
        void enqueue_front(const T& item);
        /**
         * \brief Push the item at the back of the queue.
         * \param item The item to be added.
         */
        void enqueue_back(const T& item);
        /**
         * \brief Returns the occupancy of the queue.
         * \return Whether the queue is empty.
         */
        bool empty() const;
        /**
         * \brief Dequeue the element at the front of the queue.
         * \return The item dequeued.
         */
        T dequeue_front();
        /**
         * \brief Dequeue the element at the back of the queue.
         * \return The item dequeued.
         */
        T dequeue_back();
        /**
         * \brief Remove the item at the front of the queue, returns nothing.
         */
        void pop_front();
        /**
         * \brief Remove the item at the back of the queue, returns nothing.
         */
        void pop_back();
        /**
         * \brief Provide the access to the item at the front of the queue.
         * \return The modifiable reference to the item.
         */
        T& front();
        /**
         * \brief Provide the access to the item at the back of the queue.
         * \return The modifiable reference to the item.
         */
        T& back();
        /**
         * \brief Empty the queue, and resize the queue to initial capacity.
         * \n !Note! You should set the size and the front index of the queue to 0 when this function is called!
         */
        void clear();
        /**
         * \brief Print the queue's current status according to the handout.
         * \return The string represents the array. For format please refer to the handout.
         */
        std::string print_status() const;
        /**
         * \brief Returns the number of items currently in queue.
         * \return The size of the queue.
         */
        size_t get_size() const;
        /**
         * \brief Returns the total capacity of the array.
         * \return The capacity of the array.
         */
        size_t get_capacity() const;

    private:
        size_t m_backIndex = 0;
        /**
         * Item array, the underlying data structure for the queue
         */
        T* m_data = nullptr;
        /**
         * The front index of the queue within the array
         */
        size_t m_frontIndex = 0;
        /**
         * The length of the array, including the empty slots.
         */
        size_t m_capacity = 0;
        /**
         * Keeps track of the size of the queue
         */
        size_t m_size = 0;
        /**
         * Factor by which the queue length must be increased
         */
        size_t m_increaseFactor = 0;
        /**
         * Factor by which the queue length must be decreased
         */
        size_t m_decreaseFactor = 0;
        /**
         * The initial capacity of the queue, predefined as 7
         */
        size_t m_initialCapacity = 0;
    };

    template <typename T>
    cyclic_double_queue<T>::cyclic_double_queue(const size_t initialCapacity, const size_t increaseFactor, size_t decreaseFactor)
    {
        if (m_initialCapacity) {
            throw std::out_of_range("cyclic_double_queue is empty!");
        }
        m_capacity = initialCapacity;
        m_initialCapacity = initialCapacity;
        m_increaseFactor = increaseFactor;
        m_decreaseFactor = decreaseFactor;
        m_frontIndex = 0;
        m_backIndex = 0;
        m_size = 0;
        m_data = new T[initialCapacity];

    }

    template <typename T>
    cyclic_double_queue<T>::~cyclic_double_queue()
    {
        delete[] m_data;
    }
    template <typename T>
    void cyclic_double_queue<T>::enqueue_front(const T& item)
    {
        if (m_size == m_capacity) {
            size_t new_capacity = m_capacity * m_increaseFactor;
            if (m_capacity < m_initialCapacity) {
                m_capacity = m_initialCapacity;
            }
            T* new_data = new T[new_capacity];

            for (size_t i = 0; i < m_size; ++i) {
                size_t index = (m_frontIndex + i) % m_capacity;

                new_data[i] = m_data[index];
            }

            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
            m_frontIndex = 0;
            m_backIndex = m_size;
        }

        if (m_capacity > (m_size * 4) && (m_capacity != m_initialCapacity)) {
            m_capacity = m_capacity / m_decreaseFactor;
            if (m_capacity < m_initialCapacity) {
                m_capacity = m_initialCapacity;
            }
            T* new_data = new T[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                size_t index = (m_frontIndex + i) % m_capacity;

                new_data[i] = m_data[index];
            }
            delete[] m_data;
            m_data = new_data;
            m_frontIndex = 0;
            m_backIndex = m_size;
        }
        if (m_frontIndex == -1) {
            m_frontIndex = 0;
            m_backIndex = 1;

        } else if (m_frontIndex == 0) {
            m_frontIndex = m_capacity - 1;
        } else {
            m_frontIndex = m_frontIndex - 1;
        }
        m_data[m_frontIndex] = item;
        m_size++;
    }

    template <typename T>
    void cyclic_double_queue<T>::enqueue_back(const T& item)
    {
        if (m_size == m_capacity) {
            size_t new_capacity = m_capacity * m_increaseFactor;
            if (m_capacity < m_initialCapacity) {
                m_capacity = m_initialCapacity;
            }
            T* new_data = new T[new_capacity];

            for (size_t i = 0; i < m_size; ++i) {
                size_t index = (m_frontIndex + i) % m_capacity;

                new_data[i] = m_data[index];
            }

            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
            m_frontIndex = 0;
            m_backIndex = m_size;
        }

        if (m_capacity > (m_size * 4) && (m_capacity != m_initialCapacity)) {
            m_capacity = m_capacity / m_decreaseFactor;
            if (m_capacity < m_initialCapacity) {
                m_capacity = m_initialCapacity;
            }
            T* new_data = new T[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                size_t index = (m_frontIndex + i) % m_capacity;

                new_data[i] = m_data[index];
            }
            delete[] m_data;
            m_data = new_data;
            m_frontIndex = 0;
            m_backIndex = m_size;
        }
        m_data[m_backIndex] = item;
        m_backIndex = m_backIndex + 1;
        if (m_backIndex > m_capacity) {
            m_backIndex = m_backIndex % m_capacity;
        }
        if (m_backIndex == m_capacity) {
            m_backIndex = 0;
        }
        ++m_size;
    }

    template <typename T>
    T cyclic_double_queue<T>::dequeue_front()
    {
        if (m_size == 0) {
            throw std::out_of_range("cyclic_double_queue is empty!");
        }
        T item = m_data[m_frontIndex];
        m_frontIndex = (m_frontIndex + 1) % m_capacity;
        --m_size;
        if (m_size == m_capacity) {
            size_t new_capacity = m_capacity * m_increaseFactor;
            if (m_capacity < m_initialCapacity) {
                m_capacity = m_initialCapacity;
            }
            T* new_data = new T[new_capacity];

            for (size_t i = 0; i < m_size; ++i) {
                size_t index = (m_frontIndex + i) % m_capacity;

                new_data[i] = m_data[index];
            }
            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
            m_frontIndex = 0;
            m_backIndex = m_size;
        }
        if (m_capacity > (m_size * 4) && (m_capacity != m_initialCapacity)) {
            m_capacity = m_capacity / m_decreaseFactor;
            if (m_capacity < m_initialCapacity) {
                m_capacity = m_initialCapacity;
            }
            T* new_data = new T[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                size_t index = (m_frontIndex + i) % m_capacity;
                new_data[i] = m_data[index];
            }
            delete[] m_data;
            m_data = new_data;
            m_frontIndex = 0;
            m_backIndex = m_size;
        }
        return item;
    }


    template <typename T>
    T cyclic_double_queue<T>::dequeue_back()
    {
        if (m_size == 0) {
            throw std::out_of_range("cyclic_double_queue is empty!");
        }
        if (m_backIndex == 0) {
            m_backIndex = m_capacity - 1;
        } else {
            m_backIndex = m_backIndex - 1;
        }
        T item = m_data[m_backIndex];
        m_size--;
        if (m_size == m_capacity) {
            size_t new_capacity = m_capacity * m_increaseFactor;
            if (m_capacity < m_initialCapacity) {
                m_capacity = m_initialCapacity;
            }
            T* new_data = new T[new_capacity];

            for (size_t i = 0; i < m_size; ++i) {
                size_t index = (m_frontIndex + i) % m_capacity;

                new_data[i] = m_data[index];
            }

            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
            m_frontIndex = 0;
            m_backIndex = m_size;
        }

        if (m_capacity > (m_size * 4) && (m_capacity != m_initialCapacity)) {
            m_capacity = m_capacity / m_decreaseFactor;
            if (m_capacity < m_initialCapacity) {
                m_capacity = m_initialCapacity;
            }
            T* new_data = new T[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                size_t index = (m_frontIndex + i) % m_capacity;

                new_data[i] = m_data[index];
            }
            delete[] m_data;
            m_data = new_data;
            m_frontIndex = 0;
            m_backIndex = m_size;
        }
        return item;
    }

    template <typename T>
    void cyclic_double_queue<T>::pop_front()
    {
        if (m_size == 0) {
            throw std::out_of_range("cyclic_double_queue is empty!");
        }
        m_frontIndex = (m_frontIndex + 1) % m_capacity;
        --m_size;
        if (m_size == m_capacity) {
            size_t new_capacity = m_capacity * m_increaseFactor;
            if (m_capacity < m_initialCapacity) {
                m_capacity = m_initialCapacity;
            }
            T* new_data = new T[new_capacity];

            for (size_t i = 0; i < m_size; ++i) {
                size_t index = (m_frontIndex + i) % m_capacity;

                new_data[i] = m_data[index];
            }

            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
            m_frontIndex = 0;
            m_backIndex = m_size;
        }

        if (m_capacity > (m_size * 4) && (m_capacity != m_initialCapacity)) {
            m_capacity = m_capacity / m_decreaseFactor;
            if (m_capacity < m_initialCapacity) {
                m_capacity = m_initialCapacity;
            }
            T* new_data = new T[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                size_t index = (m_frontIndex + i) % m_capacity;

                new_data[i] = m_data[index];
            }
            delete[] m_data;
            m_data = new_data;
            m_frontIndex = 0;
            m_backIndex = m_size;
        }

    }

    template <typename T>
    void cyclic_double_queue<T>::pop_back()
    {
        if (m_size == 0) {
            throw std::out_of_range("cyclic_double_queue is empty!");
        }
        if (m_backIndex == 0) {
            m_backIndex = m_capacity - 1;
        } else {
            m_backIndex = m_backIndex - 1;
        }
        --m_size;
        if (m_size == m_capacity) {
            size_t new_capacity = m_capacity * m_increaseFactor;
            if (m_capacity < m_initialCapacity) {
                m_capacity = m_initialCapacity;
            }
            T* new_data = new T[new_capacity];

            for (size_t i = 0; i < m_size; ++i) {
                size_t index = (m_frontIndex + i) % m_capacity;

                new_data[i] = m_data[index];
            }

            delete[] m_data;
            m_data = new_data;
            m_capacity = new_capacity;
            m_frontIndex = 0;
            m_backIndex = m_size;
        }

        if (m_capacity > (m_size * 4) && (m_capacity != m_initialCapacity)) {
            m_capacity = m_capacity / m_decreaseFactor;
            if (m_capacity < m_initialCapacity) {
                m_capacity = m_initialCapacity;
            }
            T* new_data = new T[m_capacity];
            for (size_t i = 0; i < m_size; ++i) {
                size_t index = (m_frontIndex + i) % m_capacity;

                new_data[i] = m_data[index];
            }
            delete[] m_data;
            m_data = new_data;
            m_frontIndex = 0;
            m_backIndex = m_size;
        }
    }

    template <typename T>
    bool cyclic_double_queue<T>::empty() const
    {
        if (m_size == 0) {
            return true;
        }
        else {
            return false;
        }

    }

    template <typename T>
    T& cyclic_double_queue<T>::front()
    {
        if (m_size == 0) {
            throw std::out_of_range("cyclic_double_queue is empty!");
        }
        return m_data[m_frontIndex];
    }

    template <typename T>
    T& cyclic_double_queue<T>::back()
    {
        if (m_size == 0) {
            throw std::out_of_range("cyclic_double_queue is empty!");
        }
        size_t backIndex;
        if (m_backIndex == 0) {
            backIndex = m_capacity - 1;
        } else {
            backIndex = m_backIndex - 1;
        }

        return m_data[backIndex];

    }

    template <typename T>
    void cyclic_double_queue<T>::clear()
    {
        delete[] m_data;
        m_data = new T[m_initialCapacity];
        m_capacity = m_initialCapacity;
        m_size = 0;
        m_frontIndex = 0;
        m_backIndex = 0;

    }

    template <typename T>
    std::string cyclic_double_queue<T>::print_status() const
    {
        std::string status = "";
        if (m_size == m_capacity) {
            for (int i = 0; i < m_capacity; i++) {
                status += "[+]";
            }
        }
        if (m_size == 0) {
            for (int i = 0; i < m_capacity; i++) {
                status += "[-]";
            }
        }
        else if (m_frontIndex < m_backIndex) {
            for (int i = 0; i < m_frontIndex; i++) {
                status += "[-]";
            }
            for (int j = m_frontIndex; j < m_backIndex; j++) {
                status += "[+]";
            }
            for (int k = m_backIndex; k < m_capacity; k++) {
                status += "[-]";
            }
        }
        else if (m_backIndex < m_frontIndex) {
            for (int k = 0; k < m_backIndex; k++) {
                status += "[+]";
            }
            for (int j = m_backIndex; j < m_frontIndex; j++) {
                status += "[-]";
            }
            for (int i = m_frontIndex; i < m_capacity; i++) {
                status += "[+]";
            }
        }
        return status;
    }
    template <typename T>
    size_t cyclic_double_queue<T>::get_size() const
    {
        return m_size;
    }
    template <typename T>
    size_t cyclic_double_queue<T>::get_capacity() const
    {
        return m_capacity;
    }
}

