This is hand made parser for parsing input string.
It is implemented in C++.
Input : id * (id + id) + id
Output :
E --> TE'
T --> FT'
F --> id
Matched id with id
T' --> *FT'
Matched * with *
F --> (E)
Matched ( with (
E --> TE'
T --> FT'
F --> id
Matched id with id
T' --> epsilon
E' --> +TE'
Matched + with +
T --> FT'
F --> id
Matched id with id
T' --> epsilon
E' --> epsilon
Matched ) with )
T' --> epsilon
E' --> +TE'
Matched + with +
T --> FT'
F --> id
Matched id with id
T' --> epsilon
E' --> epsilon
Parsing successfully completed
