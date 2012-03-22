#int part

"int oper int"
1-4
1+4

"int oper long"
1-444444444444444444444444444444444L
1+444444444444444444444444444444444L

"int oper float"
1+3.4
1-4.5

"int oper string"
1+"fsdf"
1-"fasdf"


#float part 
"float oper float"
2.3+3.3
2.3-3.3

"float oper int"
2.3+1
2.3-1

"float oper long"
2.3+1111111111111l
2.3-1111111111111l

"float oper string"
2.3+"fsdf"
3.3-"fsfd"

#long parts
"long oper long"
11111111111111111111111111111111l+11111111111111111111111111111111l
111111111111111111111111111111111l-11111111111111111111111111111111l

"long oper int"
11111111111111111111111111111111l -1 
11111111111111111111111111111111l +1

"long oper float"
11111111111111111111111111111111l+1.32
11111111111111111111111111111111l-2.3

"long oper string"
11111l+"fsf"
11111l-"fsdf"

#string parts
"string oper string"
"abcdefg"+"gfedcba"
"abcdefg"-"gfedcba"

"string oper int"
"afddsf" - 3
"adfsf" +3 

"string oper long"
"sdfsaf" + 333l
"fsfdsf" -343l

"string oper float"
"fsfsdf" - 3.3 
"fsdfds" + 3.3 




