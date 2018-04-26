#!usr/bin/python

import sys
from optparse import OptionParser

#class takes in the filename of 2 files, named file1 and file2
class comm:
    def __init__(self,file1,file2):
        if (file1=="-"):
            self.l1=sys.stdin.readlines()
        else:
            f1 = open(file1,'r')
            self.l1 = f1.readlines()
            f1.close()

        if (file2=="-"):
            self.l2=sys.stdin.readlines()
        else:
            f2 = open(file2,'r')
            self.l2 = f2.readlines()
            f2.close()
        self.result=[]

    def unsortedcomm(self):
        for i in self.l1:
            added = False
            for j in self.l2:
                if (i==j):
                    self.result.append([i,3])
                    self.l2.remove(j)
                    added = True
                    break
            if (added == False):
                self.result.append([i,1])
        for z in self.l2:
            self.result.append([z,2])

    def sortedcomm(self):
        i=0
        j=0
        while (i<len(self.l1)) and (j<len(self.l2)):
            if (self.l1[i]==self.l2[j]):
                self.result.append([self.l1[i],3])
                i+=1
                j+=1
            elif (self.l1[i] < self.l2[j]):
                self.result.append([self.l1[i],1])
                i+=1
            elif (self.l1[i] > self.l2[j]):
                self.result.append([self.l2[j],2])
                j+=1

        if (i==len(self.l1)):
            while (j<len(self.l2)):
                self.result.append([self.l2[j],2])
                j+=1
        elif (j==len(self.l2)):
            while (i<len(self.l1)):
                self.result.append([self.l1[i],1])
                i+=1

    def printcomm(self,a1,a2,a3):
        for i in self.result:
            if (i[1]==1):
                if (a1):
                    sys.stdout.write(i[0])
            elif (i[1]==2):
                if (a2):
                    sys.stdout.write("\t"+i[0])
            elif (i[1]==3):
                if (a3):
                    sys.stdout.write("\t\t"+i[0])
                    
        
        
                
def main():
    version_msg = "%prog 2.0"
    usage_msg = """ %prog [option]... File1 File2

Output comm File1 File2. """

    parser = OptionParser(version=version_msg, usage=usage_msg)
    parser.add_option("-1",
                      action="store_false",dest="add1",default=True,
                      help="whether to add first column or not")
    parser.add_option("-2",
                      action="store_false",dest="add2",default=True,
                      help="whether to add second column or not")
    parser.add_option("-3",
                      action="store_false",dest="add3",default=True,
                      help="whether to add third column or not")
    parser.add_option("-u",
                      action="store_false",dest="sorted",default=True,
                      help="is the file sorted")
    options, args = parser.parse_args(sys.argv[1:])

    
    if len(args) != 2:
        parser.error("wrong number of input files")
    file1 = args[0]
    file2 = args[1]

    try:
        generator = comm(file1,file2)
    except:
        parser.error("fail to read files")

    try: 
        
        if (options.sorted):
            generator.sortedcomm()
        else:
            generator.unsortedcomm()
    except:
        parser.error("fail to sort files")

    try:
        generator.printcomm(options.add1,options.add2,options.add3)
    except:
        parser.error("fail print compared files")

if __name__ == "__main__":
    main()
