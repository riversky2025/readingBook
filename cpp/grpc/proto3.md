# 1. 语言指南  
本指南介绍如何使用协议缓冲区语言构建协议缓冲区数据，包括.proto文件语法以及如何从.proto文件生成数据访问类。它涵盖了协议缓冲区语言的proto3版本：有关较早的proto2语法的信息，请参阅Proto2语言指南。  
这是一个参考指南 - 对于使用本文档中描述的许多功能的分步示例，请参阅所选语言的教程（目前仅限proto2;更多proto3文档即将推出）。  
## 1.1. 定义消息类型
```
syntax ="proto3";
message SearchRequest{
    string query=1;
    int32 page_number=2;
    int32 result_per_page=3;
}
```
在定义时需要注意包含以下信息:类型,字段名称,序号,域的规则(singular/repeated)  
并且一个proto文件可以包含多个类型  
**注释** 
采用C/C++风格的注释方式
```
/* SearchRequest represents a search query, with pagination options to
 * indicate which results to include in the response. */
message SearchRequest {
  string query = 1;
  int32 page_number = 2;  // Which page number do we want?
  int32 result_per_page = 3;  // Number of results to return per page.
}
```
**保留字段**  
如果通过完全删除字段或将其注释来更新消息类型，则未来用户可以在对类型进行自己的更新时重用字段编号。如果以后加载旧版本的旧版本.proto，包括数据损坏，隐私错误等，这可能会导致严重问题。确保不会发生这种情况的一种方法是指定已删除字段的字段编号（和/或名称，这也可能导致JSON序列化问题）reserved。如果将来的任何用户尝试使用这些字段标识符，协议缓冲编译器将会抱怨。  
```
message Foo {
  reserved 2, 15, 9 to 11;
  reserved "foo", "bar";
}
```
>>请注意，您不能在同一保留语句中混合字段名称和字段编号。  

**生成的内容**  
当您在a上运行协议缓冲区编译器时.proto，编译器将使用您所选语言生成代码，您需要使用您在文件中描述的消息类型，包括获取和设置字段值，将消息序列化为输出流，并从输入流解析您的消息。  
* 为C ++，编译器生成一个.h和.cc从每个文件.proto，有用于在文件中描述的每个消息类型的类。  
* 对于Java，编译器生成一个.java文件，其中包含每种消息类型的类，以及Builder用于创建消息类实例的特殊类。  
* Python有点不同 - Python编译器生成一个模块，其中包含每个消息类型的静态描述符，.proto然后与元类一起使用，以在运行时创建必要的Python数据访问类。
* 对于Go，编译器会为.pb.go文件中的每种消息类型生成一个类型的文件。  
* 对于Ruby，编译器生成一个.rb包含消息类型的Ruby模块的文件。
* 对于Objective-C，编译器从每个文件生成一个文件pbobjc.h，pbobjc.m文件中.proto描述的每种消息类型都有一个类
* 对于C＃，编译器会.cs从每个文件生成一个文件.proto，其中包含文件中描述的每种消息类型的类。
* 对于Dart，编译器会为.pb.dart文件中的每种消息类型生成一个包含类的文件。

