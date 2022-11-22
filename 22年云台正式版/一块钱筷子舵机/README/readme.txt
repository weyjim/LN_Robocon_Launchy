
使用 hobbywing_skywalker_40A 无刷电调

标准板为原子STM32F103ZET6精英版

PWM输出IO为PB5

注意电调与板子共地

！！！最大速转速过快引起安全问题！！！
	——>调试时注意安全

推荐使用周期 TIM3_PWM_Init(9999,50);

21.9.27 王恩缘 刘宇桐