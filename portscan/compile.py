import subprocess
from glob import glob


cpp_files = glob('*.cpp')

try:
    subprocess.call(["g++", "main.cpp", "-o", "test"])
except:
    print("something wrong")
