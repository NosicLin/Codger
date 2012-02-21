(1)多重 if-else 

[Program]
a=random()
b=random()
if a+b/2==5
	a++
	if a/2
		a--
	else
		a++
	end
elif a+b/3==6
	a--
else 
	b=a/2
end
print a
print b


[translate]
frame_func "random"
call 
destory_func
assign a

frame_func "random"
call 
destory_func
assign b

symbol a
pushd
symbol b
pushd 
object 2
pushd 
expr "@/"
pushd 
expr "@+"
pushd 
object 5
pushd 
expr "=="

booleaned 
jump_false "elif"
{
	symbol a
	expr "@++"
	symbol a
	pushd 
	object 2
	pushd 
	expr "@/"
	booleaned 
	jump_false "else"
	{
		symbol a 
		pushd 
		expr "@--"
		jump "end"
	label "else"
		symbol a
		pushd 
		expr "@++"
	}
	label "end"
	
	jump "end"
lable "elif"
	symbol a
	pushd 
	symbol b 
	pushd 
	object 3
	pushd 
	expr "@/"
	pushd 
	expr "@+"
	pushd 
	object 6
	pushd
	expr "@=="
	booleaned 
	jump_false "else"
	symbol a
	pushd
	expr "@++"
	jump "end"
lable "else"
	symbol a
	pushd 
	object 2
	pushd
	expr "@/"
	assign b 
}
lable "end"



