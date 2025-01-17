===========================================================================================
串口通信实验
===========================================================================================
实验目的：正确配置串口，学习其工作原理。
===========================================================================================
实验步骤：
1）将SmartRF04仿真器的USB端连接电脑，另一端连接节点的调试接口，把节点的5个跳线帽全部跳下。
2) 用USB线把节点与PC连接起来,PC的串口助手设置，设置对应的端口号，
   波特率为38400bps,8位数据位,无奇偶校验,1位停止位，去掉十六进制显示。
3）在IAR软件菜单栏选择Project->Download and debug将程序下载到CC2530节点板并进入到调试状态。
4）在IAR软件菜单栏选择Debug->Go全速运行程序，观察实验现象。
5）退出调试状态：在IAR软件菜单栏选择Debug->Stop Debugging停止程序运行。
6）此时程序已经固化到CC2530节点板的Flash中，重启或重新上电，程序将直接运行。

注意：
1）进入Debug状态若出错，请检查电脑的设备管理器是否正确识别仿真器设备，如果未成功
   识别则安装SetupSmartRFProgr驱动后重试。
2）若成功识别设备但进入Debug状态任然出错，找到仿真器上的RST按钮重复点击两次。
   点击完成后再次尝试进入Debug状态。
3）如果以上方法均无效请更换仿真器再试。
4）如果没有端口号，请打上串口的驱动程序。
===========================================================================================
实验现象：
程序运行后，PC串口助手会显示提示文字，输入任何字符以@结尾，会返回输入的字符。
===========================================================================================