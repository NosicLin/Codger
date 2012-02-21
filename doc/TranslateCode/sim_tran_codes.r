simple_translate_codes 0

[Program]

a=1
b=2
c=a+b
d=1+c

[translate]

--a=1
object 1
assign a

--b=2
object 2
assign 2

--c=a+b
symbol a
pushd
symbol b
pushd 
expr "@+"
assign c 

--d=1+c
object 1
pushd 
symbol c
pushd 
expr "@+"
assign d 

--end 
