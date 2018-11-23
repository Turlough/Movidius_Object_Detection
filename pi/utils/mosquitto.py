#!/usr/bin/python3

#_________turloughcowman.ie___________
#
# Publish object detection box parameters via mqtt
#
#_____________________________________

import paho.mqtt.client as mqtt

topic = "turlough/house/object-detection"
client =  mqtt.Client("P1")
broker_address="iot.eclipse.org" #use external broker

def connect():	

	client.connect(broker_address) #connect to broker

def publish(y1, x1, y2, x2, msg=()):

	message = "{0},{1},{2},{3},{4}".format( y1, x1, y2, x2, msg )
	client.publish(topic, message)

