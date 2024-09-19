#ifndef ERRORS_HPP
#define ERRORS_HPP

#define MenuOptionErrorMessage "Error: Invalid option!"
#define ArrayIsEmptyErrorMessage "Error: Array is empty!"
#define ArrayIndexErrorMessage "Error: Index is out of range!"
#define ListIsEmptyErrorMessage "Error: List is empty!"
#define ListIndexErrorMessage "Error: Index is out of range!"
#define SequenceTypeErrorMessage "Error: Invalid sequence type!"

enum ERRORS {
    MenuOptionErrorCode = 0,
    ArrayIsEmptyErrorCode = 1,
    ArrayIndexErrorCode = 2,
    ListIsEmptyErrorCode = 3,
    ListIndexErrorCode = 4,
    ValueTypeErrorCode = 5,
    SequenceTypeErrorCode = 7,
};

#endif