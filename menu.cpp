#include <iostream>
#include "errors.hpp"
#include "unit_tests.cpp"
using namespace std;

#define INVITE "> "

int menu(){

    size_t value_type = 0;
    size_t sequence_type = 0;
    
    cout << "Enter type of sequence: \n";
    cout << "1 - Array Sequence\n2 - List Sequence\n";
    cout << INVITE;
    cin >> sequence_type;

    while(sequence_type != 1 && sequence_type != 2){
        cout << MenuOptionErrorMessage << endl;
        cout << "Enter type of sequence: \n";
        cout << "1 - Array Sequence\n2 - List Sequence\n";
        cout << INVITE;
        cin >> sequence_type;
    }

    cout << "Enter value type: \n";
    cout << "1 - Integer\n2 - Float\n3 - Char\n";
    cout << INVITE;
    cin >> value_type;

    while(value_type != 1 && value_type != 2 && value_type != 3){
        cout << MenuOptionErrorMessage << endl;
        cout << "Enter value type: \n";
        cout << "1 - Integer\n2 - Float\n3 - Char\n";
        cout << INVITE;
        cin >> value_type;
    }

    switch(sequence_type) {
        case 1:
            switch(value_type) {
                case 1:
                    ArraySequenceTesting<int>();
                    break;

                case 2:
                    ArraySequenceTesting<float>();
                    break;

                case 3:
                    ArraySequenceTesting<char>();
                    break;

                default:
                    cout << MenuOptionErrorMessage;
                    break;
            }
        
        case 2:
            switch(value_type) {
                case 1:
                    LinkedListSequenceTesting<int>();
                    break;

                case 2:
                    LinkedListSequenceTesting<float>();
                    break;

                case 3:
                    LinkedListSequenceTesting<char>();
                    break;

                default:
                    cout << MenuOptionErrorMessage;
                    break;
            }

        default:
            cout << MenuOptionErrorMessage;
            break;
    }
    return 0;
}
