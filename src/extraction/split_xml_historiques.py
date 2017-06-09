#!/usr/bin/python

from xml.dom import minidom
import datetime
import sys
import os

reload(sys)
sys.setdefaultencoding('utf8')

print(datetime.datetime.now())

compt=0
print("Ouverture du fichier !!!!")
xmldoc = minidom.parse('../../data/frrwiki-20170401-stub-meta-history.xml')
pathOutput= "../../data/input/"
taglist = xmldoc.getElementsByTagName('page')
val = len(taglist)
print(val)

nb_pages= 1
compt=1
outFile= open(pathOutput+'dump_hist_'+str(compt)+".xml", 'w+')
outFile.write("<mediawiki>\n\t")
print("Separation du fichier !!!!")
for i in range(val) :
    if nb_pages > 100:
        compt+=1
        outFile.write("\n</mediawiki>")
        outFile.close()
        outFile = open(pathOutput+'dump_hist_'+str(compt)+".xml", 'w+')
        outFile.write("<mediawiki>\n\t")
        nb_pages= 1

    outFile.write(str(taglist[i].toxml()))
    nb_pages+=1
outFile.write("\n</mediawiki>")
outFile.close()
print("Fin du programme")
print(datetime.datetime.now())