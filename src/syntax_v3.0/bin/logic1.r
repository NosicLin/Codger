#int part
"0 1 2 1 true false"
0 and 1
0 or 1
1 and 2
1 or 2 
not 0 
not 1

#string part
" empty edfa aaa a  true false "
"" and "abcd"
"" or "edfa"
"a" and "aaa"
"a" or "bbbb"
not ""
not "a"

#long part
"0 1 2 1 true false"
0l and 1l
0l or 1l
1l and 2l
1l or 2l
not 0l 
not 1l

#float part 
"0 1 2 1 true false"
0.0 and 1.0
0.0 or 1.0 
1.0 and 2.0
1.0 or 2.0 
not 0.0
not 1.0 

#boolean part 
" false true  false true false true"
false and true
false or true 
true and false 
true or  false 
not true 
not false 


#merge part 
"0 3 0"
1 and 0 or 0 and 2
0 or 1 and 3 or 2
1 and (0 or 0) and 2

