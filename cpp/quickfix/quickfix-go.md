# 1. 安装
## 1.1. build 和install
```
go get github.com/quickfixgo/quickfix  
```
## 1.2. 生成数据库  
Everything needed to generate your database is in the _sql directory. For MySQL, there are the script and batch files create.sh and create.bat. These scripts will work on a newly installed MySQL database with default permisions. The scripts will try to generate the database using the root MySQL account with no password. If you need to use a different account or need a password, you will have to edit the script. To select a different user, simply change 'root' to another user. To add a password, use pass the -p option after the username. Similar scripts are provided for MSSQL, PostgreSQL and Oracle.  
# 2. 开始
## 2.1. Api
package 包
```
import "github.com/quickfixgo/quickfix"
```  
package quickfix是FIX协议的全功能消息传递引擎。它是流行的C ++ QuickFIX引擎的100％Go开源实现.  
### 2.1.1. 常量
```
const (
    BeginStringFIX40  = "FIX.4.0"
    BeginStringFIX41  = "FIX.4.1"
    BeginStringFIX42  = "FIX.4.2"
    BeginStringFIX43  = "FIX.4.3"
    BeginStringFIX44  = "FIX.4.4"
    BeginStringFIXT11 = "FIXT.1.1"
)
```
FIX BeginString string values
```
const (
    ApplVerIDFIX27    = "0"
    ApplVerIDFIX30    = "1"
    ApplVerIDFIX40    = "2"
    ApplVerIDFIX41    = "3"
    ApplVerIDFIX42    = "4"
    ApplVerIDFIX43    = "5"
    ApplVerIDFIX44    = "6"
    ApplVerIDFIX50    = "7"
    ApplVerIDFIX50SP1 = "8"
    ApplVerIDFIX50SP2 = "9"
)
```
FIX ApplVerID字符串值  
### 2.1.2. 变量
```
var ErrDoNotSend = errors.New("Do Not Send")
```
ErrDoNotSend是一个方便错误，表示ToApp中的DoNotSend
### 2.1.3. func ParseMessage
ParseMessage从包装FIX消息的字节切片构造消息。
```
func ParseMessage(msg *Message, rawMessage *bytes.Buffer) (err error)
```
### 2.1.4. func ParseMessageWithDataDictionary
```
func ParseMessageWithDataDictionary(
    msg *Message,
    rawMessage *bytes.Buffer,
    transportDataDictionary *datadictionary.DataDictionary,
    applicationDataDictionary *datadictionary.DataDictionary,
) (err error)
```  
ParseMessageWithDataDictionary使用可选的会话和应用程序DataDictionary从包装FIX消息的字节切片构造一个Message.  
### 2.1.5. func Send(m Messagable) (err error)
Send确定会话使用头字段BeginString，TargetCompID，SenderCompID发送Messagable
### 2.1.6. func SendToTarget(m Messagable, sessionID SessionID) error  
SendToTarget基于sessionID发送消息。方便在FromApp中使用，因为它为传入消息提供会话ID
### 2.1.7. func UnregisterSession(sessionID SessionID) error  
UnregisterSession从已知会话集中删除会话
### 2.1.8. type Acceptor
Acceptor接受来自FIX客户端的连接并管理关联的会话
1. func NewAcceptor(app Application, storeFactory MessageStoreFactory, settings *Settings, logFactory LogFactory) (a *Acceptor, err error)   
NewAcceptor创建并初始化一个新的Acceptor。 
2. func (a *Acceptor) Start() error  
开始接受连接。  
3. func (a *Acceptor) Stop()  
停止注销现有会话，关闭其连接，并停止接受新连接。
### 2.1.9. type Application
```
type Application interface {
    //创建会话通知
    OnCreate(sessionID SessionID)

    //成功登录会话的通知.
    OnLogon(sessionID SessionID)

    //注销或断开会话的通知。
    OnLogout(sessionID SessionID)

    //管理员消息发送到目标的通知。
    ToAdmin(message *Message, sessionID SessionID)

    //将应用消息发送到目标的通知。
    ToApp(message *Message, sessionID SessionID) error

    //从目标收到管理员消息的通知。
    FromAdmin(message *Message, sessionID SessionID) MessageRejectError

    //从目标收到应用消息的通知。
    FromApp(message *Message, sessionID SessionID) MessageRejectError
}
```
应用程序界面应由FIX Applications实现。这是处理来自FIX会话的消息的主要接口。  
### 2.1.10. type Body
Body是FIX消息的主要应用程序部分  
* func (b *Body) Init()  
Init初始化FIX消息
* func (t Body) Len() int
* func (t Body) Less(i, j int) bool
* func (t Body) Swap(i, j int)
### 2.1.11. type ConditionallyRequiredSetting
ConditionalRequiredSetting表示缺少设置
* func (e ConditionallyRequiredSetting) Error() string 
### 2.1.12. type FIXBoolean
FIXBoolean是一个FIX布尔值，实现FieldValue。  
* func (f FIXBoolean) Bool() bool 
Bool将FIXBoolean值转换为bool   
* func (f *FIXBoolean) Read(bytes []byte) error  
* func (f FIXBoolean) Write() []byte  
### 2.1.13. type FIXBytes
FIXBytes是一个通用的FIX字段值，表示FieldValue。从FieldMap启用零拷贝读取  
* func (f *FIXBytes) Read(bytes []byte) (err error)
* func (f FIXBytes) Write() []byte
### 2.1.14. type FIXDecimal  
FIXDecimal是一个FIX浮点值，它实现任意精度的定点小数。实现FieldValue  
* func (d *FIXDecimal) Read(bytes []byte) (err error)
* func (d FIXDecimal) Write() []byte
### 2.1.15. type FIXFloat
* func (f FIXFloat) Float64() float64
* func (f *FIXFloat) Read(bytes []byte) error
* func (f FIXFloat) Write() []byte
### 2.1.16. type FIXInt
* func (f FIXInt) Int() int
* func (f *FIXInt) Read(bytes []byte) error
* func (f FIXInt) Write() []byte
### 2.1.17. type FIXString
*  func (f *FIXString) Read(bytes []byte) (err error)
*  func (f FIXString) String() string
*  func (f FIXString) Write() []byte
### 2.1.18. type FIXUTCTimestamp
* func (f *FIXUTCTimestamp) Read(bytes []byte) (err error)
* func (f FIXUTCTimestamp) Write() []byte
### 2.1.19. type Field
Field是Message中所有类型字段实现的接口  
```
type Field interface {
    FieldWriter
    FieldValueReader
}
```
### 2.1.20. type FieldGroup
FieldGroup是Message中所有类型组实现的接口  
```
type FieldGroupReader interface {
    Tag() Tag
    Read([]TagValue) ([]TagValue, error)
}
```
### 2.1.21. type FieldGroupReader
FieldGroupReader是用于读取FieldGroup的接口
```
type FieldGroupReader interface {
    Tag() Tag
    Read([]TagValue) ([]TagValue, error)
}
```
### 2.1.22. type FieldGroupWriter
FieldGroupWriter是用于编写FieldGroup的接口
```
type FieldGroupWriter interface {
    Tag() Tag
    Write() []TagValue
}
```
### 2.1.23. type FieldMap
FieldMap是构成Fix消息的FIX字段的集合  
*  func (m *FieldMap) Clear()  
清除从字段映射中清除所有字段  
*  func (m *FieldMap) CopyInto(to *FieldMap)  
CopyInto用这个覆盖给定的FieldMap  
*  func (m FieldMap) Get(parser Field) MessageRejectError  
获取解析此FieldMap中的字段。返回拒绝可能表示该字段不存在，或字段值无效。  
*  func (m FieldMap) GetBool(tag Tag) (bool, MessageRejectError)  
GetBool is a GetField wrapper for bool fields  
*  func (m FieldMap) GetBytes(tag Tag) ([]byte, MessageRejectError)  
GetBytes是[]字节字段的零拷贝GetField包装器  
*  func (m FieldMap) GetField(tag Tag, parser FieldValueReader) MessageRejectError
*  func (m FieldMap) GetGroup(parser FieldGroupReader) MessageRejectError
*  func (m FieldMap) GetInt(tag Tag) (int, MessageRejectError)
*  func (m FieldMap) GetString(tag Tag) (string, MessageRejectError)
*  func (m FieldMap) GetTime(tag Tag) (t time.Time, err MessageRejectError)
*  func (m FieldMap) Has(tag Tag) bool
*  func (t FieldMap) Len() int
*  func (t FieldMap) Less(i, j int) bool
*  func (m *FieldMap) Set(field FieldWriter) *FieldMap
*  func (m *FieldMap) SetBool(tag Tag, value bool) *FieldMap
*  func (m *FieldMap) SetBytes(tag Tag, value []byte) *FieldMap
*  func (m *FieldMap) SetField(tag Tag, field FieldValueWriter) *FieldMap
*  func (m *FieldMap) SetGroup(field FieldGroupWriter) *FieldMap
*  func (m *FieldMap) SetInt(tag Tag, value int) *FieldMap
*  func (m *FieldMap) SetString(tag Tag, value string) *FieldMap
*  func (t FieldMap) Swap(i, j int)
*  func (m FieldMap) Tags() []Tag
### 2.1.24. type FieldValue
```
type FieldValue interface {
    FieldValueWriter
    FieldValueReader
}
```
FieldValue接口用于向/从原始字节写入/提取类型化字段值  
### 2.1.25. type FieldValueReader
FieldValueReader是用于读取字段值的接口  
### 2.1.26. type FieldValueWriter
FieldValueWriter是用于写入字段值的接口
### 2.1.27. type FieldWriter
### 2.1.28. type Group
组是在重复组中出现的一组字段  
*  func (t Group) Len() int
*  func (t Group) Less(i, j int) bool
*  func (t Group) Swap(i, j int)
### 2.1.29. type GroupItem
```
type GroupItem interface {
    //Tag returns the tag identifying this GroupItem
    Tag() Tag

    //Parameter to Read is tagValues.  For most fields, only the first tagValue will be required.
    //The length of the slice extends from the tagValue mapped to the field to be read through the
    //following fields. This can be useful for GroupItems made up of repeating groups.
    //
    //The Read function returns the remaining tagValues not processed by the GroupItem. If there was a
    //problem reading the field, an error may be returned
    Read([]TagValue) ([]TagValue, error)

    //Clone makes a copy of this GroupItem
    Clone() GroupItem
}
```
GroupItem接口用于构造重复组模板  
* func GroupElement(tag Tag) GroupItem
### 2.1.30. type GroupTemplate
* func (gt GroupTemplate) Clone() GroupTemplate
### 2.1.31. type Header  
```
type Header struct{ FieldMap }
```
Header是FIX消息的第一部分
* func (h *Header) Init()
* func (t Header) Len() int
* func (t Header) Less(i, j int) bool
* func (t Header) Swap(i, j int)  
### 2.1.32. type IncorrectFormatForSetting
IncorrectFormatForSetting表示格式不正确的设置  
* func (e IncorrectFormatForSetting) Error() string
### 2.1.33. type Initiator
Initiator为所有会话启动连接并处理消息。  
* func NewInitiator(app Application, storeFactory MessageStoreFactory, appSettings *Settings, logFactory LogFactory) (*Initiator, error)
NewInitiator创建并初始化一个新的Initiator。  
* func (i *Initiator) Start() (err error)
* func (i *Initiator) Stop()
### 2.1.34. type Log
```
type Log interface {
    //log incoming fix message
    OnIncoming([]byte)
    //log outgoing fix message
    OnOutgoing([]byte)
    //log fix event
    OnEvent(string)
    //log fix event according to format specifier
    OnEventf(string, ...interface{})
}
```
Log是用于记录FIX消息和事件的通用接口。  
### 2.1.35. type LogFactory
```
type LogFactory interface {
    //global log
    Create() (Log, error)

    //session specific log
    CreateSessionLog(sessionID SessionID) (Log, error)
}
```
LogFactory接口创建全局和会话特定的Log实例  
* func NewFileLogFactory(settings *Settings) (LogFactory, error)
NewFileLogFactory创建一个LogFactory实例，用于将消息和事件写入文件。全局和会话日志文件的位置通过FileLogPath配置。  
* func NewNullLogFactory() LogFactory
* func NewScreenLogFactory() LogFactory
### 2.1.36. type Messagable
```
type Messagable interface {
    ToMessage() *Message
}
```
Messagable是一个消息或可以转换为消息的东西  
### 2.1.37. type Message
```
type Message struct {
    Header  Header
    Trailer Trailer
    Body    Body

    //ReceiveTime is the time that this message was read from the socket connection
    ReceiveTime time.Time
    // contains filtered or unexported fields
}
```
* func NewMessage() *Message
* func (m *Message) CopyInto(to *Message)
* func (m *Message) IsMsgTypeOf(msgType string) bool
* func (m *Message) MsgType() (string, MessageRejectError)
* func (m *Message) String() string
* func (m *Message) ToMessage() *Message
### 2.1.38. type MessageRejectError
*  func ConditionallyRequiredFieldMissing(tag Tag) MessageRejectError
*  func IncorrectDataFormatForValue(tag Tag) MessageRejectError
*  func InvalidMessageType() MessageRejectError
*  func InvalidTagNumber(tag Tag) MessageRejectError
*  func NewBusinessMessageRejectError(err string, rejectReason int, refTagID *Tag) MessageRejectError
*  func NewMessageRejectError(err string, rejectReason int, refTagID *Tag) MessageRejectError
*  func RequiredTagMissing(tag Tag) MessageRejectError
*  func TagNotDefinedForThisMessageType(tag Tag) MessageRejectError
*  func TagSpecifiedWithoutAValue(tag Tag) MessageRejectError
*  func UnsupportedMessageType() MessageRejectError
*  func ValueIsIncorrect(tag Tag) MessageRejectError
### 2.1.39. type MessageRoute
MessageRoute是一个可以处理fromApp / fromAdmin回调的函数  
### 2.1.40. type MessageRouter
MessageRouter是MessageRoutes的互斥锁  
*  func NewMessageRouter() *MessageRouter
*  func (c MessageRouter) AddRoute(beginString string, msgType string, router MessageRoute)
*  func (c MessageRouter) Route(msg *Message, sessionID SessionID) MessageRejectError
### 2.1.41. type MessageStore
```
type MessageStore interface {
    NextSenderMsgSeqNum() int
    NextTargetMsgSeqNum() int

    IncrNextSenderMsgSeqNum() error
    IncrNextTargetMsgSeqNum() error

    SetNextSenderMsgSeqNum(next int) error
    SetNextTargetMsgSeqNum(next int) error

    CreationTime() time.Time

    SaveMessage(seqNum int, msg []byte) error
    GetMessages(beginSeqNum, endSeqNum int) ([][]byte, error)

    Refresh() error
    Reset() error

    Close() error
}
```
### 2.1.42. type MessageStoreFactory
```
type MessageStoreFactory interface {
    Create(sessionID SessionID) (MessageStore, error)
}
```
会话使用MessageStoreFactory接口来创建会话特定的消息存储库  
*  func NewFileStoreFactory(settings *Settings) MessageStoreFactory  
NewFileStoreFactory返回MessageStoreFactory的基于文件的实现  
*  func NewMemoryStoreFactory() MessageStoreFactory
*  func NewMongoStoreFactory(settings *Settings) MessageStoreFactory
*  func NewMongoStoreFactoryPrefixed(settings *Settings, collectionsPrefix string) MessageStoreFactory
*  func NewSQLStoreFactory(settings *Settings) MessageStoreFactory
### 2.1.43. type RejectLogon
*  func (e RejectLogon) Error() string
*  func (RejectLogon) IsBusinessReject() bool
*  func (RejectLogon) RefTagID() *Tag
*  func (RejectLogon) RejectReason() int
### 2.1.44. type RepeatingGroup
*  func NewRepeatingGroup(tag Tag, template GroupTemplate) *RepeatingGroup
*  func (f *RepeatingGroup) Add() *Group
*  func (f RepeatingGroup) Clone() GroupItem
*  func (f RepeatingGroup) Get(i int) *Group
*  func (f RepeatingGroup) Len() int
*  func (f *RepeatingGroup) Read(tv []TagValue) ([]TagValue, error)
*  func (f RepeatingGroup) Tag() Tag
*  func (f RepeatingGroup) Write() []TagValue
### 2.1.45. type SessionID
```
type SessionID struct {
    BeginString, TargetCompID, TargetSubID, TargetLocationID, SenderCompID, SenderSubID, SenderLocationID, Qualifier string
}
```
*  func (s SessionID) IsFIXT() bool
*  func (s SessionID) String() string
### 2.1.46. type SessionSettings
*  func NewSessionSettings() *SessionSettings
*  func (s SessionSettings) BoolSetting(setting string) (bool, error)
*  func (s *SessionSettings) DurationSetting(setting string) (val time.Duration, err error)
*  func (s *SessionSettings) HasSetting(setting string) bool
*  func (s *SessionSettings) Init()
*  func (s *SessionSettings) IntSetting(setting string) (val int, err error)
*  func (s *SessionSettings) Set(setting string, val string)
*  func (s *SessionSettings) Setting(setting string) (string, error)
### 2.1.47. type Tag
*  func (t Tag) IsHeader() bool
*  func (t Tag) IsTrailer() bool
### 2.1.48. type TagValue
*  func (tv TagValue) String() string
### 2.1.49. type TimestampPrecision
### 2.1.50. type Trailer
*  func (t *Trailer) Init()
*  func (t Trailer) Len() int
*  func (t Trailer) Less(i, j int) bool
*  func (t Trailer) Swap(i, j int)
[源文件](https://github.com/quickfixgo/quickfix)
## 2.2. 应用生成
```
package quickfix

type Application interface {
  //Notification of a session begin created.
  OnCreate(sessionID SessionID)

  //Notification of a session successfully logging on.
  OnLogon(sessionID SessionID)

  //Notification of a session logging off or disconnecting.
  OnLogout(sessionID SessionID)

  //Notification of admin message being sent to target.
  ToAdmin(message Message, sessionID SessionID)

  //Notification of app message being sent to target.
  ToApp(message Message, sessionID SessionID) error

  //Notification of admin message being received from target.
  FromAdmin(message Message, sessionID SessionID) MessageRejectError

  //Notification of app message being received from target.
  FromApp(message Message, sessionID SessionID) MessageRejectError
}
```
使用
```
package main

import (
  "flag"
  "github.com/quickfixgo/quickfix"
  "os"
)

func main() {
  flag.Parse()
  fileName := flag.Arg(0)

  //FooApplication is your type that implements the Application interface
  var app FooApplication

  cfg, _ := os.Open(fileName)
  appSettings, _ := quickfix.ParseSettings(cfg)
  storeFactory := quickfix.NewMemoryStoreFactory()
  logFactory, _ := quickfix.NewFileLogFactory(appSettings)
  acceptor, _ := quickfix.NewAcceptor(app, storeFactory, appSettings, logFactory)

  _ = acceptor.Start()
  //for condition == true { do something }
  acceptor.Stop()
}
```
## 2.3. 配置
```
# default settings for sessions
[DEFAULT]
ReconnectInterval=60
SenderCompID=TW

# session definition
[SESSION]
# inherit ReconnectInterval and SenderCompID from default
BeginString=FIX.4.1
TargetCompID=ARCA
StartTime=12:30:00
EndTime=23:30:00
HeartBtInt=20
SocketConnectPort=9823
SocketConnectHost=123.123.123.123
DataDictionary=somewhere/FIX41.xml

[SESSION]
BeginString=FIX.4.0
TargetCompID=ISLD
StartTime=12:00:00
EndTime=23:00:00
HeartBtInt=30
SocketConnectPort=8323
SocketConnectHost=23.23.23.23
DataDictionary=somewhere/FIX40.xml

[SESSION]
BeginString=FIX.4.2
TargetCompID=INCA
StartTime=12:30:00
EndTime=21:30:00
# overide default setting for RecconnectInterval
ReconnectInterval=30
HeartBtInt=30
SocketConnectPort=6523
SocketConnectHost=3.3.3.3
# (optional) alternate connection ports and hosts to cycle through on failover
SocketConnectPort1=8392
SocketConnectHost1=8.8.8.8
SocketConnectPort2=2932
SocketConnectHost2=12.12.12.12
DataDictionary=somewhere/FIX42.xml
```
## 2.4. 校验 
如果配置为验证，QuickFIX / Go将在它们到达您的应用程序之前验证并拒绝任何格式错误的消息。 XML文件定义会话支持的消息，字段和值。 spec /目录中包含几个标准文件。  
```
<fix type="FIX" major="4" minor="1">
  <header>
    <field name="BeginString" required="Y"/>
    ...
  </header>
  <trailer>
    <field name="CheckSum" required="Y"/>
    ...
  </trailer>
  <messages>
    <message name="Heartbeat" msgtype="0" msgcat="admin">
      <field name="TestReqID" required="N"/>
    </message>
    ...
    <message name="NewOrderSingle" msgtype="D" msgcat="app">
      <field name="ClOrdID" required="Y"/>
      ...
    </message>
    ...
  </messages>
  <fields>
    <field number="1" name="Account" type="CHAR" />
    ...
    <field number="4" name="AdvSide" type="CHAR">
     <value enum="B" description="BUY" />
     <value enum="S" description="SELL" />
     <value enum="X" description="CROSS" />
     <value enum="T" description="TRADE" />
   </field>
   ...
  </fields>
</fix>
```
验证器不会拒绝条件必需的字段，因为它们的规则没有明确定义。从应用程序的FromApp或FromAdmin方法返回MessageRejectError将导致邮件被拒绝。
# 3. 使用Messages  
## 3.1. 接收
您将要查看的大多数消息都将到达您的应用程序的FromApp功能。所有消息都有标题和预告片。如果要获取“标题”或“预告片”字段，则必须从“标题”或“预告片”嵌入式结构中访问这些字段。所有其他字段都可以在Body嵌入式结构中访问。 
QuickFIX / Go具有标准规范中定义的所有消息和字段的类型。接收消息的最简单，最安全的方法是使用QuickFIX / Go MessageRouter生成的消息类型.默认情况下，任何未为will建立路由的消息都会返回UnsupportedMessageType拒绝。 
```
import (
  "github.com/quickfixgo/quickfix"
  "github.com/quickfixgo/quickfix/field"
  "github.com/quickfixgo/quickfix/fix41/newordersingle"
)  
type MyApplication struct {
  *quickfix.MessageRouter
}
func (m *MyApplication) init() {
  m.MessageRouter=quickfix.NewMessageRouter()
  m.AddRoute(newordersingle.Route(m.onNewOrderSingle))
}
func (m *MyApplication) FromApp(msg quickfix.Message, sessionID quickfix.SessionID) (err quickfix.MessageRejectError) {
  return m.Route(msg, sessionID)
}
func (m *MyApplication) onNewOrderSingle(msg newordersingle.NewOrderSingle, sessionID quickfix.SessionID) (err quickfix.MessageRejectError) {
  clOrdID, err := msg.GetClOrdID()
  if err != nil {
    return
  }

  //compile time error!! field not defined in FIX41
  clearingAccount, err := msg.GetClearingAccount()

  ...
  return
}
```   
您还可以通过直接检查Message来绕过MessageRouter并键入安全类。执行此操作的首选方法是使用QuickFIX / Go生成的字段类型。 
```
func (m *MyApplication) FromApp(msg quickfix.Message, sessionID quickfix.SessionID) (err quickfix.MessageRejectError) {
  var price field.PriceField
  if err = msg.Body.Get(&field); err!=nil {
    return
  }

  ...
  return
}
``` 
或者你可以采用最不安全的路线。 
```
func (m *MyApplication) FromApp(msg quickfix.Message, sessionID quickfix.SessionID) (err quickfix.MessageRejectError) {
  var field quickfix.FIXString
  if err = msg.Body.GetField(quickfix.Tag(44), &field); err!=nil {
    return
  }

  ...
  return
}
```
## 3.2. 发送
可以使用Send和SendToTarget函数将消息发送到计数器方。  
```
//Send determines the session to send Messagable using header fields BeginString, TargetCompID, SenderCompID
func Send(m Messagable) error

//SendToTarget sends Messagable based on the sessionID. Convenient for use in FromApp since it provides a session ID for incoming messages
func SendToTarget(m Messagable, sessionID SessionID) error
```
## 3.3. Demo
### 客户端例子
```
package traderclient

import (
	"fmt"
	"github.com/quickfixgo/quickfix"
)

type TradeClient struct {
}

func (c TradeClient) OnLogon(sessionID quickfix.SessionID) {
	return
}

func (c TradeClient) OnLogout(sessionID quickfix.SessionID) {
	return
}

func (c TradeClient) ToAdmin(message *quickfix.Message, sessionID quickfix.SessionID) {
	return
}

func (c TradeClient) ToApp(message *quickfix.Message, sessionID quickfix.SessionID) error {
	fmt.Printf("Sending %s\n", message)
	return nil
}

func (c TradeClient) FromAdmin(message *quickfix.Message, sessionID quickfix.SessionID) quickfix.MessageRejectError {
	return nil
}

func (c TradeClient) FromApp(message *quickfix.Message, sessionID quickfix.SessionID) quickfix.MessageRejectError {
	fmt.Printf("FromApp: %s\n", message.String())
	return nil
}

func (c TradeClient) OnCreate(sessionId quickfix.SessionID) {
	return
}


func Start(){
  flag.Parse()
	cfgFileName := path.Join("./cfg", "quick2.cfg")
	if flag.NArg() > 0 {
		cfgFileName = flag.Arg(0)
	}
	cfg, e := os.Open(cfgFileName)
	if e != nil {
		fmt.Printf("Error opening %v ,%v \n", cfgFileName, e)
		return
	}
	appSetting, err := quickfix.ParseSettings(cfg)
	if err != nil {
		fmt.Println("Error reading cfg,", err)
		return
	}
	app := TradeClient{}
	logFacotry, errLof := quickfix.NewFileLogFactory(appSetting)
	if errLof != nil {
		fmt.Println("fileFacory file")
		return
	}
	var errIni error
	initiator, errIni = quickfix.NewInitiator(app, quickfix.NewMemoryStoreFactory(), appSetting, logFacotry)
	if errIni != nil {
		fmt.Printf("Unable to create Initiator: %s\n", err)
		return
	}
	initiator.Start()
  initiator.Stop()
}
```
### 服务端Demo
