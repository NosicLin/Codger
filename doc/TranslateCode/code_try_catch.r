(1)捕获除0异常
[Program]
for i in range(-5,5)
	try
		z=8/i
		print z
	catch 
		print "div zero happened"
		break
	finally
		print "no exception happend"
	end
end

[translate]

symbol range
frame_func 
object -5
pushg
object 5
pushg
call 
destory_func
frame_for <code_length>
iterator 
[ref_iter i]
{
	lable "begin_try_1"
	frame_try <try_id>
	object 8
	pushd
	object i
	pushd
	expr "@/"
	assign z
	symbol z
	print 
	lable "end_try_1"
	finally <try_id>
}
@try_id=1 from "begin_try_1" to "end_try_1"
	@catch
		object "div zero happened"
		print 
		break
	@finally
		object "no exception happened"
		print

	
(2)异常与for语句联合使用
[注意] 在i=8的时候 break 被执行了两次
[Program]
for i in range(0,10)
	try
		print i
		if i==8
			break
		end
	catch 
		print "exception happened"
	finally
		print "no exception happened"
		for j in range(0,10)
			break
		end
		if i==8
			break
		end 
	end
end

[translate]

symbol range
frame_func
object 0
pushg 
object 10
pushg 
call 
destory_func
frame_func <code_length>
iterator
[ref_iter i]
{
	try <try_id>
	{
		symbol i
		print
		symbol i
		pushd 
		object 8
		pushd 
		expr "@=="
		booleaned 
		jump_false "if1_end"
		{
			break 
		}
		@lable "if1_end"
		jump "finally1"
	@lable "catch1"
		object "exception happened"
		print 
		jump "try1_end"
	@lable "finally1"
		object "no exception happened"
		print 
		symbol range 
		frame_func
		object 0
		pushg 
		object 10
		pushg 
		call
		destory_func 
		frame_for <code_length>
		iterator
		[ref_iter j]
		{
			break 
		}
		symbol i
		pushd 
		object 8
		pushd 
		expr "@=="
		booleaned
		jump_false "if2_end"
		{
			break
		}
		@lable "if2_end"
	}
	@lable "try1_end"
}
		
		
(3)更多得try语句

[Program]
for i in [0,3,4]
	try 
		try
			break
		catch 
			print "exception happend"
		finally
			print "no exception happend"
			break
		end
	catch 
		print "exception happend"
	finally 
		print "no exception happend"
		break
	end 
end

[translate]
object [0,3,4]
frame_for <code_length>
iterator 
[ref_iter i]
{
	try <try_id=0>
	{
		try <try_id=1>
		{
			break
			jump "finally1"
		@lable "catch1"
			object "exception happened"
			print 
			jump "try1_end"
		@lable "finally1"
			object "no exception happened"
			print 
			break
		}
		@lable "try1_end"
		try_end
		jump "finally0"
	@lable "catch0"
		object "exception happened"
		print 
		jump "try0_end"
	@lable "finally0"
		object "no exception happened"
		print 
		break
	}
	@lable "try0_end"
	try_end
}


		








		
