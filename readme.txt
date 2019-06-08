Operation-1
When the implementation file is run, it first searches for the query string in each document and returns the first occurance index. If the query string is not present, it searches for the first occurance of the longest substring of the query string in each document and returns the index of first occurance along with the longest substring.


Operation-2

The program lists the first 10 documents in descending order of relevance to the query string.

The relevance is determined as follows:
if the query string is present in the title of the document, then it is more relevant.
if the query string is present more number of times in the document, it is more relevant
if the query string is partially present, then the document with the longer substring of the query string is more relevant.
Finally, the more number of times the substring occurs in the document, the more relevant it is.

Implementation-
I have used an array of suffix arrays-1 for each document along with a relevance array to store the relevance.
