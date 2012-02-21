[sentence]
	function-call

[grammar]
	<symbol> "(" <arg_expr1> "," <arg_expr2> "," ... "," <arg_exprn> ")"

[Translate Framework]

	symbol <symbol_id>
	frame_func
	{
		<arg_expr1_code>
	}
	pushg
	{
		<arg_expr2_code>
	}
	pushg
		.
		.
		.
	{
		arg_exprn_code>
	}
	pushg
	call 

