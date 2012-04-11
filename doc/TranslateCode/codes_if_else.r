(1)if-elif-else 

[program]
if expr1
	block1
elif expr2
	block2
elif 
	.
	.
	.
else 
	block3
end 


[translate]
<expr1>
bool
jump_false @L1
<block1>
jump   @end 
L1:
<expr2>
bool 
jump_false @L2:
<block2>
jump @end
L2:
...
Ln:
<block3>
end:

