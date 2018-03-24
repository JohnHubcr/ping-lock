import serial
import urllib
import httplib
import os
import time
import re
from slackclient import SlackClient


#ser = serial.Serial('dev/ttyUSB0')
ser = serial.Serial('COM5',9600)
#ser.baudrate = 9600
#ser.port = 'COM5'

temp = ''

def slack_message(message, channel):
    token = 'xoxp-335565557714-335467263395-335631328242-2374fc8ab3a4f7b2e3eafd1231a8576d'
    sc = SlackClient(token)
    sc.api_call('chat.postMessage', channel=channel, 
                text=message, username='Ping Lock Bot',
                icon_emoji=':robot_face:')



while True:
    ch = ser.read()
    if ch == '\n':
        print temp
        if temp=="Leaving":
            slack_message("Oh! Looks like someone's leaving!", "general")
        elif temp == "Entering":
            slack_message("Someone's entering!", "general")
            
        '''params = urllib.urlencode({'field1':temp, 'key':'IX3YMMI4IUBRA9RY' })
        headers = {"Content-typZZe": "application/x-www-form-urlencoded","Accept": "text/plain"}
        conn = httplib.HTTPConnection("api.thingspeak.com:80")
        try:
            conn.request("POST", "/update", params, headers)
            response = conn.getresponse()
            print temp
            print response.status, response.reason
            data = response.read()
            conn.close()
        except:
            print "connection failed"
        '''
        temp = ''
        
        #conn = httplib.HTTPConnection("api.thingspeak.com:80")
        #conn.request("GET", "/update?key=IX3YMMI4IUBRA9RY&field1=%s\n" %(temp) )
        #res = conn.getresponse()
        #print res.status, res.reason
        #conn.close()
        #temp = ''
    else:
        temp += ch
