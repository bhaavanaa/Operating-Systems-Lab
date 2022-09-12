#-----------------------------------------------------------------------------------------------------------------------------
#STATS PACKAGE
#-----------------------------------------------------------------------------------------------------------------------------
import socket 
import select 
import sys 
import datetime
import time
import subprocess
from PyQt5.QtCore import QTimer
from PyQt5.QtWidgets import QApplication, QPushButton
from PyQt5 import QtCore, QtGui, QtWidgets
from PyQt5.QtWidgets import QMainWindow, QApplication, QWidget, QPushButton, QAction, QLineEdit, QMessageBox
from PyQt5.QtGui import QIcon,QPixmap
from PyQt5.QtCore import pyqtSlot
from subprocess import Popen, PIPE
import math
import threading
#import sys
import page1_rc
import matplotlib.pyplot as plt
import numpy as np 
from PyQt5 import QtCore, QtGui, QtWidgets
global n
global a
global click,click2,click3
global message1,message2
message1=str('')
message2=str('')
click=0
click2=0
click3=0
global partA#mean
global partB#median
global partC#mode
global partD#Quartile
global partE#median_high
global partF#median_low
global partG#Variance
global partH#standard
global partI#range
global partJ#gm
global partK#hm
global array1
global array2
partA=str('')
partB=str('')
partC=str('')
partD=str('')
partE=str('')
partF=str('')
partG=str('')
partH=str('')
partI=str('')
partJ=str('')
partK=str('')
array1=str('')
array2=str('')

