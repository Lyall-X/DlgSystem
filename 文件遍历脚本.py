import os
import re
import sys

fileList = os.listdir(r"./Nodes")
print(str(fileList))
os.chdir('E:\\UE4Pro\\MyProject3\\Plugins\\Nodes')
for filename in fileList:
    portion = os.path.splitext(filename)
    with open(filename, "r+", encoding='UTF-8') as f:
        # cpp内容填充
        # read_data = f.read()
        # # f.seek(0)
        # f.truncate()
        # f.write(u'''#include "'''+ portion[0] + '''.h"
        # ''')
    # 内容替换
        content = f.read()
        f.close()

        t = content.replace("string", "FText")
        with open(filename, "w", encoding='UTF-8') as f2:
            f2.write(t)

