[sentence]
	unary-expression

[grammar1]
	<expression> <unary_right_operator> <normal_break>

	<unary_right_operator>::=
		"++"
		"--"
[grammar2]
	<unary_left_operator> <expression> <normal_break>

	<unary_left_operator>::=
		"!"

[Translate Framework]
	{
		<expression_code>
	}
	pushd
	expr_<@unary_operator>


