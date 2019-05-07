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
gRPC 提供 protocol buffer 编译插件，能够从一个服务定义的 .proto 文件生成客户端和服务端代码。通常 gRPC 用户可以在服务端实现这些API，并从客户端调用它们。  
* 在服务侧，服务端实现服务接口，运行一个 gRPC 服务器来处理客户端调用。gRPC 底层架构会解码传入的请求，执行服务方法，编码服务应答。  
* 在客户侧，客户端有一个存根实现了服务端同样的方法。客户端可以在本地存根调用这些方法，用合适的 protocol buffer 消息类型封装这些参数— gRPC 来负责发送请求给服务端并返回服务端 protocol buffer 响应。  
### 2.2.3. 同步 vs 异步  
同步 RPC 调用一直会阻塞直到从服务端获得一个应答，这与 RPC 希望的抽象最为接近。另一方面网络内部是异步的，并且在许多场景下能够在不阻塞当前线程的情况下启动 RPC 是非常有用的。  
在多数语言里，gRPC 编程接口同时支持同步和异步的特点。你可以从每个语言教程和参考文档里找到更多内容(很快就会有完整文档)。  
### 2.2.4. RPC 生命周期  
现在让我们来仔细了解一下当 gRPC 客户端调用 gRPC 服务端的方法时到底发生了什么。我们不究其实现细节，关于实现细节的部分，你可以在我们的特定语言页面里找到更为详尽的内容。  
**单项RPC**  
首先我们来了解一下最简单的 RPC 形式：客户端发出单个请求，获得单个响应。  
* 一旦客户端通过桩调用一个方法，服务端会得到相关通知 ，通知包括客户端的元数据，方法名，允许的响应期限（如果可以的话）  
* 服务端既可以在任何响应之前直接发送回初始的元数据，也可以等待客户端的请求信息，到底哪个先发生，取决于具体的应用。  
* 一旦服务端获得客户端的请求信息，就会做所需的任何工作来创建或组装对应的响应。如果成功的话，这个响应会和包含状态码以及可选的状态信息等状态明细及可选的追踪信息返回给客户端 。  
* 假如状态是 OK 的话，客户端会得到应答，这将结束客户端的调用。  

**服务端流式RPC**  
服务端流式 RPC 除了在得到客户端请求信息后发送回一个应答流之外，与我们的简单例子一样。在发送完所有应答后，服务端的状态详情(状态码和可选的状态信息)和可选的跟踪元数据被发送回客户端，以此来完成服务端的工作。客户端在接收到所有服务端的应答后也完成了工作。  

**客户端流式RPC**  
客户端流式 RPC 也基本与我们的简单例子一样，区别在于客户端通过发送一个请求流给服务端，取代了原先发送的单个请求。服务端通常（但并不必须）会在接收到客户端所有的请求后发送回一个应答，其中附带有它的状态详情和可选的跟踪数据。  
**双向流式 RPC**  
双向流式 RPC ，调用由客户端调用方法来初始化，而服务端则接收到客户端的元数据，方法名和截止时间。服务端可以选择发送回它的初始元数据或等待客户端发送请求。  
下一步怎样发展取决于应用，因为客户端和服务端能在任意顺序上读写 - 这些流的操作是完全独立的。例如服务端可以一直等直到它接收到所有客户端的消息才写应答，或者服务端和客户端可以像"乒乓球"一样：服务端后得到一个请求就回送一个应答，接着客户端根据应答来发送另一个请求，以此类推。  
**截止时间**  
gRPC 允许客户端在调用一个远程方法前指定一个最后期限值。这个值指定了在客户端可以等待服务端多长时间来应答，超过这个时间值 RPC 将结束并返回DEADLINE_EXCEEDED错误。在服务端可以查询这个期限值来看是否一个特定的方法已经过期，或者还剩多长时间来完成这个方法。  
各语言来指定一个截止时间的方式是不同的 - 比如在 Python 里一个截止时间值总是必须的，但并不是所有语言都有一个默认的截止时间。  
**RPC终止**  
在 gRPC 里，客户端和服务端对调用成功的判断是独立的、本地的，他们的结论可能不一致。这意味着，比如你有一个 RPC 在服务端成功结束("我已经返回了所有应答!")，到那时在客户端可能是失败的("应答在最后期限后才来到!")。也可能在客户端把所有请求发送完前，服务端却判断调用已经完成了。  
**取消RPC**  
无论客户端还是服务端均可以再任何时间取消一个 RPC 。一个取消会立即终止 RPC 这样可以避免更多操作被执行。它不是一个"撤销"， 在取消前已经完成的不会被回滚。当然，通过同步调用的 RPC 不能被取消，因为直到 RPC 结束前，程序控制权还没有交还给应用。  
**元数据集**  
元数据是一个特殊 RPC 调用对应的信息(授权详情]) ，这些信息以键值对的形式存在，一般键的类型是字符串，值的类型一般也是字符串(当然也可以是二进制数据)。元数据对 gRPC 本事来说是不透明的 - 它让客户端提供调用相关的信息给服务端，反之亦然。  
对于元数据的访问是语言相关的。  
**Channel**  
gRPC通道提供与指定主机和端口上的gRPC服务器的连接，并在创建客户端存根（或某些语言中的“客户端”）时使用。客户端可以指定通道参数来修改gRPC的默认行为，例如打开和关闭消息压缩。通道具有状态，包括已连接和空闲。  
gRPC如何处理关闭渠道与语言有关。某些语言还允许查询通道状态。  
## 2.3. 安全认证
本文档概述了gRPC身份验证，包括我们内置的支持身份验证机制，如何插入您自己的身份验证系统，以及如何在我们支持的语言中使用gRPC身份验证的示例。  
### 2.3.1. 简介
对于外部系统的交互就需要安全支持,例如您可以使用我们支持的机制 - 带或不带基于Google令牌的身份验证的SSL / TLS - 或者您可以通过扩展我们提供的代码来插入您自己的身份验证系统.  
RPC还提供了一个简单的身份验证API，允许您在创建channel或调用时提供所有必要的身份验证信息作为凭据。  
### 2.3.2. 支持机制  
* SSL/TLS : 
* 使用Google进行基于令牌的身份验证(OAuth2令牌)  
### 2.3.3. 认证API 
gRpc提供了一个简单的基于证书对象的统一认证概念(当在产生gRPC channel或者单个调用时)  
整数类型:
* Channel 证书(SSL证书)
* 调用证书(C++ ClientContext)
**使用客户端SSL / TLS**  
现在让我们看看Credentials如何使用我们支持的auth机制之一 ,是最简单的身份验证方案，客户端只想验证服务器并加密所有数据. 该示例使用的是C ++，但所有语言的API都类似：您可以在下面的示例部分中看到如何在更多语言中启用SSL / TLS  
```
// 生成证书
auto channel_creds =grpc::SslCredentials(grpc::SslCredentialsOptions());
//产生一个带证书的Channel
auto channel=grpc::CreateChannel(server_name,channel_creds);
//产生一个存根
std::unique_ptr<Greeter::Stub> stub(Greeter::NewStub(channel));
grpc::Status s=sutb->sayHello(&context,* request,response);
```
对于高级用例，例如修改根CA或使用客户端证书，可以在传递给工厂方法的SslCredentialsOptions参数中设置相应的选项。  
**使用基于Google令牌的身份验证**  
```
auto creds=grpc::GoogleDefaultCredentials();
auto channel=grpc::CreateChannel(server_name,creds);
std::unique_ptr<Greeter::Stub> stub(Greeter::NewStub(channel));
grpc::Statuc s=stub->sayHello(&context,*request,response);
```
**扩展gRPC以支持其他身份验证机制**  
Credentials插件API允许开发人员插入他们自己的凭据类型。这包括：  
* 创建自己的证书插件:实现grpc::MetadataCredentialsPlugin的GetMetadata方法.  
* 创建调用凭证:MetadataCredentialsFromPlugin 方法可以从 MetadataCredentialsPlugin 创建一个 调用者凭证  
```
class MyCustomAuthenticator:public grpc::MetadataCredentialsPlugin{
public:
    MyCustomAuthenticator(const grpc::string& ticket):ticket_(ticket){}  
    grpc::Status GetMetadata(grpc::string_ref service_url,grpc::string_ref method_name,const grpc::AuthContext& channel_auth_context,std::multimap<grpc::string,grpc::string>* metadata)override{
        metadata->insert(std::make_pair("x-custom-auth-ticket",ticket_))
        return grpc::Status::Ok;
    }
private:
    grpc::string ticket_;
}
auto call_creds=grpc::MetadataCredentialsFromPlugin(std::unique_ptr<grpc::MetadataCredentialsPlugin>(new MyCustomAuthenticator("super-secret-ticket")));
```
更深层次的集成可以通过在将 gRPC 的凭证实现以插件的形式集成进核心层。gRPC 内部也允许用其他加密机制来替换 SSL/TLS 。  
### 2.3.4. 各语言实现
这些身份验证机制将以所有gRPC支持的语言提供。以下部分演示了如何在每种语言中显示上述身份验证和授权功能：即将推出更多语言。  
#### 2.3.4.1. Go
未加密:
```
Client :
        conn,_:=grpc.Dial("localhost:50051",grpc.WithInsecure())
        client:=pd.NewGreeterClient(conn)
Server :
        s:=grpc.NewServer()
        lis,_:=net.Listen("tcp","localhost:50051")
        s.Serve(lis)
```
加密:  
```
client: 
        creds, _ := credentials.NewClientTLSFromFile(certFile, "")
        conn, _ := grpc.Dial("localhost:50051", grpc.WithTransportCredentials(creds))
        // error handling omitted
        client := pb.NewGreeterClient(conn)
Server:  
        creds, _ := credentials.NewServerTLSFromFile(certFile, keyFile)
        s := grpc.NewServer(grpc.Creds(creds))
        lis, _ := net.Listen("tcp", "localhost:50051")
        // error handling omitted
        s.Serve(lis)
```
#### 2.3.4.2. C++ 
未加密: 
```
auto channel = grpc::CreateChannel("localhost:50051", InsecureChannelCredentials());
std::unique_ptr<Greeter::Stub> stub(Greeter::NewStub(channel));
```
加密:  
```
auto channel_creds = grpc::SslCredentials(grpc::SslCredentialsOptions());
auto channel = grpc::CreateChannel("myservice.example.com", channel_creds);
std::unique_ptr<Greeter::Stub> stub(Greeter::NewStub(channel));
```
#### 2.3.4.3. Java
未加密
```
ManagedChannel channel = ManagedChannelBuilder.forAddress("localhost", 50051)
    .usePlaintext(true)
    .build();
GreeterGrpc.GreeterStub stub = GreeterGrpc.newStub(channel);
```
在Java中，我们建议您在使用gRPC over TLS时使用OpenSSL。您可以在gRPC Java安全性文档中找到有关安装和使用OpenSSL以及Android和非Android Java所需的其他库的详细信息  
要在服务器上启用TLS，需要以PEM格式指定证书链和私钥。这样的私钥不应该使用密码。链中的证书顺序很重要：更具体地说，顶部的证书必须是主机CA，而最底部的证书必须是根CA.标准TLS端口是443，但我们使用下面的8443以避免需要操作系统的额外权限。   
```
Server server = ServerBuilder.forPort(8443)
    // Enable TLS
    .useTransportSecurity(certChainFile, privateKeyFile)
    .addService(TestServiceGrpc.bindService(serviceImplementation))
    .build();
server.start();
``` 
如果客户端不知道颁发证书颁发机构，则应分别向NettyChannelBuilder或OkHttpChannelBuilder提供正确配置的SslContext或SSLSocketFactory。  
在客户端，使用SSL / TLS的服务器身份验证如下所示：  
```
// With server authentication SSL/TLS
ManagedChannel channel = ManagedChannelBuilder.forAddress("myservice.example.com", 443)
    .build();
GreeterGrpc.GreeterStub stub = GreeterGrpc.newStub(channel);

// With server authentication SSL/TLS; custom CA root certificates; not on Android
ManagedChannel channel = NettyChannelBuilder.forAddress("myservice.example.com", 443)
    .sslContext(GrpcSslContexts.forClient().trustManager(new File("roots.pem")).build())
    .build();
GreeterGrpc.GreeterStub stub = GreeterGrpc.newStub(channel);
```
## 2.4. 错误处理与调试  
此页面描述了gRPC如何处理错误，包括gRPC的内置错误代码。可以在此处找到不同语言的示例代码  
### 2.4.1. 错误模型  
如果发生错误，gRPC会返回其错误状态代码之一，并带有可选的字符串错误消息，该消息提供有关所发生情况的更多详细信息。所有支持的语言中的gRPC客户端都可以使用错误信息。  
### 2.4.2. 错误状态代码
gRPC在各种情况下引发错误，从网络故障到未经认证的连接，每个连接都与特定的状态代码相关联。所有gRPC语言都支持以下错误状态代码。  
#### 2.4.2.1. 一般错误
| 说明                                                              | Status code                   |
| :---------------------------------------------------------------- | :---------------------------- |
| 客户端应用程序取消了请求                                          | GRPC_STATUS_CANCELLED         |
| 调用超时                                                          | GRPC_STATUS_DEADLINE_EXCEEDED |
| 没有发现该方法                                                    | GRPC_STATUS_UNIMPLEMENTED     |
| 服务关闭                                                          | GRPC_STATUS_UNAVAILABLE       |
| 服务器抛出异常（或者做了除了返回状态代码以终止RPC之外的其他操作） | GRPC_STATUS_UNKNOWN           |

