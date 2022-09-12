#Priority non-preemptive 

AT=[0, 0, 0, 0, 0, 0]
BT=[0, 0, 0, 0, 0, 0]
pr=[0, 0, 0, 0, 0, 0]
pid=[1, 2, 3, 4, 5, 6]	
for i in range(len(pid)):
	print("pid= ", pid[i])
	print("AT: ", end = '')
	AT[i]=int(input())
	print("BT: ", end = '')
	BT[i]=int(input())
	print("priority: ", end = '')
	pr[i]=int(input())

ct=0
CT=[0, 0, 0, 0, 0, 0]
#WT=[0, 0, 0, 0, 0]
mark=[0, 0, 0, 0, 0, 0]
race=[0, 0, 0, 0, 0, 0]
while (0 in mark):
	arr=[]
	flag=0
	a=[]
	for i in range(len(AT)):			# to mark all the elements which have arrived
		if(ct>=AT[i]):
			race[i]=1
	#print(ct, race)
	for i in range(len(AT)):			# to check if there is any element which is in the race but not marked
		if(mark[i]==0 and race[i]==1):
			flag=1
	#print(flag)
	if(flag==0):
		#print("if")
		for i in range(len(AT)):
			if(race[i]==0):
				ct=AT[i]
				race[i]=1
				break
	#print(ct, race)

	for i in range(len(AT)):			# to find the shortest job among the available tasks 
		if(mark[i]==0 and race[i]==1):
			arr.append(pr[i])
	maximum=max(arr)
	for i in range(len(AT)):			# to update the values of the shortest job
		if(maximum==pr[i]):
			mark[i]=1
			ct=ct+BT[i]
			CT[i]=ct
			break

print("PID 	AT 	BT 	pr 	CT")
for i in range(len(AT)):
	print(pid[i]," 	",AT[i]," 	",BT[i], "	", pr[i], " 	",CT[i])

#print("The average WT is ", sum(WT)/len(WT))