您可以按照所选语言的教程（即将推出的proto3版本）了解有关为每种语言使用API​​的更多信息。有关更多API详细信息，请参阅相关[API参考](https://developers.google.com/protocol-buffers/docs/reference/overview)（proto3版本即将推出）。  
## 1.2. 类型
数据类型  
|.proto |Notes|C++ |Java  |Python |Go  |Ruby |C#|PHP|
|:--|:--|:--|:--|:--|:--|:--|:--|:--|
|double ||double |double|float|float64|Float|double|float|
|float||float|float|float|float32|Float|float|float|
|int32|使用可变长度编码。编码负数的效率低 - 如果您的字段可能有负值，请改用sint32。|int32|int|int|int32|Fixnum or Bignum|int|integer|
|int64|使用可变长度编码。编码负数的效率低 - 如果您的字段可能有负值，请改用sint64。|int64|long|int/long|int64|Bignum|long|integer/string|
|uint32|使用可变长度编码。|uint32|int|int/long|uint32|Fixnum or Bignum|uint|integer|
|uint64|使用可变长度编码。|uint64|long|int/long|uint64|Bignum|ulong|integer/string|
|sint32|使用可变长度编码。签名的int值。这些比常规int32更有效地编码负数。|int32|int|int|int32|Fixnum or Bignum|int|integer|
|sint64|使用可变长度编码。签名的int值。这些比常规int64更有效地编码负数。|int64|long|int/long|int64|Bignum|long|integer/string|
|fixed32|总是四个字节。如果值通常大于2^28，则比uint32更有效。|uint32|int|int/long|uint32|Fixnum or Bignum|uint|integer|
|fixed64|总是八个字节。如果值通常大于2^56，则比uint64更有效。|uint64|long|int/long|uint64|Bignum|ulong|integer|string|
|sfixed32|总是四个字节。|int32|int|int|int32|Fixnum or Bignum|int|integer|
|sfixed64|总是八个字节。|int64|long|int/long|int64|Bignum|long|integer|string|
|bool||bool|boolean|bool|bool|TrueClass/FalseClass|bool|boolean|
|string|字符串必须始终包含UTF-8编码或7位ASCII文本。|string|String|str/unicode|string|String(UTF-8)|string|string|
|bytes|可以包含任意字节序列。|string|ByteString|str|[]byte|String(ASCII-8BIT)|ByteString|string|  
在[协议缓冲区编码中](https://developers.google.com/protocol-buffers/docs/encoding)序列化消息时，您可以找到有关如何编码这些类型的更多信息。  
[1] 在Java中，无符号的32位和64位整数使用它们的带符号对应表示，最高位只是存储在符号位中。  
[2] 在所有情况下，将值设置为字段将执行类型检查以确保其有效。  
[3]  64位或无符号32位整数在解码时总是表示为long，但如果在设置字段时给出int，则可以是int。在所有情况下，该值必须符合设置时表示的类型。  
[4] Python字符串在解码时表示为unicode，但如果给出了ASCII字符串，则可以是str（这可能会发生变化）。  
[5] Integer用于64位计算机，字符串用于32位计算机。  
## 1.3. 默认值
解析消息时，如果编码消息不包含特定的单数元素，则解析对象中的相应字段将设置为该字段的默认值。这些默认值是特定于类型的：  
* 对于字符串，默认值为空字符串。  
* 对于字节，默认值为空字节。  
* 对于bools，默认值为false。
* 对于数字类型，默认值为零。
* 对于枚举，默认值是第一个定义的枚举值，该值必须为0。  
* 对于消息字段，未设置该字段。它的确切值取决于语言。有关详细信息， 请[参阅生成的代码](https://developers.google.com/protocol-buffers/docs/reference/overview)指重复字段的默认值为空（通常是相应语言的空列表）。  

请注意，对于标量消息字段，一旦解析了消息，就无法确定字段是否显式设置为默认值（例如，布尔值是否设置为false）或者根本没有设置：您应该记住这一点在定义消息类型时。例如，false如果您不希望默认情况下也发生这种行为，则没有布尔值在设置时打开某些行为。还要注意的是，如果一个标消息字段被设置为默认值，该值将不会在电线上连载。  
有关默认值如何在生成的代码中工作的更多详细信息，请参阅所选语言的[生成代码指南](https://developers.google.com/protocol-buffers/docs/reference/overview)。
## 1.4. 枚举
在定义消息类型时，您可能希望其中一个字段只有一个预定义的值列表。例如，假设你想添加一个 corpus字段每个SearchRequest，其中语料库可以 UNIVERSAL，WEB，IMAGES，LOCAL，NEWS，PRODUCTS或VIDEO。您可以通过enum在消息定义中添加每个可能值的常量来非常简单地执行此操作。  
在下面的示例中，我们添加了一个带有所有可能值的enum调用Corpus，以及一个类型的字段Corpus：  
```
message SearchRequest {
  string query = 1;
  int32 page_number = 2;
  int32 result_per_page = 3;
  enum Corpus {
    UNIVERSAL = 0;
    WEB = 1;
    IMAGES = 2;
    LOCAL = 3;
    NEWS = 4;
    PRODUCTS = 5;
    VIDEO = 6;
  }
  Corpus corpus = 4;
}
```  
如您所见，Corpus枚举的第一个常量映射为零：每个枚举定义必须包含一个映射到零的常量作为其第一个元素。这是因为：  
* 必须有一个零值，以便我们可以使用0作为数字默认值。  
* 零值必须是第一个元素，以便与proto2语义兼容，其中第一个枚举值始终是默认值。  

您可以通过为不同的枚举常量指定相同的值来定义别名。为此，您需要将allow_alias选项设置为true，否则协议编译器将在找到别名时生成错误消息。  
```
enum EnumAllowingAlias {
  option allow_alias = true;
  UNKNOWN = 0;
  STARTED = 1;
  RUNNING = 1;
}
enum EnumNotAllowingAlias {
  UNKNOWN = 0;
  STARTED = 1;
  // RUNNING = 1;  // Uncommenting this line will cause a compile error inside Google and a warning message outside.
}
```  
枚举器常量必须在32位整数范围内。由于enum值在线上使用varint编码，因此负值效率低，因此不建议使用。您可以enum在消息定义中定义s，如上例所示，enum也可以在外部定义 - 这些可以在.proto文件的任何消息定义中重用。您还可以使用enum语法将一个消息中声明的类型用作另一个消息中的字段类型。 MessageType.EnumType  
当您在.proto使用a的协议缓冲区编译器上运行时enum，生成的代码将具有enumJava或C ++ 的相应代码，这EnumDescriptor是Python的一个特殊类，用于在运行时生成的类中创建一组带有整数值的符号常量  
在反序列化期间，无法识别的枚举值将保留在消息中，但是当反序列化消息时，如何表示这种值取决于语言。在支持具有超出指定符号范围的值的开放枚举类型的语言中，例如C ++和Go，未知的枚举值仅作为其基础整数表示存储。在具有封闭枚举类型（如Java）的语言中，枚举中的大小写用于表示无法识别的值，并且可以使用特殊访问器访问基础整数。在任何一种情况下，如果消息被序列化，则仍然会使用消息序列化无法识别的值。  
有关如何enum在应用程序中使用消息的详细信息，请参阅所选语言的[生成代码指南](https://developers.google.com/protocol-buffers/docs/reference/overview)。   

**保留值**  
如果通过完全删除枚举条目或将其注释掉来更新枚举类型，则未来用户可以在对类型进行自己的更新时重用该数值。如果以后加载旧版本的旧版本.proto，包括数据损坏，隐私错误等，这可能会导致严重问题。确保不会发生这种情况的一种方法是指定已删除条目的数值（和/或名称，这也可能导致JSON序列化问题）reserved。如果将来的任何用户尝试使用这些标识符，协议缓冲编译器将会抱怨。您可以使用max关键字指定保留的数值范围达到最大可能值。  
```
enum Foo {
  reserved 2, 15, 9 to 11, 40 to max;
  reserved "FOO", "BAR";
}
```
请注意，您不能在同一reserved语句中混合字段名称和数值。  
## 1.5. 使用其他消息类型
您可以使用其他消息类型作为字段类型。例如，假设你想包括Result每个消息的SearchResponse消息-要做到这一点，你可以定义一个Result在同一个消息类型.proto，然后指定类型的字段Result中SearchResponse：  
message SearchResponse {
  repeated Result results = 1;
}  
message Result {
  string url = 1;
  string title = 2;
  repeated string snippets = 3;
}  
**导入定义**  
在上面的示例中，Result消息类型在同一文件中定义SearchResponse- 如果要用作字段类型的消息类型已在另一个.proto文件中定义，该怎么办？  
可以.proto通过导入来使用其他文件中的定义。要导入另一个.proto定义，请在文件顶部添加一个import语句：  
```
import "myproject/other_protos.proto";
```
默认情况下，您只能使用直接导入.proto文件中的定义。但是，有时您可能需要将.proto文件移动到新位置。.proto现在，您可以.proto在旧位置放置一个虚拟文件，使用import public概念将所有导入转发到新位置，而不是直接移动文件并在一次更改中更新所有调用站点。import public任何导入包含该import public语句的proto的人都可以传递依赖关系。例如：  
```
// new.proto
// All definitions are moved here
// old.proto
// This is the proto that all clients are importing.
import public "new.proto";
import "other.proto";
// client.proto
import "old.proto";
// You use definitions from old.proto and new.proto, but not other.proto
```
协议编译器使用-I/ --proto_pathflag 在协议编译器命令行中指定的一组目录中搜索导入的文件 。如果没有给出标志，它将查找调用编译器的目录。通常，您应该将--proto_path标志设置为项目的根目录，并对所有导入使用完全限定名称。  
**使用proto2消息类型**  
可以导入proto2消息类型并在proto3消息中使用它们，反之亦然。但是，proto2枚举不能直接用于proto3语法（如果导入的proto2消息使用它们就没关系）。  
## 1.6. 嵌套类型
您可以在其他消息类型中定义和使用消息类型，如下例所示 - 此处Result消息在消息中定义SearchResponse：
```
message SearchResponse {
  message Result {
    string url = 1;
    string title = 2;
    repeated string snippets = 3;
  }
  repeated Result results = 1;
}
```
如果要在其父消息类型之外重用此消息类型，请将其称为： Parent.Type
```
message SomeOtherMessage {
  SearchResponse.Result result = 1;
}
```
您可以根据需要深入嵌套邮件：  
```
message Outer {                  // Level 0
  message MiddleAA {  // Level 1
    message Inner {   // Level 2
      int64 ival = 1;
      bool  booly = 2;
    }
  }
  message MiddleBB {  // Level 1
    message Inner {   // Level 2
      int32 ival = 1;
      bool  booly = 2;
    }
  }
}
```
## 1.7. 更新消息类型
如果现有的消息类型不再满足您的所有需求 - 例如，您希望消息格式具有额外的字段 - 但您仍然希望使用使用旧格式创建的代码，请不要担心！在不破坏任何现有代码的情况下更新消息类型非常简单。请记住以下规则：  
* 请勿更改任何现有字段的字段编号。  
* 如果添加新字段，则使用“旧”消息格式按代码序列化的任何消息仍可由新生成的代码进行解析。您应该记住这些元素的默认值，以便新代码可以正确地与旧代码生成的消息进行交互。同样，您的新代码创建的消息可以由旧代码解析：旧的二进制文件在解析时只是忽略新字段。有关详细信息，请参阅“ [未知字段](https://developers.google.com/protocol-buffers/docs/proto3#unknowns)”部分   
* 只要在更新的消息类型中不再使用字段编号，就可以删除字段。您可能希望重命名该字段，可能添加前缀“OBSOLETE_”，或者保留字段编号，以便您的未来用户.proto不会意外地重复使用该号码。  
* int32，uint32，int64，uint64，和bool都是兼容的-这意味着你可以改变这些类型到另一个的一个场不破坏forwards-或向后兼容。如果从导线中解析出一个不适合相应类型的数字，您将获得与在C ++中将该数字转换为该类型相同的效果（例如，如果将64位数字作为int32读取，它将被截断为32位）。  
* sint32并且sint64彼此兼容但与其他整数类型不兼容。  
* stringbytes只要字节是有效的UTF-8 ，它们是兼​​容的。  
* bytes如果字节包含消息的编码版本，则嵌入消息兼容。  
* fixed32与兼容sfixed32，并fixed64用sfixed64。  
* enum与兼容int32，uint32，int64，和uint64电线格式条款（注意，如果他们不适合的值将被截断）。但请注意，在反序列化消息时，客户端代码可能会以不同方式对待它们：例如，enum消息中将保留未识别的proto3 类型，但在反序列化消息时如何表示它是依赖于语言的。Int字段总是保留它们的价值。  
* 将单个值更改为新 成员oneof是安全且二进制兼容的。oneof如果您确定没有代码一次设置多个字段，则将多个字段移动到新字段可能是安全的。将任何字段移动到现有字段oneof是不安全的。  
## 1.8. 未知字段
未知字段是格式良好的协议缓冲区序列化数据，表示解析器无法识别的字段。例如，当旧二进制文件解析具有新字段的新二进制文件发送的数据时，这些新字段将成为旧二进制文件中的未知字段。  
最初，proto3消息在解析期间总是丢弃未知字段，但在3.5版本中，我们重新引入了未知字段的保存以匹配proto2行为。在版本3.5及更高版本中，未知字段在解析期间保留并包含在序列化输出中。
## 1.9. any
该Any消息类型，可以使用邮件作为嵌入式类型，而不必自己.proto定义。一个Any含有任意的序列化消息bytes，以充当一个全局唯一标识符和解析到该消息的类型的URL一起。要使用该Any类型，您需要导入 google/protobuf/any.proto。  

```
import "google/protobuf/any.proto";

message ErrorStatus {
  string message = 1;
  repeated google.protobuf.Any details = 2;
}
```
给定消息类型的默认类型URL是。 type.googleapis.com/packagename.messagename  
不同的语言实现将支持运行时库佣工类型安全的方式打包和解包的任何值-例如，在Java中，任何类型都会有特殊pack()和unpack()存取，而在C ++中有PackFrom()和UnpackTo()方法：  
```
// Storing an arbitrary message type in Any.
NetworkErrorDetails details = ...;
ErrorStatus status;
status.add_details()->PackFrom(details);

// Reading an arbitrary message from Any.
ErrorStatus status = ...;
for (const Any& detail : status.details()) {
  if (detail.Is<NetworkErrorDetails>()) {
    NetworkErrorDetails network_error;
    detail.UnpackTo(&network_error);
    ... processing network_error ...
  }
}
```
目前，正在开发用于处理Any类型的运行时库。  
## 1.10. Oneof
如果您有一个包含许多字段的消息，并且最多只能同时设置一个字段，则可以使用oneof功能强制执行此行为并节省内存。  
除了一个共享内存中的所有字段之外，其中一个字段类似于常规字段，并且最多可以同时设置一个字段。设置oneof的任何成员会自动清除所有其他成员。您可以使用特殊方法case()或WhichOneof()方法检查oneof中的哪个值（如果有），具体取决于您选择的语言。  
**使用Oneof**   
要在您中定义oneof，请.proto使用oneof关键字后跟您的oneof名称，在这种情况下test_oneof：  
```
message SampleMessage {
  oneof test_oneof {
    string name = 4;
    SubMessage sub_message = 9;
  }
}
```
然后，将oneof字段添加到oneof定义中。您可以添加任何类型的字段，但不能使用repeated字段。  
在生成的代码中，oneof字段与常规字段具有相同的getter和setter。您还可以获得一种特殊方法来检查oneof中的值（如果有）。您可以在相关API参考中找到有关所选语言的oneof API的更多信息。

**特点**  
* 设置oneof字段将自动清除oneof的所有其他成员。因此，如果您设置多个字段，则只有您设置的最后一个字段仍具有值。  
```
SampleMessage message;
message.set_name("name");
CHECK(message.has_name());
message.mutable_sub_message();   // Will clear name field.
CHECK(!message.has_name());
```
* 如果解析器在线路上遇到同一个oneof的多个成员，则在解析的消息中仅使用看到的最后一个成员。  
* 不可能repeated。
* Reflection API适用于其中一个字段。
* 如果您使用的是C ++，请确保您的代码不会导致内存崩溃。以下示例代码将崩溃，因为sub_message已通过调用该set_name()方法删除了该代码。  
```
SampleMessage message;
SubMessage* sub_message = message.mutable_sub_message();
message.set_name("name");      // Will delete sub_message
sub_message->set_...            // Crashes here
```
* 同样在C ++中，如果你有Swap()两个消息与oneofs，每个消息将最终与另一个消息的一个案例：在下面的例子中，msg1将有一个sub_message和msg2将有一个name。  
```
SampleMessage msg1;
msg1.set_name("name");
SampleMessage msg2;
msg2.mutable_sub_message();
msg1.swap(&msg2);
CHECK(msg1.has_sub_message());
CHECK(msg2.has_name());
```
**向后兼容性问题**  
添加或删除其中一个字段时要小心。如果检查oneof返回的值None/ NOT_SET，这可能意味着oneof尚未设置或已在不同版本的oneof的被设置为一个字段。没有办法区分，因为没有办法知道线上的未知字段是否是其中一个成员。  
标签重用问题  
* 将字段移入或移出oneof：在序列化和解析消息后，您可能会丢失一些信息（某些字段将被清除）。但是，您可以安全地将单个字段移动到新的字段中，并且如果已知只有一个字段被设置，则可以移动多个字段。  
* 删除oneof字段并将其添加回：在序列化和解析消息后，这可能会清除当前设置的oneof字段。  
* 拆分或合并oneof：这与移动常规字段有类似的问题。  
## 1.11. map
如果要在数据定义中创建关联映射，协议缓冲区提供了一种方便的快捷方式语法：  
```
map<key_type, value_type> map_field = N;
```
其中key_type可以是任何整数或字符串类型（因此，除了浮点类型之外的任何标量类型bytes）。请注意，枚举不是有效的key_type。的value_type可以是任何类型的除另一地图。  
因此，例如，如果要创建项目映射，其中每条Project消息都与字符串键相关联，则可以像下面这样定义它：  

```
map<string, Project> projects = 3;
```
* map字段不能repeated。  
* map值的有线格式排序和地图迭代排序未定义，因此您不能依赖于特定顺序的map项目。
* 为a生成文本格式时.proto，map按键排序。数字键按数字排序。
* 从线路解析或合并时，如果有重复的映射键，则使用最后看到的键。从文本格式解析映射时，如果存在重复键，则解析可能会失败。  
* 如果为映射字段提供键但没有值，则字段序列化时的行为取决于语言。在C ++，Java和Python中，类型的默认值是序列化的，而在其他语言中没有任何序列化。  

生成的地图API目前可用于所有proto3支持的语言。您可以在相关API参考中找到有关所选语言的地图API的更多信息。  
**向后兼容性**  
映射语法在线上等效于以下内容，因此不支持映射的协议缓冲区实现仍然可以处理您的数据：  
```
message MapFieldEntry {
  key_type key = 1;
  value_type value = 2;
}

repeated MapFieldEntry map_field = N;
```
支持映射的任何协议缓冲区实现都必须生成和接受上述定义可以接受的数据
## 1.12. package
可以将可选的包说明符添加到.proto文件，以防止协议消息类型之间的名称冲突。
```
package foo.bar;
message Open { ... }
```
您可以在定义消息类型的字段时使用包说明符：
```
message Foo {
  ...
  foo.bar.Open open = 1;
  ...
}
```
包说明符影响生成的代码的方式取决于您选择的语言：  
* C++ 中代表的是命名空间
* Java中是包名
* python中会被忽略
* GO 表示模块名称
* Ruby中表示命名空间
* C#中表示命名空间

**包名称解析**  
协议缓冲区编译器通过解析导入的.proto文件来解析所有类型名称。每种语言的代码生成器都知道如何引用该语言中的每种类型，即使它具有不同的范围规则。  
## 1.13. service
在使用远程过程调用时,你可以采用该文件定义,并且可以生成你选择语言的接口代码和存根  
```
service SearchService {
  rpc Search (SearchRequest) returns (SearchResponse);
}
```
该模块主要与grpc模块搭配使用
## 1.14. json
Proto3支持JSON中的规范编码，使得在系统之间共享数据变得更加容易。在下表中逐个类型地描述编码。  
**配置**  
proto3 JSON实现可以提供以下选项：  
* 字段默认生成
* 忽略未知字段
* 使用proto file驼峰命名法
* 枚举使用整形
## 1.15. option 
.proto文件中的各个声明可以使用许多选项进行注释。选项不会更改声明的整体含义，但可能会影响在特定上下文中处理它的方式。可用选项的完整列表在中定义google/protobuf/descriptor.proto。  
一些选项是文件级选项，这意味着它们应该在顶级范围内编写，而不是在任何消息，枚举或服务定义中。一些选项是消息级选项，这意味着它们应该写在消息定义中。一些选项是字段级选项，这意味着它们应该写在字段定义中。选项也可以写在枚举类型，枚举值，服务类型和服务方法上; 但是，目前没有任何有用的选择。 
以下是一些最常用的选项：  
*  java_package（文件选项）：要用于生成的Java类的包。如果文件中没有java_package给出显式选项.proto，则默认情况下将使用proto包（使用文件中的“package”关键字指定.proto）。但是，proto包通常不能生成好的Java包，因为预期proto包不会以反向域名开头。如果不生成Java代码，则此选项无效。 `option java_package =“com.example.foo”;`  
*  java_multiple_files （文件选项）：导致在包级别定义顶级消息，枚举和服务，而不是在.proto文件之后命名的外部类中。`option java_multiple_files = true;`    
*  java_outer_classname（file option）：要生成的最外层Java类（以及文件名）的类名。如果文件中没有java_outer_classname指定explicit .proto，则通过将.proto文件名转换为camel-case（因此foo_bar.proto成为FooBar.java）来构造类名。如果不生成Java代码，则此选项无效。`option java_outer_classname =“Ponycopter”;`
*  optimize_for（文件选项）：可以设置为SPEED，CODE_SIZE或LITE_RUNTIME。这会以下列方式影响C ++和Java代码生成器（可能还有第三方生成器）：`option optimize_for = CODE_SIZE;`
```
SPEED（默认值）：协议缓冲区编译器将生成用于对消息类型进行序列化，解析和执行其他常见操作的代码。此代码经过高度优化。
CODE_SIZE：协议缓冲区编译器将生成最少的类，并依赖于基于反射的共享代码来实现序列化，解析和各种其他操作。因此生成的代码将比使用小得多SPEED，但操作会更慢。类仍将实现与SPEED模式完全相同的公共API 。此模式在包含非常大数量的.proto文件的应用程序中最有用，并且不需要所有文件都非常快速。
LITE_RUNTIME：协议缓冲区编译器将生成仅依赖于“lite”运行时库（libprotobuf-lite而不是libprotobuf）的类。lite运行时比完整库小得多（大约小一个数量级），但省略了描述符和反射等特定功能。这对于在移动电话等受限平台上运行的应用程序尤其有用。编译器仍然会像在SPEED模式中一样生成所有方法的快速实现。生成的类将仅实现MessageLite每种语言的接口，该接口仅提供完整Message接口的方法的子集。
```
*  cc_enable_arenas（文件选项）：为C ++生成的代码启用竞技场分配。
*  objc_class_prefix（文件选项）：设置Objective-C类前缀，该前缀预先添加到此.proto的所有Objective-C生成的类和枚举中。没有默认值。您应该使用Apple建议的 3-5个大写字符之间的前缀。请注意，Apple保留所有2个字母的前缀。  
*  deprecated（字段选项）：如果设置为true，则表示该字段已弃用，新代码不应使用该字段。在大多数语言中，这没有实际效果。在Java中，这成为一个@Deprecated注释。将来，其他特定于语言的代码生成器可能会在字段的访问器上生成弃用注释，这会在编译尝试使用该字段的代码时导致发出警告。如果任何人都没有使用该字段，并且您希望阻止新用户使用该字段，请考虑使用保留语句替换字段声明。`int32 old_field = 6 [deprecated = true];`  
**自定义选项**  
Protocol Buffers还允许您定义和使用自己的选项。这是大多数人不需要的高级功能。如果您确实认为需要创建自己的选项，请参阅Proto2语言指南以获取详细信息。请注意，创建自定义选项使用的扩展名仅允许用于proto3中的自定义选项。  
## 1.16. 生成
除了Golang需要单独的[生成插件](https://github.com/golang/protobuf/)其他的只需要[下载](https://developers.google.com/protocol-buffers/docs/downloads.html)安装编译器就可以了.  
指令
```
protoc --proto_path=IMPORT_PATH --cpp_out=DST_DIR --java_out=DST_DIR --python_out=DST_DIR --go_out=DST_DIR --ruby_out=DST_DIR --objc_out=DST_DIR --csharp_out=DST_DIR path/to/file.proto  
```
指令参数
* IMPORT_PATH:proto解析import指令时在其中查找文件的目录。如果省略，则使用当前目录。可以通过--proto_path多次传递选项来指定多个导入目录; 他们将按顺序搜索。 可以用作简短的形式。 -I=IMPORT_PATH--proto_path  
* 您可以提供一个或多个输出指令： 
* 您必须提供一个或多个.proto文件作为输入。.proto可以一次指定多个文件。虽然文件是相对于当前目录命名的，但每个文件必须驻留在其中一个文件中，IMPORT_PATH以便编译器可以确定其规范名称。

|指令参数|语言|
|:--|:--|
|--cpp_out| [C++代码DST_DIR](https://developers.google.com/protocol-buffers/docs/reference/cpp-generated)|
|--java_out|[Java DST_DIR](https://developers.google.com/protocol-buffers/docs/reference/java-generated)|
|--python_out|[python](https://developers.google.com/protocol-buffers/docs/reference/python-generated)|
|--go_out|[go](https://developers.google.com/protocol-buffers/docs/reference/go-generated)|

为了方便起见，如果DST_DIR结束于.zip 或.jar，编译器会将输出写入具有给定名称的单个ZIP格式存档文件。 .jar输出还将根据Java JAR规范的要求提供清单文件。请注意，如果输出存档已存在，则会被覆盖; 编译器不够智能，无法将文件添加到现有存档中。   
# 2. API指南
本节包含使用C ++，Java，Python，Go，C＃，Objective C和JavaScript中的协议缓冲区类的参考文档，以及Protocol Buffers本身的一些参考文档。每种语言的文档包括（如果可用）：  
* 协议缓冲区编译器从您的.proto文件生成的代码的参考指南。
* 为提供的源代码生成API文档。
请注意，管道中还有其他几种语言的API - 有关详细信息，请参阅[其他语言的Wiki页面](https://github.com/protocolbuffers/protobuf/blob/master/docs/third_party.md)。  
[详情](https://developers.google.com/protocol-buffers/docs/reference/overview)
## 2.1. C++指南
此页面准确描述了协议缓冲区编译器为任何给定协议定义生成的C ++代码。  
### 2.1.1. 生成指南
#### 2.1.1.1. 编译调用
当使用--cpp_out=命令行标志调用时，协议缓冲区编译器会生成C ++输出。该--cpp_out=选项的参数是您希望编译器编写C ++输出的目录。编译器为每个.proto文件输入创建头文件和实现文件。输出文件的名称是通过获取.proto文件名并进行两处更改来计算的：  
* 所述延伸部（.proto）被替换为任一.pb.h或.pb.cc分别为头或实现文件。 
* proto路径（使用--proto_path=或-I命令行标志指定）将替换为输出路径（使用--cpp_out=标志指定）。  

因此，例如，假设您按如下方式调用编译器：  
```
protoc --proto_path=src --cpp_out=build/gen src/foo.proto src/bar/baz.proto
```
编译器将读取这些文件src/foo.proto，并src/bar/baz.proto和产生四个输出文件：
build/gen/foo.pb.h，build/gen/foo.pb.cc，build/gen/bar/baz.pb.h，build/gen/bar/baz.pb.cc  build/gen/bar如有必要，编译器将自动创建目录，但不会创建build或build/gen; 他们必须已经存在。
#### 2.1.1.2. 包  
```
package foo.bar
```
文件中的所有声明都将驻留在foo :: bar命名空间中。
#### 2.1.1.3. Messages
出一个简单的消息声明：
```
message Foo {}
```
编译器生成一个名为的类Foo，该类公开派生自google::protobuf::Message。这个班是一个具体的班级; 没有纯虚拟方法未实现。根据优化模式，虚拟Message但不是纯虚拟的方法可能会被覆盖Foo，也可能不会被覆盖。默认情况下，Foo实现所有方法的专用版本以获得最大速度。但是，如果.proto文件包含以下行：  
```
option optimize_for = CODE_SIZE;
```
TODO: https://developers.google.com/protocol-buffers/docs/reference/cpp-generated#invocation

#### 2.1.1.4. Fields
#### 2.1.1.5. Any 
#### 2.1.1.6. Oneof
#### 2.1.1.7. Enumerations
#### 2.1.1.8. Extensions
#### 2.1.1.9. Arena Allocation
#### 2.1.1.10. Services
#### 2.1.1.11. Plugin Insertion Points
### 2.1.2. 缓冲区优化
### 2.1.3. API
## 2.2. Go指南
### 2.2.1. 生成指南
### 2.2.2. API
## 2.3. Java指南
### 2.3.1. 生成指南
### 2.3.2. API
## 2.4. Python指南
### 2.4.1. 生成指南
### 2.4.2. API