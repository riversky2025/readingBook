[官网文档2.2](http://kafka.apache.org/documentation/)  
# 1. 入门
## 1.1. 简介
TODO:
## 1.2. 用例
TODO: 
## 1.3. 快速Start
本教程假设您刚刚开始并且没有现有的Kafka或ZooKeeper数据。由于Kafka控制台脚本对于基于Unix和Windows的平台是不同的，因此在Windows平台上使用bin\windows\而不是bin/将脚本扩展名更改为.bat。   
1. 下载源码
2. 启动Zookeeper ` bin/zookeeper-server-start.sh config/zookeeper.properties`
3. 启动Kafka `bin/kafka-server-start.sh config/server.properties`  
4. 创建主题  
```
bin/windows/kafka-topics.bat --create --bootstrap-server localhost:9092  --replication-factor 1 --partitions 1 --topic test

./bin/windows/kafka-topics.bat --list --bootstrap-server localhost:9092
```
5. 发送一些消息
```
bin/windows/kafka-console-producer.bat --broker-list localhost:9092 --topic test

```
6. 启动消费者
Kafka还有一个命令行使用者，它会将消息转储到标准输出。  
```
bin/windows/kafka-console-consumer.bat --bootstrap-server localhost:9092 --topic test --from-beginning
```
7. 设置集群
8. 使用KafkaConnect 导入/导出数据
9. 使用KafkaStreams处理数据
Kafka Streams是一个客户端库，用于构建任务关键型实时应用程序和微服务，其中输入和/或输出数据存储在Kafka集群中。Kafka Streams结合了在客户端编写和部署标准Java和Scala应用程序的简单性以及Kafka服务器端集群技术的优势，使这些应用程序具有高度可扩展性，弹性，容错性，分布式等等。本快速入门示例将演示如何运行在此库中编码的流应用程序。 
```
// Serializers/deserializers (serde) for String and Long types
final Serde<String> stringSerde = Serdes.String();
final Serde<Long> longSerde = Serdes.Long();
 
// Construct a `KStream` from the input topic "streams-plaintext-input", where message values
// represent lines of text (for the sake of this example, we ignore whatever may be stored
// in the message keys).
KStream<String, String> textLines = builder.stream("streams-plaintext-input",
    Consumed.with(stringSerde, stringSerde);
 
KTable<String, Long> wordCounts = textLines
    // Split each text line, by whitespace, into words.
    .flatMapValues(value -> Arrays.asList(value.toLowerCase().split("\\W+")))
 
    // Group the text words as message keys
    .groupBy((key, value) -> value)
 
    // Count the occurrences of each word (message key).
    .count()
 
// Store the running counts as a changelog stream to the output topic.
wordCounts.toStream().to("streams-wordcount-output", Produced.with(Serdes.String(), Serdes.Long()));
```   
## 1.4. 生态
## 1.5. 升级
# 2. Api
# 3. 配置
# 4. 设计
# 5. 实施
# 6. 运营
# 7. 安全
# 8. 概念
# 9. Kafka流