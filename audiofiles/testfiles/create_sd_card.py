import os
from text_to_speech import save
import time

basepath=""

texts = [ ]
texts.append("Welcome")
texts.append("1 pulse 1st version")
texts.append("2 pulse 1st version")
texts.append("3 pulse 1st version")
texts.append("4 pulse 1st version")
texts.append("5 pulse 1st version")
texts.append("6 pulse 1st version")
texts.append("This should not happen.")
texts.append("This should not happen.")
texts.append("This should not happen.")
texts.append("Welcome 2nd")
texts.append("1 pulse 2nd version")
texts.append("2 pulse 2nd version")
texts.append("3 pulse 2nd version")
texts.append("4 pulse 2nd version")
texts.append("5 pulse 2nd version")
texts.append("6 pulse 2nd version")
texts.append("This should not happen.")
texts.append("This should not happen.")
texts.append("This should not happen.")
texts.append("Welcome 3rd")
texts.append("1 pulse 3rd version")
texts.append("2 pulse 3rd version")
texts.append("3 pulse 3td version")
texts.append("4 pulse 3rd version")
texts.append("5 pulse 3rd version")
texts.append("6 pulse 3rd version")
texts.append("This should not happen.")
texts.append("This should not happen.")
texts.append("This should not happen.")
texts.append("Welcome 4th")
texts.append("1 pulse 4th version")
texts.append("2 pulse 4th version")
texts.append("3 pulse 4th version")
texts.append("4 pulse 4th version")
texts.append("5 pulse 4th version")
texts.append("6 pulse 4th version")
texts.append("This should not happen.")
texts.append("This should not happen.")
texts.append("This should not happen.")
texts.append("Welcome 5th")
texts.append("1 pulse 5th version")
texts.append("2 pulse 5th version")
texts.append("3 pulse 5th version")
texts.append("4 pulse 5th version")
texts.append("5 pulse 5th version")
texts.append("6 pulse 5th version")
texts.append("This should not happen.")
texts.append("This should not happen.")
texts.append("This should not happen.")
texts.append("Welcome 6th")

os.mkdir(basepath+"00")
i=0
for text in texts:
    print("----")
    print("File: " + str(i).zfill(2))
    print(text)
    save(text,"en",file=basepath+"00"+"/"+str(i).zfill(4)+".mp3")
    time.sleep(5)
    print("++++")
    i+=1
