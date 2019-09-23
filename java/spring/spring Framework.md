# 1. 概览
Spring可以轻松创建Java企业应用程序。它提供了在企业环境中使用Java语言所需的一切，支持Groovy和Kotlin作为JVM上的替代语言，并可根据应用程序的需要灵活地创建多种体系结构。从Spring Framework 5.0开始，Spring需要JDK 8+（Java SE 8+），并且已经为JDK 9提供了开箱即用的支持。  

The Spring Framework is divided into modules. Applications can choose which modules they need. At the heart are the modules of the core container, including a configuration model and a dependency injection mechanism. Beyond that, the Spring Framework provides foundational support for different application architectures, including messaging, transactional data and persistence, and web. It also includes the Servlet-based Spring MVC web framework and, in parallel, the Spring WebFlux reactive web framework.  
## 历史和框架
Spring于2003年成立，是对早期J2EE规范复杂性的回应 。虽然有些人认为Java EE和Spring处于竞争中，但Spring实际上是对Java EE的补充。Spring编程模型不包含Java EE平台规范; 相反，它集成了EE保护伞中精心挑选的个别规格：  
*  Servlet API (JSR 340)   
*  WebSocket API (JSR 356)   
*  Concurrency Utilities (JSR 236)   
*  JSON Binding API (JSR 367)   
*  Bean Validation (JSR 303)   
*  JPA (JSR 338)   
*  JMS (JSR 914)   
*  as well as JTA/JCA setups for transaction coordination, if necessary.   

Spring Framework还支持依赖注入（JSR 330）和Common Annotations（JSR 250）规范，应用程序开发人员可以选择使用这些规范，而不是Spring Framework提供的Spring特定机制。  
从Spring Framework 5.0开始，Spring至少需要Java EE 7级别（例如Servlet 3.1 +，JPA 2.1+） - 同时在Java EE 8级别提供与新API的开箱即用集成（例如，Servlet 4.0，JSON绑定API）在运行时遇到。这使Spring与Tomcat 8和9，WebSphere 9和JBoss EAP 7完全兼容。  
随着时间的推移，Java EE在应用程序开发中的作用也在不断发展。在Java EE和Spring的早期，创建了应用程序以部署到应用程序服务器。今天，在Spring Boot的帮助下，应用程序以devops和云友好的方式创建，Servlet容器嵌入并且变得微不足道。从Spring Framework 5开始，WebFlux应用程序甚至不直接使用Servlet API，并且可以在不是Servlet容器的服务器（例如Netty）上运行。  
Spring继续创新并不断发展。除了Spring Framework之外，还有其他项目，例如Spring Boot，Spring Security，Spring Data，Spring Cloud，Spring Batch等。  
##  设计理念
当您了解框架时，重要的是不仅要知道它的作用，还要了解它遵循的原则。以下是Spring Framework的指导原则：  
*  提供各个层面的选择。Spring允许您尽可能晚地推迟设计决策。例如，您可以通过配置切换持久性提供程序，而无需更改代码。许多其他基础架构问题以及与第三方API的集成也是如此。  
*  适应不同的观点。Spring拥抱灵活性，并不认为应该如何做。它以不同的视角支持广泛的应用需求。
*  保持强大的向后兼容性。Spring的演变经过精心设计，可以在版本之间进行一些重大改变。Spring支持精心挑选的JDK版本和第三方库，以便于维护依赖于Spring的应用程序和库。
*  关心API设计。Spring团队花了很多心思和时间来制作直观的API，这些API在很多版本和多年中都有用。
*  为代码质量设定高标准。Spring Framework强调有意义，最新且准确的Javadoc。它是极少数项目之一，可以声称干净的代码结构，包之间没有循环依赖。
## 入门  
如果您刚刚开始使用Spring，您可能希望通过创建基于Spring Boot的应用程序来开始使用Spring Framework 。Spring Boot提供了一种快速（和固执己见）的方式来创建一个生产就绪的基于Spring的应用程序。它基于Spring Framework，支持约定优于配置，旨在帮助您尽快启动和运行。  

