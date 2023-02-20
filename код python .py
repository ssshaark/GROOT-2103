import serial

if __name__ == '__main__':
    ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)
ser.flush()
while True:
    answer = ser.read()
    line = ser.readline().decode('utf-8').rstrip()
    if answer != b'':
        if int.from_bytes(answer, byteorder='big') == ('otladka' or 'con' or 'bescon'):
            ser.write(0x0.encode('utf-8'))
            memory = answer
        if int.from_bytes(answer, byteorder='big') == 'con': #Перешли на новую панель
            colvo = answer
        if int.from_bytes(answer, byteorder='big') == 'bescon':
            colvo = 999
        if int.from_bytes(answer, byteorder='big') == 'yes':
            ser.write(0x1.encode('utf-8'))
            for i in range(colvo):
                answer = ser.read()
                if answer != b'':
                    ser.write(0x4.encode('utf-8'))
                ser.write(0x3.encode('utf-8'))

        if int.from_bytes(answer, byteorder='big') == 'no':
            ser.write(0x2.encode('utf-8'))



ser.write(0x0.encode('utf-8'))
