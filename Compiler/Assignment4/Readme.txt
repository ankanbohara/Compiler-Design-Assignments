Rules :
1. E --> E + T
2. E --> T
3. T --> T * F
4. T --> F
5. F --> (E)
6. F -->id

This is bottom up parser for parsing input string.
It is implemented in C++.
Input : id * (id + id) + id
Output :
F-->id
T-->F
F-->id
T-->F
E-->T
F-->id
T-->F
E-->E+T
F-->(E)
T-->T*F
E-->T
F-->id
T-->F
E-->E+T
Parsing successfully completed

