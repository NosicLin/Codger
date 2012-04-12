(1)简单for语句

[Program]

for <symbol> in <expr>
	<stmts>
end 

[translate]

{
	<expr>
}
OP_ITER

Begin:
OP_ITER_NEXT
OP_JUMPR @End 
{
	<symbol>
}
{
	<stmts>
}
OP_JUMPR @Begin

End:
OP_DESCARD

