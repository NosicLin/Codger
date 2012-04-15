
func add_defalut(x,y=1,z=2)
	return x+y+z
end 

print add_defalut(1)
print add_defalut(2,3)

func add_many(*xxx)
	sum=0;
	for i in xxx
		sum=sum+i
	end 
	return sum
end 


print add_many(1,3,3,5,6)
print add_many(10,49)
print add_many(2,3,4,5,6,2,4,5,6,7,7,8,8,9,9,7,5,4,4,5,7,7)
