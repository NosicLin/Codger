#int part
"int oper int "
8<<2
8>>2

"int oper long"
8>>2l
3<<100l

"int oper float"
4>>2.2
3<<3.3

"int oper string"
3<<"a"
3>>"a"

#float part
"float oper float "
3.3>>2.0
3.3<<2.0

"float oper int"
3.3<<2
3.3>>3

"float oper string"
3.3>>"a"
3.3<<"a"

"float oper long"
3.3<<2l
3.3>>2l

#long parts
"long oper long"
233L<<100l
3333333333333333333333333333333333333333333333l>>32l

"long oper int"
233l<<100 
3333333333333333333333333333333333333333333333l>>32 

"long oper float"
333L<<324.2
333l>>21.3

"long oper string"
333l<<"a"
33L>>"a"

#string parts
"string oper string"
"a"<<"b"
"a">>"b"

"string oper int"
"a"<<2
"b">>2

"string oper float"
"a">>2.3
"a"<<3.3 

"string oper long"
"a">>3L
"a"<<2L




