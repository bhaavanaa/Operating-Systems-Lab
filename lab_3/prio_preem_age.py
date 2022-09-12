#Priority non-preemptive 

AT=[0, 0, 0, 0, 0, 0]
BT=[0, 0, 0, 0, 0, 0]
pr=[999, 999, 999, 999, 999, 999]
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
UBT=[]
prio=[]
for i in range(len(BT)):
	UBT.append(BT[i])
for i in range(len(pr)):
	prio.append(pr[i])
flag=0
while(sum(UBT)>0):
	for i in range(len(AT)):			# to mark all the elements which have arrived
		if(ct>=AT[i]):
			mark[i]=1
	for i in range(len(AT)):			# to check if there is any element which is in the race but not marked
		if(mark[i]==1 and UBT[i]>0):
			flag=1
	if(flag==0):
		for i in range(len(AT)):
			if(mark[i]==0):
				ct=AT[i]
				mark[i]=1
				break
	arr=[]
	for i in range(len(AT)):
		if(mark[i]==1 and UBT[i]>0):
			arr.append(pr[i])
	minimum=min(arr)
	for i in range(len(AT)):
		if(minimum==pr[i] and UBT[i]!=0):
			UBT[i]=UBT[i]-1
			pr[i]=pr[i]+1
			ct=ct+1
			if(UBT[i]==0):
				CT[i]=ct
			break


print("PID 	AT 	BT 	pr 	CT")
for i in range(len(AT)):
	print(pid[i]," 	",AT[i]," 	",BT[i], "	", prio[i], " 	",CT[i])

#print("The average WT is ", sum(WT)/len(WT))