#self.label.setText(_translate("server2","<html><head></head><body align \"center\" ><p><h1><span style=\" color:#ffffff; font-size=45pt;\"><center><b>"+str(partQ)+"<<br></center><center>"+str(partT)+"</center></span></b><br><br></h1></p><br><p><h2><font face=\"Courier New\" size=\"5\"><table align=\"center\" bgcolor=\"white\" width=\"30%\" height=\"5%\"  ><tr><td align=\"center\">"+str(partA)+"<td align=\"center\">"+str(partB)+"</tr><br><br><tr><td align=\"center\">"+str(partC)+"<td align=\"center\">"+str(partD)+"</tr></table></font></h2></td></p></body></html>"))
###-----------------------------------------------------------------------------------------------------------------------------
###GUI PAGE1
###-----------------------------------------------------------------------------------------------------------------------------
class Ui_PAGE1(object):
	def on_click(self):
		global click
		click=1
		print('PyQt5 button click ',click)
		QtCore.QCoreApplication.instance().quit()
	def on_click2(self):
		global click2
		click2=1
		print('PyQt5 button click2 ',click2)
		global message1
		message1 = self.answer1.text()
		#QtCore.QCoreApplication.instance().quit()
	def on_click3(self):
		global click3
		click3=1
		print('PyQt5 button click3 ',click3)
		global message2
		message2 = self.answer2.text()
		#QtCore.QCoreApplication.instance().quit()
	def setupUi(self, PAGE1):
		PAGE1.setObjectName("PAGE1")
		PAGE1.resize(635, 472)
		self.baground = QtWidgets.QLabel(PAGE1)
		self.baground.setGeometry(QtCore.QRect(-4, -4, 700, 511))
		self.baground.setStyleSheet("background-image: url(:/newPrefix/images.jpeg);")
		self.baground.setText("")
		self.baground.setObjectName("baground")
		self.question1 = QtWidgets.QLabel(PAGE1)
		self.question1.setGeometry(QtCore.QRect(130, 80, 450, 100))
		self.question1.setObjectName("question1")
		self.question1.setText("Enter the Number of Elements in the Array:")
		self.question1.setStyleSheet("color: rgb(0,0,0);\n""font: 18pt \"Ubuntu Condensed\";")
		self.answer1 = QtWidgets.QLineEdit(PAGE1)
		self.answer1.setGeometry(QtCore.QRect(130, 270, 131, 41))
		self.answer1.setObjectName("answer1")
		self.answer1.move(130, 160)
		self.answer1.resize(280,40)
		self.button1 = QtWidgets.QPushButton(PAGE1)
		self.button1.setGeometry(QtCore.QRect(380, 330, 131, 31))
		self.button1.setStyleSheet("color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 255, 255, 255), stop:0.495 rgba(255, 255, 255, 255), stop:0.505 rgba(0, 0, 0, 255), stop:1 rgba(0, 0, 0, 255));\n"
		"background-color: rgb(186, 189, 182);")
		self.button1.setObjectName("button1")
		self.button1.move(445,160)
		self.button1.clicked.connect(self.on_click2)
		
		self.question2 = QtWidgets.QLabel(PAGE1)
		self.question2.setGeometry(QtCore.QRect(130, 180, 450, 100))
		self.question2.setObjectName("question2")
		self.question2.setText("Enter the Elements:")
		self.question2.setStyleSheet("color: rgb(0,0,0);\n""font: 18pt \"Ubuntu Condensed\";")
		self.answer2 = QtWidgets.QLineEdit(PAGE1)
		self.answer2.setGeometry(QtCore.QRect(130, 270, 131, 82))
		self.answer2.setObjectName("answer2")
		self.answer2.move(130, 260)
		self.answer2.resize(280,40)
		self.button2 = QtWidgets.QPushButton(PAGE1)
		self.button2.setGeometry(QtCore.QRect(380, 510, 131, 31))
		self.button2.setStyleSheet("color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:1, stop:0 rgba(255, 255, 255, 255), stop:0.495 rgba(255, 255, 255, 255), stop:0.505 rgba(0, 0, 0, 255), stop:1 rgba(0, 0, 0, 255));\n"
		"background-color: rgb(186, 189, 182);")
		self.button2.setObjectName("button2")
		self.button2.move(445,265)
		self.button2.clicked.connect(self.on_click3)
			

		self.pushButton = QtWidgets.QPushButton(PAGE1)
		self.pushButton.setGeometry(QtCore.QRect(270,350,90,50))
		self.pushButton.setStyleSheet("background-color: rgb(0, 0, 0);\n"
		"color: rgb(255, 255, 255);\n""font: 15pt \"Ubuntu Condensed\";")
		self.pushButton.setObjectName("pushButton")
		self.pushButton.clicked.connect(self.on_click)
		
		        
		self.retranslateUi(PAGE1)
		QtCore.QMetaObject.connectSlotsByName(PAGE1)

	def retranslateUi(self, PAGE1):
		_translate = QtCore.QCoreApplication.translate
		PAGE1.setWindowTitle(_translate("PAGE1", "Dialog"))
		self.button1.setText(_translate("PAGE1", "Submit"))
		self.button2.setText(_translate("PAGE1", "Submit"))
		self.pushButton.setText(_translate("PAGE1", "ENTER"))

def run1():
	app = QtWidgets.QApplication(sys.argv)
	PAGE1 = QtWidgets.QDialog()
	ui = Ui_PAGE1()
	ui.setupUi(PAGE1)
	PAGE1.show()
	app.exec_()

