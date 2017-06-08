#!/usr/bin/env python
# -*- coding: utf-8 -*-

from xml.dom.minidom import parse
import xml.dom.minidom
from datetime import datetime
import os
import sys

reload(sys)
sys.setdefaultencoding('utf8')


class Extract(object):
    """docstring for ClassName"""
    def __init__(self):
        super(Extract, self).__init__()
        #self.StrIputData = "../../data/input/historiques_pages.xml"
        self.StrPathInput="../../data/input/"
        self.FilesList= os.listdir(self.StrPathInput)
        self.StrIputData="../../data/input/stub-meta-history.xml"
        self.StrIputData="../../data/input/dump_hist_1.xml"
        self.StrOutputpagesInfos="../../data/output/extract_pages_infos.xml"
        self.contents_pages()



    def contents_pages(self):
        
        strattr="id,title,nbRevision,nbContributeur,nbBytes,nbMinor,year,month,day,PartsOfTheDay\n"
        with open(self.StrOutputpagesInfos, 'w+') as file:
            file.write(strattr)
            for filename in self.FilesList:
                if filename.endswith(".xml"):
                    DOMTree = xml.dom.minidom.parse(self.StrPathInput+filename)
                    collection = DOMTree.documentElement
                    lpages= collection.getElementsByTagName("page")

                    strcontent_page=""
                    
                    
                    for page in lpages:
                        lusernames=[]
                        luserids=[]
                        pageid= self.extract_pageid(page)
                        titre= self.extract_title(page)
                        
                        lrevisions= self.extract_revision(page)

                        strcontent_page+=pageid+","+titre+","+str(len(lrevisions))
                        n=0
                        time_rev=""
                        nb_bytes=0
                        nb_minor=0
                        
                        for revision in lrevisions:
                            n+=1
                            if time_rev=="":
                                time_rev= self.extract_time_rev(revision)
                            nb_bytes+= self.extract_bytes(revision)
                            nb_minor+= self.extract_minor(revision)
                            
                            contributor = self.extract_contributor(revision)
                            username = self.extract_username(contributor)
                            if not(username in lusernames):
                                lusernames.append(username)

                        strcontent_page+=","+str(len(lusernames))+","+str(nb_bytes)+","+str(nb_minor)+","+time_rev+"\n"
                        file.write(strcontent_page)
                        strcontent_page=""
                            

        file.close()




    def extract_title(self, page):
        title = page.getElementsByTagName('title')[0]
        return title.childNodes[0].data

    def extract_pageid(self, page):
        id_page = page.getElementsByTagName('id')[0]
        return id_page.childNodes[0].data

    def extract_revision(self, page):
        return page.getElementsByTagName('revision')

    def extract_time_rev(self, revision):
        time_rev = revision.getElementsByTagName('timestamp')[0]
        strdate= time_rev.childNodes[0].data
        #2015-07-22T00:45:43Z
        dt = datetime.strptime(strdate, "%Y-%m-%dT%H:%M:%SZ")
        hour = dt.hour
        moment=""
        if 0 <= hour < 6:
            moment= "night"
        elif 6 <= hour < 13:
            moment="morning"
        elif 13 <= hour < 19:
            moment="afternoon"
        elif 19 <= hour < 24:
            moment="evening"

        strdt = dt.strftime("%Y,%B,%A")
        strdt+=","+moment
        return strdt

    def extract_contributor(self, revision):
        return revision.getElementsByTagName('contributor')[0]

    def extract_bytes(self, revision):
        text= revision.getElementsByTagName('text')[0]
        bytes_rev= text.attributes["bytes"] 
        return int(bytes_rev.value)

    def extract_minor(self, revision):
        if len(revision.getElementsByTagName('minor')) != 0:
            return 1
        else:
            return 0

    def extract_username(self, contributor):

        if len(contributor.getElementsByTagName('username')) != 0:
            username = contributor.getElementsByTagName('username')[0]
            return username.childNodes[0].data
        else:
            userip = contributor.getElementsByTagName('ip')[0]
            return userip.childNodes[0].data


Extract()