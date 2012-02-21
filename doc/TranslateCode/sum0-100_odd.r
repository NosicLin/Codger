计算1-100中奇数的和

[Program]

sum=0 
for i in range(0,100)
	if i/2
		sum+=i
	end
end
print sum 

[translate]
object 0 
assign sum 

frame_func "range"
object 0
push "@arg1"
object 100
push "@arg2"
call 
destoryframe

frame_for <code_length>
iterator
[ref_iter i]
{
	for_value
	assign i 
	symbol i
	pushd 
	object 2
	pushd 
	expr "@/"

	booleaned

	false_jump "end"
	{
		symbol sum
		pushd 
		symbol i
		pushd 
		expr "@+="
	}
	lable "end"
}
end_for 

symbol sum
print 

	



	


	

