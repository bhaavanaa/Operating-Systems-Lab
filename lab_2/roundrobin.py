# Round Robin

# import required libraries
import os.path
import time, os, stat
from collections import deque 


def file_age_in_seconds(pathname):
	return(os.path.getctime(pathname))


# Open the required files
file1 = open("/home/bhaavanaa/OS_lab/lab_1/text1.txt","r") 
file2 = open("/home/bhaavanaa/OS_lab/lab_1/text2.txt","r")
file3 = open("/home/bhaavanaa/OS_lab/lab_1/text3.txt","r")
file4 = open("/home/bhaavanaa/OS_lab/lab_1/text4.txt","r")
file5 = open("/home/bhaavanaa/OS_lab/lab_1/text5.txt","r")


# Obtain their arrival time(AT) i.e. time of creation
time1=file_age_in_seconds("/home/bhaavanaa/OS_lab/lab_1/text1.txt")
time2=file_age_in_seconds("/home/bhaavanaa/OS_lab/lab_1/text2.txt")
time3=file_age_in_seconds("/home/bhaavanaa/OS_lab/lab_1/text3.txt")
time4=file_age_in_seconds("/home/bhaavanaa/OS_lab/lab_1/text4.txt")
time5=file_age_in_seconds("/home/bhaavanaa/OS_lab/lab_1/text5.txt")
#print(time1, time2, time3, time4, time5)


# Obtain the burst time(BT) i.e. wordcount
num_words1=0
for line in file1:
	words = line.split()
	num_words1 += len(words)

num_words2=0
for line in file2:
	words = line.split()
	num_words2 += len(words)

num_words3=0
for line in file3:
	words = line.split()
	num_words3 += len(words)

num_words4=0
for line in file4:
	words = line.split()
	num_words4 += len(words)

num_words5=0
for line in file5:
	words = line.split()
	num_words5 += len(words)


# To create a list of the above data
AT1 = []
AT1.append(time1)
AT1.append(time2)
AT1.append(time3)
AT1.append(time4)
AT1.append(time5)


name = ['text1','text2','text3','text4','text5']

BT1 = []
BT1.append(num_words1)
BT1.append(num_words2)
BT1.append(num_words3)
BT1.append(num_words4)
BT1.append(num_words5)


# Sort the above lists in ascending order 
AT2, BT, NAME = map(list, zip(*sorted(zip(AT1, BT1,name), reverse=False)))
sub = AT2[0]
AT = AT2
for i in range(len(AT2)):
	AT[i]=round(AT2[i]-sub)


# Calculate CT, TAT, WT
TQ=10	# defining the time quanta to be 2
ct=0
pid=[1, 2, 3, 4, 5]
CT=[0, 0, 0, 0, 0]
TAT=[0, 0, 0, 0, 0]
WT=[0, 0, 0, 0, 0]
mark=[0, 0, 0, 0, 0]
UBT=[]
for i in range(len(BT)):
	UBT.append(BT[i])
queue = deque([])
q=999

while(sum(UBT)>0):
	for i in range(len(AT)):			# to mark all the elements which have arrived
		if(ct>=AT[i] and mark[i]!=1):
			mark[i]=1
			queue.append(pid[i])
	for i in range(len(AT)):			# to check if there is any element which is in the race but not marked
		if(mark[i]==1 and UBT[i]>0):
			flag=1
	if(flag==0):
		for i in range(len(AT)):
			if(mark[i]==0):
				ct=AT[i]
				mark[i]=1
				queue.append(pid[i])
				break
	if(q!=999):
		queue.append(q)

	q=queue.popleft()
	if(UBT[q-1]<TQ):
		ct=ct+UBT[q-1]
		UBT[q-1]=0
	else:
		ct=ct+TQ
		UBT[q-1]=UBT[q-1]-TQ
	if(UBT[q-1]==0):
		CT[q-1]=ct
		TAT[q-1]=CT[q-1]-AT[q-1]
		WT[q-1]=TAT[q-1]-BT[q-1]
		q=999



print("PID 	Name 		AT 	BT 	CT 	TAT 	WT")
for i in range(len(AT)):
	print(pid[i]," 	",NAME[i]," 	",AT[i]," 	",BT[i]," 	",CT[i]," 	",TAT[i]," 	",WT[i])


print("The average WT is ", sum(WT)/len(WT))


# Close the files
file1.close()
file2.close()
file3.close()
file4.close()
file5.close()
