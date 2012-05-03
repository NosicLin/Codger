#int part 
"int oper int"
"true false false"
2<3
2<1
2<2

"true false true"
2<=3
2<=1
2<=2

"false true true"
2>=3
2>=1
2>=2

"false true flase"
2>3
2>1
2>2

"int oper float"
"true false false"
1<2.3
1<0.1
1<1.0

"true false true"
1<=2.3
1<=0.1
1<=1.0


"false true true"
1>=2.3
1>=0.1
1>=1.0

"false true false"
1>2.3
1>0.1
1>1.0

"int oper long"
"true false false"
1000<1000000000000000000000l
1000<100l
1000<1000l

"true false true"
1000<=1000000000000000000000l
1000<=100l
1000<=1000l

"flase true true"
1000>=1000000000000000000000l
1000>=100l
1000>=1000l


"flase true false"
1000>1000000000000000000000l
1000>100l
1000>1000l

"int oper sting"
1000<"a"
100>"a"
1000<="a"
1000>="a"

#float part 
"float oper float"
"true false false"
2.1<3.1
2.1<1.1
2.1<2.1 

"true false true"
2.1<=3.1
2.1<=1.1
2.1<=2.1 

"false true true"
2.1>=3.1
2.1>=1.1
2.1>=2.1 

"false true false "
2.1>3.1
2.1>1.1
2.1>2.1 

"float oper int"
"true false false"
2.1<3
2.1<1
2.0<2 

"true false true"
2.1<=3
2.1<=1
2.0<=2 

"false true true"
2.1>=3
2.1>=1
2.0>=2 

"false true false "
2.1>3
2.1>1
2.0>2 

"float oper long "

"true false false"
2.1<3l
2.1<1l
2.0<2l 

"true false true"
2.1<=3l
2.1<=1l
2.0<=2l

"false true true"
2.1>=3l
2.1>=1l
2.0>=2l

"false true false "
2.1>3l
2.1>1l
2.0>2l 

"float oper sting"
2.2>"a"
2.2<"a"
2.2>="a"
2.2<="a"


#long part 
"long oper long"

"true false false"
2l<3l
2l<1l
2l<2l

"true false true"
2l<=3l
2l<=1l
2l<=2l

"false true true"
2l>=3l
2l>=1l
2l>=2l

"false true flase"
2l>3l
2l>1l
2l>2l

"long oper float"
"true false false"
1l<2.3
1l<0.1
1l<1.0

"true false true"
1l<=2.3
1l<=0.1
1l<=1.0


"false true true"
1l>=2.3
1l>=0.1
1l>=1.0

"false true false"
1l>2.3
1l>0.1
1l>1.0

"long oper int "
"true false false"
1000l<100000000
1000l<100
1000l<1000

"true false true"
1000l<=100000
1000l<=100l
1000l<=1000l

"flase true true"
1000l>=1000000
1000l>=100l
1000l>=1000l


"flase true false"
1000l>10000000
1000l>100l
1000l>1000l

"long oper sting"
1000l<"a"
100l>"a"
1000l<="a"
1000l>="a"

#sting part
"string oper sting"
"true false false"
"b"<"c"
"b"<"a"
"b"<"b"

"true false true"
"b"<="c"
"b"<="a"
"b"<="b"

"false true true"
"b">="c"
"b">="a"
"b">="b"

"false true false"
"b">"c"
"b">"a"
"b">"b"

"string oper int"
"a">1
"a"<1
"a"<=1
"a">=1

"string oper long"
"a">1l
"a"<1l
"a"<=1l
"a">=1l

"string oper float"
"a">1.0
"a"<1.0
"a"<=1.0
"a">=1.0

