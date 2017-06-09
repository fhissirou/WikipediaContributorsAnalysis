#!/usr/bin/python


import datetime
import sys
import os
import xml.etree.ElementTree as ET

reload(sys)
sys.setdefaultencoding('utf8')

print(datetime.datetime.now())
print("Ouverture du fichier !!!!")

#inputfile= '../../data/historiques_pages.xml'
inputfile= '../../data/frrwiki-20170401-stub-meta-history.xml'
pathOutput= "../../data/input/"
nsp= "http://www.mediawiki.org/xml/export-0.10/"
strtag=' xmlns="http://www.mediawiki.org/xml/export-0.10/\"'
genfilename= "dump_hist_"

tree = ET.parse(inputfile)
root = tree.getroot()
nb_pages= 1
compt=1
outFile= open(pathOutput+genfilename+str(compt)+".xml", 'w+')
outFile.write("<mediawiki>\n\t")

ET.register_namespace("", nsp)
for page in root.findall('{%s}page' % nsp):
    if nb_pages > 100:
        compt+=1
        outFile.write("\n</mediawiki>")
        outFile.close()
        outFile = open(pathOutput+genfilename+str(compt)+".xml", 'w+')
        outFile.write("<mediawiki>\n\t")
        print(pathOutput+genfilename+str(compt)+".xml")
        nb_pages= 1

    strpage=str(ET.tostring(page))
    strpage = strpage.replace(strtag, '')
    outFile.write(strpage)
    
    nb_pages+=1
outFile.write("\n</mediawiki>")
outFile.close()
print(datetime.datetime.now())