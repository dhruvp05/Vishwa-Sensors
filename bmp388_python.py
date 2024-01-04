import serial
import csv
import time

# Define the serial port and baud rate
ser = serial.Serial('COM3', 9600)  # Change 'COM3' to your Arduino's serial port

# Create a CSV file and write header
with open('sensor_data.csv', 'w', newline='') as file:
    writer = csv.writer(file)
    writer.writerow(['Timestamp', 'SensorValue'])  # Modify column names as needed

try:
    while True:
        # Read data from Arduino
        data = ser.readline().decode().strip()
        timestamp = time.strftime('%Y-%m-%d %H:%M:%S')  # Timestamp for data

        # Print data to console (optional)
        print(f'{timestamp}, {data}')

        # Append data to CSV file
        with open('sensor_data.csv', 'a', newline='') as file:
            writer = csv.writer(file)
            writer.writerow([timestamp, data])

except KeyboardInterrupt:
    ser.close()  # Close the serial port on Ctrl+C