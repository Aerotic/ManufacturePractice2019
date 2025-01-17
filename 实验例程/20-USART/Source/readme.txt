===========================================================================================
串口通信实验（例程）
===========================================================================================
实验目的：正确配置串口，学习其工作原理。
===========================================================================================
实验准备：
一个plus节点，一个USB mini线
一个12V电源，一个jlink仿真器
===========================================================================================
实验步骤：
1）将jlink仿真器的USB端连接电脑，另一端连接节点的调试接口。
2）用USB mini线连接PC与节点，打开串口助手设置波特率为115200，数据位8，校验0,停止位1.
  给节点通上电源，点击打开串口。
3）在IAR软件菜单栏选择Project->Download and debug将程序下载到plus节点板并进入到调试状态。
4）在IAR软件菜单栏选择Debug->Go全速运行程序，观察实验现象。
5）退出调试状态：在IAR软件菜单栏选择Debug->Stop Debugging停止程序运行。
6）此时程序已经固化到节点板的Flash中，重启或重新上电，程序将直接运行。

注意：
1）进入Debug状态若出错，请检查电脑的设备管理器是否正确识别仿真器设备，如果未成功
   识别则安装jlink驱动后重试。
2）如果以上方法均无效请更换仿真器再试。
===========================================================================================
实验现象：
程序运行首先通过串口向pc打印"Hello IOT!"，"Usart is ready!"字符串
随后进入循环体，将pc传过来的数据在通过串口打印到pc上
每通信一次D3D4闪烁一次
===========================================================================================

