from sets import Set
import os
import pyshark
length = 0
len1 = 0
len2 = 0
len3 = 0
cap = pyshark.LiveCapture(interface = 'en1')
for pkt in cap.sniff_continuously():
	try:
		source = pkt.ip.src
		protocol = pkt.highest_layer
		#host = pkt.http.host
		if(source == '192.168.0.107' and protocol == 'HTTP'):
			host = pkt.http.host
			if(host == 'www.bing.com'):
				print('SENT')
				length = len(pkt.http.request_uri_query.split('&')[2].split('=')[1])
				print(length)
				#print(pkt.http.request_uri_query.split('&')[2].split('=')[1])
				#if(length == 1):
					#ch = pkt.http.request_uri_query.split('&')[2].split('=')[1]
		elif(source == '172.31.1.4' and protocol == 'DATA-TEXT-LINES'):
			if(pkt.http.set_cookie.split('=')[-1] == 'bing.com'):
				print('RECEIVED')
				print(pkt.http.content_length)
				if (length == 1):
					len1 = int(pkt.http.content_length) 
				elif(length == 2):
					len2 = int(pkt.http.content_length)	
				elif(length == 3):
					len3 = int(pkt.http.content_length)
					print('BREAKING..')
					break			
	except AttributeError as e:
		pass

fp = open("map1_final.txt", "r+")
rm = {}
while True:
	str = fp.readline()
	if str == "":
		break
	s, val = str.split(' ')
	s = s.strip()
	val = (int)(val)
	val2 = abs(val - len1)
	if val2 < 10:
		rm[s] = val2
fp = open("map2_final.txt", "r+")
m = {}
st = set()
while True:
	str = fp.readline()
	if str == "":
		break
	s, val = str.split(' ')
	s = s.strip()
	val = (int)(val)
	val2 = abs(val - len2)
	if s[0:1] in rm and val2 < 30:
		m[s] = (val2 + rm[s[0:1]], rm[s[0:1]], val2)
fp.close()
fp = open('map3_final.txt', 'r+')

while True:
	str = fp.readline()
	if str == "":
		break
	s, val = str.split(' ')
	s = s.strip()
	val = (int)(val)
	val2 = abs(val - len3)
	if s[0:2] in m and val2 < 40:
		st.add((val2  + m[s[0:2]][0], m[s[0:2]][1], m[s[0:2]][2], val2, s))
		if len(st) > 10:
			st.remove(max(st))
result = []
count = 0
while st:
	b = min(st)
	if(count < 3):
		result.append(b[4])
	print(b[0], b[4])
	st.remove(b)
	count += 1
cmd = "./TRIE"
for res in result:
	cmd += (" "+res)
os.system(cmd)