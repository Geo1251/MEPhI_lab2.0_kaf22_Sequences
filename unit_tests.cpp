#include <iostream>
#include "errors.hpp"
#include "templates.hpp"
#define INVITE "> "
using namespace std;

template <typename T> void ArraySequenceTesting(){
    size_t array_sequence_type = 0;
    cout << "How do you want initialize your array sequence?" << endl;
    cout << "1 - Create empty sequence\n2 - Create sequence from array\n";
    cout << INVITE;
    cin >> array_sequence_type;

    while(array_sequence_type != 1 && array_sequence_type != 2){
        cout << MenuOptionErrorMessage << endl;
        cout << "How do you want initialize your array sequence?" << endl;
        cout << "1 - Create empty sequence\n2 - Create sequence from array\n";
        cout << INVITE;
        cin >> array_sequence_type;
    }

    ArraySequence <T> *array_sequence;
    switch(array_sequence_type){
        case 1:
            array_sequence = new ArraySequence<T>();
            break;
        
        case 2:
        {
            size_t array_sequence_size = 0;
            cout << "Enter the size of your sequence:";
            cin >> array_sequence_size;
            T *temp = new T[array_sequence_size];
            cout << "Enter the elements of your sequence:\n";
            cout << INVITE;
            for(int i = 0; i < array_sequence_size; i++){
                cin >> temp[i];
            }
            array_sequence = new ArraySequence<T>(temp, array_sequence_size);
            delete [] temp;
            break;
        }

        default:
            throw runtime_error(SequenceTypeErrorMessage);
    }

    size_t constant = 0;
    size_t option = 0;
    while (constant != 1){

        cout << "Select an option: \n";
        cout << "1 - Get first element of the sequence\n2 - Get last element of the sequence\n";
        cout << "3 - Get the element by index\n4 - Get subsequence of the sequence\n";
        cout << "5 - Get length of the sequence\n6 - Append the element in the sequence\n";
        cout << "7 - Prepend the element in the sequence\n8 - Insert the element in the sequence by index\n";
        cout << "9 - Concatenate two sequences\n10 - Output the sequence\n";
        cout << "11 - Delete the element from the sequence by index\n12 - Resize the sequence\n";
        cout << "13 - Set an element in the sequence by index\n14 - Exit the program\n";

        cout << INVITE;
        cin >> option;

        switch(option) {

            case 1:
                cout << "First element of the sequence: " << array_sequence->GetFirst() << endl;
                break;

            case 2:
                cout << "Last element of the sequence: " << array_sequence->GetLast() << endl;
                break;

            case 3:
            {
                size_t index;
                cout << "Enter the index of the element: ";
                cin >> index;
                cout << "Your element: " << array_sequence->Get(index) << endl;
                break;
            }


            case 4:
            {
                size_t start, end;
                cout << "Enter start and end of the subsequence: \n";
                cout << "Start: ";
                cin >> start;
                cout << "End: ";
                cin >> end;
                ArraySequence <T> *temp_sequence = array_sequence->getSubSequence(start, end);
                cout << "Your subsequence: ";
                for(int i = 0; i < temp_sequence->GetLength(); i++){
                    cout << temp_sequence->Get(i) << " ";
                }
                cout << endl;
                delete temp_sequence;
                break;
            }

            case 5:
                cout << "Length of the sequence: " << array_sequence->GetLength() << endl;
                break;

            case 6:
            {
                T item;
                cout << "Enter item: ";
                cin >> item;
                array_sequence->Append(item);
                ArraySequencePrint(*array_sequence);
                break;
            }

            case 7:
            {
                T item;
                cout << "Enter item: ";
                cin >> item;
                array_sequence->Prepend(item);
                ArraySequencePrint(*array_sequence);
                break;
            }

            case 8:
            {
                size_t index;
                T item;
                cout << "Enter index: ";
                cin >> index;
                cout << "Enter item: ";
                cin >> item;
                array_sequence->InsertAt(item, index);
                ArraySequencePrint(*array_sequence);
                break;
            }

            case 9:
            {
                size_t sequence_size;
                cout << "Enter size of your sequence: ";
                cin >> sequence_size;
                T *temp_sequence_first = new T[sequence_size];
                cout << "Enter elements of your sequence: ";
                for(int i = 0; i < sequence_size; i++){
                    cin >> temp_sequence_first[i];
                }
                ArraySequence <T> *bufSequence = new ArraySequence <T> (temp_sequence_first, sequence_size);
                delete [] temp_sequence_first;
                ArraySequence <T> *temp_sequence_second = array_sequence->Concat(bufSequence);
                cout << "New sequence: ";
                for(int i = 0; i < temp_sequence_second->GetLength(); i++){
                    cout << temp_sequence_second->Get(i) << " ";
                }
                cout << endl;
                delete temp_sequence_second;
                break;
            }

            case 10:
                cout << "Array Sequence: ";
                for(int i = 0; i < array_sequence->GetLength(); i++){
                    cout << array_sequence->Get(i) << " ";
                }
                cout << endl;
                break;

            case 11:
            {
                size_t index;
                cout << "Enter index: ";
                cin >> index;
                array_sequence->DeleteAt(index);
                ArraySequencePrint(*array_sequence);
                break;
            }

            case 12:
                T newSize;
                cout << "Enter new size: ";
                cin >> newSize;
                array_sequence->Resize(newSize);
                break;

            case 13:
                size_t index;
                T item;
                cout << "Enter index: ";
                cin >> index;
                cout << "Enter item: ";
                cin >> item;
                array_sequence->Set(index, item);
                ArraySequencePrint(*array_sequence);
                break;

            case 14:
                delete array_sequence;
                cout << "Shutting down..." << endl;
                cout << "Goodbye!" << endl;
                exit(0);

            default:
                cout <<MenuOptionErrorMessage << endl;
                break;
        }
    }
}

