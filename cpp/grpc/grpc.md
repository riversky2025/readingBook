# 1. 简介
gRPC  是一个高性能、开源和通用的 RPC 框架，面向移动和 HTTP/2 设计。目前提供 C、Java 和 Go 语言版本，分别是：grpc, grpc-java, grpc-go. 其中 C 版本支持 C, C++, Node.js, Python, Ruby, Objective-C, PHP 和 C# 支持.  
gRPC 基于 HTTP/2 标准设计，带来诸如双向流、流控、头部压缩、单 TCP 连接上的多复用请求等特。这些特性使得其在移动设备上表现更好，更省电和节省空间占用。  
# 2. 指南
## 2.1. 概览
### 2.1.1. 开始  
欢迎进入 gRPC 的开发文档，gRPC 一开始由 google 开发，是一款语言中立、平台中立、开源的远程过程调用(RPC)系统。  
本文档通过快速概述和一个简单的 Hello World 例子来向您介绍 gRPC 。你可以在本站发现更详细的教程和参考文档——文档将会越来越丰富  
### 2.1.2. 快速开始 
为了直观地着手运行 gRPC，可以从你所选择的语言对应的快速开始入手，里面包含创建这个列子的安装指导、快速上手指南等更多内容。  
* C++
* Java 
* Go
* Python
* Ruby
* Node.js
* Android Java
* C# 
* Objuceive-C
* PHP
你可以从[这里](https://github.com/grpc/grpc)找到 gRPC 的源码库。我们大多数例子都在源码库 examples 目录下。  
### 2.1.3. gRPC 是什么？
 在 gRPC 里客户端应用可以像调用本地对象一样直接调用另一台不同的机器上服务端应用的方法，使得您能够更容易地创建分布式应用和服务。与许多 RPC 系统类似，gRPC 也是基于以下理念：定义一个服务，指定其能够被远程调用的方法（包含参数和返回类型）。在服务端实现这个接口，并运行一个 gRPC 服务器来处理客户端调用。在客户端拥有一个存根能够像服务端一样的方法。  
 ![](./img/grpc_concept_diagram_00.png)  
 gRPC 客户端和服务端可以在多种环境中运行和交互 - 从 google 内部的服务器到你自己的笔记本，并且可以用任何 gRPC 支持的语言来编写。所以，你可以很容易地用 Java 创建一个 gRPC 服务端，用 Go、Python、Ruby 来创建客户端。此外，Google 最新 API 将有 gRPC 版本的接口，使你很容易地将 Google 的功能集成到你的应用里。  
 **使用 protocol buffers**  
 gRPC 默认使用 protocol buffers，这是 Google 开源的一套成熟的结构数据序列化机制（当然也可以使用其他数据格式如 JSON）。正如你将在下方例子里所看到的，你用 proto files 创建 gRPC 服务，用 protocol buffers 消息类型来定义方法参数和返回类型。你可以在 [Protocol Buffers 文档](http://doc.oschina.net/https%EF%BC%9A//developers.google.com/protocol-buffers/docs/overview)找到更多关于 Protocol Buffers 的资料。  
 **Protocol buffers 版本** 
 尽管 protocol buffers 对于开源用户来说已经存在了一段时间，例子内使用的却一种名叫 proto3 的新风格的 protocol buffers，它拥有轻量简化的语法、一些有用的新功能，并且支持更多新语言。当前针对 Java 和 C++ 发布了 beta 版本，针对 JavaNano（即 Android Java）发布 alpha 版本，在protocol buffers Github 源码库里有 Ruby 支持， 在golang/protobuf Github 源码库里还有针对 Go 语言的生成器， 对更多语言的支持正在开发中。 你可以在 proto3 语言指南里找到更多内容， 在与当前默认版本的发布说明比较，看到两者的主要不同点。更多关于 proto3 的文档很快就会出现。虽然你可以使用 proto2 (当前默认的 protocol buffers 版本)， 我们通常建议你在 gRPC 里使用 proto3，因为这样你可以使用 gRPC 支持全部范围的的语言，并且能避免 proto2 客户端与 proto3 服务端交互时出现的兼容性问题，反之亦然。  
### 2.1.4. 你好 gRPC!  
 现在你已经对 gRPC 有所了解，了解其工作机制最简单的方法是看一个简单的例子。 Hello World 将带领你创建一个简单的客户端——服务端应用，向你展示：  
 * 通过一个 protocol buffers 模式，定义一个简单的带有 Hello World 方法的 RPC 服务。  
 * 用你最喜欢的语言(如果可用的话)来创建一个实现了这个接口的服务端。  
 * 用你最喜欢的(或者其他你愿意的)语言来访问你的服务端。  

这个例子完整的代码在我们 GitHub 源码库的 examples 目录下。  
我们使用 Git 版本系统来进行源码管理，但是除了如何安装和运行一些 Git 命令外，你没必要知道其他关于 Git 的任何事情。  
需要注意的是，并不是所有 gRPC 支持的语言都可以编写我们例子的服务端代码，比如 PHP 和 Objective-C 仅支持创建客户端。  
比起针对于特定语言的复杂教程，这更像是一个介绍性的例子。你可以在本站找到更有深度的教程，gRPC 支持的语言的参考文档很快就会全部开放。  
### 2.1.5. 准备  
本节解释了如何在你本机上准备好例子代码的运行环境。如果你只是想读一下例子，你可以直接到下一步。   
**安装 Git**  
你可以从http://git-scm.com/download下载和安装 Git。安装好 Git 后，你应该能访问 git 命令行工具。你需要的主要命令如下：  
*  git clone ... ： 从远程代码库克隆一份到本机。  
*  git checkout ... ： 检出一个特殊分支或一个标签版本的代码来改进。  
**安装 gRPC**  
针对你选择的语言构建和安装 gRPC 插件和相关工具，可以参照[快速开始](http://doc.oschina.net/grpc?t=58008#quickstart)。 Java gRPC 除了 JDK 外不需要其他工具。

**获得源码**  
例子代码在 GitHub 源码库的 examples 目录。你可以运行如下命令克隆源码到本地：  
`git clone https：//github.com/grpc/grpc-java.git`    
1. java     
切换当前目录到grpc-java/examples  
`cd grpc-java/examples`  
2. C++  
切换当前目录到 examples/cpp/helloworld  
`$ cd examples/cpp/helloworld/`  
3. python  
切换当前目录到 examples/python/helloworld  
`$ cd examples/python/helloworld/`
4. Go  
获取例子：  
```
$ go get -u github.com/grpc/grpc-go/examples/helloworld/greeter_client
$ go get -u github.com/grpc/grpc-go/examples/helloworld/greeter_server
```
切换当前目录到 examples/helloworld   
5. Node.js
切换当前目录到 examples/node ， 接着安装包依赖：  
```
$ cd examples/node
$ npm install
```
### 2.1.6. 定义服务
创建我们例子的第一步是定义一个服务：一个 RPC 服务通过参数和返回类型来指定可以远程调用的方法。就像你在 概览 里所看到的， gRPC 通过 protocol buffers 来实现。  
我们使用 protocol buffers 接口定义语言来定义服务方法，用 protocol buffer 来定义参数和返回类型。客户端和服务端均使用服务定义生成的接口代码。  
```
syntax="proto3"  
option java_package="io.grpc.example"
package helloworld;
//服务定义
service Greeter{
    rpc SayHello(HelloRequest) returns(HelloReply){}
}
message HelloRequest{
    string name=1;
}
message HelloReply{
    string message=1;
}
```
这里Greeter服务有一个方法SayHello,可以让服务端从远程客户端接收一个包含用户名HelloRequest消息后,在一个HelloReply里发送回一个Greeter,这里你可以在gRPC里指定最简单的RPC
### 2.1.7. 生成gRPC代码
一旦定义好服务，我们可以使用 protocol buffer 编译器 protoc 来生成创建应用所需的特定客户端和服务端的代码 - 你可以生成任意 gRPC 支持的语言的代码，当然 PHP 和 Objective-C 仅支持创建客户端代码。生成的代码同时包括客户端的存根和服务端要实现的抽象接口，均包含 Greeter 所定义的方法。  
(假如你没有在系统里安装 gRPC 插件和 protoc ，并且仅仅是要看一下这个例子，你可以跳过这一步，直接到下一步来查看生成的代码。)  
**Java**  
这个例子的构建系统也是 Java gRPC 本身构建的一部分 —— 为了简单起见，我们推荐使用我们事先生成的例子代码。你可以参考 README 来看一下如何从你自己的 .proto 文件生成代码。  这个例子事先生成的代码在 src/generated/main下。  
以下类包含所有我们需要创建这个例子所有的代码：  
* HelloRequest.java HelloResponse.java是解析和填充 protocol buffer 数据的
* GreeterGrpc.java, Greeter 服务端需要实现的接口
服务端需要实现的接口
```
public static interface Greeter{
    public void sayHello(Helloworld.HelloRequest request,StreamObserver<Helloword.HelloReply> responseObserver);
}
```
客户端用来与Greeter服务端进行对话存根类如下
```
public static class GreeterStub extends AbstractStub<GreeterStub> implements Greeter{}
```
**C++**  
生成客户端和服务端接口，运行：  
```
make helloworld.grpc.pb.cc helloworld.pb.cc
```
这从内部调用 protocol buffer 编译器：  
```
protoc -I ../../protos/ --grpc_out . --plugin=protoc-gen-grpc=grpc_cpp_plugin ../../protos/helloworld.proto
protoc -I ../../protos/ --cpp_out. ../../protos/helloworld.proto
```
生成结果  
helloworld.pb.h 声明了用于填充、序列化、提取 HelloRequest 和 HelloResponse 消息类型的类，并且还有它的实现 helloworld.pb.cc .  
helloworld.grpc.pb.h，声明了我们生成的服务类和它的实现 helloworld.grpc.pb.cc.  
**Python**  
可以用如下命令生成客户端和服务端：  
`$./run_codegen.sh`  
这内部调用 protocol buffer 编译器：  
```
protoc -I ../../protos --python_out . --grpc_out. --plugin=protoc-gen-grpc=`which grpc_python_plugin` ../../protos/helloworld.proto 
```
这生成了 helloworld_pb2.py ，包含我们生成的客户端和服务端类，此外还有用于填充、序列化、提取 HelloRequest 和 HelloResponse 消息类型的类。  
**Go**  
为了生成客户端和服务端接口，运行 protocol buffer 编译器：  
```
protoc -I ../protos ../protos/helloworld.proto --go_out=plugins=grpc：helloworld
```
**NodeJs**  
Node.js库从运行时加载的 .proto 文件动态生成服务描述和客户端存根的定义，所以使用此语言时没必要生成任何特殊代码。而是在例子客户端和服务端里，我们 require gRPC 库，然后用它的 load() 方法： 
``` 
var grpc = require('grpc');
var hello_proto = grpc.load(PROTO_PATH).helloworld;  
```  
### 2.1.8. 写一个服务器
现在让我们写点代码！首先我们将创建一个服务应用来实现服务(你会记起来，我们可以是使用除了Objective-C and PHP 外的其他所有语言来实现)。在本节，我们不打算对如何创建一个服务端进行更深入地探讨 —— 更详细的信息可以在你选择语言对应的教程里找到。  
 
#### 2.1.8.1. Java
正如你所见，GreeterImpl 类通过实现 sayHello 方法，实现了从 proto_gen_rpc中生成的GreeterGrpc.Greeter 接口 。  
```
@override
public void sayHello(HelloRequest req,StreamObserver<HelloReply> responseObserver){
    HelloReply reply=HelloReply.newBuilder().setMesssage("Hello"+req.getName()).build();//构建消息
    responseObserver.onNext(reply);//发送
    responseObserver.onCompleted();//表明发送完毕
}
```
服务提供代码:
```
private int port=50051;
private Server server;
private void start()throws Exception{
    server=ServerBuilder.forPort(port)
         .addService(GreeterGrpc.bindService(new GreeterImpl))
         .build()
         .start();
    logger.info("Server started,listening on "+port);
    Runtime.getRuntime().addShutdownHook(new Thread(()->{
        System.err.println("*** shutting down gRPC server since JVM is shutting down");
        HelloWorldServer.this.stop();
        System.err.println("*** server shut down");
    }));
}
```
#### 2.1.8.2. C++
通过实现Gretter::Service接口中的sayHello方法的类GreeterServiceImpl达到目的
```
class GreeterServiceImpl final:public Greeter::Service{
    Status SayHello(ServerContext* context,const HelloRequest* request,HelloReply* reply)override{
        std::string prefix("hello");
        reply->set_message(prefix+request->name());
        return Status::Ok;
    }
}
```
服务提供代码:  
```
void Runerver(){
    std::string server_address("0.0.0.0:50051");
    GreeterServiceImpl service;
    ServerBuilder builder;
    builder.AddListeningPort(server_address,grpc::InsecureServerCredentials());
    builder.RegisterService(&server);
    std::unique_ptr<Server> server(builder.BuilderAndStart());
    std::cout<<"Server listening on"<<server_address<<std::endl;
    server->Wait();
}
```
#### 2.1.8.3. Python  
服务端通过实现helloworld_pb2.BetaGreeterServicer中的sayHello方法的Greeter类进行实现
```
class Greeter(helloworld_pd2.BetaGreeterServicer):
def SayHello(self,request,context):
    return helloworld_pd2.HelloReply(message="hello,%s" % request.name)
```
服务提供代码:  
```
server=helloworld_pd2.beta_create_Greeter_server(Greeter())
server.add_insecure_port("[::]:50051")
server.start()
try:
    while True:
        time.sleep(_ONE_DAY_IN_SECONDS)
except KeybordInterrupt:
    server.stop()
```
#### 2.1.8.4. Go
通过实现从proto生成的GreeterServer接口中的sayHello实现
```
type server struct{}
func (s* server) SayHello(ctx context.Context,in * pd.HelloRequest)(* pb.HelloReply,error){
    return &pb.HelloReply{Message:"hello"+in.Name},nil
}
```
服务提供代码:  
```
const(
    port=":50051"
)
func main(){
    lis,err:=net.Listen("tcp",port)
    if err!=nil{
        log.Fatalf("failed to listen: %v",err)
    }
    s:=grpc.NewSever()
    pb.RegisterGreeterServer(s,&server{})
    s.Serve(lis)
}
```
在这里我们创建了合理的 gRPC 服务器，将我们实现的 Greeter 服务绑定到一个端口。然后我们启动服务器：服务器现在已准备好从 Greeter 服务客户端接收请求。我们将在具体语言对应的文档里更深入地了解这所有的工作是怎样进行的。  
### 2.1.9. 写一个客户端
客户端的 gRPC 非常简单。在这一步，我们将用生成的代码写一个简单的客户程序来访问我们在上一节里创建的 Greeter 服务器。  
#### 2.1.9.1. Java 
```
private final ManagedChannel channel;
private final GreeterGrpc.GreeterBlockingStub blockingStub;
public HelloWorldClient(String host,int port){
    channel =ManagedChannelBuilder.forAddress(host,port)
        .usePlaintext(true)
        .build();
    blockingStub=GreeterGrpc.newBlockingStub(channel);
}
```
在这个例子里，我们创建了一个阻塞的存根。这意味着 RPC 调用要等待服务器应答，将会返回一个应答或抛出一个异常。 gRPC Java 还可以有其他种类的存根，可以向服务器发出非阻塞的调用，这种情况下应答是异步返回的。  
#### 2.1.9.2. C++
```
int main(int argc,char** argv){
    GreeterClient greeter(grpc::CreateChannel("localhost:50015",grpc::InsecureCredentials(),ChannelArguments()));
}
class GreeterClient{
public:
    GreeterClient(std::shared_ptr<ChannelInterface> channel):stub_(Greeter::NewStub(channel)){}
private:
    std::unique_ptr<Greeter::Stub> stub_;
}
```
## 2.2. gRPC概念  
本文档通过对于 gRPC 的架构和 RPC 生命周期的概览来介绍 gRPC 的主要概念。本文是在假设你已经读过文档部分的前提下展开的。针对具体语言细节请查看对应语言的快速开始、教程和参考文档（很快就会有完整的文档）。  
### 2.2.1. 概览
#### 2.2.1.1. 服务定义  
正如其他 RPC 系统，gRPC 基于如下思想：定义一个服务， 指定其可以被远程调用的方法及其参数和返回类型。gRPC 默认使用 protocol buffers 作为接口定义语言，来描述服务接口和有效载荷消息结构。如果有需要的话，可以使用其他替代方案。  
```
service HelloService{
    rpc SayHello(HelloRequest) returns (HelloResponse);
}
message HelloRequest{
    requited string greeting=1;
}
message HelloResponse{
    required string reply=1;
}
```
**grpc 允许定义的四类服务方法**  
* 单项RPC,即客户端发送一个请求给服务端,从服务端获取一个应答,就像一次普通的函数调用
```
rpc SayHello(HelloRequest) returns(HelloResponse){}
```
* 服务端流式RPC,即客户端发送一个请求给服务端，可获取一个数据流用来读取一系列消息。客户端从返回的数据流里一直读取直到没有更多消息为止。  
```
rpc LotsOfReplies(HelloRequest) returns(stream Helloresponse){}
```
* 客户端流式RPC,即客户端用提供的一个数据流写入并发送一系列消息给服务端.一旦客户端完成消息写入,就等待服务端读取这些消息并返回应答  
```
rpc LosOfGreetings(stream HelloRequest) return (HelloResponse)
```
* 双向流式 RPC，即两边都可以分别通过一个读写数据流来发送一系列消息。这两个数据流操作是相互独立的，所以客户端和服务端能按其希望的任意顺序读写，例如：服务端可以在写应答前等待所有的客户端消息，或者它可以先读一个消息再写一个消息，或者是读写相结合的其他方式。每个数据流里消息的顺序会被保持。
  
```
rpc BidiHello(stream HelloRequest) returns(stream HelloResponse){}
```
### 2.2.2. 使用 API 接口  

## 2.3. 安全认证
## 2.4. 通讯协议  
# 3. 教程
