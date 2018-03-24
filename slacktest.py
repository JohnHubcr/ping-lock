from slackclient import SlackClient


def slack_message(message, channel):
    token = 'xoxp-335565557714-335467263395-335631328242-2374fc8ab3a4f7b2e3eafd1231a8576d'
    sc = SlackClient(token)
    sc.api_call('chat.postMessage', channel="general", 
                text=message, username='Ping Lock Bot',
                icon_emoji=':robot_face:')
