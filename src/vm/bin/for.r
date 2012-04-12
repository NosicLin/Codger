
for i in [1,2,3,4,5,6,7]
	if i>=5 
		break;
	end 
	print i
end 

print "delimeter"
for i in [1,2,3,4,5,6,7]
	if i<5
		continue
	end 
	print i
end 


for i in ["a","b","c","d","e","f"]
	if i>"d"
		break;
	end 
	for j in [1,2,3,4,5,6]
		if j>4
			break;
		end 
		print i,j
	end 
end 
