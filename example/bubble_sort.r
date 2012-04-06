#sort array item by bubble sort methed
size=7
array=[45,23,9,134,54,56,26]
i=0
while i<size-1
	j=size-1
	while j>i
		if array[j]<array[j-1]
			temp=array[j]
			array[j]=array[j-1]
			array[j-1]=temp
		end
		j=j-1
	end
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
