import speech_recognition as sr
import time
from mqtt_client import publishoutput

import requests
# Define the recognizer
recognizer = sr.Recognizer()

while True:
    with sr.Microphone() as source:
        print("Say something...")
        recognizer.adjust_for_ambient_noise(source)
        audio = recognizer.listen(source,timeout=25)
        try:
            print("Recognizing...")
            text = recognizer.recognize_google(audio)
            print(text)
            rasa_endpoint = "http://localhost:5005/webhooks/rest/webhook"
            recognized_text=text.lower();
            if(recognized_text=="stop"):
                break
            message = {
                "message": recognized_text
            }
            response = requests.post(rasa_endpoint, json=message)
            if response.status_code == 200:
                bot_response = response.json()
                mess=bot_response[0]['text']
                print("Bot:", bot_response[0]['text']) 
                publishoutput(mess)
            else:
                print("Failed to get a response from Rasa server")
        except sr.UnknownValueError:
            print("Sorry, could not understand the audio")
        except sr.RequestError as e:
            print(f"Error: {e}")

    time.sleep(5)





