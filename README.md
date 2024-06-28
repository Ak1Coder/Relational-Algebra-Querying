# Querying in Relational Algebra
In this app any commands are case insensitive, on the other hand names of variables are case sensitive.

## Explanation of all the Commands
### IMPORT and EXPORT
Any .csv or .tsv files can be imported and exported in the following way. To import a file you need the path to the file to import it and also the name of the variable which you can use later in the app to reference this file.</br>
IMPORT "myDir/file.csv" "name"

Export works in a similar way.</br>
EXPORT name "myDir/fileNew.csv"

An important thing to note is, that the app continously reads the file from the path until it's edited, therefore if at any point you change the data in the original .csv file, the data in the variable also changes.

### Set Operations
Intersection of two variables A and B: INTERSECT A B</br>
Union of two variables A and B: UNION A B</br>
Set Difference of two variables A and B: DIFF A B</br>
Cartesian Cross of two variables A and B: CROSS A B</br>

### Other Operations
Selection of only rows containing value X in a column C of variable A: SELECTION A "C = X"</br>
In case X is a number, let's say 6: SELECTION A "C = 6"</br>
In case X is a string with spaces, let's say 'John Doe' and C is 'Full Name': SELECTION A "'Full Name' = 'John Doe'"</br>
Projection of columns C1, C2, C3 from variable A: PROJECTION A "C1 C2 C3"</br>
Natural join (from SQL) of variables A and B: NJOIN A B</br>
Join of variables A and B, with a condition that column from A called 'ColA' is equal to B column called 'ColB': JOIN A B "ColA = ColB"</br>
Rename of a column from name "Col1" to "Col2" in variable A: RENAME A "Col1 Col2"</br>

### Setting a Variable
To set a variable A to be equal to another variable B: A = B</br>
To set a varaible A to be equal to some operation (eg. INTERSECT) of X and Y: A = INTERSECT X Y</br>

### Other commands
Printing the result of a query: PRINT <QUERY></br>
Printing variable A: PRINT A</br>
Translating relational algebra query to SQL: TRANSLATE <QUERY></br>
Exiting the app: EXIT</br>

### Combining Queries
Combining and embedding is possible.</br>
And example of more complicated command that can be done:</br>
RENAME PROJECTION UNION INTERSECT A B DIFF A SELECTION A "col1 = 'Car'" "col1" "col1 col2"</br>
RENAME PROJECTION UNION INTERSECT A B DIFF A SELECTION A "col1 = 'Car'" "col1" "col1 col2"</br>

Explanation:
- First, we take the variable A and omit all rows where 'col1' is not equal to 'Car'
- We take the original A variable and do a set difference from the the result of the selection
- Then, we do intersect of variables A (original) and B
- The intersection of A and B will merged using UNION with the A minus the rows where col1 = 'Car'
- Then, we do projection on the current result, leaving us with only column col1
- Last, we rename this column to 'col2'
</br>
All this could also be either printed out by adding PRINT before all these commands or saved into a variable by adding before something like "VAR ="