###-----------------------------------------------------------------------------------------------------------------------------
###GUI PAGE2
###-----------------------------------------------------------------------------------------------------------------------------
class Ui_Dialog(object):
	def setupUi(self, Dialog):
		Dialog.setObjectName("Dialog")
		Dialog.resize(1017, 674)
		Dialog.setStyleSheet("background-image: url(:/newPrefix/image3.jpg);")
		self.label = QtWidgets.QLabel(Dialog)
		self.label.setGeometry(QtCore.QRect(-4, -4,1017 , 674))
		self.label.setObjectName("label")
		self.retranslateUi(Dialog)
		QtCore.QMetaObject.connectSlotsByName(Dialog)

	def retranslateUi(self, Dialog):
		_translate = QtCore.QCoreApplication.translate
		Dialog.setWindowTitle(_translate("Dialog", "Dialog"))
		self.label.setText(_translate("Dialog","<html><head></head><body align \"center\" ><p><h1><span style=\" color:#000000; font-size=45pt;\"><center><b>CALCULATED VALUES</center></span></b><br><hr></h1></p><p><h2><span style=\" color:#000000; font-size=45pt;\"><center><b>GIVEN ARRAY:"+str(array1)+"</center></span></b><h2><span style=\" color:#000000; font-size=45pt;\"><center><b>SORTED ARRAY:"+str(array2)+"</center></span></b><hr></h2></p><p><h2><font face=\"Courier New\" size=\"5\"><style type=\"text/css\"> .hoverTable tr:hover{ background-color:yellow;}</style><table class=\"hoverTable\" border=1 align=\"center\" bgcolor=\"white\" width=\"60%\" height=\"10%\"  ><tr><td align=\"center\">Mean<td align=\"center\">Median<td align=\"center\">Mode</tr><tr><td align=\"center\">"+str(partA)+"<td align=\"center\">"+str(partB)+"<td align=\"center\">"+str(partC)+"</tr></table><br><table border=1 align=\"center\" bgcolor=\"white\" width=\"60%\" height=\"10%\"  ><tr><td align=\"center\">Quartile<td align=\"center\">Median_low<td align=\"center\">Median_high</tr><tr><td align=\"center\">"+str(partD)+"<td align=\"center\">"+str(partE)+"<td align=\"center\">"+str(partF)+"</tr></table><br><table border=1 align=\"center\" bgcolor=\"white\" width=\"60%\" height=\"10%\"  ><tr><td align=\"center\">Variance<td align=\"center\">Standard Deviation<td align=\"center\">Range</tr><tr><td align=\"center\">"+str(partG)+"<td align=\"center\">"+str(partH)+"<td align=\"center\">"+str(partI)+"</tr></table><br><table border=1 align=\"center\" bgcolor=\"white\" width=\"60%\" height=\"10%\"  ><tr><td align=\"center\">Geometric Mean<td align=\"center\">Harmonic Mean</tr><tr><td align=\"center\">"+str(partJ)+"<td align=\"center\">"+str(partK)+"</tr></table></font></h2></p><br><hr></body></html>"))

def run2():
	app = QtWidgets.QApplication(sys.argv)
	Dialog = QtWidgets.QDialog()
	ui = Ui_Dialog()
	ui.setupUi(Dialog)
	Dialog.show()
	app.exec_()
#-----------------------------------------------------------------------------------------------------------------------------
#BOX PLOT, STEM LEAF, DOT PLOT
#-----------------------------------------------------------------------------------------------------------------------------



#-----------------------------------------------------------------------------------------------------------------------------
#STATS PACKAGE
#-----------------------------------------------------------------------------------------------------------------------------
def Mean():           
    sum=0;
    for i in range(int(n)):
        sum=sum+int(a[i])
    mean=round(sum/int(n),3)
    global partA
    partA=mean
    print("mean: ", mean)
#-----------------------------------------------------------------------------------------------------------------------------
#STATS PACKAGE
#-----------------------------------------------------------------------------------------------------------------------------
def Median():            
    if int(n)%2==0:
    	median1=round((int(a[int(int(n)/2)-1])+int(a[int(int(n)/2)])/2), 3)
    else:
    	median1=int(a[int(int(n)/2)])
    global partB
    partB=str(median1)
    print("median: ", median1)
#-----------------------------------------------------------------------------------------------------------------------------
#STATS PACKAGE
#-----------------------------------------------------------------------------------------------------------------------------
def Mode():
	count=[]
	global mode11
	mode11=[]
	for i in range(0,int(n)):
		count.append(0)
	x=int(a[0])
	xi=0
	for i in range(int(n)):
		if(int(a[i])==x):
			count[xi]=count[xi]+1
		else:
			x=int(a[i])
			xi=i
			count[xi]=count[xi]+1
	max=0
	for i in range(int(n)):
		if(count[i]>max):
			max=count[i]
	for i in range(int(n)):
		if(count[i]==max):
			mode=int(a[i])
			mode11.append(a[i])
			#print(mode11)
			#break
	global partC
	partC=str(mode11)
	print("mode: ", mode11)
