[sentence]
	binary-expression

[grammar]
	<expr_left> <binary_operator> <expr_right> <normal_break>

	<binary_operator>::=
		"+"
		"-"
		"*"
		"/"
		">"
		"<"
		"=="
		"!="
		"<<"
		">>"
		"<="
		">="

[Translate Framework]
	{
		<expr_left_code>
	}
	pushd
	{
		<expr_right_code>

	}
	pushd
	expr_<@binary_operator>

	
