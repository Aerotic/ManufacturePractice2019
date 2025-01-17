===========================================================================================
外部中断实验
===========================================================================================
实验目的：正确配置外部中断寄存器，学习其工作原理。
===========================================================================================
实验步骤：
1）将SmartRF04仿真器的USB端连接电脑，另一端连接节点的调试接口。
2）在IAR软件菜单栏选择Project->Download and debug将程序下载到CC2530节点板并进入到调试状态。
3）在IAR软件菜单栏选择Debug->Go全速运行程序，观察实验现象。
4）退出调试状态：在IAR软件菜单栏选择Debug->Stop Debugging停止程序运行。
5）此时程序已经固化到CC2530节点板的Flash中，重启或重新上电，程序将直接运行。

注意：
1）进入Debug状态若出错，请检查电脑的设备管理器是否正确识别仿真器设备，如果未成功
   识别则安装SetupSmartRFProgr驱动后重试。
2）若成功识别设备但进入Debug状态任然出错，找到仿真器上的RST按钮重复点击两次。
   点击完成后再次尝试进入Debug状态。
3）如果以上方法均无效请更换仿真器再试。
===========================================================================================
实验现象：
程序运行后，节点上的D2点亮、D1熄灭，按下K1按键之后，会进入外部中断，翻转D1、D2的状态。
===========================================================================================