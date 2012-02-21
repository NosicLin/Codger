[sentence]
	while

[grammar]
	while <expression> <while_break>
		<stmts>
	end <normal_break>

[Translate Framework]
	@label "while_begin"
	{
		<expression_code>
	}
	booleaned
	jump_false "while_end"
	{
		<stmts_code>
	}
	jump "while_begin"
	@label "while_end"

