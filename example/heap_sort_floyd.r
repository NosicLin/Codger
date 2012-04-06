#sort array item by normal heap sort methed 
size=11
array=[45,23,9,134,54,56,26,100,34,87,77]

#buiding heap use floyd method 
i=size/2-1
while i>=0
	f_now=i
	largest=f_now*2+1
	while largest<size
		if largest+1<size and array[largest+1]>array[largest]
			largest=largest+1
		end 
		if array[f_now]<array[largest]
			temp=array[f_now]
			array[f_now]=array[largest]
			array[largest]=temp
			f_now=largest
			largest=2*largest+1
		else
			largest=size
		end 
	end
	i=i-1
end 



#sort by move the head to tail 
k=size-1
while k>0
	#swap(head,tail)
	temp=array[k]
	array[k]=array[0]
	array[0]=temp

	#rebulding the heap
	i=0
	while i<k-1
		j=i+1
		while j!=0 and array[j]>array[j/2]
			temp=array[j]
			array[j]=array[j/2]
			array[j/2]=temp
			j=j/2
		end
		i=i+1
	end
	k=k-1
end


real=[9,23,26,34,45,54,56,77,87,100,134]
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
