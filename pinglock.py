import serial
import urllib
import httplib
from slackclient import SlackClient

ser = serial.Serial('COM5',9600)


temp = ''

def slack_message(message, channel):
    #Sample Slack Legacy Token -- replace this with your own Legacy Token, obtainable from Slack's website
    token = 'xoxp-335565557714-335467263395-335707145298-61b765cb2975e0dc054430a95a545ce3' 
    sc = SlackClient(token)
    sc.api_call('chat.postMessage', channel=channel, 
                text=message, username='Ping Lock Bot',
                icon_emoji=':robot_face:')



while True:
    ch = ser.read()
    if ch == '\n':
        print temp
        
        if temp=="Leaving":
            slack_message("Oh! Looks like someone's leaving the room!", "iot-project")
        elif temp == "Entering":
            slack_message("Someone's entering the room!", "iot-project")
        temp = ''    
        '''
        if temp!='':
            conn = httplib.HTTPConnection("api.thingspeak.com:80")
            conn.request("GET", "/update?key=IX3YMMI4IUBRA9RY&field1=%s\n" %(temp) )
            res = conn.getresponse()
            print res.status, res.reason
            conn.close()
            temp = ''
        '''
    else:
        temp += ch