template <typename T> void LinkedListSequenceTesting(){
    size_t linked_list_sequence_type = 0;
    cout << "How do you want initialize your linked list sequence?\n";
    cout << "1 - Create empty sequence\n2 - Create sequence from list\n";
    cout << INVITE;
    cin >> linked_list_sequence_type;

    while(linked_list_sequence_type != 1 && linked_list_sequence_type != 2){
        cout << MenuOptionErrorMessage << endl;
        cout << "How do you want initialize your array sequence?" << endl;
        cout << "1 - Create empty sequence\n2 - Create sequence from array\n";
        cout << INVITE;
        cin >> linked_list_sequence_type;
    }

    LinkedListSequence <T> *list_sequence;
    switch(linked_list_sequence_type){

        case 1:
            list_sequence = new LinkedListSequence <T>();
            break;

        case 2:
        {
            size_t sequence_size = 0;
            cout << "Enter the size of your sequence: ";
            cin >> sequence_size;
            T *temp = new T[sequence_size];
            cout << "Enter the elements of your sequence:\n";
            cout << INVITE;
            for(int i = 0; i < sequence_size; i++){
                cin >> temp[i];
            }
            list_sequence = new LinkedListSequence<T>(temp, sequence_size);
            delete [] temp;
            break;
        }


        default:
            cout << MenuOptionErrorMessage << endl;
            break;
    }

    size_t constant = 0;
    size_t option = 0;
    while (constant != 1){

        cout << "Select an option: \n";
        cout << "1 - Get first element of the sequence\n2 - Get last element of the sequence\n";
        cout << "3 - Get the element by index\n4 - Get subsequence of the sequence\n";
        cout << "5 - Get length of the sequence\n6 - Append the element in the sequence\n";
        cout << "7 - Prepend the element in the sequence\n8 - Insert the element in the sequence by index\n";
        cout << "9 - Concatenate two sequences\n10 - Output the sequence\n";
        cout << "11 - Delete the element from the sequence by index\n";
        cout << "12 - Set an element in the sequence by index\n13 - Exit the program\n";

        cout << INVITE;
        cin >> option;

        switch(option) {

            case 1:
                cout << "First element of the sequence: " << list_sequence->GetFirst() << endl;
                break;

            case 2:
                cout << "Last element of the sequence: " << list_sequence->GetLast() << endl;
                break;

            case 3:
            {
                size_t index;
                cout << "Enter the index of the element: ";
                cin >> index;
                cout << "Your element: " << list_sequence->Get(index) << endl;
                break;
            }

            case 4:
            {
                size_t start, end;
                cout << "Enter start and end of the subsequence: \n";
                cout << "Start: ";
                cin >> start;
                cout << "End: ";
                cin >> end;
                LinkedListSequence <T> *temp_sequence = list_sequence->getSubSequence(start, end);
                cout << "Your subsequence: ";
                for(int i = 0; i < temp_sequence->GetLength(); i++){
                    cout << temp_sequence->Get(i) << " ";
                }
                cout << endl;
                delete temp_sequence;
                break;
            }

            case 5:
                cout << "Length of the sequence: " << list_sequence->GetLength() << endl;
                break;

            case 6:
            {
                T item;
                cout << "Enter item: ";
                cin >> item;
                list_sequence->Append(item);
                LinkedListSequencePrint(*list_sequence);
                break;
            }

            case 7:
            {
                T item;
                cout << "Enter item: ";
                cin >> item;
                list_sequence->Prepend(item);
                LinkedListSequencePrint(*list_sequence);
                break;
            }

            case 8:
            {
                size_t index;
                T item;
                cout << "Enter index: ";
                cin >> index;
                cout << "Enter item: ";
                cin >> item;
                list_sequence->InsertAt(item, index);
                LinkedListSequencePrint(*list_sequence);
                break;
            }

            case 9:
            {
                size_t sequence_size;
                cout << "Enter size of your sequence: ";
                cin >> sequence_size;
                T *temp_sequence_first = new T[sequence_size];
                cout << "Enter elements of your sequence: ";
                for(int i = 0; i < sequence_size; i++){
                    cin >> temp_sequence_first[i];
                }
                LinkedListSequence <T> *bufSequence = new LinkedListSequence <T> (temp_sequence_first, sequence_size);
                delete [] temp_sequence_first;
                LinkedListSequence <T> *temp_sequence_second = list_sequence->Concat(bufSequence);
                cout << "New sequence: ";
                for(int i = 0; i < temp_sequence_second->GetLength(); i++){
                    cout << temp_sequence_second->Get(i) << " ";
                }
                cout << endl;
                delete temp_sequence_second;
                break;
            }

            case 10:
                cout << "List Sequence: ";
                for(int i = 0; i < list_sequence->GetLength(); i++){
                    cout << list_sequence->Get(i) << " ";
                }
                cout << endl;
                break;

            case 11:
            {
                size_t index;
                cout << "Enter index: ";
                cin >> index;
                list_sequence->DeleteAt(index);
                LinkedListSequencePrint(*list_sequence);
                break;
            }

            case 12:
                size_t index;
                T item;
                cout << "Enter index: ";
                cin >> index;
                cout << "Enter item: ";
                cin >> item;
                list_sequence->Set(index, item);
                LinkedListSequencePrint(*list_sequence);
                break;

            case 13:
                delete list_sequence;
                cout << "Shutting down..." << endl;
                cout << "Goodbye!" << endl;
                exit(0);

            default:
                cout << MenuOptionErrorMessage << endl;
                break;
        }
    }
}
