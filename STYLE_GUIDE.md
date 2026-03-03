# Style Guide
## Variable names
User-defined structures and functions must use prefixes, if applicable. Use the `m` prefix for struct fields and `p` for function arguments that are pointers. All variables, arguments, and struct fields must be in camelCase.

```c
struct MyStruct {
    int mMyValue;
    float mMyOtherValue;
};

void MyFunction(int myValue, int* pMyPointer);

int myValue = 4;
```

When declaring pointers, the asterisk should be on the side of the data type. Do not declare multiple pointers on the same line.
```c
// OK
int* ptr1;
int* ptr2;

// Not OK
int *ptr;
int *ptr1, *ptr2;
```

## Structure
Source files (`.c`) and header files (`.h`) are to be within the `src` folder. The `src` directory can be subdivided with additional folders if necessary.

When `#include`-ing files, you should never have to use `..`. Simply include the folder in the include path if necessary.

```c
// OK
#include "folder/dependency.h"

// Not OK
#include "../folder/dependency.h"
```

## Visual formatting
Never omit spaces in between keywords, parentheses, brackets, and the like.

```c
if (condition) { // OK
    // ...
} else if(someOtherCondition){ // Not OK
    // ...
}
```

Always be explicit when comparing values.

```c
bool condition;
int value;
int* ptr;

// OK
if (condition) { }
if (value == 0) { }
if (ptr != NULL) { }

// Not OK
if (value) { }
if (ptr) { }
```

User-defined structures and functions should be named with PascalCase.
```c
// OK
struct MyStruct { };

void MyFunction();

// Not OK
struct myStruct { };

void myFunfction();
```
