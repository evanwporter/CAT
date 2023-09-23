#1
import os 
from os import listdir
#2
folder_path = "%s/" % os.getcwd()
#3
for file_name in listdir(folder_path):
    #4
    if file_name.endswith('.obj') or file_name.endswith('.exe') or file_name.endswith('.ilk') or file_name.endswith('.pdb'):
        #5
        os.remove(folder_path + file_name)