#-----------------------------------------------------------------------------------------------------------------------------
#STATS PACKAGE
#-----------------------------------------------------------------------------------------------------------------------------
def Range():             
    range1=int(a[int(n)-1])-int(a[0])
    global partI
    partI=str(range1)
    print("range: ", range1)
#-----------------------------------------------------------------------------------------------------------------------------
#STATS PACKAGE
#-----------------------------------------------------------------------------------------------------------------------------
def Median_low():      
    if(int(n)%2==0):
        median_low=int(a[int(int(n)/2)-1])
    else:
        median_low=int(a[int(int(n)/2)])
    global partE
    partE=str(median_low)
    print("median_low: ", median_low)
#-----------------------------------------------------------------------------------------------------------------------------
#STATS PACKAGE
#-----------------------------------------------------------------------------------------------------------------------------
def Median_high():        
    median_high=int(a[int(int(n)/2)])
    global partF
    partF=str(median_high)
    print("median_high: ", median_high)
#-----------------------------------------------------------------------------------------------------------------------------
#STATS PACKAGE
#-----------------------------------------------------------------------------------------------------------------------------
def Quartiles():            
    n1=int(n)/2
    if(n1%2==0):
        q1=round((a[int(int(n)/4)-1]+a[int(int(n)/4)])/2, 3)
        q3=round((a[int(3*int(n)/4)-1]+a[int(3*int(n)/4)])/2, 3)
    else:
        q1=a[int(int(n)/4)-1]
        q3=a[int(3*int(n)/4)-1]
    ret=[q1, q3]
    global partD
    partD=str(ret)
    print("quartiles: ", ret)
#-----------------------------------------------------------------------------------------------------------------------------
#STATS PACKAGE
#-----------------------------------------------------------------------------------------------------------------------------
def Variance():          
    sum=0
    for i in range(int(n)):
        sum=sum+int(a[i])
    mean=round(sum/int(n))
    sum1=0
    for i in range(int(n)):
    	sum1=sum1+(mean-int(a[i])*(mean-int(a[i])))
    variance=round(sum1/int(n), 3)
    global partG
    partG=str(variance)
    print("variance: ", variance)
#-----------------------------------------------------------------------------------------------------------------------------
#STATS PACKAGE
#-----------------------------------------------------------------------------------------------------------------------------
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
    global partH
    partH=str(stdev)
    print("stdev: ", stdev)
#-----------------------------------------------------------------------------------------------------------------------------
#STATS PACKAGE
#-----------------------------------------------------------------------------------------------------------------------------
def Geometric_mean():           
    prod=1
    for i in range(int(n)):
        prod=prod*int(a[i])
    gm=round(pow(prod, 1/int(n)), 3)
    global partJ
    partJ=str(gm)
    print("gm: ", gm)
#-----------------------------------------------------------------------------------------------------------------------------
#STATS PACKAGE
#-----------------------------------------------------------------------------------------------------------------------------
def Harmonic_mean():           
    sum=0
    for i in range(int(n)):
        sum=sum+round((1/int(a[i])), 3)
    hm=round(int(n)/sum, 3);
    global partK
    partK=str(hm)
    print("hm: ", hm)
#-----------------------------------------------------------------------------------------------------------------------------
#STATS PACKAGE
#-----------------------------------------------------------------------------------------------------------------------------

run1();
#print("enter the number of elements in the array: ")
#print(message1)
n=message1.replace(' ','')
#print("enter the elements:\n")
#print(message2)
a=[]
y1=[]
b1=[]
b1=message2.split(' ')
#print(int(n))
for i in range(0,int(n)):
	a.append(int(b1[i]))
print(a)
array1=str(a)
a.sort()
array2=str(a)
print(a)
if click==1:
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

run2()


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


print("done!!")

#time.sleep(3)
run2()


