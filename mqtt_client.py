import paho.mqtt.client as mqtt
import time

# Callback when the client connects to the broker
def on_connect(client, userdata, flags, rc):
    print(f"Connected with result code {rc}")
    
# Callback when a message is received from the broker
def on_message(client, userdata, msg):
    print(f"Received message: {msg.payload.decode()} on topic {msg.topic}")

# Set up the MQTT client

def publishoutput(message):
    client = mqtt.Client()
    client.on_connect = on_connect
    client.on_message = on_message

    # Connect to the broker
    client.connect("broker.mqtt-dashboard.com", 1883, 60)

    # Start the MQTT client loop
    client.loop_start()

    # Publish a message to a topic
    # print("topic:technotron_atomquest_2023\npayload:sarthak kumar")
    topic = "technotron_atomquest_2023"
    message=message[-1]

    print(f"topic:{topic}\npayload:{message}")
    client.publish(topic,message)

    # Wait for a while to receive messages (you can customize this)
    time.sleep(10)

    # Disconnect from the broker
    client.loop_stop()
    client.disconnect()
