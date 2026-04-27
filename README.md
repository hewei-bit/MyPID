# MyPID - STM32温控系统

基于STM32F103的PID算法温控系统，用于精确控制温度。

## 项目简介

本项目使用STM32F103微控制器实现PID温度控制算法，通过MAX6675热电偶传感器读取温度，使用PID算法计算输出值，实现精确的温度控制。

## 硬件组成

- **主控芯片**: STM32F103
- **温度传感器**: MAX6675 (K型热电偶)
- **存储芯片**: AT24C02 (EEPROM，用于存储PID参数)
- **显示模块**: 12864 LCD
- **用户界面**: 按键 + LED指示灯

## 引脚分配

### PID输出
- **PIDout** - PB8

### MAX6675 温度传感器
- **SCK** - PD2
- **SO** - PC12
- **CS** - PC11

### AT24C02 EEPROM (IIC)
- **SCL** - PB6
- **SDA** - PB7

### LED指示灯
- **LED0** - PB5
- **LED1** - PE5

### 按键输入
- **KEY0** - PE2
- **KEY1** - PE3
- **KEY2** - PE4
- **WK_UP** - PA0

## 项目结构

```
MyPID/
├── CORE/              # STM32核心文件
├── HARDWARE/         # 硬件驱动
│   ├── 12864/       # LCD显示驱动
│   ├── 24CXX/       # EEPROM驱动
│   ├── display/     # 显示功能
│   ├── IIC/         # IIC通信
│   ├── KEY/         # 按键驱动
│   ├── LCD/         # LCD驱动
│   ├── LED/         # LED驱动
│   ├── max6675/     # 温度传感器驱动
│   ├── PID/         # PID算法实现
│   └── timer_init/  # 定时器初始化
├── STM32F10x_FWLib/ # STM32标准外设库
├── SYSTEM/          # 系统文件
├── USER/            # 用户代码
│   ├── main.c      # 主函数
│   └── ...
└── USMART/         # 串口调试工具
```

## 功能特性

- ✅ PID温度控制算法
- ✅ 实时温度采集与显示
- ✅ PID参数存储与读取
- ✅ 按键设置目标温度
- ✅ LCD显示当前温度和设置温度
- ✅ LED状态指示

## 开发环境

- **IDE**: Keil uVision5
- **芯片**: STM32F103
- **调试工具**: J-Link

## 使用方法

1. 使用Keil uVision5打开 `USER/IIC.uvprojx` 工程文件
2. 编译并下载程序到STM32开发板
3. 通过按键设置目标温度
4. 系统将自动调节PID输出以维持目标温度

## 许可证

本项目仅供学习交流使用。
