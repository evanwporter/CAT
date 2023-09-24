#1
import os 
from os import listdir


folder_path = "%s/" % os.getcwd()
#3
for file_name in listdir(folder_path):
    if os.path.isdir(file_name):
        for j in listdir(file_name):
            if j.endswith('.obj') or j.endswith('.ilk') or j.endswith('.pdb'):
                os.remove(folder_path + file_name + "\\" + j)
    if file_name.endswith('.obj') or file_name.endswith('.ilk') or file_name.endswith('.pdb'):
        os.remove(folder_path + file_name)