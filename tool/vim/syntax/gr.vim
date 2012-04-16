"Vim syntax file
"Language: GR 
"Maintainer: NosicLin  <nosiclin@foxmail.com>
"Last Change: 2012-4-17


" Codger Is An Object Oriented Language

if !exists("main_syntax")
	if version < 600
		syntax clear
	elseif exists("b:current_syntax")
		finish
	endif 
	let main_syntax = "gr"
endif 


syn keyword grCommentTodo TODO FIXME XXX  contained
syn match grComment "\#.*" contains=@Spell,grCommentTodo
syn match   grCommentSkip      "^[ \t]*\*\($\|[ \t]\+\)"
syn region  grComment2	       start="/\*"  end="\*/" contains=@Spell,grCommentTodo
syn match   grLineComment      "\/\/.*" contains=@Spell,grCommentTodo

syn match   grNumber    "-\=\<\([1-9]\d*\|0[xX][0-9a-fA-F]\+\|0[bB][0-1]\+\|0[oO]\?[0-8]\+\|0\)[lL]\=\>"

syn match grGlobal 		"\</$[a-fA-F]\+\>"

syn match   grSpecial	       "\\\d\d\d\|\\."
syn region  grStringD	       start=+"+  skip=+\\\\\|\\"\|\\$+  end=+"\|$+  contains=grSpecial,@htmlPreproc

syn keyword grConditional 		if elif else  then
syn keyword grRepeat 			while for do in  
syn keyword grBranch 			break continue 
syn keyword grType 				Array Boolean Func Object 
syn keyword grBoolean			true false 
syn keyword grNull				null 
syn keyword grException 		try catch finally throw 
syn keyword grReserved 			class const func end this global  return 
syn keyword grOperator			new delete instanceof typeof
syn match	grBraces	   "[{}\[\]]"
syn match	grParens	   "[(,)]"

syn sync fromstart 
syn sync maxlines=100

if main_syntax=="gr"
	syn sync ccomment grComment
endif 


if version >= 508 || !exists("did_gr_syn_inits")
	if version < 508
		let did_gr_syn_inits = 1
		command -nargs=+ HiLink hi link <args>
	else
		command -nargs=+ HiLink hi def link <args>
	endif

	HiLink grComment 			Comment
	HiLink grCommentTodo 		Todo
  	HiLink grComment2 		Comment
  	HiLink grLineComment		Comment
	HiLink grNumber			Number
	HiLink grConditional 		Conditional
	HiLink grRepeat 			Repeat
	HiLink grBranch			Conditional 
	HiLink grType				Type 
	HiLink grBoolean 			Boolean 
	HiLink grNull 			Keyword 
	HiLink grException		Exception
	HiLink grReserved			Keyword 
	HiLink grGlobal        	Keyword	
	HiLink grStringD			String
  	HiLink grBraces		Function
	HiLink grParens    Function	
  	HiLink grOperator		Operator
	delcommand HiLink
endif 

let b:current_syntax="gr"
if main_syntax=="gr"
	unlet main_syntax
endif






















