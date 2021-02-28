# fast-experiments
该框架可快速进行网络离线实验。

使用方法：
1. 新建类继承BaseScheme，重写BaseScheme中的start方法和getResultHeader方法，start是你的方案，getResultHeader是你输出结果的头部目录
2. 新建类继承FastExperiment，重写其createScheme方法，返回你自己的Scheme方案对象
3. 在fast-experimentsDlg.cpp中设置initData、initUserConfig、createFastExperiment方法。
