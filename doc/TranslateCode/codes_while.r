(1)计算在1+2+3...+n<4000的最大整数n
[Program]

sum=0
i=1
while sum<4000
	sum+=i
	i++
end

[translate]

object 0
assign sum
object 1
assign i

frame_while <code_length>
symbol sum
pushd 
object 4000
pushd 
expr "@<"
boolean 
jump_false "end"
{
	symbol sum
	pushd
	symbol i
	pushd
	expr "@+="
	symbol i
	pushd
	expr "@++"
}
label "end"
end_while


(2)计算在1+2+3...+n<4000的最大整数n
[Program]

sum=0
i=1
do 
	sum+=i
	i++
until sum>4000

[translate]

object 0
assign sum
object 1
assign i
frame_until <code_length>
label "until"
{
	symbol sum
	pushd 
	symbol i
	pushd
	expr "@+="
	symbol i
	pushd
	expr "@++"
}
symbol sum
pushd
symbol 4000
pushd
expr "@>"
jump_false "until"




	