#### 2.4.2.2. 网络错误
| 说明                                                                                           | Status code                   |
| :--------------------------------------------------------------------------------------------- | :---------------------------- |
| 在截止日期到期之前没有传输数据。也适用于在截止日期到期之前传输某些数据且未检测到其他故障的情况 | GRPC_STATUS_DEADLINE_EXCEEDED |
| 在连接中断之前传输了一些数据（例如，请求元数据已写入TCP连接）                                  | GRPC_STATUS_UNAVAILABLE       |
#### 2.4.2.3. 协议错误  
| 说明                               | Status code                    |
| :--------------------------------- | :----------------------------- |
| 无法解压缩但支持压缩算法           | GRPC_STATUS_INTERNAL           |
| 客户端使用的压缩机制不受服务器支持 | GRPC_STATUS_UNIMPLEMENTED      |
| 达到流量控制资源限制               | GRPC_STATUS_RESOURCE_EXHAUSTED |
| 流量控制协议违规                   | GRPC_STATUS_INTERNAL           |
| 解析返回状态时出错                 | GRPC_STATUS_UNKNOWN            |
| 未经身份验证：凭据无法获取元数据   | GRPC_STATUS_UNAUTHENTICATED    |
| 认证失败                           | GRPC_STATUS_UNAUTHENTICATED    |
| 解析响应协议缓冲区时出错           | GRPC_STATUS_INTERNAL           |
| 解析请求协议缓冲时出错             | GRPC_STATUS_INTERNAL           |
## 2.5. 基准测试  
gRPC旨在支持多种语言的高性能开源RPC。  
本文档描述了性能基准测试工具，测试所考虑的方案以及测试基础架构。 
### 2.5.1. 简介 
gRPC专为分布式应用的高性能和高生产率设计而设计。持续性能基准测试是gRPC开发工作流程的关键部分。针对主分支每小时运行多语言性能测试，并将这些数字报告给仪表板以进行可视化。   

