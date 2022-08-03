# Http API 接口中文文档

本文档用于通过http接口获取spate的数据。此数据可以应用于自动化测试框架。

若需要开启HTTP API支持，需要在spate的配置文件做配置，举例如下：

```shell
# 使能 Spate 的 http 配置
http.enable      = 1
# spate启动http服务器监听的地址
http.listen_ip   = 127.0.0.1
# spate启动http服务器监听的端口
http.listen_port = 9000
```



## 获取traffic信息接口

spate client 会记录每秒的数据,例如发送了多少包，收到了多少包，RTT等信息，可以通过http接口动态获取这些信息。

- **查询当前总计多少数据**

  接口：

  ```shell
  curl  "http://127.0.0.1:9000/stat/current_total"
  ```

  返回举例：

  ```json
  {
  	"Error": 0,
  	"Total": 97,
  	"Max": 1200
  }
  ```

  其中Max表示总共可以存储多少时间数据（它是写在配置文件中的）。
  Total表示spate运行到现在,总共产生了多少秒的数据。

- **查询指定时间段数据**

  接口：

  ```shell
  # 查询最近的几秒数据,uri参数count表示需要查的几秒,下面表示查询最近的2秒数据
  curl  "http://127.0.0.1:9000/stat/history_last?count=2"
  
  # 查询范围数据，下面表示查询从第4到第10秒数据，此处是 [ ) 区间，即前闭后开
  curl  "http://127.0.0.1:9000/stat/history_range?begin=4&end=10"
  
  # 备注: 上面2种接口本质是一个类型，都是返回 [ ) 这一段时间的数据
  ```

  返回举例：

  ```json
  {
  	"Error": 0,
  	"Begin": 45,
  	"End": 46,
  	"Traffic": {
  		"rx": 10000,
  		"tx": 10000,
  		"rtt_mean": 0.112,
  		"rtt_standard_deviation": 0.429874,
  		"tp_50": 0.075,
  		"tp_90": 0.085,
  		"tp_95": 0.095,
  		"tp_99": 0.150,
  		"tx_busy": 0,
  		"rx_bugs": 0
  	}
  }
  ```
  
  其中 rtt_mean 表示这组数据的平均RTT（即期望值）。
  
  rtt_standard_deviation 是这组数据RTT的标准差（用于衡量延迟波动性）。
  
  tp_50等数据即TP50，所有关于延迟的数据单位都是ms。
  
  

## 控制spate参数

* **修改pps**

  通过http API 修改per_worker_pps。

  接口：

  ```shell
  curl  "http://127.0.0.1:9000/change_pps_per_worker?pps=10000"
  ```

  返回举例：

  ```shell
  {
  	"Error": 0,
  	"pps": 10000
  }
  ```