# 2. Core
其中最重要的是Spring Framework的控制反转（IoC）容器。Spring框架的IoC容器的全面处理紧随其后，全面覆盖了Spring的面向切面编程（AOP）技术。Spring Framework有自己的AOP框架，它在概念上易于理解，并且成功地解决了Java企业编程中AOP要求的80％最佳点。  
## IOC容器
### Spring IOC容器和Bean简介  
本章介绍了Spring Framework实现的控制反转（IoC）[ 1 ]原理。IoC也称为依赖注入（DI）。这是一个过程，通过这个过程，对象定义它们的依赖关系，即它们使用的其他对象，只能通过构造函数参数，工厂方法的参数，或者在构造或从工厂方法返回后在对象实例上设置的属性。 。然后容器 在创建bean时注入这些依赖项。这个过程基本上是相反的，因此称为控制反转（IoC），bean本身通过使用类的直接构造或诸如服务定位器模式之类的机制来控制其依赖关系的实例化或位置。  
在org.springframework.beans和org.springframework.context包是Spring框架的IoC容器的基础。该 BeanFactory 接口提供了一种能够管理任何类型对象的高级配置机制。 ApplicationContext 是一个BeanFactory的子类。它增加了与Spring的AOP功能的更容易的集成; 消息资源处理（用于国际化），事件发布; 和特定于应用程序层的上下文，例如WebApplicationContext 在Web应用程序中使用的上下文。  
简而言之，它BeanFactory提供了配置框架和基本功能，并ApplicationContext添加了更多特定于企业的功能。它ApplicationContext是完整的超集，BeanFactory在本章中仅用于Spring的IoC容器的描述。有关使用BeanFactory而不是ApplicationContext,引用 BeanFactory的更多信息。  
在Spring中，构成应用程序主干并由Spring IoC 容器管理的对象称为bean。bean是一个由Spring IoC容器实例化，组装和管理的对象。否则，bean只是应用程序中许多对象之一。Bean及其之间的依赖 关系反映在容器使用的配置元数据中。  
### 容器概述   
该接口org.springframework.context.ApplicationContext代表Spring IoC容器，负责实例化，配置和组装上述bean。容器通过读取配置元数据获取有关要实例化，配置和组装的对象的指令。配置元数据以XML，Java注释或Java代码表示。它允许您表达组成应用程序的对象以及这些对象之间丰富的相互依赖性。  
Spring的开箱即用的几个ApplicationContext接口实现。在独立应用程序中，通常会创建一个ClassPathXmlApplicationContext 或的实例 FileSystemXmlApplicationContext。虽然XML一直是定义配置元数据的传统格式，但您可以通过提供少量XML配置来声明性地支持这些额外的元数据格式，从而指示容器使用Java注释或代码作为元数据格式。    

# 3. Testing

# 4. Data Access

# 5. WebServlet

# 6. WebReactive

# 7. Integration

# 8. Langurage

# 注意点
1. beanfacotry 懒加载  applicationContext一次加载单例的所有
2. ioc三种注入方式:构造,set以及其变种,注解
3. 对象的声明(bean): 构造,静态工厂,实例工厂
4. Component父类注解以及repository,service,Controller,不写value的值即为短类名的驼峰表示法
5. 注入注解:autowared按照类型,如果歧义则按照属性名称找id,Qualifier在属性上需要与autowared配合指定id(在方法上可以单独使用,常见使用配置类的传参),resource注解需要指定id.
6. 新注解:import注解导入配置类,propertySource(4.3之前需要先声明bean-propertySourcePlaceHolderConfiger),bean,configuration,componentScan
7. spring junit整合,(本质junit的Test注解只是封装了main函数),包,@RunWith(SpringJUnit4ClassRunner.class)+@ContextConfiguration(classes = )/@ContextConfiguration(locations = )即可
8. 动态代理1,jdk方案  
>>   jdk属于官方的代理方案,基于接口实现,具体使用时需要Proxy.newInstance()
9.   动态代理2,cglib方案  
>>   需要一个被代理类不能为final的,基于子类的一种实现,需要Enhance.create(class,callback),其中需要写callback的接口实现,一般实现callback的子接口(MethodInterceptor), 其中的参数多了一个proxyMethod,使用方法相同.  
