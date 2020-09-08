#   Zipkin

##  what 

Zipkin 是一套分布式跟踪系统，他可以帮助手机时间数据，主要是解决分布式微服务架构下的延迟问题，它管理这些数据的收集和查找

> >  项目来源是Google Dapper论文

思想：每个应用向Zipkin报告定时数据，Zipkin UI 呈现了一个依赖图表展示了跟踪请求经过了每个应用程序，如果想解决延迟问题，可以过滤或者排序所有的跟踪请求。  

##   why

随着业务越来越复杂，系统也随之进行各种拆分，特别是随着微服务架构和容器技术的兴起，看似简单的一个应用，后台可能有几十个甚至几百个服务在支撑；一个前端的请求可能需要多次的服务调用最后才能完成；当请求变慢或者不可用时，我们无法得知是哪个后台服务引起的，这时就需要解决如何快速定位服务故障点，Zipkin分布式跟踪系统就能很好的解决这样的问题。

## how



span信息结构体

```
{
      "traceId": "bd7a977555f6b982",
      "name": "get-traces",
      "id": "ebf33e1a81dc6f71",
      "parentId": "bd7a977555f6b982",
      "timestamp": 1458702548478000,
      "duration": 354374,
      "annotations": [
        {
          "endpoint": {
            "serviceName": "zipkin-query",
            "ipv4": "192.168.1.2",
            "port": 9411
          },
          "timestamp": 1458702548786000,
          "value": "cs"
        }
      ],
      "binaryAnnotations": [
        {
          "key": "lc",
          "value": "JDBCSpanStore",
          "endpoint": {
            "serviceName": "zipkin-query",
            "ipv4": "192.168.1.2",
            "port": 9411
          }
        }
      ]
}
```

traceId：标记一次请求的跟踪，相关的Spans都有相同的traceId；

id：spanid 

name：span的名称，一般是接口方法的名称； 

parentId：可选的id，当前Span的父Span id，通过parentId来保证Span之间的依赖关系，如果没有parentId，表示当前Span为根Span；

timestamp：Span创建时的时间戳，使用的单位是微秒（而不是毫秒），所有时间戳都有错误，包括主机之间的时钟偏差以及时间服务重新设置时钟的可能性，出于这个原因，Span应尽可能记录其duration；

duration：持续时间使用的单位是微秒（而不是毫秒）；

annotations：注释用于及时记录事件；有一组核心注释用于定义RPC请求的开始和结束；

```
cs:Client Send，客户端发起请求；
sr:Server Receive，服务器接受请求，开始处理；
ss:Server Send，服务器完成处理，给客户端应答；
cr:Client Receive，客户端接受应答从服务器；
```

发送格式

1.  http
2.  kafka
3.  scribe

##  自定义格式规划

数据流逻辑图

新格式

![1596787331829](.\img\1596787331829.png)

旧格式

![1596787500902](.\img\1596787500902.png)



###  单链路-新格式

旧格式定义  

一级   

```
[{
      "traceId": "bd7a977555f6b982",
      "name": "traces-1",
      "id": "ebf33e1a81dc6f71",
      "timestamp": 1458702548478000,
      "duration": 100374
}]
```

MD-Center

```
[{
      "traceId": "bd7a977555f6b982",
      "name": "traces-2",
      "id": "ebf33e1a81dc6f72",
      "parentId": "ebf33e1a81dc6f71",
      "timestamp": 1458702548678000,
      "duration": 100374
}]
```

hub1   

```
[{
      "traceId": "bd7a977555f6b982",
      "name": "traces-3",
      "id": "ebf33e1a81dc6f73",
      "parentId": "ebf33e1a81dc6f72",
      "timestamp": 1458702548878000,
      "duration": 100374
}]
```

hub2 

```
[{
      "traceId": "bd7a977555f6b982",
      "name": "traces-4",
      "id": "ebf33e1a81dc6f74",
      "parentId": "ebf33e1a81dc6f73",
      "timestamp": 1458702549178000,
      "duration": 100345
}]
```

level1-new

```
[{
      "traceId": "bd7a977555f6b982",
      "name": "traces-5",
      "id": "ebf33e1a81dc6f75",
      "parentId": "ebf33e1a81dc6f74",
      "timestamp": 1458702549467000,
      "duration": 142374
}]
```

合并效果

```
[{
      "traceId": "bd7a977555f6b982",
      "name": "traces-1",
      "id": "ebf33e1a81dc6f71",
      "timestamp": 1458702548478000,
      "duration": 100374
},{
      "traceId": "bd7a977555f6b982",
      "name": "traces-2",
      "id": "ebf33e1a81dc6f72",
      "parentId": "ebf33e1a81dc6f71",
      "timestamp": 1458702548678000,
      "duration": 100374
},{
      "traceId": "bd7a977555f6b982",
      "name": "traces-3",
      "id": "ebf33e1a81dc6f73",
      "parentId": "ebf33e1a81dc6f72",
      "timestamp": 1458702548878000,
      "duration": 100374
},{
      "traceId": "bd7a977555f6b982",
      "name": "traces-4",
      "id": "ebf33e1a81dc6f74",
      "parentId": "ebf33e1a81dc6f73",
      "timestamp": 1458702549178000,
      "duration": 100345
},{
      "traceId": "bd7a977555f6b982",
      "name": "traces-5",
      "id": "ebf33e1a81dc6f75",
      "parentId": "ebf33e1a81dc6f74",
      "timestamp": 1458702549467000,
      "duration": 142374
}
]
```

扩展合并

```
 [{
      "traceId": "bd7a977555f6b989",
      "name": "hyunday",
      "id": "ebf33e1a81dc6f71",
      "timestamp": 1458702548478000,
      "duration": 100374,
      "localEndpoint":{
      	"serviceName": "marketdelay",
        "ipv4": "192.168.1.2",
        "port": 9411
      },
      "annotations": 
      [{
          "timestamp": 1458702548478000,
          "value": "cr"
        },{
          "timestamp": 1458702548678000,
          "value": "cs"
       }]
},{
      "traceId": "bd7a977555f6b989",
      "name": "traces-2",
      "id": "ebf33e1a81dc6f72",
      "parentId": "ebf33e1a81dc6f71",
      "timestamp": 1458702548678000,
      "duration": 100374
},{
      "traceId": "bd7a977555f6b989",
      "name": "traces-3",
      "id": "ebf33e1a81dc6f73",
      "parentId": "ebf33e1a81dc6f72",
      "timestamp": 1458702548878000,
      "duration": 100374
},{
      "traceId": "bd7a977555f6b989",
      "name": "traces-4",
      "id": "ebf33e1a81dc6f74",
      "parentId": "ebf33e1a81dc6f73",
      "timestamp": 1458702549178000,
      "duration": 100345
},{
      "traceId": "bd7a977555f6b989",
      "name": "traces-5",
      "id": "ebf33e1a81dc6f75",
      "parentId": "ebf33e1a81dc6f74",
      "timestamp": 1458702549467000,
      "duration": 142374
}
]          
```

