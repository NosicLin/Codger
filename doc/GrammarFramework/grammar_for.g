[sentence]
	for

[grammar]
	for <symbol> in <expression> <for_break>
		<stmts>
	end <normal_break>

[Translate Framework]
	{
		<expression_code>
	}
	assign @for_<id>
	@label "for_begin"
	iterator <id>
	jump_false "for_end"
	{
		<stmts_code>
	}
	jump "for_begin"
	@label "for_end"

