# 简介
微服务中高性能的rpc-java方案主流的有grpc,dubbo.融入spring cloud项目是罪普遍的选择.
## 概述
非主流微服务架构解决方案 Spring Cloud Alibaba + Dubbo + Vue，该章节为拓展章节，主要目的是想实现之前在视频里说的对内 RPC，对外 REST 并利用 Vue Element Admin 实现一个相对完整的前后分离效果。  
## 目标  
Spring Cloud Alibaba Dubbo 项目的目标是将 Dubbo 融入到 Spring Cloud Alibaba 生态中，使微服务之间的调用同时具备 RESTful 和 Dubbo 调用的能力。做到对业务代码无侵入，无感知；引入 JAR 包则微服务间调用使用 Dubbo，去掉 JAR 包则使用默认的 RESTful  
## Nacos  
