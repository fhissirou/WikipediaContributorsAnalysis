#!/usr/bin/env python
# -*- coding: utf-8 -*-

from xml.dom.minidom import parse
import xml.dom.minidom



# Open XML document using minidom parser
DOMTree = xml.dom.minidom.parse("../data/input/historiques_pages.xml")
collection = DOMTree.documentElement


pages= collection.getElementsByTagName("page")
# Print detail of each movie.
dic_pages={}
for page in pages:
	print ("\n\n")
	"""if page.hasAttribute("title"):
		print ("Title: %s" % page.getAttribute("title"))"""

	title = page.getElementsByTagName('title')[0]
	str_title = title.childNodes[0].data
	print ("Title: %s" % str_title)
	revisions= page.getElementsByTagName('revision')
	print("taille est ", len(revisions))
	dic_contributor={}
	for revision in revisions:
		contributors = revision.getElementsByTagName('contributor')
		for contributor in contributors:
			username = contributor.getElementsByTagName('username')[0]
			str_username= username.childNodes[0].data
			print ("username: %s" % str_username)
			
			if dic_contributor.has_key(str_username):
				dic_contributor[str_username] += 1
			else:
				dic_contributor[str_username]=1

	dic_pages[str_title]= dic_contributor


print(dic_pages)
