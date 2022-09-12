import math
import threading
import matplotlib.pyplot as plt
import numpy as np 


global n
global a
global maxi


def Mean():           
    sum=0;
    for i in range(int(n)):
        sum=sum+int(a[i])
    mean=round(sum/int(n),3)
    print("mean: ", mean)


def Median():        
    if int(n)%2==0:
    	median1=round((int(a[int(int(n)/2)-1])+int(a[int(int(n)/2)]))/2, 3)
    else:
    	median1=int(a[int(int(n)/2)])
    print("median: ", median1)


def Mode():
	count=[]
	for i in range(0,int(n)):
		count.append(0)
	x=int(a[0])
	xi=0
	global maxi
	maxi=0
	for i in range(int(n)):
		if(int(a[i])==x):
			count[xi]=count[xi]+1
		else:
			x=int(a[i])
			xi=i
			count[xi]=count[xi]+1
	for i in range(int(n)):
		if(count[i]>maxi):
			maxi=count[i]
	for i in range(int(n)):
		if(count[i]==maxi):
			mode=int(a[i])
			break
	print("mode: ", mode)
  

def Range():             
    range1=int(a[int(n)-1])-int(a[0])
    print("range: ", range1)


def Median_low():      
    if(int(n)%2==0):
        median_low=int(a[int(int(n)/2)-1])
    else:
        median_low=int(a[int(int(n)/2)])
    print("median_low: ", median_low)
  

def Median_high():        
    median_high=int(a[int(int(n)/2)])
    print("median_high: ", median_high)


def Quartiles():            
    n1=int(n)/2
    if(n1%2==0):
        q1=round((a[int(int(n)/4)-1]+a[int(int(n)/4)])/2, 3)
        q3=round((a[int(3*int(n)/4)-1]+a[int(3*int(n)/4)])/2, 3)
    else:
        q1=a[int(int(n)/4)-1]
        q3=a[int(3*int(n)/4)-1]
    ret=[q1, q3]
    print("quartiles: ", ret)


def Variance():          
    sum=0
    for i in range(int(n)):
        sum=sum+int(a[i])
    mean=round(sum/int(n))
    sum1=0
    for i in range(int(n)):
    	sum1=sum1+(mean-int(a[i])*(mean-int(a[i])))
    variance=round(sum1/int(n), 3)
    print("variance: ", variance)


def Stdev():           
    sum=0
    for i in range(int(n)):
    	sum=sum+int(a[i])
    mean=round(sum/int(n), 3)
    sum1=0
    for i in range(int(n)):
        sum1=sum1+(mean-int(a[i]))*(mean-int(a[i]))
    variance=round(sum1/int(n))
    stdev=round(math.sqrt(variance), 3)
    print("stdev: ", stdev)


def Geometric_mean():           
    prod=1
    for i in range(int(n)):
        prod=prod*int(a[i])
    gm=round(pow(prod, 1/int(n)), 3)
    print("gm: ", gm)


def Harmonic_mean():           
    sum=0
    for i in range(int(n)):
        sum=sum+round((1/int(a[i])), 3)
    hm=round(int(n)/sum, 3);
    print("hm: ", hm)


a=[]
b=[]
c=[]
t=[]
print("enter the number of elements in the array: ")
n=input()
print("enter the elements:")
for i in range(int(n)):
	k=int(input())
	a.append(k)
	b.append(k)
	t.append(k)
a.sort()
for i in range(len(b)):
	j=b[i]		
	j=j/(10*len(str(i)))
	c.append(int(j))

data_to_plot = [a]

t1=threading.Thread(target=Mean, args=( ))
t2=threading.Thread(target=Median, args=())
t3=threading.Thread(target=Mode, args=())
t4=threading.Thread(target=Range, args=())
t5=threading.Thread(target=Median_low, args=())
t6=threading.Thread(target=Median_high, args=())
t7=threading.Thread(target=Quartiles, args=())
t8=threading.Thread(target=Variance, args=())
t9=threading.Thread(target=Stdev, args=())
t10=threading.Thread(target=Geometric_mean, args=())
t11=threading.Thread(target=Harmonic_mean, args=())

t1.start()
t2.start()
t3.start()
t4.start()
t5.start()
t6.start()
t7.start()
t8.start()
t9.start()
t10.start()
t11.start()

t1.join()
t2.join()
t3.join()
t4.join()
t5.join()
t6.join()
t7.join()
t8.join()
t9.join()
t10.join()
t11.join()


#boxplot
plt.figure(figsize = (7, 5)) 
plt.title('Box plot')
plt.boxplot(a) 
plt.show() 


#stemleaf plot
leaf=[]							#leaf: the righmost digit
stem=[]							#stem: the rest of the data
for i in range(len(a)):
	leaf.append(a[i]%10)
	stem.append(int(a[i]/10))
plt.ylabel('stem')   
plt.xlabel('leaf')   
plt.title('Stem leaf plot')
plt.xlim(0, 10)  
plt.stem(leaf, stem)
plt.show()  


#histogram
#d = np.random.laplace(loc=15, scale=3, size=500)
#[:5]
n, bins, patches = plt.hist(x=a, bins='auto', color='#0504aa', alpha=0.7, rwidth=0.5)
plt.grid(axis='y', alpha=0.75)
plt.xlabel('Value')
plt.ylabel('Frequency')
plt.title('Histogram')
plt.text(23, 45, r'$\mu=15, b=3$')
#global maxi
maxfreq = maxi
plt.ylim(top=np.ceil(maxfreq / 1) if maxfreq % 1 else maxfreq)
plt.show()


# Mean()
# Median()
# Mode()
# Range()
# Median_low()
# Median_high()
# Quartiles()
# Variance()
# Stdev()
# Geometric_mean()
# Harmonic_mean()
