#coding=utf-8


import sys																# 导入系统模块
import os

import time																# 导入时间模块
import subprocess

def main():

	appVerStr = input("输入app版本号，范围 1~65535\r\n")

	# 是否输入非空
	if appVerStr != "":

		# 转换成int型
		appVerInt = int(appVerStr)

		# 是否越界
		if appVerInt < 1 or appVerInt > 65535:
			print("app版本号越界，采用默认值65535!\r\n")
			appVerStr = "65535"
	else:
		appVerStr = "65535"

	# 补空格
	appVerStr += " "
	print("appVerStr = " + appVerStr)

	# 获取路径
	baseAddr   = os.path.abspath('..')
	cmdAddr    = baseAddr + "\DFU\\nrfutil dfu genpkg "
	sdVersion  = "--sd-req 0x64 "
	appVersion = "--application-version " + appVerStr
	appAddr    = "--application " + baseAddr + "\MDK\Objects\Duck.hex "
	ZIPname    = time.strftime("%Y_%m_%d", time.localtime()) 
	ZIPAddr    = baseAddr + "\DFU\\nrfutil_dfu_" + ZIPname + ".zip"
	shellcmd   = cmdAddr + sdVersion + appVersion + appAddr + ZIPAddr

	print(shellcmd)

	# ִ执行
	os.system(shellcmd)

	# 延时关闭
	time.sleep(1);


if __name__ == "__main__":  
    main() 