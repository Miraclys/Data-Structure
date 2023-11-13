#include <initializer_list>
#include <exception>

template<class T>
class LinkedList {
    private:
        template<class E>
        class Node {
            public: 
                E item;
                Node<E>* next;
                Node<E>* prev;
                Node(Node<E>* prev, E element, Node<E>* next) {
                    this->item = element;
                    this->next = next;
                    this->prev = prev;
                }
        };

        unsigned size = 0;
        unsigned modCount = 0;
        Node<T>* first;
        Node<T>* last;

        void addAll(std::initializer_list<T> c) {
            // TODO
        }

        void linkFirst(T t) {
            Node<T>* f = first;
            Node<T>* newNode = new Node<T>(nullptr, t, f);
            this->first = newNode;
            if (f == nullptr) this->last = newNode;
            else f->prev = newNode;
            size++;
            modCount++;
        }

        void linkBefore(T t, Node<T>* succ) {
            Node<T>* pred = succ->prev;
            Node<T>* newNode = new Node<T>(pred, t, succ);
            succ->prev = newNode;
            if (pred == nullptr) this->first = newNode;
            else pred->next = newNode;
            size++;
            modCount++;
        }
        
        T& unlinkFirst(Node<T>* f) {
            T& element = f->item;
            Node<T>* next = f->next;
            f->next = nullptr;
            this->first = next;
            if (next == nullptr) this->last = nullptr;
            else next->prev = nullptr;
            size--;
            modCount++;
            return element;
        }
        T& unlinkLast(Node<T>* l) {
            T& element = l->item;
            Node<T>* prev = l->prev;
            l->item = nullptr;
            this->last = prev;
            if (prev == nullptr) this->first = nullptr;
            else prev->next = nullptr;
            size--;
            modCount++;
            return element;
        }

        T& unlink(Node<T>* x) {
            T& element = x->item;
            Node<T>* next = x->next;
            Node<T>* prev = x->prev;

            if (prev == nullptr) {
                this->first = next;
            } else {
                prev->next = next;
                x.prev = nullptr;
            }

            if (next == nullptr) {
                this->last = prev;
            } else {
                next->prev = prev;
                x->next = nullptr;
            }
            size--;
            modCount++;
            return element;
        }

        bool isElementIndex(int index) {
            return index >= 0 && index < size;
        }

        bool isPositionIndex(int index) {
            return index >= 0 && index <= size;
        }

        void checkElementIndex(int index) {
            if (!isElementIndex(index))
                throw new std::exception();
        }

        void checkPositionIndex(int index) {
            if (!isPositionIndex(index))
                throw new std::exception();
        }

        void linkLast(T e) {
            Node<T>* l = last;
            Node<T>* newNode = new Node<T>(l, e, nullptr);
            last = newNode;
            if (!l)
                first = newNode;
            else
                l->next = newNode;
            size++;
            modCount++;
        }

    public: 
        LinkedList() {
            this->first = nullptr;
            this->last = nullptr;
        }

        T& getFirst() {
            Node<T>* f = first;
            if (f == nullptr) throw std::exception();
            return f->item;
        }

        T& getLast() {
            Node<T>* l = last;
            if (l == nullptr) throw std::exception();
            return l->item;
        }

        T& removeFirst() {
            Node<T>* f = first;
            if (!f) throw std::exception();
            return unlinkFirst(f);
        }

        T& removeLast() {
            Node<T>* l = last;
            if (l == nullptr) return nullptr;
            return unlinkLast(l);
        }

        void addFirst(T e) {
            linkFirst(e);
        }

        void addLast(T e) {
            linkLast(e);
        }

        bool contains(T e) const {
            return indexOf(e) >= 0; 
        }

        int getSize() const {
            return this->size;
        }

        bool isEmpty() const {
            return !getSize();
        }

        bool add(T e) const {
            linkLast(e);
            return true;
        }

        void clear() {
            for (Node<T>* x = first; x != nullptr; ) {
                Node<T>* next = x->next;
                x->item = nullptr;
                x->next = nullptr;
                x->prev = nullptr;
                x = next;
            }
            first = last = nullptr;
            size = 0;
            modCount++;
        }

        

        Node<T>* node(int index) {

            if (index < (size >> 1)) {
                Node<T>* x = first;
                for (int i = 0; i < index; i++)
                    x = x->next;
                return x;
            } else {
                Node<T>* x = last;
                for (int i = size - 1; i > index; i--)
                    x = x->prev;
                return x;
            }
        }

        T& get(int index) {
            checkElementIndex(index);
            return node(index);
        }

        T& set(int index, T element) {
            checkElementIndex(index);
            Node<T>* x = node(index);
            T oldVal = x->item;
            x->item = element;
            return oldVal;
        }

        void add(int index, T element) {
            checkPositionIndex(index);

            if (index == size)
                linkLast(element);
            else
                linkBefore(element, node(index));
        }

        T& remove(int index) {
            checkElementIndex(index);
            return unlink(node(index));
        }

};

