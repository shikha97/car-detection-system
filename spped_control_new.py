import RPi.GPIO as GPIO
import time
from time import sleep
from datetime import datetime
from decimal import *
from picamera import PiCamera
from smtplib import SMTP
from smtplib import SMTPException
import os
import smtplib
import email
from email.mime.text import MIMEText
from email.mime.image import MIMEImage
from email.mime.multipart import MIMEMultipart
pht= 27
pht1= 22
msg=MIMEMultipart()
msg['Subject'] ='information about overspeeding'
msg['From'] = 'gaurav.150410111015@gmail.com'
msg['To'] = 'abhilash.nair031@gmail.com'
body =MIMEText("""The pic of vehicle!""")
msg.attach(body)

camera = PiCamera()
global dt,dt1,diff,deltat
def setup():
     GPIO.setwarnings(False)
     GPIO.setmode(GPIO.BCM)
     GPIO.setup(pht, GPIO.IN)
     GPIO.setup(pht1,GPIO.IN)
     GPIO.setup(2,GPIO.OUT)
     GPIO.output(2,GPIO.LOW)
     global i
     i=0
def loop():
        
        print('System ON')
        while (True):
            x= GPIO.input(pht)
            y= GPIO.input(pht1)
            if(x==GPIO.HIGH and y==GPIO.LOW):
               camera.rotation= 180
               camera.start_preview(alpha=100)
               GPIO.output(2,GPIO.LOW)
               dt=datetime.now()
               print('sensor 1 Triggered at:',dt)
               print('Car entered')
               y=GPIO.input(pht1)
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                        
               if(y==GPIO.LOW):
                   while(y==GPIO.LOW):
                    
                    y=GPIO.input(pht1)
                    
                    if(y==GPIO.HIGH):
                        exit
                        
                       
               dt1=datetime.now()
               print('sensor 2 triggered at:',dt1)
               diff=dt1-dt
               print('Time diff', diff)
               dist= 0.05
               deltat = diff.seconds + (diff.microseconds/1000000)
               print('Deltat Time :', deltat)
               getcontext().prec = 2 
               vel=dist/deltat
               print('Speed:',vel)
               
               if(vel>0.05):
                    print('Overspeeding')
                    GPIO.output(2,GPIO.HIGH)
                    global i
                    i=i+1
                    time.sleep(0.5)
                    GPIO.output(2,GPIO.LOW)
                    camera.capture('/home/pi/Desktop/image%i.png' %i)
                    print(i)
                    directory = ('/home/pi/Desktop/image%i.png' %i)
 
                    spl_dir=directory.split('/')
                     
                    filename=spl_dir[len(spl_dir)-1]
                     
                    spl_type=directory.split('.')
                     
                    type=spl_type[len(spl_type)-1]
                     
                    fp=open(directory,'rb')
                    att = email.mime.application.MIMEApplication(fp.read(),_subtype=type)
                    fp.close()
                    att.add_header('Content-Disposition','attachment',filename=filename)
                    msg.attach(att)
                     
                    s = smtplib.SMTP('smtp.gmail.com:587')
                    s.ehlo()
                    s.starttls()
                    s.login('gaurav.150410111015@gmail.com','gaurav14')
                    s.sendmail('gaurav.150410111015@gmail.com','abhilash.nair031@gmail.com', msg.as_string())
                    s.quit()

               else:
                        print('All clear')
                        dt1=0
                        dt=0
               #GPIO.output(2,GPIO.LOW)
               time.sleep(1.0)
            elif (y==GPIO.HIGH and x==GPIO.HIGH):
                dt1=0
                dt=0
                print('make way clear')
def endprogram():
    GPIO.cleanup()
    camera.stop_preview()
if __name__ == '__main__':
    setup()
    try:
        
        loop()
    except KeyboardInterrupt:
        
        endprogram()
