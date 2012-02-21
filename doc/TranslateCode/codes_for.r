(1)简单for语句

[Program]

for i in range(0,100)
	for j in range(i,100)
		sum+=j
	end
end

print sum 

[translate]

--range(0,100)
frame_func "range"
object 0
pushg 
object 100
pushg 
call 
destory_func

frame_for <code_length>
iterator 
[ref_iter i]
{

	frame_func "range"
	symbol i 
	pushg
	object 100
	pushg
	call 
	destory_func

	frame_for <code_length>
	iterator
	[ref_iter j]
	{
		symbol sum
		pushd 
		symbol j
		pushd 
		expr "@+="
	}
	end_for
}
end_for 

		

(2) 含有continue,break的for语句

[Program]

a=range(3,100)
sum=0
for i in a
	if sum==100
		break
	end
	if sum/3!=0
		continue
	end
	sum+=i
end

[translate]

frame_func "range"
object 3
pushg
object 100
pushg
call
destory_func
assign a 

object 0
assign sum 

frame_for <code_length> 
iterator a 
[ref_iter i]
{
	symbol sum
	pushd 
	object 100
	pushd 
	expr "@=="
	booleaned 
	jump_false "end"
	{
		break
	}
	lable "end"
	symbol sum
	pushd 
	object 3
	pushd 
	expr "@/"
	pushd 
	object 0
	pushd 
	expr "@=="
	jump_false "end"
	{
		continue
	}
	lable "end"
	symbol sum
	pushd 
	symbol i 
	pushd 
	expr "@+="
	next_for
}
end_for 


	








