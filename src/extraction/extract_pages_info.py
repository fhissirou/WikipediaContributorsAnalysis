#!/usr/bin/env python
# -*- coding: utf-8 -*-


import xml.etree.ElementTree as ET
from datetime import datetime
import os
import sys

reload(sys)
sys.setdefaultencoding('utf8')


class Extract(object):

    def __init__(self):
        super(Extract, self).__init__()
        self.StrPathInput="../../data/input/"
        self.FilesList= os.listdir(self.StrPathInput)
        self.StrOutputpagesInfos="../../data/output/extract_pages_infos.csv"
        self.StrOutputpagesInfos2="../../data/output/gen_mat_page_usr1.csv"
        self.StrOutputpagesInfos3="../../data/output/gen_mat_page_listusr.txt"
        self.StrOutputpagesInfos4="../../data/output/gen_mat_usr_lpage.txt"
        #self.contents_pages()
        #self.gen_mat_page_usr1()
        #self.gen_mat_page_listusr()
        self.gen_mat_usr_lpage()

    def gen_mat_page_usr1(self):
        lusernames={}

        for filename in self.FilesList:
            if filename.endswith(".xml"):
                tree = ET.parse(self.StrPathInput+filename, "utf-8")
                root = tree.getroot()

                for page in root.findall("page"):
                    lrevisions= page.findall("revision")
                    for revision in lrevisions:
                        contributor= revision.find("contributor")
                        username = self.extract_userid(contributor)

                        if not (lusernames.has_key(username)):
                            lusernames[username]=0

        with open(self.StrOutputpagesInfos2, 'w+') as file:
            strattr="title"
            for key in lusernames:
                strattr+=",idusr_"+str(key)
            strattr+="\n"
            file.write(strattr)
            for filename in self.FilesList:
                if filename.endswith(".xml"):
                    tree = ET.parse(self.StrPathInput+filename)
                    root = tree.getroot()

                    strcontent_page=""
                    
                    
                    for page in root.findall("page"):
                        for key in lusernames.keys():
                            lusernames[key]= 0
                        
                        lrevisions= page.findall("revision")
                        for revision in lrevisions:
                            contributor= revision.find("contributor")
                            username = self.extract_userid(contributor)
                            lusernames[username]+=1

                        str_mat_page_usr= page.find('title').text
                        for val in lusernames.values():
                            str_mat_page_usr+=","+str(val)
                        str_mat_page_usr+="\n"
                        file.write(str_mat_page_usr)


    def gen_mat_page_listusr(self):
        with open(self.StrOutputpagesInfos3, 'w+') as file:
            for filename in self.FilesList:
                if filename.endswith(".xml"):
                    tree = ET.parse(self.StrPathInput+filename)
                    root = tree.getroot()

                    for page in root.findall("page"):
                        luserid=[]
                        lrevisions= page.findall("revision")
                        for revision in lrevisions:
                            contributor= revision.find("contributor")
                            userid = str(self.extract_userid(contributor))

                            if not(("user_"+userid) in luserid):
                                luserid.append("user_"+userid)
                        title=page.find('title').text
                        file.write(title+"=["+",".join(luserid)+"]\n")
  

    def gen_mat_usr_lpage(self):

        with open(self.StrOutputpagesInfos4, 'w+') as file:
            luserid=[]
            for filename in self.FilesList:
                if filename.endswith(".xml"):
                    tree = ET.parse(self.StrPathInput+filename)
                    root = tree.getroot()

                    strcontent_page=""
                    
                    for page in root.findall("page"):
                        title= page.find('title').text
                        pageid= "page_"+str(page.find('id').text)
                        lrevisions= page.findall("revision")

                        for revision in lrevisions:
                            contributor= revision.find("contributor")
                            userid = "user_"+str(self.extract_userid(contributor))

                            if userid !="user_None":
                                if any(userid in elem for elem in luserid):
                                    for item in range(0,len(luserid)):
                                        if luserid[item].has_key(userid):
                                            value = luserid[item][userid].append(pageid)
                                            break
                                else:
                                    new_dict={}
                                    new_dict[userid]= [pageid]
                                    luserid.append(new_dict)

            file.write("\n\n".join(str(item) for item in luserid))


    def contents_pages(self):
        
        strattr="id,title,nbRevision,nbContributeur,nbBytes,nbMinor,night,morning,afternoon,evening,year,month,day\n"
        with open(self.StrOutputpagesInfos, 'w+') as file:
            file.write(strattr)
            for filename in self.FilesList:
                if filename.endswith(".xml"):
                    tree = ET.parse(self.StrPathInput+filename)
                    root = tree.getroot()

                    strcontent_page=""
                    
                    
                    for page in root.findall("page"):
                        lusernames=[]
                        luserids=[]

                        pageid= page.find('id').text
                        titre= page.find('title').text
                        lrevisions= page.findall("revision")


                        strcontent_page+=pageid+","+titre+","+str(len(lrevisions))
                        n=0
                        time_rev=""
                        nb_bytes=0
                        nb_minor=0
                        nb_night=0
                        nb_morning=0
                        nb_afternoon=0
                        nb_evening=0
                        
                        for revision in lrevisions:
                            n+=1
                            
                            moment= self.extract_moment_rev(revision)
                            if moment == "night":
                                nb_night+=1
                            elif moment =="morning":
                                nb_morning+=1
                            elif moment=="afternoon":
                                nb_afternoon+=1
                            elif moment =="evening":
                                nb_evening+=1

                            if time_rev=="":
                                time_rev= self.extract_time_create(revision)

                            type_bytes= revision.find("text").get("bytes")
                            if type_bytes is not None:
                                nb_bytes += int(type_bytes)

                            minor= revision.find("minor")
                            if minor != None:
                                nb_minor+= 1

                            contributor= revision.find("contributor")
                            username = self.extract_username(contributor)


                            if not(username in lusernames) and (username != None):
                                lusernames.append(username)

                        strcontent_page+=","+str(len(lusernames))+","+str(nb_bytes)+","+str(nb_minor)+","\
                        +str(nb_night)+","+str(nb_morning)+","+str(nb_afternoon)+","+str(nb_evening)+","+time_rev+"\n"
                        file.write(strcontent_page)
                        strcontent_page=""
                            
        file.close()



    def extract_moment_rev(self, revision):

        strdate= revision.find("timestamp").text

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
        return moment


    def extract_time_create(self, revision):
        strdate= revision.find("timestamp").text
        #2015-07-22T00:45:43Z
        dt = datetime.strptime(strdate, "%Y-%m-%dT%H:%M:%SZ")
        strdt = dt.strftime("%Y,%B,%A")
        return strdt

    def extract_userid(self, contributor):
        if contributor.find('id') != None:
            return contributor.find('id').text
        elif contributor.find('ip')!=None:
            return contributor.find('ip').text 
        return None    
    
    def extract_username(self, contributor):

        if contributor.find('username') != None:
            return contributor.find('username').text
        elif contributor.find("ip") != None:
            return contributor.find("ip").text
        else:
            return None


Extract()