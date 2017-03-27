# coding=utf-8

# 导入系统模块
import sys
import os

import time  															# 导入时间模块
import subprocess


def main():

    # 获取路径
	baseAddr = os.path.abspath('.')
	FileNames = os.listdir(baseAddr)

	for i in FileNames:
		fullfilename = os.path.join(baseAddr, i)
        #print(fullfilename)
    	# 判断是否目录
		if os.path.isdir(fullfilename) == False:

    		# 判断是否是*.zip
			if (os.path.splitext(i)[1] == ".zip"):

				# 移除*.zip
				print(fullfilename)
				os.remove(fullfilename)

	# 延时关闭
	time.sleep(1);

if __name__ == "__main__":
    main()