### 2.5.2. 性能测试设计
[基准测试](https://performance-dot-grpc-testing.appspot.com/explore?dashboard=5652536396611584&widget=828849126&container=1808124444&maximized)  
**C++自身**  
时延  
单项
![](./img/TIM图片20190425171240.png)  
异步流
![](./img/TIM图片20190425171325.png)  

多核单项比较(8-32)
![](./img/TIM图片20190425171601.png)  
多核流式(8-32)
![](./img/TIM图片20190425171657.png)  
单核流式
![](./img/TIM图片20190425171759.png) 
**多语言**  
时延比较(单项)  
![](./img/TIM图片20190425172051.png)  
| 语言  | 时延us |
| :---- | :----- |
| C++   | 150    |
| Go    | 250    |
| Java  | 230    |
| C#    | 430    |
| Ruby  | 600    |
| Pyton | 800    |
Qps(8Core)
![](./img/TIM图片20190425172945.png)  
| 语言  | QPS |
| :---- | :----- |
|Java|250 000|
|Go|225 000|
|C++|120  000|
|C#|45 000|
|PHP |37 000|
|Ruby|3 000|
|Python|1 500|
### 2.5.3. 测试的情景
有几个重要的方案正在测试中并显示在上面的仪表板中，包括以下内容：  
* 无争用延迟 - 只有1个客户端使用StreamingCall一次发送一条消息时看到的中位数和尾部​​响应延迟
* QPS - 当有2个客户端和总共64个通道时的消息/秒速率，每个通道使用StreamingCall一次发送100个未完成的消息  
* 可伸缩性（适用于所选语言） - 每个服务器核心的消息数/秒  
大多数性能测试都使用安全通信和protobufs。一些C ++测试还使用不安全的通信和通用（非protobuf）API来显示峰值性能。将来可能会添加其他方案。  
### 2.5.4. 测试基础架构  
所有性能基准测试都通过我们的Jenkins测试基础架构作为GCE中的实例运行。我们还运行基线netperf TCP_RR延迟数，以了解底层网络特征。这些数字出现在我们的仪表板上，有时会根据我们的实例在GCE中的分配位置而有所不同。   
大多数测试实例都是8核系统，这些系统用于延迟和QPS测量。对于C ++和Java，我们还支持在32核系统上进行QPS测试。所有QPS测试都为每台服务器使用2台相同的客户端计算机，以确保QPS测量不受客户端限制。  

## 2.6. 通讯协议  
本文档作为 gRPC 在 HTTP2 草案17框架上的实现的详细描述  
**协议**  
生产规则使用ABNF语法。  
### 2.6.1. 请求响应  
以下是GRPC请求和响应消息流中的消息原子的一般序列    
Example  
Sample unary-call showing HTTP2 framing sequence  
请求：  
```
HEADERS (flags = END_HEADERS)
:method = POST
:scheme = http
:path = /google.pubsub.v2.PublisherService/CreateTopic
:authority = pubsub.googleapis.com
grpc-timeout = 1S
content-type = application/grpc+proto
grpc-encoding = gzip
authorization = Bearer y235.wef315yfh138vh31hv93hv8h3v

DATA (flags = END_STREAM)
<Length-Prefixed Message>
```
应答
```
HEADERS (flags = END_HEADERS)
:status = 200
grpc-encoding = gzip
content-type = application/grpc+proto

DATA
<Length-Prefixed Message>

HEADERS (flags = END_STREAM, END_HEADERS)
grpc-status = 0 # OK
trace-proto-bin = jher831yy13JHy3hc
```
# 3. 教程
本节包含我们支持的每种语言的教程。他们向您介绍gRPC   
## 3.1. C++ 
本教程提供了一个基本的C ++程序员介绍如何使用gRPC。  
学习过程
* 定义一个.proto文件的服务
* 通过protocol buffer 生成客户端和服务端代码
* 使用C++ grpcAPI 写一个服务  
### 3.1.1. 使用场景  
我们的示例是一个简单的路由映射应用程序，它允许客户端获取有关其路由功能的信息，创建其路由摘要，以及与服务器和其他客户端交换路由信息（如流量更新）。  
[实例代码](https://github.com/grpc/grpc/tree/v1.20.0/examples/cpp/route_guide)的获取和安装    
```
 git clone -b v1.20.0 https://github.com/grpc/grpc
 cd examples/cpp/route_guide
```
### 3.1.2. 定义服务
其实就是定义一个proto文件,具体文件如下
```
syntax ="proto3";
option java_multiple_files=true ;
option  java_package ="cn.riversky.rpc";
option java_outer_classname ="RouteGruideProto";
option objc_class_prefix="RTG";
package routeguide;
/**
定义的接口
**/
service RouteGuide{
 //获取位置特征
 rpc  GetFeature(Point) returns (Feature){}
 //获取区域的地点
 rpc ListFeatures(Rectangle) returns (stream Feature){}
 
 //获取点的统计信息->单向流
 rpc RecordRoute(stream Point) returns (RouteSummary){}
 //遍历路线的消息信息->双向流
 rpc RouteChat(stream RouteNote) returns (stream RouteNote){}

}
//表示一个点,经纬度
message Point{
int32  latitude=1;
int32 longitude=2;
}
//矩形表示--需要对角线的两个点
message Rectangle{
	Point lo=1;
	Point hi=2;
}
//获取位置信息
message Feature{
	string name=1;
	Point location=2;
}
//获取位置上的消息
message RouteNote{
	Point location=1;
	string message=2;
}

message RouteSummary{
	int32  pointCount=1;
	int32  featureCount=2;
	int32  distance=3;
	int32  elapsedTime=4;
}
```
代码生成
```
protoc -I ./ --grpc_out ./tmp --cpp_out ./tmp  --plugin=protoc-gen-grpc=D:/tool/grpc_cpp_plugin  .\route_guide.proto  
```
### 3.1.3. 服务端设计
帮助类设计
``` 头文件
#pragma once
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include "route_guide.grpc.pb.h"
using namespace routeguide;
struct Location {
	int64_t latitude;
	int64_t longitude;
};
void from_json(const nlohmann::json& j, Location& nodeData);
void to_json(nlohmann::json& j, const Location nodeData);
struct NodeData
{
	Location location;
	std::string name;
};
Point MakePoint(long latitude, long longitude);
Feature MakeFeature(const std::string& name, long latitude, long longitude);
RouteNote MakeRouteNote(const std::string& message, long latitude, long longitude);
void from_json(const nlohmann::json& j, NodeData& nodeData);
void to_json(nlohmann::json& j, const NodeData nodeData);
void ParseDb(const std::string& db, std::vector<NodeData>* feature_list);
```
```cpp
#include "ServerHelper.h"
#include <fstream>
void from_json(const nlohmann::json & j, Location& nodeData)
{
	j.at("latitude").get_to(nodeData.latitude);
	j.at("longitude").get_to(nodeData.longitude);
}

void to_json(nlohmann::json & j, const Location nodeData)
{
	j = nlohmann::json{
		{ "latitude",nodeData.latitude },
		{"longitude",nodeData.longitude}
	};
}

Point MakePoint(long latitude, long longitude)
{
	Point p;
	p.set_latitude(latitude);
	p.set_longitude(longitude);
	return p;
}

Feature MakeFeature(const std::string & name, long latitude, long longitude)
{
	Feature f;
	f.set_name(name);
	f.mutable_location()->CopyFrom(MakePoint(latitude, longitude));
	return f;
}

RouteNote MakeRouteNote(const std::string & message, long latitude, long longitude)
{
	RouteNote n;
	n.set_message(message);
	n.mutable_location()->CopyFrom(MakePoint(latitude, longitude));
	return n;
}

void from_json(const nlohmann::json & j, NodeData & nodeData)
{
	j.at("location").get_to(nodeData.location);
	j.at("name").get_to(nodeData.name);
}

void to_json(nlohmann::json & j, const NodeData nodeData)
{
	j = nlohmann::json{ {"location",nodeData.location},{"name",nodeData.name} };
}

void ParseDb(const std::string & db, std::vector<NodeData>* feature_list)
{
	std::ifstream i(db);
	nlohmann::json json;
	i >> json;
	for (auto item : json) {
		feature_list->push_back(item);
	}
}
```
服务接口实现
```
#pragma once
#include "route_guide.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include "ServerHelper.h"
#include <chrono>
using namespace routeguide;
using namespace grpc;
using std::chrono::system_clock;
class RouterServer final :public  RouteGuide::Service
{
public:
	explicit RouterServer(const std::string & db) :db_(db)
	{
		ParseDb(db, &dataVect);
		for (auto data : dataVect)
		{
			Feature route;
			route.mutable_location()->CopyFrom(MakePoint(data.location.latitude, data.location.longitude));
			route.set_name(data.name);
			featueseList.push_back(route);
		}
	}
	~RouterServer() {}
public:
	virtual Status GetFeature(::grpc::ServerContext* context, const ::routeguide::Point* request, ::routeguide::Feature* response) override {
		response->set_name(GetFeatureName(*request, featueseList));
		response->mutable_location()->CopyFrom(*request);
		return Status::OK;
	}
	// 获取区域的地点
	virtual Status ListFeatures(::grpc::ServerContext* context, const ::routeguide::Rectangle* rectangle, ::grpc::ServerWriter< ::routeguide::Feature>* writer)override {
		auto lo = rectangle->lo();
		auto hi = rectangle->hi();
		long left = (std::min)(lo.longitude(), hi.longitude());
		long right = (std::max)(lo.longitude(), hi.longitude());
		long top = (std::max)(lo.latitude(), hi.latitude());
		long bottom = (std::min)(lo.latitude(), hi.latitude());
		for (const Feature& f : featueseList) {
			if (f.location().longitude() >= left &&
				f.location().longitude() <= right &&
				f.location().latitude() >= bottom &&
				f.location().latitude() <= top) {
				writer->Write(f);
			}
		}
		return Status::OK;
	}
	// 获取点的统计信息->单向流
	virtual Status RecordRoute(::grpc::ServerContext* context, ::grpc::ServerReader< ::routeguide::Point>* reader, ::routeguide::RouteSummary* summary)override {
		Point point;
		int point_count = 0;
		int feature_count = 0;
		float distance = 0.0;
		Point previous;

		system_clock::time_point start_time = system_clock::now();
		while (reader->Read(&point)) {
			point_count++;
			if (!GetFeatureName(point, featueseList).empty()) {
				feature_count++;
			}
			if (point_count != 1) {
				distance += GetDistance(previous, point);
			}
			previous = point;
		}
		system_clock::time_point end_time = system_clock::now();
		summary->set_pointcount(point_count);
		summary->set_featurecount(feature_count);
		summary->set_distance(static_cast<long>(distance));
		auto secs = std::chrono::duration_cast<std::chrono::seconds>(
			end_time - start_time);
		summary->set_elapsedtime(secs.count());
		return Status::OK;
	}
	// 遍历路线的消息信息->双向流
	virtual Status RouteChat(::grpc::ServerContext* context, ::grpc::ServerReaderWriter< ::routeguide::RouteNote, ::routeguide::RouteNote>* stream)override {
		std::vector<RouteNote> received_notes;
		RouteNote note;
		while (stream->Read(&note)) {
			for (const RouteNote& n : received_notes) {
				if (n.location().latitude() == note.location().latitude() &&
					n.location().longitude() == note.location().longitude()) {
					stream->Write(n);
				}
			}
			received_notes.push_back(note);
		}

		return Status::OK;
	}
public:
	/**
	 *启动服务
	 *Date :[4/26/2019 ]
	 *Author :[RS]
	 */
	static void RunServer(const std::string netStr = "192.168.1.159:50051") {
		std::string serverAddress(netStr);
		RouterServer routerServer("./route_guide_db.json");
		ServerBuilder serverBuilder;
		serverBuilder.AddListeningPort(serverAddress, InsecureServerCredentials());
		serverBuilder.RegisterService(&routerServer);
		std::unique_ptr<Server> server(serverBuilder.BuildAndStart());
		std::cout << "Server listening on " << serverAddress << std::endl;
		server->Wait();
	}
private:
	float GetDistance(const Point& start, const Point& end) {
		const float kCoordFactor = 10000000.0;
		float lat_1 = start.latitude() / kCoordFactor;
		float lat_2 = end.latitude() / kCoordFactor;
		float lon_1 = start.longitude() / kCoordFactor;
		float lon_2 = end.longitude() / kCoordFactor;
		float lat_rad_1 = ConvertToRadians(lat_1);
		float lat_rad_2 = ConvertToRadians(lat_2);
		float delta_lat_rad = ConvertToRadians(lat_2 - lat_1);
		float delta_lon_rad = ConvertToRadians(lon_2 - lon_1);

		float a = pow(sin(delta_lat_rad / 2), 2) + cos(lat_rad_1) * cos(lat_rad_2) *
			pow(sin(delta_lon_rad / 2), 2);
		float c = 2 * atan2(sqrt(a), sqrt(1 - a));
		int R = 6371000; // metres

		return R * c;
	}
	float ConvertToRadians(float num) {
		return num * 3.1415926 / 180;
	}
	std::string GetFeatureName(const Point& point,
		const std::vector<Feature>& feature_list) {
		for (const Feature& f : feature_list) {
			if (f.location().latitude() == point.latitude() &&
				f.location().longitude() == point.longitude()) {
				return f.name();
			}
		}
		return "";
	}

	std::string GetFeatureName(const ::routeguide::Point* request) {
		for (auto item : featueseList)
		{
			if (item.location().latitude() == request->latitude() && item.location().longitude() == request->longitude())
			{
				return item.name();
			}
		}
		return "";
	}
private:
	std::string db_;
	std::vector<NodeData> dataVect;
	std::vector<Feature> featueseList;
};
```
创建过程  
1. 创建我们的服务实现类的实例RouteGuideImpl。
2. 创建工厂ServerBuilder类的实例。
3. 使用构建器的AddListeningPort()方法指定我们要用于侦听客户端请求的地址和端口。
4. 向构建器注册我们的服务实现。
5. 调用BuildAndStart()构建器为我们的服务创建和启动RPC服务器。
6. 调用Wait()服务器进行阻塞等待，直到进程被终止或被 Shutdown()调用。  
### 3.1.4. 客户端设计
```
#pragma once
#include "route_guide.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include "ServerHelper.h"
#include <random>
#include <chrono>
#include <iostream>
#include <memory>
using namespace routeguide;
using namespace grpc;


class RouterClient
{

public:
	RouterClient(std::shared_ptr<Channel> channel, const std::string &db) :stub_(RouteGuide::NewStub(channel)) {
		ParseDb(db, &dataVect);
		for (auto data : dataVect)
		{
			Feature route;
			route.mutable_location()->CopyFrom(MakePoint(data.location.latitude, data.location.longitude));
			route.set_name(data.name);
			feature_list_.push_back(route);
		}
	}
	~RouterClient() {}
	void ListFeatures() {
		routeguide::Rectangle rect;
		Feature feature;
		ClientContext context;

		rect.mutable_lo()->set_latitude(400000000);
		rect.mutable_lo()->set_longitude(-750000000);
		rect.mutable_hi()->set_latitude(420000000);
		rect.mutable_hi()->set_longitude(-730000000);
		std::cout << "Looking for features between 40, -75 and 42, -73"
			<< std::endl;

		std::unique_ptr<ClientReader<Feature> > reader(
			stub_->ListFeatures(&context, rect));
		while (reader->Read(&feature)) {
			std::cout << "Found feature called "
				<< feature.name() << " at "
				<< feature.location().latitude() / kCoordFactor_ << ", "
				<< feature.location().longitude() / kCoordFactor_ << std::endl;
		}
		Status status = reader->Finish();
		if (status.ok()) {
			std::cout << "ListFeatures rpc succeeded." << std::endl;
		}
		else {
			std::cout << "ListFeatures rpc failed." << std::endl;
		}
	}
	void RecordRoute() {
		Point point;
		RouteSummary stats;
		ClientContext context;
		const int kPoints = 10;
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

		std::default_random_engine generator(seed);
		std::uniform_int_distribution<int> feature_distribution(
			0, feature_list_.size() - 1);
		std::uniform_int_distribution<int> delay_distribution(
			500, 1500);

		std::unique_ptr<ClientWriter<Point> > writer(
			stub_->RecordRoute(&context, &stats));
		for (int i = 0; i < kPoints; i++) {
			const Feature& f = feature_list_[feature_distribution(generator)];
			std::cout << "Visiting point "
				<< f.location().latitude() / kCoordFactor_ << ", "
				<< f.location().longitude() / kCoordFactor_ << std::endl;
			if (!writer->Write(f.location())) {
				// Broken stream.
				break;
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(
				delay_distribution(generator)));
		}
		writer->WritesDone();
		Status status = writer->Finish();
		if (status.ok()) {
			std::cout << "Finished trip with " << stats.pointcount() << " points\n"
				<< "Passed " << stats.featurecount() << " features\n"
				<< "Travelled " << stats.distance() << " meters\n"
				<< "It took " << stats.elapsedtime() << " seconds"
				<< std::endl;
		}
		else {
			std::cout << "RecordRoute rpc failed." << std::endl;
		}
	}
	void RouteChat() {
		ClientContext context;

		std::shared_ptr<ClientReaderWriter<RouteNote, RouteNote> > stream(
			stub_->RouteChat(&context));

		std::thread writer([stream]() {
			std::vector<RouteNote> notes{
			  MakeRouteNote("First message", 0, 0),
			  MakeRouteNote("Second message", 0, 1),
			  MakeRouteNote("Third message", 1, 0),
			  MakeRouteNote("Fourth message", 0, 0) };
			for (const RouteNote& note : notes) {
				std::cout << "Sending message " << note.message()
					<< " at " << note.location().latitude() << ", "
					<< note.location().longitude() << std::endl;
				stream->Write(note);
			}
			stream->WritesDone();
		});

		RouteNote server_note;
		while (stream->Read(&server_note)) {
			std::cout << "Got message " << server_note.message()
				<< " at " << server_note.location().latitude() << ", "
				<< server_note.location().longitude() << std::endl;
		}
		writer.join();
		Status status = stream->Finish();
		if (!status.ok()) {
			std::cout << "RouteChat rpc failed." << std::endl;
		}
	}
	void GetFeature() {
		Point point;
		Feature feature;
		point = MakePoint(409146138, -746188906);
		GetOneFeature(point, &feature);
		point = MakePoint(0, 0);
		GetOneFeature(point, &feature);
	}
public:
	/**
	 *测试接口
	 *Date :[4/26/2019 ]
	 *Author :[RS]
	 */
	static void Test() {
		std::string db = "./route_guide_db.json";
		RouterClient guide(CreateChannel("192.168.1.159:50051", InsecureChannelCredentials()), db);
		std::cout << "-------------- GetFeature --------------" << std::endl;
		guide.GetFeature();
		std::cout << "-------------- ListFeatures --------------" << std::endl;
		guide.ListFeatures();
		std::cout << "-------------- RecordRoute --------------" << std::endl;
		guide.RecordRoute();
		std::cout << "-------------- RouteChat --------------" << std::endl;
		guide.RouteChat();
	}
private:
	bool GetOneFeature(const Point& point, Feature *feature) {
		ClientContext context;
		Status status = stub_->GetFeature(&context, point, feature);
		if (!status.ok()) {
			std::cout << "GetFeature rpc failed." << std::endl;
			return false;
		}
		if (!feature->has_location()) {
			std::cout << "Server returns incomplete feature." << std::endl;
			return false;
		}
		if (feature->name().empty()) {
			std::cout << "Found no feature at "
				<< feature->location().latitude() / kCoordFactor_ << ", "
				<< feature->location().longitude() / kCoordFactor_ << std::endl;
		}
		else {
			std::cout << "Found feature called " << feature->name() << " at "
				<< feature->location().latitude() / kCoordFactor_ << ", "
				<< feature->location().longitude() / kCoordFactor_ << std::endl;
		}
		return true;
	}
private:
	const float kCoordFactor_ = 10000000.0;
	std::unique_ptr<RouteGuide::Stub> stub_;
	std::vector<NodeData> dataVect;
	std::vector<Feature> feature_list_;
};
```
## 3.2. Async C++
本教程将向您展示如何使用gRPC的异步/非阻塞API在C ++中编写简单的服务器和客户端。它假设您已经熟悉编写简单的同步gRPC代码，如gRPC Basics：C ++中所述。本教程中使用的示例来自我们在概述中使用 的基本Greeter示例。您可以在grpc / examples / cpp / helloworld中找到它和安装说明   
### 介绍
gRPC使用 CompletionQueue API进行异步操作。基本工作流程如下：  
* 绑定CompletionQueue到RPC调用  
* 做一些像读或写的东西，带有一个独特的void*标签 
* 呼叫CompletionQueue::Next等待操作完成。如果出现标签，则表示相应的操作已完成  
### 异步客户端
要使用异步客户端调用远程方法，首先要创建通道和存根，就像在同步客户端中一样。获得存根后，执行以下操作以进行异步调用：  

有两种方案,一种是在一个线程中完成,一种是在新线程中进行数据读取
```共用一个线程
#pragma once
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
#include "helloworld.grpc.pb.h"
#include <iostream>
#include <memory>
#include <string>  
#include "TimerClock.hpp"
using namespace grpc;
using namespace helloworld;
class AsyncClient1 {
public:
	explicit AsyncClient1(std::shared_ptr<Channel> channel) :stub_(Greeter::NewStub(channel)) {}
	std::string SayHello(const std::string& user = "likai") {
		HelloRequest req;
		req.set_name(user);
		HelloReply rep;
		// 客户端的上下文。它可以用来传达额外的信息     
		//  服务器和/或调整某些RPC行为。
		ClientContext context;
		CompletionQueue cq;
		Status status;
		// stub _-> PrepareAsyncSayHello（）创建一个RPC对象，返回    
		//存储在“call”中但不实际启动RPC的实例
		//因为我们正在使用异步API，所以我们需要坚持下去     
		//“call”实例，以获取正在进行的RPC的更新。
		std::unique_ptr<ClientAsyncResponseReader<HelloReply> > rpc(stub_->PrepareAsyncSayHello(&context, req, &cq));
		// StartCall启动RPC调用
		rpc->StartCall();
		// 请求在完成RPC后，使用“更新”更新“回复”    
		//服务器的响应; “状态”与是否操作的指示    
		// 那是成功的。使用整数1标记请求。
		rpc->Finish(&rep, &status, (void*)1);
		void* got_tag;
		bool ok = false;
		GPR_ASSERT(cq.Next(&got_tag, &ok));
		GPR_ASSERT(got_tag == (void*)1);
		GPR_ASSERT(ok);
		if (status.ok()) {
			return rep.message();
		}
		else {
			return "RPC failed";
		}
	}
	static void StartClient() {
		AsyncClient1 client(CreateChannel("192.168.1.159:50051", grpc::InsecureChannelCredentials()));
		std::string user("li");
		utils::TimerClock timer;
		timer.reset();
		int loop = 1000;
		for (int i = 0; i < loop; ++i)
		{
			auto rep = client.SayHello(user);
			std::cout << "receive:" << rep << std::endl;
		}
		std::cout << "time spend:" << timer.getMills() / loop << std::endl;
	}
private:
	std::unique_ptr<Greeter::Stub> stub_;
};
```
多个线程中
```
#pragma once
#include "helloworld.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include "TimerClock.hpp"
using namespace grpc;
using namespace helloworld;
class AsyncClient2
{
public:
	AsyncClient2(std::shared_ptr<Channel> channel) :stub_(Greeter::NewStub(channel)) {}
	virtual ~AsyncClient2() {}
	void SayHello(const std::string & user = "likai") {
		HelloRequest req;
		req.set_name(user);
		AsyncClientCall* call = new AsyncClientCall();
		call->reponserReader = stub_->PrepareAsyncSayHello(&call->ctx, req, &cq_);
		call->reponserReader->StartCall();
		call->reponserReader->Finish(&call->rep, &call->status, (void*)call);
	}
	void AysncCpmpleteRpc() {
		void* gotTag;
		bool ok = false;
		while (cq_.Next(&gotTag, &ok)) {
			AsyncClientCall * call = static_cast<AsyncClientCall*> (gotTag);
			GPR_ASSERT(ok);

			if (call->status.ok())
				std::cout << "Greeter received: " << call->rep.message() << std::endl;
			else
				std::cout << "RPC failed" << std::endl;
			delete call;
		}
	}
	static void StartClient() {
		AsyncClient2 client(CreateChannel("192.168.1.159:50051", InsecureChannelCredentials()));
		std::thread t(&AsyncClient2::AysncCpmpleteRpc, &client);
		int loop = 1000;
		for (int i = 0; i < loop; i++)
		{
			std::string user("word " + std::to_string(i));
			client.SayHello(user);
		}
		std::cout << "Press control-c to quit" << std::endl << std::endl;
		t.join();
	}
private:
	struct AsyncClientCall {
		HelloReply rep;
		ClientContext ctx;
		Status status;
		std::unique_ptr<ClientAsyncResponseReader<HelloReply> > reponserReader;
	};
	// Out of the passed in Channel comes the stub, stored here, our view of the
	// server's exposed services.
	std::unique_ptr<Greeter::Stub> stub_;
	// The producer-consumer queue we use to communicate asynchronously with the
	// gRPC runtime.
	CompletionQueue cq_;
};
```
要使用异步客户端调用远程方法，首先要创建通道和存根，就像在同步客户端中一样。获得存根后，执行以下操作以进行异步调用：  
1. 启动RPC并为其创建句柄。将RPC绑定到a CompletionQueue。  
```
CompletionQueue cq;
std::unique_ptr<ClientAsyncResponseReader<HelloReply> > rpc(stub_->AsyncSayHello(&context, request, &cq));
```
2. 通过唯一标记询问回复和最终状态
```
Status status;
rpc->Finish(&reply, &status, (void*)1);
```
3. 等待完成队列返回下一个标记。一旦Finish()返回传递到相应调用的标记，则回复和状态就绪
```
void* got_tag;
bool ok = false;
cq.Next(&got_tag, &ok);
if (ok && got_tag == (void*)1) {
    // check reply and status
}
```
### 异步服务器
服务器实现请求带有标记的RPC调用，然后等待完成队列返回标记。异步处理RPC的基本流程是：  
1. 构建导出异步服务的服务器  
```
helloword::Greeter::AsyncServer service;
ServerBuild builder;
builder.AddListeningPort("0.0.0.0:50051",InsercureServerCredentials());
builder.RegisterAsyncService(&service);
auto cq=builder.AddCompletionQueue();
auto server=builder.BuildAndStart();
```
2. 请求一个RPC，提供唯一标记  
```
ServerContext ctx;
HelloRequest req;
ServerAsyncResponseWriter<HelloReply> responser;
service.RequestSayHello(&ctx,&req,&responser,&cq,&cq,(void*)1);
```
3. 等待完成队列返回标记。一旦检索到标记，就会准备好上下文，请求和响应者。  
```
HelloReply rep;
Status status;
void* got_ta;
bool ok=false;
cq.Next(&got_tag,&ok);
if(ok&&got_tag==(void*)1){
    responser.Finish(rep,status(void*)1);
}
```
4. 等待完成队列返回标记。标签返回时RPC完成。
```
void* got_tag;
bool ok=false;
cq.Next(&got_tag,&ok);
if(ok&& got_tag==(void*)2){
    //clean up
}
```
但是，这个基本流程没有考虑服务器同时处理多个请求。为了解决这个问题，我们的完整异步服务器示例使用一个CallData对象来维护每个RPC的状态，并使用该对象的地址作为调用的唯一标记。  
```
 class CallData {
   public:
    // Take in the "service" instance (in this case representing an asynchronous
    // server) and the completion queue "cq" used for asynchronous communication
    // with the gRPC runtime.
    CallData(Greeter::AsyncService* service, ServerCompletionQueue* cq)
        : service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {
      // Invoke the serving logic right away.
      Proceed();
    }

    void Proceed() {
      if (status_ == CREATE) {
        // As part of the initial CREATE state, we *request* that the system
        // start processing SayHello requests. In this request, "this" acts are
        // the tag uniquely identifying the request (so that different CallData
        // instances can serve different requests concurrently), in this case
        // the memory address of this CallData instance.
        service_->RequestSayHello(&ctx_, &request_, &responder_, cq_, cq_,
                                  this);
        // Make this instance progress to the PROCESS state.
        status_ = PROCESS;
      } else if (status_ == PROCESS) {
        // Spawn a new CallData instance to serve new clients while we process
        // the one for this CallData. The instance will deallocate itself as
        // part of its FINISH state.
        new CallData(service_, cq_);

        // The actual processing.
        std::string prefix("Hello ");
        reply_.set_message(prefix + request_.name());

        // And we are done! Let the gRPC runtime know we've finished, using the
        // memory address of this instance as the uniquely identifying tag for
        // the event.
        responder_.Finish(reply_, Status::OK, this);
        status_ = FINISH;
      } else {
        GPR_ASSERT(status_ == FINISH);
        // Once in the FINISH state, deallocate ourselves (CallData).
        delete this;
      }
    }
  }
```
为简单起见，服务器仅对所有事件使用一个完成队列，并运行主循环HandleRpcs以查询队列：  
```
void HandleRpcs() {
    // Spawn a new CallData instance to serve new clients.
    new CallData(&service_, cq_.get());
    void* tag;  // uniquely identifies a request.
    bool ok;
    while (true) {
      // Block waiting to read the next event from the completion queue. The
      // event is uniquely identified by its tag, which in this case is the
      // memory address of a CallData instance.
      cq_->Next(&tag, &ok);
      GPR_ASSERT(ok);
      static_cast<CallData*>(tag)->Proceed();
    }
  }
```
**关闭服务器**  
我们一直在使用完成队列来获取异步通知。服务器关闭后必须小心将其关闭。  
```
 ~ServerImpl() {
    server_->Shutdown();
    // Always shutdown the completion queue after the server.
    cq_->Shutdown();
  }
```

完整的代码
```
#pragma once
#include "helloworld.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <grpc/support/log.h>
using namespace helloworld;
using namespace grpc;
class AsyncServer final
{
public:
	virtual ~AsyncServer() {
		server_->Shutdown();
		//始终在服务器之后关闭完成队列。
		cq_->Shutdown();
	}
	void Run() {
		std::string serverAddress("192.168.1.159:50051");
		ServerBuilder serverBuilder;
		serverBuilder.AddListeningPort(serverAddress, grpc::InsecureServerCredentials());
		//将“service_”注册为我们将与之通信的实例     客户在这种情况下，它对应于*异步*服务。    
		serverBuilder.RegisterService(&service_);
		//获取用于异步通信的完成队列    使用gRPC运行时。
		cq_ = serverBuilder.AddCompletionQueue();
		//最后组装服务器。
		server_ = serverBuilder.BuildAndStart();
		std::cout << "Server listening on " << serverAddress << std::endl;
		//继续进入服务器的主循环。     
		HandleRpcs();
	}
	static void StartServer() {
		AsyncServer server222;
		server222.Run();
		std::cout << "after server222.Run();" << std::endl;
	}
private:
	/**
	 *包含提供请求所需的状态和逻辑的类。
	 *Date :[4/26/2019 ]
	 *Author :[RS]
	 */
	class CallData {
	public:
		CallData(Greeter::AsyncService* service, ServerCompletionQueue* cq)
			: service_(service), cq_(cq), responder_(&ctx_), status_(CREATE) {
			// Invoke the serving logic right away.
			Proceed();
		}
		void Proceed() {
			if (status_ == CREATE) {
				// Make this instance progress to the PROCESS state.
				status_ = PROCESS;

				// As part of the initial CREATE state, we *request* that the system
				// start processing SayHello requests. In this request, "this" acts are
				// the tag uniquely identifying the request (so that different CallData
				// instances can serve different requests concurrently), in this case
				// the memory address of this CallData instance.
				service_->RequestSayHello(&ctx_, &request_, &responder_, cq_, cq_,
					this);
			}
			else if (status_ == PROCESS) {
				// Spawn a new CallData instance to serve new clients while we process
				// the one for this CallData. The instance will deallocate itself as
				// part of its FINISH state.
				new CallData(service_, cq_);

				// The actual processing.
				std::string prefix("Hello ");
				reply_.set_message(prefix + request_.name());

				// And we are done! Let the gRPC runtime know we've finished, using the
				// memory address of this instance as the uniquely identifying tag for
				// the event.
				status_ = FINISH;
				responder_.Finish(reply_, Status::OK, this);
			}
			else {
				GPR_ASSERT(status_ == FINISH);
				// Once in the FINISH state, deallocate ourselves (CallData).
				delete this;
			}
		}

	private:
		// The means of communication with the gRPC runtime for an asynchronous
		// server.
		Greeter::AsyncService* service_;
		// The producer-consumer queue where for asynchronous server notifications.
		ServerCompletionQueue* cq_;
		// Context for the rpc, allowing to tweak aspects of it such as the use
		// of compression, authentication, as well as to send metadata back to the
		// client.
		ServerContext ctx_;

		// What we get from the client.
		HelloRequest request_;
		// What we send back to the client.
		HelloReply reply_;

		// The means to get back to the client.
		ServerAsyncResponseWriter<HelloReply> responder_;

		// Let's implement a tiny state machine with the following states.
		enum CallStatus { CREATE, PROCESS, FINISH };
		CallStatus status_;  // The current serving state.
	};
	// This can be run in multiple threads if needed.
	void HandleRpcs() {
		// Spawn a new CallData instance to serve new clients.
		new CallData(&service_, cq_.get());
		void* tag;  // uniquely identifies a request.
		bool ok;
		while (true) {
			// Block waiting to read the next event from the completion queue. The
			// event is uniquely identified by its tag, which in this case is the
			// memory address of a CallData instance.
			// The return value of Next should always be checked. This return value
			// tells us whether there is any kind of event or cq_ is shutting down.
			GPR_ASSERT(cq_->Next(&tag, &ok));
			GPR_ASSERT(ok);
			static_cast<CallData*>(tag)->Proceed();
		}
	}
	std::unique_ptr<ServerCompletionQueue> cq_;
	Greeter::AsyncService service_;
	std::unique_ptr<Server> server_;
};
```
## 3.4. Go
本教程提供了一个基本的Go程序员介绍如何使用gRPC。  
### 场景
我们的示例是一个简单的路由映射应用程序，它允许客户端获取有关其路由功能的信息，创建其路由摘要，以及与服务器和其他客户端交换路由信息（如流量更新）。  
### 示例代码和设置  
[源码位置](https://github.com/grpc/grpc-go/tree/master/examples/route_guide)  
### 服务定义
```
yntax = "proto3";

option java_multiple_files = true;
option java_package = "io.grpc.examples.routeguide";
option java_outer_classname = "RouteGuideProto";

package routeguide;

service RouteGuide {
  rpc GetFeature(Point) returns (Feature) {}
  rpc ListFeatures(Rectangle) returns (stream Feature) {}
  rpc RecordRoute(stream Point) returns (RouteSummary) {}
  rpc RouteChat(stream RouteNote) returns (stream RouteNote) {}
}
message Point {
  int32 latitude = 1;
  int32 longitude = 2;
}
message Rectangle {
  Point lo = 1;
  Point hi = 2;
}
message Feature {
  string name = 1;
  Point location = 2;
}
message RouteNote {
  Point location = 1;
  string message = 2;
}
message RouteSummary {
  int32 point_count = 1;
  int32 feature_count = 2;
  int32 distance = 3;
  int32 elapsed_time = 4;
}
```
### 代码生成
```
protoc -I ./  route_guide.proto --go_out=plugins=grpc:.
```
服务端
```
import (
	"context"
	"encoding/json"
	"flag"
	"fmt"
	"github.com/golang/protobuf/proto"
	"google.golang.org/grpc"
	"google.golang.org/grpc/credentials"
	pb "google.golang.org/grpc/examples/route_guide/routeguide"
	"google.golang.org/grpc/testdata"
	"io"
	"io/ioutil"
	"log"
	"math"
	"net"
	"sync"
	"time"
)

var (
	tls=flag.Bool("tls",false,"Connection uses TLS if true,else plain TCP")
	certFile   = flag.String("cert_file", "", "The TLS cert file")
	keyFile    = flag.String("key_file", "", "The TLS key file")
	jsonDBFile = flag.String("json_db_file", "", "A json file containing a list of features")
	//jsonDBFile = flag.String("json_db_file", "H:/sutdy/cpp/grp/Grp/x64/Release/route_guide_db.json", "A json file containing a list of features")
	port       = flag.Int("port", 50051, "The server port")
)
type routeGuideServer struct {
	savedFeatures []*pb.Feature
	mu sync.Mutex
	routeNotes map[string][]*pb.RouteNote
}
func (s *routeGuideServer) loadFeatures(filePath string) {
	var data []byte
	if filePath != "" {
		var err error
		data, err = ioutil.ReadFile(filePath)
		if err != nil {
			log.Fatalf("Failed to load default features: %v", err)
		}
	} else {
		data=exampleData
	}
	if err := json.Unmarshal(data, &s.savedFeatures); err != nil {
		log.Fatalf("Failed to load default features: %v", err)
	}
}
func (s* routeGuideServer) GetFeature(ctx context.Context, point *pb.Point) (*pb.Feature, error) {
	for _,feature:=range s.savedFeatures {
		if proto.Equal(feature.Location,point ){
			return  feature,nil
		}
	}
	return &pb.Feature{Location:point},nil
}

func (s *routeGuideServer) ListFeatures(rect *pb.Rectangle,stream  pb.RouteGuide_ListFeaturesServer) error {
	for _,feature:=range s.savedFeatures{
		if inRange(feature.Location,rect){
			if err:=stream.Send(feature);err!=nil{
				return  err
			}
		}
	}
	return  nil;
}

func (s* routeGuideServer) RecordRoute(stream pb.RouteGuide_RecordRouteServer) error {
	var pointCount, featureCount, distance int32
	var lastPoint *pb.Point
	startTime := time.Now()
	for {
		point, err := stream.Recv()
		if err == io.EOF {
			endTime := time.Now()
			return stream.SendAndClose(&pb.RouteSummary{
				PointCount:   pointCount,
				FeatureCount: featureCount,
				Distance:     distance,
				ElapsedTime:  int32(endTime.Sub(startTime).Seconds()),
			})
		}
		if err != nil {
			return err
		}
		pointCount++
		for _, feature := range s.savedFeatures {
			if proto.Equal(feature.Location, point) {
				featureCount++
			}
		}
		if lastPoint != nil {
			distance += calcDistance(lastPoint, point)
		}
		lastPoint = point
	}
}

func (s * routeGuideServer) RouteChat(stream pb.RouteGuide_RouteChatServer) error {
	for {
		in, err := stream.Recv()
		if err == io.EOF {
			return nil
		}
		if err != nil {
			return err
		}
		key := serialize(in.Location)

		s.mu.Lock()
		s.routeNotes[key] = append(s.routeNotes[key], in)
		// Note: this copy prevents blocking other clients while serving this one.
		// We don't need to do a deep copy, because elements in the slice are
		// insert-only and never modified.
		rn := make([]*pb.RouteNote, len(s.routeNotes[key]))
		copy(rn, s.routeNotes[key])
		s.mu.Unlock()

		for _, note := range rn {
			if err := stream.Send(note); err != nil {
				return err
			}
		}
	}
}

func toRadians(num float64)float64{
	return  num*math.Pi/float64(180)
}
func calcDistance(p1 *pb.Point,p2 *pb.Point)int32{
	const CordFactor float64 = 1e7
	const R = float64(6371000) // earth radius in metres
	lat1 := toRadians(float64(p1.Latitude) / CordFactor)
	lat2 := toRadians(float64(p2.Latitude) / CordFactor)
	lng1 := toRadians(float64(p1.Longitude) / CordFactor)
	lng2 := toRadians(float64(p2.Longitude) / CordFactor)
	dlat := lat2 - lat1
	dlng := lng2 - lng1

	a := math.Sin(dlat/2)*math.Sin(dlat/2) +
		math.Cos(lat1)*math.Cos(lat2)*
			math.Sin(dlng/2)*math.Sin(dlng/2)
	c := 2 * math.Atan2(math.Sqrt(a), math.Sqrt(1-a))

	distance := R * c
	return int32(distance)
}
/**
点是否在这个区域
 */
func inRange(point *pb.Point, rect *pb.Rectangle) bool {
	left := math.Min(float64(rect.Lo.Longitude), float64(rect.Hi.Longitude))
	right := math.Max(float64(rect.Lo.Longitude), float64(rect.Hi.Longitude))
	top := math.Max(float64(rect.Lo.Latitude), float64(rect.Hi.Latitude))
	bottom := math.Min(float64(rect.Lo.Latitude), float64(rect.Hi.Latitude))

	if float64(point.Longitude) >= left &&
		float64(point.Longitude) <= right &&
		float64(point.Latitude) >= bottom &&
		float64(point.Latitude) <= top {
		return true
	}
	return false
}
func serialize(point *pb.Point) string {
	return fmt.Sprintf("%d %d", point.Latitude, point.Longitude)
}

func newServer() *routeGuideServer {
	s := &routeGuideServer{routeNotes: make(map[string][]*pb.RouteNote)}
	s.loadFeatures(*jsonDBFile)
	return s
}
func RouteGuideStartServer(){
	flag.Parse()
	lis,err:=net.Listen("tcp","192.168.1.159:50051")
	if err != nil {
		log.Fatalf("failed to listen: %v", err)
	}
	var opts []grpc.ServerOption
	if *tls{
		if *certFile == "" {
			*certFile = testdata.Path("server1.pem")
		}
		if *keyFile == "" {
			*keyFile = testdata.Path("server1.key")
		}
		creds, err := credentials.NewServerTLSFromFile(*certFile, *keyFile)
		if err != nil {
			log.Fatalf("Failed to generate credentials %v", err)
		}
		opts = []grpc.ServerOption{grpc.Creds(creds)}
	}
	grpcServer := grpc.NewServer(opts...)
	pb.RegisterRouteGuideServer(grpcServer, newServer())
	grpcServer.Serve(lis)
}
```
客户端
```
var (
	tls                = flag.Bool("tls", false, "Connection uses TLS if true, else plain TCP")
	caFile             = flag.String("ca_file", "", "The file containning the CA root cert file")
	serverAddr         = flag.String("server_addr", "192.168.1.159:50051", "The server address in the format of host:port")
	serverHostOverride = flag.String("server_host_override", "x.test.youtube.com", "The server name use to verify the hostname returned by TLS handshake")
)

func printFeature(client pd.RouteGuideClient, point *pd.Point) {
	log.Printf("Getting feature for point (%d, %d)", point.Latitude, point.Longitude)
	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()
	feature, err := client.GetFeature(ctx, point)
	if err != nil {
		log.Fatalf("%v.GetFeatures(_) = _, %v: ", client, err)
	}
	log.Println(feature)
}
func printFeatures(client pd.RouteGuideClient, rect *pd.Rectangle) {
	log.Printf("Looking for features within %v", rect)
	timeout, cancelFunc := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancelFunc()
	featuresClient, e := client.ListFeatures(timeout, rect)
	if e != nil {
		log.Fatalf("%v.ListFeatures(_) = _, %v", client, e)
	}
	for{
		feature, err := featuresClient.Recv()
		if err==io.EOF{
			break
		}
		if err!=nil{
			log.Fatalf("%v.ListFeatures(_) = _, %v", client, err)
		}
		log.Println(feature)
	}
}
func runRecordRoute(client pd.RouteGuideClient) {
	// Create a random number of random points
	r := rand.New(rand.NewSource(time.Now().UnixNano()))
	pointCount := int(r.Int31n(100)) + 2 // Traverse at least two points
	var points []*pd.Point
	for i := 0; i < pointCount; i++ {
		points = append(points, randomPoint(r))
	}
	log.Printf("Traversing %d points.", len(points))
	ctx, cancel := context.WithTimeout(context.Background(), 10*time.Second)
	defer cancel()
	stream, err := client.RecordRoute(ctx)
	if err != nil {
		log.Fatalf("%v.RecordRoute(_) = _, %v", client, err)
	}
	for _, point := range points {
		if err := stream.Send(point); err != nil {
			log.Fatalf("%v.Send(%v) = %v", stream, point, err)
		}
	}
	reply, err := stream.CloseAndRecv()
	if err != nil {
		log.Fatalf("%v.CloseAndRecv() got error %v, want %v", stream, err, nil)
	}
	log.Printf("Route summary: %v", reply)
}
func runRouteChat(client pd.RouteGuideClient){
	notes := []*pd.RouteNote{
		{Location: &pd.Point{Latitude: 0, Longitude: 1}, Message: "First message"},
		{Location: &pd.Point{Latitude: 0, Longitude: 2}, Message: "Second message"},
		{Location: &pd.Point{Latitude: 0, Longitude: 3}, Message: "Third message"},
		{Location: &pd.Point{Latitude: 0, Longitude: 1}, Message: "Fourth message"},
		{Location: &pd.Point{Latitude: 0, Longitude: 2}, Message: "Fifth message"},
		{Location: &pd.Point{Latitude: 0, Longitude: 3}, Message: "Sixth message"},
	}
	ctx, cancelFunc := context.WithTimeout(context.Background(),10*time.Second)
	defer cancelFunc()
	stream, err := client.RouteChat(ctx)
	if err!=nil{
		log.Fatalf("%v.RouteChat(_) = _, %v", client, err)
	}
	waitc:=make(chan struct{})
	go func() {
		for{
			in, err := stream.Recv()
			if err==io.EOF{
				close(waitc)
				return
			}
			if err!=nil{
				log.Fatalf("Failed to receive a note : %v", err)
			}
			log.Printf("Got message %s at point(%d, %d)", in.Message, in.Location.Latitude, in.Location.Longitude)
		}
	}()
	for _,note:=range notes{
		if err:=stream.Send(note);err!=nil{
			log.Fatalf("Failed to send a note: %v", err)
		}
	}
	stream.CloseSend()
	<-waitc
}
func randomPoint(r *rand.Rand) *pd.Point {
	lat := (r.Int31n(180) - 90) * 1e7
	long := (r.Int31n(360) - 180) * 1e7
	return &pd.Point{Latitude: lat, Longitude: long}
}
func StartClientRoute(){
	flag.Parse()
	var opts []grpc.DialOption
	if *tls {
		if *caFile == "" {
			*caFile = testdata.Path("ca.pem")
		}
		creds, err := credentials.NewClientTLSFromFile(*caFile, *serverHostOverride)
		if err != nil {
			log.Fatalf("Failed to create TLS credentials %v", err)
		}
		opts = append(opts, grpc.WithTransportCredentials(creds))
	} else {
		opts = append(opts, grpc.WithInsecure())
	}
	conn, err := grpc.Dial(*serverAddr, opts...)
	if err != nil {
		log.Fatalf("fail to dial: %v", err)
	}
	defer conn.Close()
	client := pd.NewRouteGuideClient(conn)

	// Looking for a valid feature
	printFeature(client, &pd.Point{Latitude: 409146138, Longitude: -746188906})

	// Feature missing.
	printFeature(client, &pd.Point{Latitude: 0, Longitude: 0})

	// Looking for features between 40, -75 and 42, -73.
	printFeatures(client, &pd.Rectangle{
		Lo: &pd.Point{Latitude: 400000000, Longitude: -750000000},
		Hi: &pd.Point{Latitude: 420000000, Longitude: -730000000},
	})

	// RecordRoute
	runRecordRoute(client)

	// RouteChat
	runRouteChat(client)
}
```
## 3.3. Java 
本教程提供了一个基本的Java程序员介绍如何使用gRPC。  
通过这个例子，您将学习如何：

* 在.proto文件中定义服务。
* 使用协议缓冲区编译器生成服务器和客户端代码。
* 使用Java gRPC API为您的服务编写简单的客户端和服务器。  
### 为什么要使用gRPC？
我们的示例是一个简单的路由映射应用程序，它允许客户端获取有关其路由功能的信息，创建其路由摘要，以及与服务器和其他客户端交换路由信息（如流量更新）。  
### 示例代码和设置
[源码](https://github.com/grpc/grpc-java/tree/master/examples/src/main/java/io/grpc/examples)  
```
$ git clone -b v1.20.0 https://github.com/grpc/grpc-java.git
$ cd grpc-java/examples  
```
### 服务定义  
服务端
```
public class RouteGuideServer {
    private static final Logger logger = LoggerFactory.getLogger(RouteGuideServer.class.getName());
    private final int port;
    private final Server server;
    public RouteGuideServer(int port) throws IOException {
        this(port, RouteGuideUtil.getDefaultFeaturesFile());
    }
    /** Create a RouteGuide server listening on {@code port} using {@code featureFile} database. */
    public RouteGuideServer(int port, URL featureFile) throws IOException {
        this(ServerBuilder.forPort(port), port, RouteGuideUtil.parseFeatures(featureFile));
    }

    /** Create a RouteGuide server using serverBuilder as a base and features as data. */
    public RouteGuideServer(ServerBuilder<?> serverBuilder, int port, Collection<Feature> features) {
        this.port = port;
        server = serverBuilder.addService(new RouteGuideService(features))
                .build();
    }
    /** Start serving requests. */
    public void start() throws IOException {
        server.start();
        logger.info("Server started, listening on " + port);
        Runtime.getRuntime().addShutdownHook(new Thread() {
            @Override
            public void run() {
                // Use stderr here since the logger may has been reset by its JVM shutdown hook.
                System.err.println("*** shutting down gRPC server since JVM is shutting down");
                RouteGuideServer.this.stop();
                System.err.println("*** server shut down");
            }
        });
    }

    /** Stop serving requests and shutdown resources. */
    public void stop() {
        if (server != null) {
            server.shutdown();
        }
    }
    /**
     * Await termination on the main thread since the grpc library uses daemon threads.
     */
    private void blockUntilShutdown() throws InterruptedException {
        if (server != null) {
            server.awaitTermination();
        }
    }
    /**
     * Main method.  This comment makes the linter happy.
     */
    public static void StartRoutServer() throws Exception {
        RouteGuideServer server = new RouteGuideServer(50051);
        server.start();
        server.blockUntilShutdown();
    }

    /**
     * Our implementation of RouteGuide service.
     *
     * <p>See route_guide.proto for details of the methods.
     */
    private static class RouteGuideService extends RouteGuideGrpc.RouteGuideImplBase {
        private final Collection<Feature> features;
        private final ConcurrentMap<Point, List<RouteNote>> routeNotes =
                new ConcurrentHashMap<Point, List<RouteNote>>();

        RouteGuideService(Collection<Feature> features) {
            this.features = features;
        }

        /**
         * Gets the {@link Feature} at the requested {@link Point}. If no feature at that location
         * exists, an unnamed feature is returned at the provided location.
         *
         * @param request the requested location for the feature.
         * @param responseObserver the observer that will receive the feature at the requested point.
         */
        @Override
        public void getFeature(Point request, StreamObserver<Feature> responseObserver) {
            responseObserver.onNext(checkFeature(request));
            responseObserver.onCompleted();
        }

        /**
         * Gets all features contained within the given bounding {@link Rectangle}.
         *
         * @param request the bounding rectangle for the requested features.
         * @param responseObserver the observer that will receive the features.
         */
        @Override
        public void listFeatures(Rectangle request, StreamObserver<Feature> responseObserver) {
            int left = min(request.getLo().getLongitude(), request.getHi().getLongitude());
            int right = max(request.getLo().getLongitude(), request.getHi().getLongitude());
            int top = max(request.getLo().getLatitude(), request.getHi().getLatitude());
            int bottom = min(request.getLo().getLatitude(), request.getHi().getLatitude());

            for (Feature feature : features) {
                if (!RouteGuideUtil.exists(feature)) {
                    continue;
                }

                int lat = feature.getLocation().getLatitude();
                int lon = feature.getLocation().getLongitude();
                if (lon >= left && lon <= right && lat >= bottom && lat <= top) {
                    responseObserver.onNext(feature);
                }
            }
            responseObserver.onCompleted();
        }

        /**
         * Gets a stream of points, and responds with statistics about the "trip": number of points,
         * number of known features visited, total distance traveled, and total time spent.
         *
         * @param responseObserver an observer to receive the response summary.
         * @return an observer to receive the requested route points.
         */
        @Override
        public StreamObserver<Point> recordRoute(final StreamObserver<RouteSummary> responseObserver) {
            return new StreamObserver<Point>() {
                int pointCount;
                int featureCount;
                int distance;
                Point previous;
                final long startTime = System.nanoTime();

                @Override
                public void onNext(Point point) {
                    pointCount++;
                    if (RouteGuideUtil.exists(checkFeature(point))) {
                        featureCount++;
                    }
                    // For each point after the first, add the incremental distance from the previous point to
                    // the total distance value.
                    if (previous != null) {
                        distance += calcDistance(previous, point);
                    }
                    previous = point;
                }

                @Override
                public void onError(Throwable t) {
                    logger.warn("recordRoute cancelled");
                }

                @Override
                public void onCompleted() {
                    long seconds = NANOSECONDS.toSeconds(System.nanoTime() - startTime);
                    responseObserver.onNext(RouteSummary.newBuilder().setPointCount(pointCount)
                            .setFeatureCount(featureCount).setDistance(distance)
                            .setElapsedTime((int) seconds).build());
                    responseObserver.onCompleted();
                }
            };
        }

        /**
         * Receives a stream of message/location pairs, and responds with a stream of all previous
         * messages at each of those locations.
         *
         * @param responseObserver an observer to receive the stream of previous messages.
         * @return an observer to handle requested message/location pairs.
         */
        @Override
        public StreamObserver<RouteNote> routeChat(final StreamObserver<RouteNote> responseObserver) {
            return new StreamObserver<RouteNote>() {
                @Override
                public void onNext(RouteNote note) {
                    List<RouteNote> notes = getOrCreateNotes(note.getLocation());

                    // Respond with all previous notes at this location.
                    for (RouteNote prevNote : notes.toArray(new RouteNote[0])) {
                        responseObserver.onNext(prevNote);
                    }

                    // Now add the new note to the list
                    notes.add(note);
                }

                @Override
                public void onError(Throwable t) {
                    logger.warn("routeChat cancelled");
                }

                @Override
                public void onCompleted() {
                    responseObserver.onCompleted();
                }
            };
        }

        /**
         * Get the notes list for the given location. If missing, create it.
         */
        private List<RouteNote> getOrCreateNotes(Point location) {
            List<RouteNote> notes = Collections.synchronizedList(new ArrayList<RouteNote>());
            List<RouteNote> prevNotes = routeNotes.putIfAbsent(location, notes);
            return prevNotes != null ? prevNotes : notes;
        }

        /**
         * Gets the feature at the given point.
         *
         * @param location the location to check.
         * @return The feature object at the point. Note that an empty name indicates no feature.
         */
        private Feature checkFeature(Point location) {
            for (Feature feature : features) {
                if (feature.getLocation().getLatitude() == location.getLatitude()
                        && feature.getLocation().getLongitude() == location.getLongitude()) {
                    return feature;
                }
            }

            // No feature was found, return an unnamed feature.
            return Feature.newBuilder().setName("").setLocation(location).build();
        }

        /**
         * Calculate the distance between two points using the "haversine" formula.
         * The formula is based on http://mathforum.org/library/drmath/view/51879.html.
         *
         * @param start The starting point
         * @param end The end point
         * @return The distance between the points in meters
         */
        private static int calcDistance(Point start, Point end) {
            int r = 6371000; // earth radius in meters
            double lat1 = toRadians(RouteGuideUtil.getLatitude(start));
            double lat2 = toRadians(RouteGuideUtil.getLatitude(end));
            double lon1 = toRadians(RouteGuideUtil.getLongitude(start));
            double lon2 = toRadians(RouteGuideUtil.getLongitude(end));
            double deltaLat = lat2 - lat1;
            double deltaLon = lon2 - lon1;

            double a = sin(deltaLat / 2) * sin(deltaLat / 2)
                    + cos(lat1) * cos(lat2) * sin(deltaLon / 2) * sin(deltaLon / 2);
            double c = 2 * atan2(sqrt(a), sqrt(1 - a));
            return (int) (r * c);
        }
    }
}
```
客户端
```
public class RouteClient {
    private static final Logger logger = LoggerFactory.getLogger(RouteClient.class);

    private final ManagedChannel channel;
    private final RouteGuideGrpc.RouteGuideBlockingStub blockingStub;
    private final RouteGuideGrpc.RouteGuideStub asyncStub;

    private Random random = new Random();
    private TestHelper testHelper;

    /** Construct client for accessing RouteGuide server at {@code host:port}. */
    public RouteClient(String host, int port) {
        this(ManagedChannelBuilder.forAddress(host, port).usePlaintext());
    }

    /** Construct client for accessing RouteGuide server using the existing channel. */
    public RouteClient(ManagedChannelBuilder<?> channelBuilder) {
        channel = channelBuilder.build();
        blockingStub = RouteGuideGrpc.newBlockingStub(channel);
        asyncStub = RouteGuideGrpc.newStub(channel);
    }

    public void shutdown() throws InterruptedException {
        channel.shutdown().awaitTermination(5, TimeUnit.SECONDS);
    }

    /**
     * Blocking unary call example.  Calls getFeature and prints the response.
     */
    public void getFeature(int lat, int lon) {
        logger.info("*** GetFeature: lat={} lon={}", lat, lon);

        Point request = Point.newBuilder().setLatitude(lat).setLongitude(lon).build();

        Feature feature;
        try {
            feature = blockingStub.getFeature(request);
            if (testHelper != null) {
                testHelper.onMessage(feature);
            }
        } catch (StatusRuntimeException e) {
            logger.warn("RPC failed: {0}", e.getStatus());
            if (testHelper != null) {
                testHelper.onRpcError(e);
            }
            return;
        }
        if (RouteGuideUtil.exists(feature)) {
            logger.info("Found feature called {0} at {1}, {2}",
                    feature.getName(),
                    RouteGuideUtil.getLatitude(feature.getLocation()),
                    RouteGuideUtil.getLongitude(feature.getLocation()));
        } else {
            logger.info("Found no feature at {0}, {1}",
                    RouteGuideUtil.getLatitude(feature.getLocation()),
                    RouteGuideUtil.getLongitude(feature.getLocation()));
        }
    }

    /**
     * Blocking server-streaming example. Calls listFeatures with a rectangle of interest. Prints each
     * response feature as it arrives.
     */
    public void listFeatures(int lowLat, int lowLon, int hiLat, int hiLon) {
        logger.info("*** ListFeatures: lowLat={0} lowLon={1} hiLat={2} hiLon={3}", lowLat, lowLon, hiLat,
                hiLon);

        Rectangle request =
                Rectangle.newBuilder()
                        .setLo(Point.newBuilder().setLatitude(lowLat).setLongitude(lowLon).build())
                        .setHi(Point.newBuilder().setLatitude(hiLat).setLongitude(hiLon).build()).build();
        Iterator<Feature> features;
        try {
            features = blockingStub.listFeatures(request);
            for (int i = 1; features.hasNext(); i++) {
                Feature feature = features.next();
                logger.info("Result #" + i + ": "+ feature.toString());
                if (testHelper != null) {
                    testHelper.onMessage(feature);
                }
            }
        } catch (StatusRuntimeException e) {
            logger.warn("RPC failed: {0}", e.getStatus());
            if (testHelper != null) {
                testHelper.onRpcError(e);
            }
        }
    }

    /**
     * Async client-streaming example. Sends {@code numPoints} randomly chosen points from {@code
     * features} with a variable delay in between. Prints the statistics when they are sent from the
     * server.
     */
    public void recordRoute(List<Feature> features, int numPoints) throws InterruptedException {
        logger.info("*** RecordRoute");
        final CountDownLatch finishLatch = new CountDownLatch(1);
        StreamObserver<RouteSummary> responseObserver = new StreamObserver<RouteSummary>() {
            @Override
            public void onNext(RouteSummary summary) {
                logger.info("Finished trip with {0} points. Passed {1} features. "
                                + "Travelled {2} meters. It took {3} seconds.", summary.getPointCount(),
                        summary.getFeatureCount(), summary.getDistance(), summary.getElapsedTime());
                if (testHelper != null) {
                    testHelper.onMessage(summary);
                }
            }

            @Override
            public void onError(Throwable t) {
                logger.warn("RecordRoute Failed: {0}", Status.fromThrowable(t));
                if (testHelper != null) {
                    testHelper.onRpcError(t);
                }
                finishLatch.countDown();
            }

            @Override
            public void onCompleted() {
                logger.info("Finished RecordRoute");
                finishLatch.countDown();
            }
        };

        StreamObserver<Point> requestObserver = asyncStub.recordRoute(responseObserver);
        try {
            // Send numPoints points randomly selected from the features list.
            for (int i = 0; i < numPoints; ++i) {
                int index = random.nextInt(features.size());
                Point point = features.get(index).getLocation();
                logger.info("Visiting point {}, {}", RouteGuideUtil.getLatitude(point),
                        RouteGuideUtil.getLongitude(point));
                requestObserver.onNext(point);
                // Sleep for a bit before sending the next one.
                Thread.sleep(random.nextInt(1000) + 500);
                if (finishLatch.getCount() == 0) {
                    // RPC completed or errored before we finished sending.
                    // Sending further requests won't error, but they will just be thrown away.
                    return;
                }
            }
        } catch (RuntimeException e) {
            // Cancel RPC
            requestObserver.onError(e);
            throw e;
        }
        // Mark the end of requests
        requestObserver.onCompleted();

        // Receiving happens asynchronously
        if (!finishLatch.await(1, TimeUnit.MINUTES)) {
            logger.warn("recordRoute can not finish within 1 minutes");
        }
    }

    /**
     * Bi-directional example, which can only be asynchronous. Send some chat messages, and print any
     * chat messages that are sent from the server.
     */
    public CountDownLatch routeChat() {
        logger.info("*** RouteChat");
        final CountDownLatch finishLatch = new CountDownLatch(1);
        StreamObserver<RouteNote> requestObserver =
                asyncStub.routeChat(new StreamObserver<RouteNote>() {
                    @Override
                    public void onNext(RouteNote note) {
                        logger.info("Got message {} at {}, {}", note.getMessage(), note.getLocation()
                                .getLatitude(), note.getLocation().getLongitude());
                        if (testHelper != null) {
                            testHelper.onMessage(note);
                        }
                    }

                    @Override
                    public void onError(Throwable t) {
                        logger.warn("RouteChat Failed: {0}", Status.fromThrowable(t));
                        if (testHelper != null) {
                            testHelper.onRpcError(t);
                        }
                        finishLatch.countDown();
                    }

                    @Override
                    public void onCompleted() {
                        logger.info("Finished RouteChat");
                        finishLatch.countDown();
                    }
                });

        try {
            RouteNote[] requests =
                    {newNote("First message", 0, 0), newNote("Second message", 0, 1),
                            newNote("Third message", 1, 0), newNote("Fourth message", 1, 1)};

            for (RouteNote request : requests) {
                logger.info("Sending message \"{0}\" at {1}, {2}", request.getMessage(), request.getLocation()
                        .getLatitude(), request.getLocation().getLongitude());
                requestObserver.onNext(request);
            }
        } catch (RuntimeException e) {
            // Cancel RPC
            requestObserver.onError(e);
            throw e;
        }
        // Mark the end of requests
        requestObserver.onCompleted();

        // return the latch while receiving happens asynchronously
        return finishLatch;
    }

    /** Issues several different requests and then exits. */
    public static void StartClient() throws InterruptedException {
        List<Feature> features;
        try {
            features = RouteGuideUtil.parseFeatures(RouteGuideUtil.getDefaultFeaturesFile());
        } catch (IOException ex) {
            ex.printStackTrace();
            return;
        }

        RouteClient client = new RouteClient("localhost", 50051);
        try {
            // Looking for a valid feature
            client.getFeature(409146138, -746188906);

            // Feature missing.
            client.getFeature(0, 0);

            // Looking for features between 40, -75 and 42, -73.
            client.listFeatures(400000000, -750000000, 420000000, -730000000);

            // Record a few randomly selected points from the features file.
            client.recordRoute(features, 10);
            // Send and receive some notes.
            CountDownLatch finishLatch = client.routeChat();

            if (!finishLatch.await(1, TimeUnit.MINUTES)) {
               logger.warn("routeChat can not finish within 1 minutes");
            }
        } finally {
            client.shutdown();
        }
    }



    private RouteNote newNote(String message, int lat, int lon) {
        return RouteNote.newBuilder().setMessage(message)
                .setLocation(Point.newBuilder().setLatitude(lat).setLongitude(lon).build()).build();
    }

    /**
     * Only used for unit test, as we do not want to introduce randomness in unit test.
     */
    @VisibleForTesting
    void setRandom(Random random) {
        this.random = random;
    }

    /**
     * Only used for helping unit test.
     */
    @VisibleForTesting
    interface TestHelper {
        /**
         * Used for verify/inspect message received from server.
         */
        void onMessage(Message message);

        /**
         * Used for verify/inspect error received from server.
         */
        void onRpcError(Throwable exception);
    }

    @VisibleForTesting
    void setTestHelper(TestHelper testHelper) {
        this.testHelper = testHelper;
    }
}
```

## 3.5. Android Java  

主要是用于客户端


