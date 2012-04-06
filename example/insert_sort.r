#sort array item by insert sort methed
size=7
array=[45,23,9,134,54,56,26]
i=1
while i<size
	temp=array[i]
	j=i
	while j>0 and temp<array[j-1]
		array[j]=array[j-1]
		j=j-1
	end
	array[j]=temp
	i=i+1

end 

real=[9,23,26,45,54,56,134]
print "Program Result:",array
print "Real Result:",real
i=0
ok=true
while i<size
	if real[i]!=array[i]
		ok=false
	end
	i=i+1
end

if ok
	print "Program Ok"
else
	print "Program Failed"
end 
