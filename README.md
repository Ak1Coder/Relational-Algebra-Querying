# Querying in Relational Algebra
In this app any commands are case insensitive, on the other hand names of variables are case sensitive.

## Explanation of all the Commands
### IMPORT and EXPORT
Any .csv or .tsv files can be imported and exported in the following way. To import a file you need the path to the file to import it and also the name of the variable which you can use later in the app to reference this file.
IMPORT "myDir/file.csv" "name"

Export works in a similar way.
EXPORT name "myDir/fileNew.csv"

An important thing to note is, that the app continously reads the file from the path until it's edited, therefore if at any point you change the data in the original .csv file, the data in the variable also changes.

### Set Operations
Intersection of two variables A and B: INTERSECT A B
Union of two variables A and B: UNION A B
Set Difference of two variables A and B: DIFF A B
Cartesian Cross of two variables A and B: CROSS A B

### Other Operations
Selection of only rows containing value X in a column C of variable A: SELECTION A "C = X"
In case X is a number, let's say 6: SELECTION A "C = 6"
In case X is a string with spaces, let's say 'John Doe' and C is 'Full Name': SELECTION A "'Full Name' = 'John Doe'"
Projection of columns C1, C2, C3 from variable A: PROJECTION A "C1 C2 C3"
Natural join (from SQL) of variables A and B: NJOIN A B
Join of variables A and B, with a condition that column from A called 'ColA' is equal to B column called 'ColB': JOIN A B "ColA = ColB"
Rename of a column from name "Col1" to "Col2" in variable A: RENAME A "Col1 Col2"

### Setting a Variable
To set a variable A to be equal to another variable B: A = B
To set a varaible A to be equal to some operation (eg. INTERSECT) of X and Y: A = INTERSECT X Y

### Other commands
Printing the result of a query: PRINT <QUERY>
Printing variable A: PRINT A
Translating relational algebra query to SQL: TRANSLATE <QUERY>
Exiting the app: EXIT

### Combining Queries
Combining and embedding is possible.
And example of more complicated command that can be done:
RENAME PROJECTION UNION INTERSECT A B DIFF A SELECTION A "col1 = 'Car'" "col1" "col1 col2"
RENAME PROJECTION UNION INTERSECT A B DIFF A SELECTION A "col1 = 'Car'" "col1" "col1 col2"
Explanation:
- First, we take the variable A and omit all rows where 'col1' is not equal to 'Car'
- We take the original A variable and do a set difference from the the result of the selection
- Then, we do intersect of variables A (original) and B
- The intersection of A and B will merged using UNION with the A minus the rows where col1 = 'Car'
- Then, we do projection on the current result, leaving us with only column col1
- Last, we rename this column to 'col2'

All this could also be either printed out by adding PRINT before all these commands or saved into a variable by adding before something like "VAR ="
