import serial
import urllib
import httplib
from slackclient import SlackClient

ser = serial.Serial('COM5',9600)


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
            slack_message("Oh! Looks like someone's leaving!", "iot-project")
        elif temp == "Entering":
            slack_message("Someone's entering!", "iot-project")
            
        temp = ''
        
        #conn = httplib.HTTPConnection("api.thingspeak.com:80")
        #conn.request("GET", "/update?key=IX3YMMI4IUBRA9RY&field1=%s\n" %(temp) )
        #res = conn.getresponse()
        #print res.status, res.reason
        #conn.close()
        #temp = ''
    else:
        temp += ch
