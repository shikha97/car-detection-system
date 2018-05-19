# Python code to demonstrate table creation and 
# insertions with SQL

# importing module
import sqlite3
import time
import sys
import csv

#with open('/home/pi/Desktop/def_list.csv', newline='') as csvfile:
 #   data = list(csv.reader(csvfile))


# connecting to the database 
connection = sqlite3.connect("myTable.db")
def_file=open("/home/pi/Desktop/def_list.txt","r+",1)

# cursor 
crsr = connection.cursor()
crsr.execute("""DROP TABLE emp;""")
# SQL command to create a table in the database
sql_command = """CREATE TABLE emp ( 
staff_number INTEGER PRIMARY KEY, 
name VARCHAR(30), 
mail VARCHAR (30),
license VARCHAR (10)
);"""

# execute the statement
crsr.execute(sql_command)

# SQL command to insert the data in the table
sql_command = """INSERT INTO emp VALUES (1, "Abhilash Nair", "abhilash.nair031@gmail.com",'123456ABCD');"""
crsr.execute(sql_command)
#connection.commit()

# another SQL command to insert the data in the table
sql_command = """INSERT INTO emp VALUES (2, "Gaurav Chowda", "gaurav.150410111015@gmail.com",'567890KLMN');"""
crsr.execute(sql_command)

# To save the changes in the files. Never skip this. 
# If we skip this, nothing will be saved in the database.
connection.commit()
crsr.close()
time.sleep(2)
crsr1=connection.cursor()
for line in def_file:
   
    t=(line,)
    print(t,'           ')
    crsr1.execute('SELECT mail FROM emp WHERE license =%s',t )
    ans=crsr1.fetchall() 
    for i in ans:
      print(i)


# close the connection
crsr1.close()
connection.close()
