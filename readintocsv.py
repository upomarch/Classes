import serial
import csv
#import pandas as pd

print(serial.__version__)

arduino_port = "COM8" #serial port of Arduino
baud = 9600 #arduino uno runs at 9600 baud
fileName = "analog-data.csv" #name of the CSV file generated

ser = serial.Serial(arduino_port, baud)
print("Connected to Arduino port:" + arduino_port)
file = open(fileName, "w")
print("Created file")

samples = 200 #how many samples to collect
print_labels = False
line = 0 #start at 0 because our header is 0 (not real data)
sensor_data = [] #store data

# collect the samples
while line <= samples:
    getData = ser.readline()
    dataString = getData.decode('utf-8')
    data=dataString[0:][:-2]
    print(data)

    readings = data.split(",")
    print(readings)

    sensor_data.append(readings)
    print(sensor_data)

    line = line+1

#display the data to the terminal
getData=ser.readline()
dataString = getData.decode('utf-8')
data=dataString[0:][:-2]
print(data)

readings = data.split(",")
print(readings)

sensor_data.append(readings)
print(sensor_data)

# create the CSV
with open(fileName, 'w', encoding = 'UTF8', newline = '') as f:
    writer = csv.writer(f)
    writer.writerows(sensor_data)

print("Data collection complete!")
file.close()
  
###pandas attempt
# reading csv file
# df = pd.read_csv("analog_data.csv")

# new_row = pd.DataFrame({'Courses':'Hyperion', 'Fee':24000, 'Duration':'55days', 'Discount':1800}, index=[0])
# df2 = pd.concat([new_row,df.loc[:]]).reset_index(drop=True)
# print (df2)
  
# # filtering the rows where Credit-Rating is Fair
# df = df.loc[df['Heat index F']]
# print(df)