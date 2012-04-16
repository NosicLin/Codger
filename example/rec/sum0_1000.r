func sum(x)
	if x==0
		return 0
	else
		return $sum(x-1)+x
	end 
end 

print sum(1000)
