sum=0
i=0
while i<10000
	if i%2==0
		sum=sum+i
	end 
	i=i+1
end 
real=24995000
print "Program Result:",sum
print "Real Result:",real

if sum==real
	print "Program Ok"
else 
	print "Program Failed"
end 

