# wtr_diy_joystick
### 更新：加入了解码样例和优化了一些Bug。



#### 这是WTR第一版自己制作的手柄。

### 软件开发基于hal库：

#### 通信包为：

接收器模块地址0x00+0x01(2位)+信道(410+0x14MHZ)(1位) +包头0xff+0x55(2位）+长度(1位)+crc8(1位)+状态(1位)+摇杆1的两个通道(8位）+摇杆2的两个通道(8位)+矩阵键盘(1位)

#### 显示功能：显示按键状态，摇杆通道状态和通信状态和传输速度累计标识。

### usercode:

- **app.c/h：自定义功能函数库**
- **ST7735.c/h：自定义显示屏使用库**
- **my_serial.c/h：自定义通信协议**

#### 通信模式：

基于无线串口通信的定点传输：任意模块发送数据，可指定模块接收，多个接收模块地址信道相同时，均可接收数据。数据可以实现跨信道点对点传输。

##### 注意：接收模块使用时MD0为高电平，MD1为低电平来开启唤醒模式。

#### 矩阵键盘扫描读取单个按键并记录：

![](https://github.com/zhuzhengming/wtr_diy_joystick/blob/main/picture/1.jpg)

#### 电路连接设计：

![](https://github.com/zhuzhengming/wtr_diy_joystick/blob/main/picture/image-20210811114523792.png)

![](https://github.com/zhuzhengming/wtr_diy_joystick/blob/main/picture/image-20210811114542407.png)

