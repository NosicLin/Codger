[sentence]
	if-else

[grammar]
	if <expression> <if_break>
		<stmts>
	end <normal_break>
[Translate Framework]
	{
		<expression_code>
	}
	booleaned
	jump_false "if_end"
	{
		<stmts_code>
	}
	@label "if_end"


[grammar]
	if <expression> <if_break>
		<stmts1>
	else <normal_break>
		<stmts2>
	end
	
[Translate Framework]
	{
		<expression_code>
	}
	booleaned
	jump_false "else"
	{
		<stmts1_code>
	}
	jump "if_end"
	@label "else"
	{
		<stmts2_code>
	}
	@label "if_end"

[grammar]
	if <expression1> <if_break>
		<stmts1>
	elif <expression2> <if_break>
		<stmts2>
	elif <expression3> <if_break>
		<stmts3>
		.
		.
		.
	elif <expression4> <if_break>
		<stmtsn>
	end

[Translate Framework]
	{
		<expression1_code>
	}
	booleaned
	jump_false "elif_2"
	{
		<stmts1_code>
	}
	jump "if_end"
	@label "elif_2"
	{
		<expression2_code>
	}
	booleaned
	jump_false "elif_3"
	{
		<stmts2_code>
	}
	jump "if_end"
	@label "elif_3"
	{
		<expression3_code>
	}
	booleaned
	jump_false "elif_4"
	{
		<stmts3_code>
	}
	jump "if_end"
		.
		.
		.
	@lable "elif_n"
	{
		<expressionn_code>
	}
	booleaned
	jump_false "if_end"
	{
		<stmtsn_code>
	}
	@label "if_end"

