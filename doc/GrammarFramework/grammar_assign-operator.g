[sentence]
	assign-operator

[grammar]
	<symbol> <assign-operator> <expression>

	<assign-operator>::=
		"+="
		"-="
		"*="
		"/="
		">>="
		"<<="

[Translate Framework]
	
	symbol <symbol_id>
	pushd
	{
		<expression_code>
	}
	pushd
	expr_<@assign_operator>
	assign <symbol_id>


