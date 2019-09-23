# 1. 快速入门
在您第1次接触和学习Spring框架的时候，是否因为其繁杂的配置而退却了？在你第n次使用Spring框架的时候，是否觉得一堆反复黏贴的配置有一些厌烦？那么您就不妨来试试使用Spring Boot来让你更易上手，更简单快捷地构建Spring应用！  
Spring Boot让我们的Spring应用变的更轻量化。比如：你可以仅仅依靠一个Java类来运行一个Spring引用。你也可以打包你的应用为jar并通过使用java -jar来运行你的Spring Web应用。  
Spring Boot的主要优点：  
* 为所有Spring开发者更快的入门 
* 开箱即用，提供各种默认配置来简化项目配置  
* 内嵌式容器简化Web项目  
* 没有冗余代码生成和XML配置的要求
## 1.1. 快速入门
本章主要目标完成Spring Boot基础项目的构建，并且实现一个简单的Http请求处理，通过这个例子对Spring Boot有一个初步的了解，并体验其结构简单、开发快速的特性。  
## 1.2. 系统要求
Java 7及以上
Spring Framework 4.1.5及以上  
## 1.3. 使用Maven构建项目  
采用IDEA生成spring boot的方式.  
## 1.4. 引入web模块
当前的pom.xml内容如下，仅引入了两个模块：  
*  spring-boot-starter：核心模块，包括自动配置支持、日志和YAML  
*  spring-boot-starter-test：测试模块，包括JUnit、Hamcrest、Mockito  
```
<dependencies>
    <dependency>
        <groupId>org.springframework.boot</groupId>
		<artifactId>spring-boot-starter</artifactId>
	</dependency>

	<dependency>
		<groupId>org.springframework.boot</groupId>
		<artifactId>spring-boot-starter-test</artifactId>
		<scope>test</scope>
	</dependency>
</dependencies>
```
引入Web模块，需添加spring-boot-starter-web模块：  
```
<dependency>
	<groupId>org.springframework.boot</groupId>
	<artifactId>spring-boot-starter-web</artifactId>
</dependency>
```
## 1.5. 编写HelloWorld服务
创建web包中的  
```
@RestController
public class HelloController {

    @RequestMapping("/hello")
    public String index() {
        return "Hello World";
    }

}
```
启动主程序，打开浏览器访问http://localhost:8080/hello，可以看到页面输出Hello World  
## 1.6. 编写单元测试用例
打开的src/test/下的测试入口Chapter1ApplicationTests类。下面编写一个简单的单元测试来模拟http请求，具体如下：  
```
@RunWith(SpringJUnit4ClassRunner.class)
@SpringApplicationConfiguration(classes = MockServletContext.class)
@WebAppConfiguration
public class Demo01ApplicationTests {
    private MockMvc mvc;
    @Before
    public void setUp(){
        mvc= MockMvcBuilders.standaloneSetup(new HelloController()).build();
    }
    @Test
    public void getHello() throws Exception {
        mvc.perform(MockMvcRequestBuilders.get("/hello").accept(MediaType.APPLICATION_JSON))
                .andExpect(status().isOk())
                .andExpect(content().string(equalTo("hello World"))
                );
    }

}
```
注意springboot版本 ` <version>1.3.2.RELEASE</version>`
# 2. Spring Boot开发Web应用  
## 2.1. 静态资源访问
在我们开发Web应用的时候，需要引用大量的js、css、图片等静态资源。  
**默认配置**  
Spring Boot默认提供静态资源目录位置需置于classpath下，目录名需符合如下规则：  
```
/static
/public
/resources
/META-INF/resources
```
举例：我们可以在src/main/resources/目录下创建static，在该位置放置一个图片文件。启动程序后，尝试访问http://localhost:8080/D.jpg。如能显示图片，配置成功。  
## 2.2. 渲染Web页面
在之前的示例中，我们都是通过@RestController来处理请求，所以返回的内容为json对象。那么如果需要渲染html页面的时候，要如何实现呢？  
**模板引擎**  
在动态HTML实现上Spring Boot依然可以完美胜任，并且提供了多种模板引擎的默认配置支持，所以在推荐的模板引擎下，我们可以很快的上手开发动态网站。  
Spring Boot提供了默认配置的模板引擎主要有以下几种：  
```
Thymeleaf
FreeMarker
Velocity
Groovy
Mustache
```  
Spring Boot建议使用这些模板引擎，避免使用JSP，若一定要使用JSP将无法实现Spring Boot的多种特性，具体可见后文：支持JSP的配置  
当你使用上述模板引擎中的任何一个，它们默认的模板配置路径为：src/main/resources/templates。当然也可以修改这个路径，具体如何修改，可在后续各模板引擎的配置属性中查询并修改。  
### 2.2.1. Thymeleaf  
Thymeleaf是一个XML/XHTML/HTML5模板引擎，可用于Web与非Web环境中的应用开发。它是一个开源的Java库，基于Apache License 2.0许可，由Daniel Fernández创建，该作者还是Java加密库Jasypt的作者。  
Thymeleaf提供了一个用于整合Spring MVC的可选模块，在应用开发中，你可以使用Thymeleaf来完全代替JSP或其他模板引擎，如Velocity、FreeMarker等。Thymeleaf的主要目标在于提供一种可被浏览器正确显示的、格式良好的模板创建方式，因此也可以用作静态建模。你可以使用它创建经过验证的XML与HTML模板。相对于编写逻辑或代码，开发者只需将标签属性添加到模板中即可。接下来，这些标签属性就会在DOM（文档对象模型）上执行预先制定好的逻辑。  
```
<table>
  <thead>
    <tr>
      <th th:text="#{msgs.headers.name}">Name</td>
      <th th:text="#{msgs.headers.price}">Price</td>
    </tr>
  </thead>
  <tbody>
    <tr th:each="prod : ${allProducts}">
      <td th:text="${prod.name}">Oranges</td>
      <td th:text="${#numbers.formatDecimal(prod.price,1,2)}">0.99</td>
    </tr>
  </tbody>
</table>
```
可以看到Thymeleaf主要以属性的方式加入到html标签中，浏览器在解析html时，当检查到没有的属性时候会忽略，所以Thymeleaf的模板可以通过浏览器直接打开展现，这样非常有利于前后端的分离。    
在Spring Boot中使用Thymeleaf，只需要引入下面依赖，并在默认的模板路径src/main/resources/templates下编写模板文件即可完成。  
```
<dependency>
	<groupId>org.springframework.boot</groupId>
	<artifactId>spring-boot-starter-thymeleaf</artifactId>
</dependency>
```
在完成配置之后，举一个简单的例子，在快速入门工程的基础上，举一个简单的示例来通过Thymeleaf渲染一个页面。  
Controller的编写
```
@Controller
public class HelloController {
    @RequestMapping("/")
    public String index(ModelMap map) {
        map.addAttribute("host", "www.riversy.xyz");
        return "index";
    }
}
```
模版编写,如果不修改路径,必须放在resources的templates目录下
```
<!DOCTYPE html>
<html>
<head lang="en">
    <meta charset="UTF-8" />
    <title></title>
</head>
<body>
<h1 th:text="${host}">Hello World</h1>
</body>
</html>
```
启动即可访问.  
**Thymeleaf的默认参数配置**  
如有需要修改默认配置的时候，只需复制下面要修改的属性到application.properties中，并修改成需要的值，如修改模板文件的扩展名，修改默认的模板路径等。  
```
# Enable template caching.
spring.thymeleaf.cache=true 
# Check that the templates location exists.
spring.thymeleaf.check-template-location=true 
# Content-Type value.
spring.thymeleaf.content-type=text/html 
# Enable MVC Thymeleaf view resolution.
spring.thymeleaf.enabled=true 
# Template encoding.
spring.thymeleaf.encoding=UTF-8 
# Comma-separated list of view names that should be excluded from resolution.
spring.thymeleaf.excluded-view-names= 
# Template mode to be applied to templates. See also StandardTemplateModeHandlers.
spring.thymeleaf.mode=HTML5 
# Prefix that gets prepended to view names when building a URL.
spring.thymeleaf.prefix=classpath:/templates/ 
# Suffix that gets appended to view names when building a URL.
spring.thymeleaf.suffix=.html  spring.thymeleaf.template-resolver-order= # Order of the template resolver in the chain. spring.thymeleaf.view-names= # Comma-separated list of view names that can be resolved.
```
**支持JSP的配置**  
Spring Boot并不建议使用，但如果一定要使用，可以参考此工程作为脚手架：[jsp](https://github.com/spring-projects/spring-boot/tree/v1.3.2.RELEASE/spring-boot-samples/spring-boot-sample-web-jsp)  
# 3. springBoot 工程结构推荐
## 3.1. 工程结构（最佳实践）  
Spring Boot框架本身并没有对工程结构有特别的要求，但是按照最佳实践的工程结构可以帮助我们减少可能会遇见的坑，尤其是Spring包扫描机制的存在，如果您使用最佳实践的工程结构，可以免去不少特殊的配置工作。  
## 3.2. 典型示例  
*  root package：com.example.myproject，所有的类和其他package都在root package之下。  
*  应用主类：Application.java，该类直接位于root package下。通常我们会在应用主类中做一些框架配置扫描等配置，我们放在root package下可以帮助程序减少手工配置来加载到我们希望被Spring加载的内容    
*  com.example.myproject.domain包：用于定义实体映射关系与数据访问相关的接口和实现  
*  com.example.myproject.service包：用于编写业务逻辑相关的接口与实现  
*  com.example.myproject.web：用于编写Web层相关的实现，比如：Spring MVC的Controller等  
```
com
  +- example
    +- myproject
      +- Application.java
      |
      +- domain
      |  +- Customer.java
      |  +- CustomerRepository.java
      |
      +- service
      |  +- CustomerService.java
      |
      +- web
      |  +- CustomerController.java
      |
```
上面的结构中，root package与应用主类的位置是整个结构的关键。由于应用主类在root package中，所以按照上面的规则定义的所有其他类都处于root package下的其他子包之后。默认情况下，Spring Boot的应用主类会自动扫描root package以及所有子包下的所有类来进行初始化。
## 3.3. 非典型结构下的初始化
那么如果，我们一定要加载非root package下的内容怎么办呢？  
方法一：使用@ComponentScan注解指定具体的加载包，比如：  
```
@SpringBootApplication
@ComponentScan(basePackages="com.example")
public class Bootstrap {

    public static void main(String[] args) {
        SpringApplication.run(Bootstrap.class, args);
    }

}
```
这种方法通过注解直接指定要扫描的包，比较直观。如果有这样的需求也是可以用的，但是原则上还是推荐以上面的典型结构来定义，这样也可以少写一些注解，代码更加简洁。  
方法二：使用@Bean注解来初始化，比如：  
```
@SpringBootApplication
public class Bootstrap {

    public static void main(String[] args) {
        SpringApplication.run(Bootstrap.class, args);
    }

    @Bean
    public CustomerController customerController() {
        return new CustomerController();
    }

}
```
这种方法在业务开发的时候并不是特别推荐，更适合用于框架封装等场景，关于更多封装上的技巧，后面我们在进阶教程中详细讲解。  
# 4. Spring Boot构建RESTful API与单元测试  
首先，回顾并详细说明一下在快速入门中使用的@Controller、@RestController、@RequestMapping注解。如果您对Spring MVC不熟悉并且还没有尝试过快速入门案例，建议先看一下快速入门的内容。    
*  @Controller：修饰class，用来创建处理http请求的对象  
*  @RestController：Spring4之后加入的注解，原来在@Controller中返回json需要@ResponseBody来配合，如果直接用@RestController替代@Controller就不需要再配置@ResponseBody，默认返回json格式。  
*  @RequestMapping：配置url映射   
下面我们尝试使用Spring MVC来实现一组对User对象操作的RESTful API，配合注释详细说明在Spring MVC中如何映射HTTP请求、如何传参、如何编写单元测试。  
RESTful API具体设计如下：  
![](./img/springbootrestfulapi-1.png)   
User实体定义：  
```
public class User { 
 
    private Long id; 
    private String name; 
    private Integer age; 
 
    // 省略setter和getter 
     
}
```
实现对User对象的操作接口  
domain包
```
public class User {
    private Long id;
    private String name;
    private Integer age;
}
```
web包
```
@RestController
@RequestMapping("/users")
public class UserController {
    static Map<Long, User> users= Collections.synchronizedMap(new HashMap<Long,User>());
    @RequestMapping(value = "/",method = RequestMethod.GET)
    public List<User> getUserList(){
        ArrayList<User> users = new ArrayList<>(UserController.users.values());
        return  users;
    }
    @RequestMapping(value="/", method=RequestMethod.POST)
    public String postUser(@ModelAttribute User user) {
        // 处理"/users/"的POST请求，用来创建User
        // 除了@ModelAttribute绑定参数之外，还可以通过@RequestParam从页面中传递参数
        users.put(user.getId(), user);
        return "success";
    }
    @RequestMapping(value="/{id}", method=RequestMethod.GET)
    public User getUser(@PathVariable Long id) {
        // 处理"/users/{id}"的GET请求，用来获取url中id值的User信息
        // url中的id可通过@PathVariable绑定到函数的参数中
        return users.get(id);
    }
    @RequestMapping(value="/{id}", method=RequestMethod.PUT)
    public String putUser(@PathVariable Long id, @ModelAttribute User user) {
        // 处理"/users/{id}"的PUT请求，用来更新User信息
        User u = users.get(id);
        u.setName(user.getName());
        u.setAge(user.getAge());
        users.put(id, u);
        return "success";
    }
    @RequestMapping(value="/{id}", method=RequestMethod.DELETE)
    public String deleteUser(@PathVariable Long id) {
        // 处理"/users/{id}"的DELETE请求，用来删除User
        users.remove(id);
        return "success";
    }
}
```
测试类  
```
@RunWith(SpringJUnit4ClassRunner.class)
@SpringApplicationConfiguration(classes = MockServletContext.class)
@WebAppConfiguration
public class ApplicationTests {
    private MockMvc mvc;
    @Before
    public void setUp(){
        mvc= MockMvcBuilders.standaloneSetup(new UserController()).build();
    }
    @Test
    public void testUserController() throws Exception {
        //测试UserController
        RequestBuilder request=null;
        //1,get查一下user列表,应该为空

        request=get("/users/");
        mvc.perform(request)
                .andExpect(status().isOk())
                .andExpect(content().string(equalTo("[]")));
        // 2、post提交一个user
        request = post("/users/")
                .param("id", "1")
                .param("name", "测试大师")
                .param("age", "20");
        mvc.perform(request)
                .andExpect(content().string(equalTo("success")));
        // 3、get获取user列表，应该有刚才插入的数据
        request = get("/users/");
        mvc.perform(request)
                .andExpect(status().isOk())
                .andExpect(content().string(equalTo("[{\"id\":1,\"name\":\"测试大师\",\"age\":20}]")));

        // 4、put修改id为1的user
        request = put("/users/1")
                .param("name", "测试终极大师")
                .param("age", "30");
        mvc.perform(request)
                .andExpect(content().string(equalTo("success")));

        // 5、get一个id为1的user
        request = get("/users/1");
        mvc.perform(request)
                .andExpect(content().string(equalTo("{\"id\":1,\"name\":\"测试终极大师\",\"age\":30}")));

        // 6、del删除id为1的user
        request = delete("/users/1");
        mvc.perform(request)
                .andExpect(content().string(equalTo("success")));

        // 7、get查一下user列表，应该为空
        request = get("/users/");
        mvc.perform(request)
                .andExpect(status().isOk())
                .andExpect(content().string(equalTo("[]")));
    }
}
```
至此，我们通过引入web模块（没有做其他的任何配置），就可以轻松利用Spring MVC的功能，以非常简洁的代码完成了对User对象的RESTful API的创建以及单元测试的编写。其中同时介绍了Spring MVC中最为常用的几个核心注解：@Controller,@RestController,RequestMapping以及一些参数绑定的注解：@PathVariable,@ModelAttribute,@RequestParam等。  
# 5. Spring Boot中使用Swagger2构建强大的RESTful API文档
 由于Spring Boot能够快速开发、便捷部署等特性，相信有很大一部分Spring Boot的用户会用来构建RESTful API。而我们构建RESTful API的目的通常都是由于多终端的原因，这些终端会共用很多底层业务逻辑，因此我们会抽象出这样一层来同时服务于多个移动端或者Web前端。  
 这样一来，我们的RESTful API就有可能要面对多个开发人员或多个开发团队：IOS开发、Android开发或是Web开发等。为了减少与其他团队平时开发期间的频繁沟通成本，传统做法我们会创建一份RESTful API文档来记录所有接口细节，然而这样的做法有以下几个问题：  
 *  由于接口众多，并且细节复杂（需要考虑不同的HTTP请求类型、HTTP头部信息、HTTP请求内容等），高质量地创建这份文档本身就是件非常吃力的事，下游的抱怨声不绝于耳。  
 *  随着时间推移，不断修改接口实现的时候都必须同步修改接口文档，而文档与代码又处于两个不同的媒介，除非有严格的管理机制，不然很容易导致不一致现象。  
 为了解决上面这样的问题，本文将介绍RESTful API的重磅好伙伴Swagger2，它可以轻松的整合到Spring Boot中，并与Spring MVC程序配合组织出强大RESTful API文档。它既可以减少我们创建文档的工作量，同时说明内容又整合入实现代码中，让维护文档和修改代码整合为一体，可以让我们在修改代码逻辑的同时方便的修改文档说明。另外Swagger2也提供了强大的页面测试功能来调试每个RESTful API。具体效果如下图所示：  
 依赖  
 ```
<dependency>
    <groupId>io.springfox</groupId>
    <artifactId>springfox-swagger2</artifactId>
    <version>2.2.2</version>
</dependency>
<dependency>
    <groupId>io.springfox</groupId>
    <artifactId>springfox-swagger-ui</artifactId>
    <version>2.2.2</version>
</dependency>
 ```
 domain包
 ```
 public class User {
    private Long id;
    private String name;
    private Integer age;
 }
 ```
 web包
 ```
 @RestController
@RequestMapping(value="/users")     // 通过这里配置使下面的映射都在/users下，可去除
public class UserController {

    static Map<Long, User> users = Collections.synchronizedMap(new HashMap<Long, User>());

    @ApiOperation(value="获取用户列表", notes="")
    @RequestMapping(value={""}, method=RequestMethod.GET)
    public List<User> getUserList() {
        List<User> r = new ArrayList<User>(users.values());
        return r;
    }

    @ApiOperation(value="创建用户", notes="根据User对象创建用户")
    @ApiImplicitParam(name = "user", value = "用户详细实体user", required = true, dataType = "User")
    @RequestMapping(value="", method=RequestMethod.POST)
    public String postUser(@RequestBody User user) {
        users.put(user.getId(), user);
        return "success";
    }

    @ApiOperation(value="获取用户详细信息", notes="根据url的id来获取用户详细信息")
    @ApiImplicitParam(name = "id", value = "用户ID", required = true, dataType = "Long", paramType = "path")
    @RequestMapping(value="/{id}", method=RequestMethod.GET)
    public User getUser(@PathVariable Long id) {
        return users.get(id);
    }

    @ApiOperation(value="更新用户详细信息", notes="根据url的id来指定更新对象，并根据传过来的user信息来更新用户详细信息")
    @ApiImplicitParams({
            @ApiImplicitParam(name = "id", value = "用户ID", required = true, dataType = "Long", paramType = "path"),
            @ApiImplicitParam(name = "user", value = "用户详细实体user", required = true, dataType = "User")
    })
    @RequestMapping(value="/{id}", method=RequestMethod.PUT)
    public String putUser(@PathVariable Long id, @RequestBody User user) {
        User u = users.get(id);
        u.setName(user.getName());
        u.setAge(user.getAge());
        users.put(id, u);
        return "success";
    }
    @ApiOperation(value="删除用户", notes="根据url的id来指定删除对象")
    @ApiImplicitParam(name = "id", value = "用户ID", required = true, dataType = "Long", paramType = "path")
    @RequestMapping(value="/{id}", method=RequestMethod.DELETE)
    public String deleteUser(@PathVariable Long id) {
        users.remove(id);
        return "success";
    }
}
 ```
 Swagger2配置
 ```
 @Configuration
@EnableSwagger2
public class Swagger2 {
    @Bean
    public Docket createRestApi(){
        return  new Docket(DocumentationType.SWAGGER_2)
                .apiInfo(apiInfo())
                .select()
                .apis(RequestHandlerSelectors.basePackage("xyz.riversky.demo5.web"))
                .paths(PathSelectors.any())
                .build();
    }

    private ApiInfo apiInfo() {
        return new ApiInfoBuilder()
                .title("Restful Api")
                .description("开发接口文档")
                .termsOfServiceUrl("www.riversky.xyz")
                .contact("balabala")
                .version("1.0")
                .build();
    }
}
 ```
 /swggger-ui.html  
 >> 特别需要注意Docket中apis的web包指定,不然无法发现swagger的注解
 ![](./img/TIM图片20190514110441.png)  
# 6. 数据库访问  
之前介绍了很多Web层的例子，包括构建RESTful API、使用Thymeleaf模板引擎渲染Web视图，但是这些内容还不足以构建一个动态的应用。通常我们做App也好，做Web应用也好，都需要内容，而内容通常存储于各种类型的数据库，服务端在接收到访问请求之后需要访问数据库获取并处理成展现给用户使用的数据形式。  
本文介绍在Spring Boot基础下配置数据源和通过JdbcTemplate编写数据访问的示例。  
## 6.1. 数据源配置  
在我们访问数据库的时候，需要先配置一个数据源，下面分别介绍一下几种不同的数据库配置方式。  
首先，为了连接数据库需要引入jdbc支持，在pom.xml中引入如下配置：  
```
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-jdbc</artifactId>
</dependency>  
```
**嵌入式数据库支持**  
嵌入式数据库通常用于开发和测试环境，不推荐用于生产环境。Spring Boot提供自动配置的嵌入式数据库有H2、HSQL、Derby，你不需要提供任何连接配置就能使用。  
比如，我们可以在pom.xml中引入如下配置使用HSQL  
```
<dependency>
    <groupId>org.hsqldb</groupId>
    <artifactId>hsqldb</artifactId>
    <scope>runtime</scope>
</dependency>
```
连接生产数据源   
以MySQL数据库为例，先引入MySQL连接的依赖包，在pom.xml中加入：    
```
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>5.1.21</version>
</dependency>
```
在src/main/resources/application.properties中配置数据源信息  
```
spring.datasource.url=jdbc:mysql://localhost:3306/test
spring.datasource.username=dbuser
spring.datasource.password=dbpass
spring.datasource.driver-class-name=com.mysql.jdbc.Driver
```
连接JNDI数据源   
当你将应用部署于应用服务器上的时候想让数据源由应用服务器管理，那么可以使用如下配置方式引入JNDI数据源。  
```
spring.datasource.jndi-name=java:jboss/datasources/customers
```
## 6.2. 使用JdbcTemplate操作数据库  
Spring的JdbcTemplate是自动配置的，你可以直接使用@Autowired来注入到你自己的bean中来使用。  
举例：我们在创建User表，包含属性name、age，下面来编写数据访问对象和单元测试用例。 

数据库创建  
```
CREATE TABLE `user2` (
  `name` varchar(255) DEFAULT NULL,
  `age` int(11) DEFAULT NULL,
  `id` int(11) NOT NULL AUTO_INCREMENT,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=6 DEFAULT CHARSET=utf8
``` 
service包
定义包含有插入、删除、查询的抽象接口UserService  
```
public interface UserService {
    void create(String name,Integer age);
    void deleteByName(String name);
    Integer getAllUsers();
    void deleteAllUsers();
}
```
实现类
```
@Service
public class UserServiceImpl implements UserService {
    @Autowired
    private JdbcTemplate jdbcTemplate;
    @Override
    public void create(String name, Integer age) {
        jdbcTemplate.update("insert  into USER2 (name ,age) values (?,?)",name,age);
    }

    @Override
    public void deleteByName(String name) {
        jdbcTemplate.update("delete from USER2 where name =?",name);
    }

    @Override
    public Integer getAllUsers() {
        return jdbcTemplate.queryForObject("select count(1) from USER2 ",Integer.class);
    }

    @Override
    public void deleteAllUsers() {
        jdbcTemplate.update("delete from user2 ");
    }
}
```
测试类
```
@RunWith(SpringJUnit4ClassRunner.class)
@SpringApplicationConfiguration(Application.class)
public class ApplicationTests {
    @Autowired
    private UserService userSerivce;
    @Before
    public void setUp() {
        // 准备，清空user表
        userSerivce.deleteAllUsers();
    }
    @Test
    public void test() throws Exception {
        // 插入5个用户
        userSerivce.create("a", 1);
        userSerivce.create("b", 2);
        userSerivce.create("c", 3);
        userSerivce.create("d", 4);
        userSerivce.create("e", 5);

        // 查数据库，应该有5个用户
        Assert.assertEquals(5, userSerivce.getAllUsers().intValue());

        // 删除两个用户
        userSerivce.deleteByName("a");
        userSerivce.deleteByName("e");
        // 查数据库，应该有5个用户
        Assert.assertEquals(3, userSerivce.getAllUsers().intValue());
    }
}
```
# 7. spring-data-jpa 让数据访问更简单更优雅
在实际开发过程中，对数据库的操作无非就“增删改查”。就最为普遍的单表操作而言，除了表和字段不同外，语句都是类似的，开发人员需要写大量类似而枯燥的语句来完成业务逻辑。  
为了解决这些大量枯燥的数据操作语句，我们第一个想到的是使用ORM框架，比如：Hibernate。通过整合Hibernate之后，我们以操作Java实体的方式最终将数据改变映射到数据库表中。  
为了解决抽象各个Java实体基本的“增删改查”操作，我们通常会以泛型的方式封装一个模板Dao来进行抽象简化，但是这样依然不是很方便，我们需要针对每个实体编写一个继承自泛型模板Dao的接口，再编写该接口的实现。虽然一些基础的数据访问已经可以得到很好的复用，但是在代码结构上针对每个实体都会有一堆Dao的接口和实现。  
由于模板Dao的实现，使得这些具体实体的Dao层已经变的非常“薄”，有一些具体实体的Dao实现可能完全就是对模板Dao的简单代理，并且往往这样的实现类可能会出现在很多实体上。Spring-data-jpa的出现正可以让这样一个已经很“薄”的数据访问层变成只是一层接口的编写方式。比如，下面的例子：    
```
public interface UserRepository extends JpaRepository<User, Long> {
    User findByName(String name);
    @Query("from User u where u.name=:name")
    User findUser(@Param("name") String name);
}
```
我们只需要通过编写一个继承自JpaRepository的接口就能完成数据访问，下面以一个具体实例来体验Spring-data-jpa给我们带来的强大功能。  
## 7.1. 使用示例  
由于Spring-data-jpa依赖于Hibernate。如果您对Hibernate有一定了解，下面内容可以毫不费力的看懂并上手使用Spring-data-jpa。如果您还是Hibernate新手，您可以先按如下方式入门，再建议回头学习一下Hibernate以帮助这部分的理解和进一步使用。  
**工程配置**  
添加依赖  
```
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>5.1.21</version>
</dependency>
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-jpa</artifactId>
</dependency>
```
配置文件application.properties   
```
spring.datasource.url=jdbc:mysql://gogs:3306/test
spring.datasource.username=root
spring.datasource.password=riversky
spring.datasource.driver-class-name=com.mysql.jdbc.Driver

spring.jpa.properties.hibernate.hbm2ddl.auto=create-drop
spring.jpa.show-sql=true
```
spring.jpa.properties.hibernate.hbm2ddl.auto 需要注意:
* create：每次加载hibernate时都会删除上一次的生成的表，然后根据你的model类再重新来生成新表，哪怕两次没有任何改变也要这样执行，这就是导致数据库表数据丢失的一个重要原因。  
* create-drop：每次加载hibernate时根据model类生成表，但是sessionFactory一关闭,表就自动删除。  
* update：最常用的属性，第一次加载hibernate时根据model类会自动建立起表的结构（前提是先建立好数据库），以后加载hibernate时根据model类自动更新表结构，即使表结构改变了但表中的行仍然存在不会删除以前的行。要注意的是当部署到服务器后，表结构是不会被马上建立起来的，是要等应用第一次运行起来后才会。  
* validate：每次加载hibernate时，验证创建数据库表结构，只会和数据库中的表进行比较，不会创建新表，但是会插入新值。  

至此已经完成基础配置，如果您有在Spring下整合使用过它的话，相信你已经感受到Spring Boot的便利之处：JPA的传统配置在persistence.xml文件中，但是这里我们不需要。当然，最好在构建项目时候按照之前提过的最佳实践的工程结构来组织，这样以确保各种配置都能被框架扫描到。  
**创建实体**  
```
@Entity
public class User {
    @Id
    @GeneratedValue
    private Long id;

    @Column(nullable = false)
    private String name;

    @Column(nullable = false)
    private Integer age;
}
```
在Spring-data-jpa中，只需要编写类似上面这样的接口就可实现数据访问。不再像我们以往编写了接口时候还需要自己编写接口实现类，直接减少了我们的文件清单。  
下面对上面的UserRepository做一些解释，该接口继承自JpaRepository，通过查看JpaRepository接口的API文档，可以看到该接口本身已经实现了创建（save）、更新（save）、删除（delete）、查询（findAll、findOne）等基本操作的函数，因此对于这些基础操作的数据访问就不需要开发者再自己定义。   
在我们实际开发中，JpaRepository接口定义的接口往往还不够或者性能不够优化，我们需要进一步实现更复杂一些的查询或操作。由于本文重点在spring boot中整合spring-data-jpa，在这里先抛砖引玉简单介绍一下spring-data-jpa中让我们兴奋的功能，后续再单独开篇讲一下spring-data-jpa中的常见使用。  
在上例中，我们可以看到下面两个函数：  
```
public interface UserRepository extends JpaRepository<User, Long> {
    User findByName(String name);
    User findByNameAndAge(String name, Integer age);
    @Query("from User u where u.name=:name")
    User findUser(@Param("name") String name);
}
```
它们分别实现了按name查询User实体和按name和age查询User实体，可以看到我们这里没有任何类SQL语句就完成了两个条件查询方法。这就是Spring-data-jpa的一大特性：通过解析方法名创建查询。   
除了通过解析方法名来创建查询外，它也提供通过使用@Query 注解来创建查询，您只需要编写JPQL语句，并通过类似“:name”来映射@Param指定的参数，就像例子中的第三个findUser函数一样。  
**单元测试**  
在完成了上面的数据访问接口之后，按照惯例就是编写对应的单元测试来验证编写的内容是否正确。这里就不多做介绍，主要通过数据操作和查询来反复验证操作的正确性。  
```
@RunWith(SpringJUnit4ClassRunner.class)
@SpringApplicationConfiguration(Application.class)
public class ApplicationTests {
    @Autowired
    private UserRepository userRepository;

    @Test
    public void test() {
        userRepository.save(new User("AAA", 10));
        userRepository.save(new User("BBB", 20));
        userRepository.save(new User("CCC", 30));
        userRepository.save(new User("DDD", 40));
        userRepository.save(new User("EEE", 50));
        userRepository.save(new User("FFF", 60));
        userRepository.save(new User("GGG", 70));
        userRepository.save(new User("HHH", 80));
        userRepository.save(new User("III", 90));
        userRepository.save(new User("JJJ", 100));
        // 测试findAll, 查询所有记录
        Assert.assertEquals(10, userRepository.findAll().size());
        // 测试findByName, 查询姓名为FFF的User
        Assert.assertEquals(60, userRepository.findByName("FFF").getAge().longValue());
        // 测试findUser, 查询姓名为FFF的User
        Assert.assertEquals(60, userRepository.findUser("FFF").getAge().longValue());

        // 测试findByNameAndAge, 查询姓名为FFF并且年龄为60的User
        Assert.assertEquals("FFF", userRepository.findByNameAndAge("FFF", 60).getName());

        // 测试删除姓名为AAA的User
        userRepository.delete(userRepository.findByName("AAA"));

        // 测试findAll, 查询所有记录, 验证上面的删除是否成功
        Assert.assertEquals(9, userRepository.findAll().size());
    }
}
```
# 8. 多数据源的配置与使用  
之前在介绍使用JdbcTemplate和Spring-data-jpa时，都使用了单数据源。在单数据源的情况下，Spring Boot的配置非常简单，只需要在application.properties文件中配置连接参数即可。但是往往随着业务量发展，我们通常会进行数据库拆分或是引入其他数据库，从而我们需要配置多个数据源，下面基于之前的JdbcTemplate和Spring-data-jpa例子分别介绍两种多数据源的配置方式。 
依赖
```
 <dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-jdbc</artifactId>
</dependency>
<dependency>
    <groupId>mysql</groupId>
    <artifactId>mysql-connector-java</artifactId>
    <version>5.1.21</version>
</dependency>
<dependency>
    <groupId>org.projectlombok</groupId>
    <artifactId>lombok</artifactId>
    <version>1.16.18</version>
    <scope>provided</scope>
</dependency>
``` 
## 8.1. jdbcTemplate 多数据源配置
前提
两个数据库
初始表  
```
CREATE TABLE `user` (
  `id` int(11) NOT NULL AUTO_INCREMENT,
  `name` varchar(255) DEFAULT NULL,
  `age` int(11) DEFAULT NULL,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=2 DEFAULT CHARSET=utf8
```
**配置**  
创建一个Spring配置类，定义两个DataSource用来读取application.properties中的不同配置。如下例子中，主数据源配置为spring.datasource.primary开头的配置，第二数据源配置为spring.datasource.secondary开头的配置。  
```
spring.datasource.primary.url=jdbc:mysql://gogs:3306/test1
spring.datasource.primary.username=root
spring.datasource.primary.password=riversky
spring.datasource.primary.driver-class-name=com.mysql.jdbc.Driver

spring.datasource.secondary.url=jdbc:mysql://gogs:3306/test2
spring.datasource.secondary.username=root
spring.datasource.secondary.password=riversky
spring.datasource.secondary.driver-class-name=com.mysql.jdbc.Driver
```
JDBCTemplate配置类  
```
@Configuration
public class DataSourceConfig {
    @Bean(name = "primaryDataSource")
    @Qualifier("primaryDataSource")
    @ConfigurationProperties(prefix = "spring.datasource.primary")
    public DataSource primaryDataSource(){
        return DataSourceBuilder.create().build();
    }
    @Bean(name = "secondaryDataSource")
    @Qualifier("secondaryDataSource")
    @Primary
    @ConfigurationProperties(prefix = "spring.datasource.secondary")
    public DataSource secondaryDataSource(){
        return DataSourceBuilder.create().build();
    }
    @Bean(name = "primaryJdbcTemplate")
    public JdbcTemplate primaryJdbcTemplate( @Qualifier("primaryDataSource") DataSource dataSource){
        return  new JdbcTemplate(dataSource);
    }
    @Bean(name = "secondaryJdbcTemplate")
    public JdbcTemplate secondaryyJdbcTemplate( @Qualifier("secondaryDataSource") DataSource dataSource){
        return  new JdbcTemplate(dataSource);
    }
}
```
测试类  
```
@RunWith(SpringJUnit4ClassRunner.class)
@SpringApplicationConfiguration(Application.class)
public class ApplicationTest {
    @Autowired
    @Qualifier("primaryJdbcTemplate")
    protected JdbcTemplate jdbcTemplate1;
    @Autowired
    @Qualifier("secondaryJdbcTemplate")
    protected  JdbcTemplate jdbcTemplate2;
    @Before
    public void setUp(){
        jdbcTemplate1.update("delete from user");
        jdbcTemplate2.update("delete from user ");
    }
    @Test
    public void test(){
        // 往第一个数据源中插入两条数据
        jdbcTemplate1.update("insert into user(id,name,age) values(?, ?, ?)", 1, "aaa", 20);
        jdbcTemplate1.update("insert into user(id,name,age) values(?, ?, ?)", 2, "bbb", 30);
        // 往第二个数据源中插入一条数据，若插入的是第一个数据源，则会主键冲突报错
        jdbcTemplate2.update("insert into user(id,name,age) values(?, ?, ?)", 1, "aaa", 20);
        // 查一下第一个数据源中是否有两条数据，验证插入是否成功
        Assert.assertEquals("2", jdbcTemplate1.queryForObject("select count(1) from user", String.class));
        // 查一下第一个数据源中是否有两条数据，验证插入是否成功
        Assert.assertEquals("1", jdbcTemplate2.queryForObject("select count(1) from user", String.class));
    }
}
```
## 8.2. JAP多数据源配置  
数据源配置
```
@Configuration
public class DataSourceConfig {

    @Bean(name = "primaryDataSource")
    @Qualifier("primaryDataSource")
    @ConfigurationProperties(prefix="spring.datasource.primary")
    public DataSource primaryDataSource() {
        return DataSourceBuilder.create().build();
    }

    @Bean(name = "secondaryDataSource")
    @Qualifier("secondaryDataSource")
    @Primary
    @ConfigurationProperties(prefix="spring.datasource.secondary")
    public DataSource secondaryDataSource() {
        return DataSourceBuilder.create().build();
    }
    @Bean(name = "primaryJdbcTemplate")
    public JdbcTemplate primaryJdbcTemplate( @Qualifier("primaryDataSource") DataSource dataSource){
        return  new JdbcTemplate(dataSource);
    }
    @Bean(name = "secondaryJdbcTemplate")
    public JdbcTemplate secondaryyJdbcTemplate( @Qualifier("secondaryDataSource") DataSource dataSource){
        return  new JdbcTemplate(dataSource);
    }
}
```
jpa数据源1
```
@Configuration
@EnableTransactionManagement
@EnableJpaRepositories(
        entityManagerFactoryRef="entityManagerFactoryPrimary",
        transactionManagerRef="transactionManagerPrimary",
        basePackages= { "xyz.riversky.demo8.repository.p" }) //设置Repository所在位置
public class PrimaryConfig {

    @Autowired @Qualifier("primaryDataSource")
    private DataSource primaryDataSource;

    @Primary
    @Bean(name = "entityManagerPrimary")
    public EntityManager entityManager(EntityManagerFactoryBuilder builder) {
        return entityManagerFactoryPrimary(builder).getObject().createEntityManager();
    }

    @Primary
    @Bean(name = "entityManagerFactoryPrimary")
    public LocalContainerEntityManagerFactoryBean entityManagerFactoryPrimary (EntityManagerFactoryBuilder builder) {
        return builder
                .dataSource(primaryDataSource)
                .properties(getVendorProperties(primaryDataSource))
                .packages("xyz.riversky.demo8.domain") //设置实体类所在位置
                .persistenceUnit("primaryPersistenceUnit")
                .build();
    }

    @Autowired
    private JpaProperties jpaProperties;

    private Map<String, String> getVendorProperties(DataSource dataSource) {
        return jpaProperties.getHibernateProperties(dataSource);
    }

    @Primary
    @Bean(name = "transactionManagerPrimary")
    public PlatformTransactionManager transactionManagerPrimary(EntityManagerFactoryBuilder builder) {
        return new JpaTransactionManager(entityManagerFactoryPrimary(builder).getObject());
    }
}
```
二配置
```
@Configuration
@EnableTransactionManagement
@EnableJpaRepositories(
        entityManagerFactoryRef="entityManagerFactorySecondary",
        transactionManagerRef="transactionManagerSecondary",
        basePackages= { "xyz.riversky.demo8.repository.s" }) //设置Repository所在位置
public class SecondaryConfig {

    @Autowired @Qualifier("secondaryDataSource")
    private DataSource secondaryDataSource;

    @Bean(name = "entityManagerSecondary")
    public EntityManager entityManager(EntityManagerFactoryBuilder builder) {
        return entityManagerFactorySecondary(builder).getObject().createEntityManager();
    }

    @Bean(name = "entityManagerFactorySecondary")
    public LocalContainerEntityManagerFactoryBean entityManagerFactorySecondary (EntityManagerFactoryBuilder builder) {
        return builder
                .dataSource(secondaryDataSource)
                .properties(getVendorProperties(secondaryDataSource))
                .packages("xyz.riversky.demo8.domain") //设置实体类所在位置
                .persistenceUnit("secondaryPersistenceUnit")
                .build();
    }

    @Autowired
    private JpaProperties jpaProperties;

    private Map<String, String> getVendorProperties(DataSource dataSource) {
        return jpaProperties.getHibernateProperties(dataSource);
    }

    @Bean(name = "transactionManagerSecondary")
    PlatformTransactionManager transactionManagerSecondary(EntityManagerFactoryBuilder builder) {
        return new JpaTransactionManager(entityManagerFactorySecondary(builder).getObject());
    }

}
```
>> 应该特别注意每个数据源,需要显示指定两个包,一个为repository,一个为domain的.  

domain包  
```
@Entity
@Data
@NoArgsConstructor
public class User {
    @Id
    @GeneratedValue
    private Long id;
    @Column(nullable = false)
    private String name;
    @Column(nullable = false)
    private Integer age;
    public User(String name, Integer age) {
        this.name = name;
        this.age = age;
    }
}

@Entity
@Data
@AllArgsConstructor
@NoArgsConstructor
public class Message {
    @Id
    @GeneratedValue
    private Long id;

    @Column(nullable = false)
    private String name;

    @Column(nullable = false)
    private String content;

    public Message(String name, String content) {
        this.name = name;
        this.content = content;
    }
}
```
**单元测试**  

# 9. 日志管理  
Spring Boot在所有内部日志中使用Commons Logging，但是默认配置也提供了对常用日志的支持，如：Java Util Logging，Log4J, Log4J2和Logback。每种Logger都可以通过配置使用控制台或者文件输出日志内容。  
**格式化日志**  
默认的日志输出如下：  
```
2016-04-13 08:23:50.120  INFO 37397 --- [           main] org.hibernate.Version         
```
输出内容元素具体如下：  
```
时间日期 — 精确到毫秒
日志级别 — ERROR, WARN, INFO, DEBUG or TRACE
进程ID
分隔符 — --- 标识实际日志的开始
线程名 — 方括号括起来（可能会截断控制台输出）
Logger名 — 通常使用源代码的类名
日志内容
```  
**控制台输出**  
在Spring Boot中默认配置了ERROR、WARN和INFO级别的日志输出到控制台。  
我们可以通过两种方式切换至DEBUG级别：  
```
在运行命令后加入--debug标志，如：$ java -jar myapp.jar --debug
在application.properties中配置debug=true，该属性置为true的时候，核心Logger（包含嵌入式容器、hibernate、spring）会输出更多内容，但是你自己应用的日志并不会输出为DEBUG级别。
```
**多彩输出**  
如果你的终端支持ANSI，设置彩色输出会让日志更具可读性。通过在application.properties中设置spring.output.ansi.enabled参数来支持。  
```
NEVER：禁用ANSI-colored输出（默认项）
DETECT：会检查终端是否支持ANSI，是的话就采用彩色输出（推荐项）
ALWAYS：总是使用ANSI-colored格式输出，若终端不支持的时候，会有很多干扰信息，不推荐使用
```
**文件输出**  
Spring Boot默认配置只会输出到控制台，并不会记录到文件中，但是我们通常生产环境使用时都需要以文件方式记录。  
若要增加文件输出，需要在application.properties中配置logging.file或logging.path属性。  
```
logging.file，设置文件，可以是绝对路径，也可以是相对路径。如：logging.file=my.log
logging.path，设置目录，会在该目录下创建spring.log文件，并写入日志内容，如：logging.path=/var/log
```
>>  日志文件会在10Mb大小的时候被截断，产生新的日志文件，默认级别为：ERROR、WARN、INFO  

**级别控制**  
在Spring Boot中只需要在application.properties中进行配置完成日志记录的级别控制。  
配置格式：logging.level.*=LEVEL  
```
logging.level：日志级别控制前缀，*为包名或Logger名
LEVEL：选项TRACE, DEBUG, INFO, WARN, ERROR, FATAL, OFF
```
例如:
```
logging.level.com.didispace=DEBUG：com.didispace包下所有class以DEBUG级别输出
logging.level.root=WARN：root日志以WARN级别输出
```
**自定义日志配置**  
由于日志服务一般都在ApplicationContext创建前就初始化了，它并不是必须通过Spring的配置文件控制。因此通过系统属性和传统的Spring Boot外部配置文件依然可以很好的支持日志控制和管理。  
根据不同的日志系统，你可以按如下规则组织配置文件名，就能被正确加载：  
```
Logback：logback-spring.xml, logback-spring.groovy, logback.xml, logback.groovy
Log4j：log4j-spring.properties, log4j-spring.xml, log4j.properties, log4j.xml
Log4j2：log4j2-spring.xml, log4j2.xml
JDK (Java Util Logging)：logging.properties
```
>>  Spring Boot官方推荐优先使用带有-spring的文件名作为你的日志配置（如使用logback-spring.xml，而不是logback.xml）  
**自定义输出格式**  
在Spring Boot中可以通过在application.properties配置如下参数控制输出格式：  
```
logging.pattern.console：定义输出到控制台的样式（不支持JDK Logger）
logging.pattern.file：定义输出到文件的样式（不支持JDK Logger）
```
## 9.1. logback输出日志到控制台
slf4j是Java的简单日志门面API，很多日志实现都可以与之集成，如JDK logging (java.util.logging), log4j和logback。优点是代码里不会有具体的日志实现类，减少侵入。    
与log4j相比，logback具有一些优势，如更好的性能、更少的内存使用、自动重加载配置文件以及过滤功能等。   
**依赖**  
```
<properties>  
  <logback.version>1.0.11</logback.version>  
  <slf4j.api.version>1.7.5</slf4j.api.version>  
</properties>  
  
<dependencies>  
  <dependency>  
    <groupId>org.slf4j</groupId>  
    <artifactId>slf4j-api</artifactId>  
    <version>${slf4j.api.version}</version>  
  </dependency>  
  <dependency>  
    <groupId>ch.qos.logback</groupId>  
    <artifactId>logback-classic</artifactId>  
    <version>${logback.version}</version>  
  </dependency>  
  <dependency>  
    <groupId>ch.qos.logback</groupId>  
    <artifactId>logback-core</artifactId>  
    <version>${logback.version}</version>  
  </dependency>  
</dependencies>  
```
在类路径下新建logback.xml或logback-test.xml（优先级高）文件：  
```
<?xml version="1.0" encoding="UTF-8"?>

<configuration debug="false" xmlns="http://ch.qos.logback/xml/ns/logback"
               xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
               xsi:schemaLocation="http://ch.qos.logback/xml/ns/logback
               https://raw.githubusercontent.com/enricopulatzo/logback-XSD/master/src/main/xsd/logback.xsd">
    <appender name="STDOUT" class="ch.qos.logback.core.ConsoleAppender">
        <!-- encoder的默认实现类是ch.qos.logback.classic.encoder.PatternLayoutEncoder -->
        <encoder>
            <pattern>%d{HH:mm:ss.SSS} [%thread] %-5level %logger{5} ---- %msg%n</pattern>
        </encoder>
    </appender>
    <!-- name值可以是包名或具体的类名：该包（包括子包）下的类或该类将采用此logger -->
    <logger name="xyz.riversky.logtest" level="INFO" additivity="false">
        <appender-ref ref="STDOUT"/>
    </logger>

    <!-- root的默认level是DEBUG -->
    <root level="DEBUG">
        <appender-ref ref="STDOUT" />
    </root>
</configuration>
```
所有logger的始祖是ROOT，默认会继承ROOT的配置，因此b中的日志会打印两次。   
解决：logger的additivity属性设置为false   
```
<logger name="com.john.logging.b" level="INFO" additivity="false">  
```
## 9.2. logback:输出日志到文件
```
<?xml version="1.0" encoding="UTF-8"?>

<configuration debug="false" xmlns="http://ch.qos.logback/xml/ns/logback"
               xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
               xsi:schemaLocation="http://ch.qos.logback/xml/ns/logback
               https://raw.githubusercontent.com/enricopulatzo/logback-XSD/master/src/main/xsd/logback.xsd">
    <appender name="fileAppender" class="ch.qos.logback.core.FileAppender">
        <file>/logs/granularity.log</file>
        <encoder><!-- 必须指定，否则不会往文件输出内容 -->
            <pattern>%d{HH:mm:ss.SSS} [%thread] %-5level %logger{5} ---- %msg%n</pattern>
        </encoder>
        <append>true</append>
        <prudent>false</prudent>
    </appender>
    <root level="DEBUG">
        <appender-ref ref="fileAppender" />
    </root>
</configuration>
```
>>  prudent：小心的，慎重的。如果设置为true，不同JVM的file appenders能够安全地将日志输出到同一个文件中
>>  当prudent为true时，如果append设置为false，会被强行转成true。 
## 9.3. logback:输出日志到文件（滚动） 
实际生产中，每天都有大量的日志生成，单个文件（FileAppender）已经不能满足要求，RollingFileAppender继承了FileAppender，并提供了更多的功能：  
*  每天生成一个日志文件
*  将前一天的日志重命名为包含日期的格式
*  根据需要，删除过期历史日志  

 ```
 <?xml version="1.0" encoding="UTF-8"?>

<configuration debug="false" xmlns="http://ch.qos.logback/xml/ns/logback"
               xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
               xsi:schemaLocation="http://ch.qos.logback/xml/ns/logback
               https://raw.githubusercontent.com/enricopulatzo/logback-XSD/master/src/main/xsd/logback.xsd">
    <appender name="rollingAppender" class="ch.qos.logback.core.rolling.RollingFileAppender">
        <file>/logs/heuristic.log</file>
        <rollingPolicy class="ch.qos.logback.core.rolling.TimeBasedRollingPolicy">
            <fileNamePattern>/logs/heuristic-%d{yyyy-MM-dd}.log</fileNamePattern>
            <maxHistory>30</maxHistory>
        </rollingPolicy>
        <encoder><!-- 必须指定，否则不会往文件输出内容 -->
            <pattern>%d{HH:mm:ss.SSS} [%thread] %-5level %logger{5} - %msg%n</pattern>
        </encoder>
        <append>false</append>
        <prudent>false</prudent>
    </appender>
    <root level="DEBUG">
        <appender-ref ref="rollingAppender" />
    </root>
</configuration>
 ```
## 9.4. logback：输出日志到不同文件
不同包的日志可能要放到不同的文件中，如service层和dao层的日志；   
不同日志级别：调试、信息、警告和错误等也要分文件输出。  
### 9.4.1. 根据包输出，通过logger的name属性指定不同的包
配置logback(-test).xml
```
<?xml version="1.0" encoding="UTF-8"?>

<configuration debug="false" xmlns="http://ch.qos.logback/xml/ns/logback"
               xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
               xsi:schemaLocation="http://ch.qos.logback/xml/ns/logback
               https://raw.githubusercontent.com/enricopulatzo/logback-XSD/master/src/main/xsd/logback.xsd">
    <appender name="serviceAppender" class="ch.qos.logback.core.rolling.RollingFileAppender">
        <file>/logs/service.log</file>
        <rollingPolicy class="ch.qos.logback.core.rolling.TimeBasedRollingPolicy">
            <fileNamePattern>/logs/bribery-%d{yyyy-MM-dd}.log</fileNamePattern>
        </rollingPolicy>
        <encoder>
            <pattern>%d{HH:mm:ss.SSS} [%thread] %-5level %logger{5} - %msg%n</pattern>
        </encoder>
    </appender>

    <appender name="daoAppender" class="ch.qos.logback.core.rolling.RollingFileAppender">
        <file>/logs/dao.log</file>
        <rollingPolicy class="ch.qos.logback.core.rolling.TimeBasedRollingPolicy">
            <fileNamePattern>/logs/venality-%d{yyyy-MM-dd}.log</fileNamePattern>
        </rollingPolicy>
        <encoder>
            <pattern>%d{HH:mm:ss.SSS} [%thread] %-5level %logger{5} - %msg%n</pattern>
        </encoder>
    </appender>

    <logger name="xyz.riversky.service" level="DEBUG" additivity="false">
        <appender-ref ref="serviceAppender" />
    </logger>

    <logger name="xyz.riversky.dao" level="DEBUG" additivity="false">
        <appender-ref ref="daoAppender" />
    </logger>
</configuration>
```
### 9.4.2. 根据日志级别输出  
修改logback(-test).xml    
这里把所有级别为ERROR的日志输出到一个文件中    
serviceAppender和daoAppender都加入以下级别过滤器，这样错误日志就不会在bribery.log和venality.log中打印了：   
```
<<?xml version="1.0" encoding="UTF-8"?>

<configuration debug="false" xmlns="http://ch.qos.logback/xml/ns/logback"
               xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
               xsi:schemaLocation="http://ch.qos.logback/xml/ns/logback
               https://raw.githubusercontent.com/enricopulatzo/logback-XSD/master/src/main/xsd/logback.xsd">
    <appender name="errorAppender" class="ch.qos.logback.core.rolling.RollingFileAppender">
        <file>/logs/error.log</file>
        <rollingPolicy class="ch.qos.logback.core.rolling.TimeBasedRollingPolicy">
            <fileNamePattern>/logs/error-%d{yyyy-MM-dd}.log</fileNamePattern>
        </rollingPolicy>
        <encoder>
            <pattern>%d{HH:mm:ss.SSS} %thread %X{invokeNo} %logger{40} %msg%n</pattern>
        </encoder>
        <filter class="ch.qos.logback.classic.filter.LevelFilter"><!-- 只打印错误日志 -->
            <level>ERROR</level>
            <onMatch>ACCEPT</onMatch>
            <onMismatch>DENY</onMismatch>
        </filter>
    </appender>
    <appender name="infoAppender" class="ch.qos.logback.core.rolling.RollingFileAppender">
        <file>/logs/info.log</file>
        <rollingPolicy class="ch.qos.logback.core.rolling.TimeBasedRollingPolicy">
            <fileNamePattern>/logs/info-%d{yyyy-MM-dd}.log</fileNamePattern>
        </rollingPolicy>
        <encoder>
            <pattern>%d{HH:mm:ss.SSS} %thread %X{invokeNo} %logger{40} %msg%n</pattern>
        </encoder>
        <filter class="ch.qos.logback.classic.filter.LevelFilter"><!-- 只打印错误日志 -->
            <level>INFO</level>
            <onMatch>ACCEPT</onMatch>
            <onMismatch>DENY</onMismatch>
        </filter>
    </appender>
    <root level="ALL">
        <appender-ref ref="errorAppender"/>
        <appender-ref ref="infoAppender"/>
    </root>
</configuration>
```
name为com.john.dao和com.john.service的logger都加上errorAppender：   

# 10. redis数据库使用
Spring Boot中除了对常用的关系型数据库提供了优秀的自动化支持之外，对于很多NoSQL数据库一样提供了自动化配置的支持，包括：Redis, MongoDB, Elasticsearch, Solr和Cassandra。  
## 10.1. 使用Redis  
Redis是一个开源的使用ANSI C语言编写、支持网络、可基于内存亦可持久化的日志型、Key-Value数据库。  
[官网](http://redis.io/)  
[中文社区](http://www.redis.cn/)  
## 10.2. 环境配置
Spring Boot提供的数据访问框架Spring Data Redis基于Jedis。可以通过引入spring-boot-starter-redis来配置依赖关系。  
依赖
```
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-redis</artifactId>
</dependency>
```
注意不同版本的spring boot下，redis的starter依赖名略有不同，如果上面的不行，可以尝试
spring-boot-starter-data-redis  
## 10.3. 使用
配置文件
```
#Redis配置
#其中spring.redis.database的配置通常使用0即可，Redis在配置的时候可以设置数据库数量，默认为16，可以理解为数据库的schema
spring.redis.database=0
spring.redis.host=gogs
spring.redis.port=6379
spring.redis.password=riversky
#连接池最大连接数
spring.redis.pool.max-active=9
#连接池最大阻塞等待时间(使用负值表示没有限制)
spring.redis.pool.max-wait=-1
#连接池中最大空闲连接
spring.redis.pool.max-idle=8
#连接池中最小空闲连接
spring.redis.pool.min-idle=0
#连接超时时间
spring.redis.timeout=0
```
## 10.4. 普通使用
```
@RunWith(SpringJUnit4ClassRunner.class)
@SpringApplicationConfiguration(Application.class)
public class ApplicationTest {
    @Autowired
    private StringRedisTemplate redisTemplate;

    @Test
    public void testRes() {
        redisTemplate.opsForValue().set("aaa", "111");
        Assert.assertEquals("111", redisTemplate.opsForValue().get("aaa"));
        redisTemplate.delete("aaa");
    }
}
```
## 10.5. 自定义的序列解析类
domain
```
package xyz.riversky.demo10.domain;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;
import java.io.Serializable;
@Data
@AllArgsConstructor
@NoArgsConstructor
public class User implements Serializable {

    private static final long serialVersionUID = -4731293996744105302L;
    private String username;
    private Integer age;
}
```
自定义解析类
```
/**
 * 序列反序列化器,更为普遍的是存储json串
 */
public class RedisObjectSerializer implements RedisSerializer<Object> {
    private Converter<Object,byte[]> serializer=new SerializingConverter();
    private Converter<byte[],Object> deserializer=new DeserializingConverter();
    static final byte[] EMPTY_ARRAY=new byte[0];
    @Override
    public byte[] serialize(Object o)  {
        if (o == null) {
            return EMPTY_ARRAY;
        }
        try {
            return serializer.convert(o);
        }catch (Exception e){
            e.printStackTrace();
            return EMPTY_ARRAY;
        }
    }
    @Override
    public Object deserialize(byte[] bytes) throws SerializationException {
        if (isEmpty(bytes)) {
            return null;
        }
        try {
            return deserializer.convert(bytes);
        } catch (Exception ex) {
            throw new SerializationException("Cannot deserialize", ex);
        }
    }
    private boolean isEmpty(byte[] data) {
        return (data == null || data.length == 0);
    }
}
```
spring redis配置类
```
@Configuration
public class RedisConfig {
    @Value("${spring.redis.host}")String hostName;
    @Value("${spring.redis.port}")int port;
    @Value("${spring.redis.password}")String password;
    @Value("${spring.redis.database}")int database;
    @Value("${spring.redis.timeout}") int timeout;
    @Value("${spring.redis.pool.max-active}")int maxActive;
    @Value("${spring.redis.pool.max-idle}")int maxIdle;
    @Value("${spring.redis.pool.min-idle}")int minIdle;
    @Value("${spring.redis.pool.max-wait}")long maxWaitMillis;
    @Bean
    JedisConnectionFactory getRedisConnectionFactory(){
        JedisShardInfo jedisShardInfo = new JedisShardInfo(hostName, port, timeout);
        jedisShardInfo.setPassword(password);

        JedisConnectionFactory jedisConnectionFactory = new JedisConnectionFactory(jedisShardInfo);
        jedisConnectionFactory.setDatabase(database);
        JedisPoolConfig jedisPoolConfig = new JedisPoolConfig();
        jedisPoolConfig.setMaxIdle(maxIdle);
        jedisPoolConfig.setMinIdle(minIdle);
        jedisPoolConfig.setMaxWaitMillis(maxWaitMillis);
        jedisPoolConfig.setMaxTotal(maxActive);
        jedisConnectionFactory.setPoolConfig(jedisPoolConfig);
        return jedisConnectionFactory;
    }
    @Bean
    public RedisTemplate<String , User> redisTemplate(){
        RedisTemplate<String, User> stringUserRedisTemplate = new RedisTemplate<>();
        stringUserRedisTemplate.setConnectionFactory(getRedisConnectionFactory());
        stringUserRedisTemplate.setKeySerializer(new StringRedisSerializer());
        stringUserRedisTemplate.setValueSerializer(new RedisObjectSerializer());
        return stringUserRedisTemplate;
    }
}
```
测试
```
@RunWith(SpringJUnit4ClassRunner.class)
@SpringApplicationConfiguration(Application.class)
public class ApplicationTest {
    @Autowired
    private RedisTemplate<String, User> userRedisTemplate;
    @Test
    public void UserRedisTest() {
        ValueOperations<String, User> ops = userRedisTemplate.opsForValue();
        User user = new User("chaoren", 20);
        ops.set(user.getUsername(), user);
        User user1 = new User("蝙蝠侠", 12);
        ops.set(user1.getUsername(), user1);
        redisTemplate.delete(user.getUsername());
        redisTemplate.delete(user1.getUsername());
    }
}
```
# Spring Boot中使用MongoDB数据库  
## MongoDB简介  
MongoDB是一个基于分布式文件存储的数据库，它是一个介于关系数据库和非关系数据库之间的产品，其主要目标是在键/值存储方式（提供了高性能和高度伸缩性）和传统的RDBMS系统（具有丰富的功能）之间架起一座桥梁，它集两者的优势于一身。  
MongoDB支持的数据结构非常松散，是类似json的bson格式，因此可以存储比较复杂的数据类型，也因为他的存储格式也使得它所存储的数据在Nodejs程序应用中使用非常流畅。  
既然称为NoSQL数据库，Mongo的查询语言非常强大，其语法有点类似于面向对象的查询语言，几乎可以实现类似关系数据库单表查询的绝大部分功能，而且还支持对数据建立索引。  
但是，MongoDB也不是万能的，同MySQL等关系型数据库相比，它们在针对不同的数据类型和事务要求上都存在自己独特的优势。在数据存储的选择中，坚持多样化原则，选择更好更经济的方式，而不是自上而下的统一化。  
较常见的，我们可以直接用MongoDB来存储键值对类型的数据，如：验证码、Session等；由于MongoDB的横向扩展能力，也可以用来存储数据规模会在未来变的非常巨大的数据，如：日志、评论等；由于MongoDB存储数据的弱类型，也可以用来存储一些多变json数据，如：与外系统交互时经常变化的JSON报文。而对于一些对数据有复杂的高事务性要求的操作，如：账户交易等就不适合使用MongoDB来存储。  
[官网](https://www.mongodb.org/)    
##  访问MongoDB  
在Spring Boot中，对如此受欢迎的MongoDB，同样提供了自配置功能。  
Spring Boot中可以通过在pom.xml中加入spring-boot-starter-data-mongodb引入对mongodb的访问支持依赖。它的实现依赖spring-data-mongodb。是的，您没有看错，又是spring-data的子项目，之前介绍过spring-data-jpa、spring-data-redis，对于mongodb的访问，spring-data也提供了强大的支持，下面就开始动手试试吧。  
依赖  
```
<dependency>
    <groupId>org.springframework.boot</groupId>
    <artifactId>spring-boot-starter-data-mongodb</artifactId>
</dependency>
```
domain   
```
@Data
@NoArgsConstructor
@AllArgsConstructor
public class User {
    @Id
    private Long id;
    private String username;
    private Integer age;
}
```  
repository  
```
public interface UserRepository extends MongoRepository<User, Long> {
    User findByUsername(String username);
}
```
测试
```
@SpringBootApplication
public class Application {
    public static void main(String[] args) {
        SpringApplication.run(Application.class,args);
    }
}
```
```
@RunWith(SpringJUnit4ClassRunner.class)
@SpringApplicationConfiguration(Application.class)
public class ApplicationTests {
	@Autowired
	private UserRepository userRepository;
	@Before
	public void setUp() {
		userRepository.deleteAll();
	}
	@Test
	public void test() throws Exception {
		// 创建三个User，并验证User总数
		userRepository.save(new User(1L, "didi", 30));
		userRepository.save(new User(2L, "mama", 40));
		userRepository.save(new User(3L, "kaka", 50));
		Assert.assertEquals(3, userRepository.findAll().size());
		// 删除一个User，再验证User总数
		User u = userRepository.findOne(1L);
		userRepository.delete(u);
		Assert.assertEquals(2, userRepository.findAll().size());
		// 删除一个User，再验证User总数
		u = userRepository.findByUsername("mama");
		userRepository.delete(u);
		Assert.assertEquals(1, userRepository.findAll().size());
	}
}
```
若MongoDB的安装配置采用默认端口，那么在自动配置的情况下，我们不需要做任何参数配置，就能马上连接上本地的MongoDB。下面直接使用spring-data-mongodb来尝试对mongodb的存取操作。（记得mongod启动您的mongodb）    
**参数配置**   
通过上面的例子，我们可以轻而易举的对MongoDB进行访问，但是实战中，应用服务器与MongoDB通常不会部署于同一台设备之上，这样就无法使用自动化的本地配置来进行使用。这个时候，我们也可以方便的配置来完成支持，只需要在application.properties中加入mongodb服务端的相关配置，具体示例如下：  
```
spring.data.mongodb.uri=mongodb://name:pass@localhost:27017/test
```
在尝试此配置时，记得在mongo中对test库创建具备读写权限的用户（用户名为name，密码为pass），不同版本的用户创建语句不同，注意查看文档做好准备工作  
若使用mongodb 2.x，也可以通过如下参数配置，该方式不支持mongodb 3.x。  
```
spring.data.mongodb.host=localhost spring.data.mongodb.port=27017
```