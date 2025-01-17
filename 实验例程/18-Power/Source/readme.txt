===========================================================================================
电源管理实验（例程）
===========================================================================================
实验目的：正确配置中断及睡眠模式，学习其工作原理。
===========================================================================================
实验准备：
一个plus节点，一个USB mini线
一个12V电源，一个jlink仿真器
===========================================================================================
实验步骤：
1）将jlink仿真器的USB端连接电脑，另一端连接节点的调试接口。
2）在IAR软件菜单栏选择Project->Download and debug将程序下载到plus节点板并进入到调试状态。
3）在IAR软件菜单栏选择Debug->Go全速运行程序，观察实验现象。
4）退出调试状态：在IAR软件菜单栏选择Debug->Stop Debugging停止程序运行。
5）此时程序已经固化到节点板的Flash中，重启或重新上电，程序将直接运行。

注意：
1）进入Debug状态若出错，请检查电脑的设备管理器是否正确识别仿真器设备，如果未成功
   识别则安装jlink驱动后重试。
2）如果以上方法均无效请更换仿真器再试。
===========================================================================================
*实验现象：
*       D3、D4常亮表示系统处于运行状态
*       D3熄灭、D4常亮表示系统处于休眠状态
*       系统运行一段时间后自动进入休眠状态
*       按下k3或k4按键可以将系统从休眠状态唤醒
===========================================================================================
