#!/usr/bin/python
import urllib
import urllib2
import re
import requests
import json
import hashlib

'''
#for proxy authenticated internet: code_starts
proxy = urllib2.ProxyHandler({'http':'http://username:password@proxy_address:port'})
auth = urllib2.HTTPBasicAuthHandler()
opener = urllib2.build_opener(proxy,auth,urllib2.HTTPBasicAuthHandler)
urllib2.install_opener(opener)
#code_ends
'''
first_name = raw_input("First Name: ")
last_name = raw_input("Last Name: ");
email_id = raw_input("Email id: ");
query = first_name+"+"+last_name+"+"+email_id
str_len = len(email_id)
i = 0

while email_id[i]!='@':
	i=i+1
email = email_id[0:i]

#The following results will be from http://en.gravatar.com api
flag_gravatar = 0
email_md5 = hashlib.md5(email_id.encode())
email_md5 = email_md5.hexdigest()
get_gravatar = requests.get('https://en.gravatar.com/'+email_md5+'.json')
json_gravatar = get_gravatar.content
object_gravatar = json.loads(json_gravatar)
if 'entry' not in object_gravatar:
	print "User data not found gravatar"
else:
	for index,result in enumerate(object_gravatar['entry']):
		print "Gravatar Search Results:\n"
		print "A little introduction about "+first_name +" "+last_name+ ": "+result['aboutMe']
		print "Username: "+result['preferredUsername']
		try:
			print "Current location: "+result['currentLocation']
		except:
			print "Current Location not provided"
		
#gravatar results end

#The following results will be from https://www.flickr.com
flag_flickr=0
get_flickr= requests.get('https://api.flickr.com/services/rest/?api_key=put_your_key_here&format=json&find_email='+email_id+'&method=flickr.people.findbyemail')
json_flickr = get_flickr.content
i = 0
op = 0
cp = 0
while i<len(json_flickr):
	if json_flickr[i]=='(':
		op=i+1
	if json_flickr[i]==')':
		cp=i
	i=i+1
object_flickr = json_flickr[op:cp]	
object_flickr = json.loads(object_flickr)
if object_flickr['stat']=="fail":
	print "User data not found on flickr!"
else:
	flag_flickr=1
	object_flickr = object_flickr['user']
	get_flickr = requests.get('https://api.flickr.com/services/rest/?method=flickr.people.getInfo&api_key=put_your_key_here&user_id='+object_flickr['id']+'&format=json&nojsoncallback=1&auth_token=put_your_token_here&api_sig=put_your_api_sig_here')
	json_flickr = get_flickr.content
	object_flickr = json.loads(json_flickr)
	object_flickr = object_flickr['person']	
	username_flickr =  object_flickr['username']
	photosurl_flickr = object_flickr['photosurl']
	profileurl_flickr = object_flickr['profileurl']
	location_flickr = object_flickr['location']
	realname_flickr = object_flickr['realname']
	description_flickr = object_flickr['description']
	print "Data as on flickr:\nUsername: "+username_flickr['_content']+"\nUser ID: "+object_flickr['id']+"\nFull Name: "+realname_flickr['_content']+"\nProfile URL: "+profileurl_flickr['_content']+"\nPhotos URL: "+photosurl_flickr['_content']+"\nDescription(if provided): "+description_flickr['_content']+"\nLocation(if provided): "+location_flickr['_content']
#flickr results end

'''
#The following results will be from https://www.github.com/ api
flag_git = 0
get_github = requests.get('https://api.github.com/search/users?q='+email+'&in%3Aemail')
json_github = get_github.content
object_github = json.loads(json_github)
if object_github['total_count']!=0:
	print "Total number of results on github for given query: "+str(object_github['total_count'])
	# Print it all out
	for index,result in enumerate(object_github['items']):
		github_get = requests.get(result['url'])
		github_json = github_get.content
		github_object = json.loads(github_json)
		if 'email' not in github_object:
			flag_git=0 
		else:
			if github_object['email']==email_id:
				print "User's github username: " + result['login'];
				print "User's github url: " + result['url'];
				print "User's email-id on github: "+github_object['email'];
				if 'location' in github_object:
					print "User's location: "+github_object['location'];
				flag_git = 1
if flag_git==0:
	print "User data not found on GitHub"
#github results end
'''

#if everything above fails, go for google search results:
if	flag_flickr==0	and	flag_gravatar==0:
	r = requests.get('http://ajax.googleapis.com/ajax/services/search/web?v=1.0&num=20&q=' + email_id)

	# JSON object
	theJson = r.content
	theObject = json.loads(theJson)

	# Print it all out
	for index,result in enumerate(theObject['responseData']['results']):
		print result['titleNoFormatting']
		print result['url']
