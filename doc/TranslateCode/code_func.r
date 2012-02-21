(1)加法减法函数

[Program]
func add(left,right)
	return left+right
end

func minus(left,right)
	return left-right
end

i=9
j=8
print add(i,j)
z=minus(i,j)
print z

[translate]

@add 
	symbol left
	pushd 
	symbol right 
	pushd
	expr "@+"
	return 

@minus 
	symbol left 
	pushd
	symbol right
	pushd 
	expr "@-"
	return 

@entry
	object 9
	assign i
	object 8 
	assign j
	symbol add
	frame_func
	symbol i 
	pushg
	symbol j
	pushg
	call 
	destory_func
	print 

	symbol minus
	frame_func 
	symbol i
	pushd
	symbol j
	pushd 
	call 
	destory_func
	assign z

	symbol z
	print 

(2)判断奇偶数
[Program]
func even_or_odd(value)
	if value/2
		return "odd"
	else
		return "even"
	end
end

print even_or_odd(5)

[translate]

@even_or_odd
	symbol value
	pushd
	object 2
	pushd 
	expr "@/"
	booleaned
	jump_false "else"
	{
		object "odd"
		return 
		jump "end"
	lable "else"
		object "even"
		return 
	}
	lable "end"

	return none

@entry 
	symbol even_or_odd
	frame_func
	object 5
	pushd 
	call
	destory_func
	print 


