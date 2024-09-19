#ifndef templates_hpp
#define templates_hpp

#include <iostream>
#include "errors.hpp"
using namespace std;

template <typename T> class Item {

    private:
        T data;
        Item <T> *next;
        Item <T> *prev;

    public:
        Item (T data) : data(data){
            next = NULL;
            prev = NULL;
        };

        void SetNext(Item<T>* n){
            next = n;
        };
        
        void SetPrev(Item<T>* n){
            prev = n;
        }
        
        Item<T>* GetPrev(){
            return prev;
        }
        
        Item<T>* GetNext(){
            return next;
        }
        
        T GetData(){
            return data;
        }
        
        void SetData(T newData){
            data = newData;
        }
};

template <class T> class Sequence{
    public:
        virtual int GetLength() = 0;
        virtual T GetFirst() = 0;
        virtual T GetLast() = 0;
        virtual T Get(int index) = 0;
        virtual void Append(T item) = 0;
        virtual void Prepend(T item) = 0;
        virtual void InsertAt(T item, int index) = 0;
        virtual void Set(int index, T value) = 0;
};

template <class T> class DynamicArray{

    private:
        int array_size = 0;
        int capacity = 0;
        T *data;

    public:
        //object creation
        DynamicArray(T *items, int count) : array_size(count){
            capacity = (count % 5 == 0) ? 5 * (count / 5) : 5 * (count / 5 + 1);
            this->data = new T[capacity];
            for (int i = 0; i < count; i++){
                this->data[i] = items[i];
            }
        };

        DynamicArray(int size) : capacity(size){
            this->data = new T[size];
        };

        DynamicArray(){
            this->array_size = 0;
            this->data = NULL;
        };

        DynamicArray(DynamicArray<T> &dynamicArray) : array_size(dynamicArray.array_size){
            capacity = (array_size % 5 == 0) ? 5 * (array_size / 5) : 5 * (array_size / 5 + 1);
            this->data = new T[capacity];
            for (int i = 0; i < this->array_size; i++){
                this->data[i] = dynamicArray.Get(i);
            }
        };

        ~DynamicArray(){
            delete [] data;
        };

        //decomposition
        T Get(int index){
            try{
                if(array_size == 0){
                     throw runtime_error(ArrayIsEmptyErrorMessage);
                }
                if(index >= array_size || index < 0){
                    throw runtime_error(ArrayIndexErrorMessage);
                }
                return this->data[index];
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
            return -1;
        };

        int GetSize(){
            return this->array_size;
        };

        T GetFirst(){
            try{
                if (array_size == 0){
                    throw runtime_error(ArrayIsEmptyErrorMessage);
                 }
                else {
                    return data[0];
                }
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
            return -1;
        };

        T GetLast(){
            try{
                if (array_size == 0){
                    throw runtime_error(ArrayIsEmptyErrorMessage);
                }
                else{
                    return data[array_size - 1];
                }
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
            return -1;
        };

        DynamicArray <T> *GetSubArray(int start, int end){
            try{
                if(start < 0 || start >= array_size|| end < 0 || end >= array_size){
                    throw runtime_error(ArrayIndexErrorMessage);
                }
                if(start == end){
                    data[start];
                }
                T *array = new T[end - start + 1];
                for (int i = start; i <= end; i++){
                    array[i - start] = data[i];
                }
                DynamicArray <T> *subArray = new DynamicArray <T> (array, end - start + 1);
                delete [] array;
                return subArray;
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
            return NULL;
        };

        //operations
        void Set(int index, T value){
            try{
                if(array_size == 0){
                    throw runtime_error(ArrayIsEmptyErrorMessage);
                }
                if(index < 0 || index > array_size){
                    throw runtime_error(ArrayIndexErrorMessage);
                }
                data[index] = value;
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
        };

        void Resize(int newSize){
            this->array_size = newSize;
            T *newData = new T[array_size];
            for (int i = 0; i < array_size; i++){
                newData[i] = data[i];
            }
            delete data;
            data = newData;
        };

        void InsertAt(T item, int index){
            try{
                if(array_size == 0){
                    throw runtime_error(ArrayIsEmptyErrorMessage);
                }
                if(index < 0 || index >= array_size){
                    throw runtime_error(ArrayIndexErrorMessage);
                }
                if (capacity == array_size + 1){
                    capacity += 5;
                    T* temp = new T[capacity];
                    temp[index] = item;
                    for (int i = 0; i < index; i++)
                    {
                        temp[i] = this->data[i];
                    }
                    for (int i = index + 1; i < this->array_size + 1; i++)
                    {
                        temp[i] = this->data[i - 1];
                    }
                    delete this->data;
                    this->data = temp;
                    (this->array_size)++;
                }
                else{
                    for (int i = array_size; i > index; i--)
                    {
                        data[i] = data[i - 1];
                    }
                    data[index] = item;
                    array_size ++;
                }
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
        };

        void Append(T item){
            if(capacity <= array_size + 1){
                capacity += 5;
                T *temp = new T[capacity];
                temp[this->array_size] = item;
                for (int i = 0; i < this->array_size; i++){
                    temp[i] = this->data[i];
                }
                delete this->data;
                this->data = temp;
                (this->array_size)++;
            }
            else {
                data[this->array_size] = item;
                (this->array_size)++;
            }
        };

        void Prepend(T item){
            if(capacity == array_size + 1){
                capacity += 5;
                T *temp = new T[capacity];
                temp[0] = item;
                for(int i = 0; i < this->array_size; i++){
                    temp[i + 1] = this->data[i];
                }
                delete this->data;
                this->data = temp;
                (this->array_size)++;
            }
            else {
                for(int i = array_size; i > 0; i--){
                    data[i] = data[i - 1];
                }
                data[0] = item;
                array_size++;
            }
            if(array_size == 0){
                data[0] = item;
            }
        };

        DynamicArray<T> *Concat(DynamicArray<T> &array) {
        int size = this->array_size + array.GetSize();
        T *data = new T[size];
        for (int i = 0; i < this->array_size; i++) {
            data[i] = this->data[i];
        }
        for (int i = 0; i < array.GetSize(); i++) {
            data[this->array_size + i] = array[i];
        }
        DynamicArray<T> *result = new DynamicArray<T>(data, size);
        delete[] data;

        return result;
        }
        
        void DeleteIndex(int index){
            try{
                if(array_size == 0){
                    throw runtime_error(ArrayIsEmptyErrorMessage);
                }
                if(index < 0 || index >= array_size){
                    throw runtime_error(ArrayIndexErrorMessage);
                }
                for(int i = index; i < array_size - 1; i++){
                    data[i] = data[i + 1];
                }
                array_size--;
                if(array_size + 5 == capacity){
                    capacity -= 5;
                    T *temp = new T[capacity];
                    for(int i = 0; i < array_size; i++){
                        temp[i] = this->data[i];
                    }
                    delete this->data;
                    this->data = temp;
                }
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
        };

        //operator
        T operator[](const int i){
            try{
                if(array_size == 0){
                    throw runtime_error(ArrayIsEmptyErrorMessage);
                }
                if(i < 0 || i >= array_size){
                    throw runtime_error(ArrayIndexErrorMessage);
                }
                return this->data[i];
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
            return -1;
        };
};

template <class T> class LinkedList{

    private:
        Item <T> *head;
        Item <T> *tail;
        int list_size;

    public:

        //object creation
        LinkedList(T *items, int count) : list_size(count){
            head = new Item<T>(items[0]);
            Item <T> *first = head;
            for(int i = 1; i < count; i++){
                Item <T> *temp = new Item <T> (items[i]);
                first->SetNext(temp);
                temp->SetPrev(first);
                first = temp;
            }
            tail = first;
        };

        LinkedList(){
            head = NULL;
            tail = NULL;
            list_size = 0;
        };

        LinkedList(LinkedList <T> &list){
            list_size = 0;
            for (int i = 0; i < list.GetLength(); i++){
                this->Append(list.Get(i));
            }
        };

        ~LinkedList(){
            Item <T> *first = head;
            if(first != NULL){
                while(first != NULL){
                    Item <T> *temp = first->GetNext();
                    delete first;
                    first = temp;
                }
                delete first;
            }
        };

        //decomposition
        T GetFirst(){
            try{
                if(list_size == 0){
                    throw runtime_error(ListIsEmptyErrorMessage);
                }
                return head->GetData();
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
            return -1;
        };

        T GetLast(){
            try{
                if(list_size == 0){
                    throw runtime_error(ListIsEmptyErrorMessage);
                }
                return tail->GetData();
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
            return -1;
        }

        T Get(int index){
            try{
                if(list_size == 0){
                    throw runtime_error(ListIsEmptyErrorMessage);
                }
                else if(index < 0 || index >= list_size){
                    throw runtime_error(ArrayIndexErrorMessage);
                }
                else if(index > list_size / 2){
                    Item <T> *item = tail;
                    for(int i = list_size - 1; i > index; i--){
                        item = item->GetPrev();
                    }
                    return item->GetData();
                }
                else{
                    Item <T> *item = head;
                    for(int i = 0; i < index; i++){
                        item = item->GetNext();
                    }
                    return item->GetData();
                }
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
            return -1;
        };

        LinkedList <T> *getSubList(int startIndex, int endIndex){
            try{
                if(list_size == 0){
                    throw runtime_error(ListIndexErrorMessage);
                }
                if(startIndex < 0 || startIndex >= list_size || endIndex < 0 || endIndex >= list_size){
                    throw runtime_error(ListIndexErrorMessage);
                }
                Item<T> *item = head;
                LinkedList<T> * newList = new LinkedList();
                for (int i = 0; i <= startIndex; i++)
                {
                    item = item->GetNext();
                }
                for (int i = startIndex; i <= endIndex; i++)
                {
                    newList->Append(item->GetData());
                    item = item->GetNext();
                }
                return newList;
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
        };

        int GetLength(){
            return list_size;
        }
        
        //operations
        void Append(T item){
            list_size++;
            if(tail != NULL){
                Item <T> *first = tail;
                Item <T> *temp = new Item <T> (item);
                first->SetNext(temp);
                temp->SetPrev(first);
                tail = temp;
            }
            else{
                Item <T> *current = new Item <T> (item);
                head = current;
                tail = current;
            }
        };

        void Prepend(T item){
            list_size++;
            if(list_size == 1){
                head = new Item <T> (item);
            }
            Item <T> *current = head;
            head = new Item <T> (item);
            Item <T> *buffer = current;
            head->SetNext(buffer);
            buffer->SetPrev(head);
            if(tail == NULL){
                tail = buffer;
            }
        };  

        void DeleteIndex(int index){
            try{
                if(list_size == 0){
                    throw runtime_error(ListIsEmptyErrorMessage);
                }
                else if(index < 0 || index >= list_size){
                    throw runtime_error(ListIndexErrorMessage);
                }
                else if(index >= list_size / 2){
                    Item <T> *item = tail;
                    for (int i = list_size - 1; i > index; i--){
                        item = item->GetPrev();
                    }
                    if(index < list_size - 1 && index != 0){
                        Item <T> *previous = item->GetPrev();
                        Item <T> *next = item->GetNext();
                        previous->SetNext(next);
                        next->SetPrev(previous);
                        delete item;
                    }
                    else if(index == 0 && list_size == 1){
                        delete head;
                        head = NULL;
                        tail = NULL;
                    }
                    else if(index == 0){
                        Item <T> *next = item->GetNext();
                        head = next;
                        next->SetPrev(NULL);
                        delete item;
                    }
                    else{
                        Item <T> *previous = item->GetPrev();
                        tail = previous;
                        previous->SetNext(NULL);
                        delete item;
                    }
                    list_size--;
                }
                else{
                    Item <T> *item = head;
                    for (int i = 0; i < index; i++){
                        item = item->GetNext();
                    }
                    if(index > 0 && index != list_size - 1){
                        Item <T> *previous = item->GetPrev();
                        Item <T> *next = item->GetNext();
                        previous->SetNext(next);
                        next->SetPrev(previous);
                        delete item;
                    }
                    else if(index == 0 && list_size == 1){
                        delete head;
                        head = NULL;
                        tail = NULL;
                    }
                    else if(index == list_size - 1){
                        Item <T> *previous = item->GetPrev();
                        tail = previous;
                        previous->SetNext(NULL);
                        delete item;
                    }
                    else{
                        Item <T> *next = item->GetNext();
                        head = next;
                        next->SetPrev(NULL);
                        delete item;
                    }
                    list_size--;
                }
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
        };

        void InsertAt(T item, int index){
            try{
                if(list_size == 0){
                    throw runtime_error(ListIsEmptyErrorMessage);
                }
                else if(index < 0 || index >= list_size){
                    throw runtime_error(ListIndexErrorMessage);
                }
                else if(index == 0){
                    Prepend(item);
                }
                else if(index > list_size / 2){
                    Item <T> *buf = tail;
                    for (int i = list_size - 1; i >= index; i--){
                        buf = buf->GetPrev();
                    }
                    Item <T> *new_element = new Item <T> (item);
                    new_element->SetPrev(buf->GetPrev());
                    new_element->SetNext(buf);
                    buf->SetPrev(new_element);
                }
                else{
                    Item <T> *buf = head;
                    for (int i = 0; i < index; i++){
                        buf = buf->GetNext();
                    }
                    Item <T> *new_element = new Item <T> (item);
                    Item <T> *current = buf->GetPrev();
                    current->SetNext(new_element);
                    buf->SetPrev(new_element);
                    new_element->SetPrev(current);
                    new_element->SetNext(buf);
                }
                list_size++;
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
        };

        void Set(int index, T value){
            try{
                if(list_size == 0){
                    throw runtime_error(ListIsEmptyErrorMessage);
                }
                else if(index < 0 || index >= list_size){
                    throw runtime_error(ListIndexErrorMessage);
                }
                else if(index > list_size / 2){
                    Item <T> *item = tail;
                    for (int i = list_size - 1; i > index; i--){
                        item = item->GetPrev();
                    }
                    item->SetData(value);
                }
                else{
                    Item <T> *item = head;
                    for (int i = 0; i < index; i++){
                        item = item->GetNext();
                    }
                    item->SetData(value);
                }
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
        };

        LinkedList <T> *GetSubList(int startIndex, int endIndex){
            try{
                if(list_size == 0){
                    throw runtime_error(ListIsEmptyErrorMessage);
                }
                else if (startIndex < 0 || endIndex > list_size - 1 || startIndex > endIndex){
                    throw runtime_error(ListIndexErrorMessage);
                }
                LinkedList<T>* subList = new LinkedList<T>();
                Item <T>* current = head;
                int i = 0;
                if(startIndex == 0){
                    while (i <= endIndex) {
                        subList->Append(current->GetData());
                        current = current->GetNext();
                        i++;
                    }
                }
                do{
                    current = current->GetNext();
                    i++;
                } while (i < startIndex);

                while (i <= endIndex) {
                    subList->Append(current->GetData());
                    current = current->GetNext();
                    i++;
                }
                return subList;
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
            return NULL;
        };

        LinkedList <T> *Concat(LinkedList <T> &list){
            LinkedList<T>* newList = new LinkedList<T>();
            Item <T> *temp = head;
            while(temp){
                newList->Append(temp->GetData());
                temp = temp->GetNext();
            }
            temp = list.head;
            while(temp){
                newList->Append(temp->GetData());
                temp = temp->GetNext();
            }
            return newList;
        };

        //operator
        T operator[](const int index){
            try{
                if(list_size == 0){
                    throw runtime_error(ListIsEmptyErrorMessage);
                }
                else if(index < 0 || index >= list_size){
                    throw runtime_error(ListIndexErrorMessage);
                }
                else if(index >= list_size / 2){
                    Item <T> *item = tail;
                    for (int i = list_size - 1; i > index; i--){
                        item = item->GetPrev();
                    }
                    return item->GetData();
                }
                else{
                    Item <T> *item = head;
                    for (int i = 0; i < index; i++){
                        item = item->GetNext();
                    }
                    return item->GetData();
                }
            } catch (exception const& e){
                cerr << e.what() << endl;
            }
            return -1;
        };
};

template <typename T> class ArraySequence : Sequence <T> {
    private:
        DynamicArray <T> *data;
        
    public:
        ArraySequence(T *items, int count){
            data = new DynamicArray <T> (items, count);
        };

        ArraySequence(){
            data = new DynamicArray <T> ();
        };

        ArraySequence(DynamicArray <T> &list){
            data = new DynamicArray <T> (list);
        };

        ~ArraySequence(){
            delete data;
        };

        void Append(T item) override{
            data->Append(item);
        };

        void Prepend(T item) override{
            data->Prepend(item);
        };

        void InsertAt(T item, int index) override{
            data->InsertAt(item, index);
        };

        T GetFirst() override{
            return data->GetFirst();
        };

        T GetLast() override{
            return data->GetLast();
        };

        T Get(int index) override{
            return data->Get(index);
        };

        int GetLength() override{
            return data->GetSize();
        };

        void DeleteAt(int index){
            data->DeleteIndex(index);
        };

        void Set(int index, T value) override{
            data->Set(index, value);
        };

        void Resize(int newSize){
            data->Resize(newSize);
        };

        DynamicArray <T> *GetData(){
            return data;
        };

        ArraySequence <T> *getSubSequence(int startIndex, int endIndex){
            return new ArraySequence<T> (*data->GetSubArray(startIndex, endIndex));
        };

        ArraySequence <T> *Concat(ArraySequence<T> *list){
            return new ArraySequence<T> (*data->Concat(*list->GetData()));
        };

        T operator [] (const int index){
            return data->get(index);
        };
};

template <typename T> class LinkedListSequence : Sequence <T> {
    private:
        LinkedList <T> *data;
    
    public:
        LinkedListSequence(T *items, int count){
            data = new LinkedList <T> (items, count);
        };

        LinkedListSequence(){
            data = new LinkedList <T> ();
        }

        LinkedListSequence(LinkedList <T> &list){
            data = new LinkedList <T> (list);
        };

        ~LinkedListSequence(){
            delete data;
        };

        void Append(T item) override{
            data->Append(item);
        };

        void Prepend(T item) override{
            data->Prepend(item);
        };

        void InsertAt(T item, int index) override{
            data->InsertAt(item, index);
        };

        void DeleteAt(int index){
            data->DeleteIndex(index);
        };

        T GetFirst() override{
            return data->GetFirst();
        };

        T GetLast() override{
            return data->GetLast();
        };

        T Get(int index) override{
            return data->Get(index);
        };

        int GetLength() override{
            return data->GetLength();
        };

        void Set(int index, T value) override{
            data->Set(index, value);
        };

        LinkedList <T> *GetData(){
            return data;
        };

        LinkedListSequence <T> *getSubSequence(int startIndex, int endIndex){
            LinkedList <T> *copy = data->GetSubList(startIndex, endIndex);
            LinkedListSequence <T> *newList = new LinkedListSequence<T> (*copy);
            delete copy;
            return newList;
        };

        LinkedListSequence <T> *Concat(LinkedListSequence<T> *list){
            return new LinkedListSequence<T> (*data->Concat(*list->GetData()));
        };

        T operator [] (const int index){
            return data->Get(index);
        };
};

template <typename T> void ArraySequencePrint(ArraySequence<T>& array_sequence){
    cout << "Array Sequence: ";
    for(int i = 0; i < array_sequence.GetLength(); i++){
        cout << array_sequence.Get(i) << " ";
    }
    cout << endl;
}

template <typename T> void LinkedListSequencePrint(LinkedListSequence<T>& list_sequence){
    cout << "List Sequence: ";
    for(int i = 0; i < list_sequence.GetLength(); i++){
        cout << list_sequence.Get(i) << " ";
    }
    cout << endl;
}
       
#endif







    