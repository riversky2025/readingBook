[原文 2.1.12版本](https://docs.spring.io/spring-kafka/docs/2.1.12.RELEASE/reference/html/)  
# 前言
Spring for Apache Kafka项目将核心Spring概念应用于基于Kafka的消息传递解决方案的开发。我们提供“模板”作为发送消息的高级抽象。我们还为消息驱动的POJO提供支持。  
# 新功能
1. Kafka版本需求(此版本需要1.0.0 kafka-clients或更高版本。)  
2. Json序列化与反序列化支持
3. 容器停止错误处理
4. 暂停与恢复容器(pause,resume)
5. 状态重试(2.1.3之后)
6. 客户端Id:(从2.1.1开始)现在可以设置client.id前缀@KafkaListener。以前，要自定义客户端ID，每个侦听器需要一个单独的使用者工厂（和容器工厂）。前缀后缀-n为在使用并发时提供唯一的客户端ID。  
7. 记录偏移量提交:从版本2.1.2开始，ContainerProperties调用了一个新属性commitLogLevel，允许您指定这些消息的日志级别。   
8. 默认的KafkaHandler
9. KafkaTemplate支持(2.1.3)  
10. ChainedKafkaTransactionManager(2.1.3)  
11. 事务Id
# 简介  
Spring for Apache Kafka的高级概述，以及可以尽快启动和运行的基础概念和一些代码片段。  
## 简单体验
依赖-maven
```
<dependency>
  <groupId>org.springframework.kafka</groupId>
  <artifactId>spring-kafka</artifactId>
  <version>2.1.12.RELEASE</version>
</dependency>
```
依赖
```
compile 'org.springframework.kafka:spring-kafka:2.1.12.RELEASE'
```
前提条件
```
Apache Kafka Clients 1.0.x or later (See note below)
Spring Framework 5.0.x
Minimum Java version: 8
```
## 发送接收数据测试

# 参考示例
# Stream支持
# 测试
# Spring集成