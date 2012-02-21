(1)计算1-100的和

[Program]

sum=0
for i in range(0,100)
	sum+=i
end 
print sum 

[translate]
--sum=0
object 0
assign sum  

--range(0,100)
frame_func "range"
object 0 
pushg        --arg1
object 100
pushg 		--arg2
call 
destory_func

--for 
frame_for <code_length>
iterator
[ref_iter i]
{
	symbol sum 
	pushd 
	symbol i 
	pushd
	expr "@+="

	next_for 
}
end_for 

--print sum
symbol sum
print 




