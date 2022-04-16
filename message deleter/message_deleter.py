#This script will automatically fetch messages from Discord.com (IRC service) using their
#API, and delete all messages matching the parameters entered by the user. This includes
#the ID of the user who posted the messages, the channel they are in, and filtering to 
#specific text.

import time
import requests
import json

messages_loaded = False

#Attempt to load messages from the site.
while (not messages_loaded):
    term = ""

    token = input("Authorization Token: ")
    uuid = input("From user (UUID): ")
    channel = input("Channel ID: ")
    if input("Filter messages? (y/n): ").lower() == 'y':
        term = input("Messages containing: ")

    head = {"authorization": token}
    while (not messages_loaded):
        urlbase = "https://discord.com/api/v9/channels/" + channel + "/messages/search?content=" + term

        r = requests.get(url=urlbase, headers=head)
        if r.status_code != requests.codes.ok:
            #If an error occurred, ask the user if they would like to change their parameters, or retry.
            choice = input("Error: failed fetch messages. [Status code: " + str(r.status_code) + "] Retry? (r) Or change parameters? (c)\ntoken: " + token +"\nUUID:" + uuid + "\nChannel ID: " + channel + "\nContaining: " + term + "\n")
            if choice == "c" or "C":
                break
        else:
            messages_loaded = True

#Load a list of all message IDs matching the author parameter
ids = []
data = json.loads(r.text)
for i in data["messages"]:
    if i[0]["author"]["id"] == uuid:
        ids.append(i[0]["id"])

#Begin deleting messages, and display information about each deletion
message_index = 0
for id in ids:
    url_ = "https://discord.com/api/v9/channels/" + channel + "/messages/" + id
    print("Attempting to delete: " + id)
    requests.delete(url=url_, headers=head)
    #sleep for latency & to avoid overloading the server
    time.sleep(0.75) 
        
    #check message status
    if r.status_code != requests.codes.ok:
        print("Error: failed to update message: " + id + ":")
        print(r.text)
    else:
        print("Message deleted: " + str(id))
        print("   Deleted Content:")
        print("   " + str(json.loads(r.text)["messages"][message_index][0]["content"]))
    message_index = message_index + 1
