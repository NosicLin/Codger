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

