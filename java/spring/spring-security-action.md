#  基本依赖

##  最小依赖

```
 <dependency>
            <groupId>org.springframework.security</groupId>
            <artifactId>spring-security-config</artifactId>
 </dependency>
 <dependency>
            <groupId>org.springframework.security</groupId>
            <artifactId>spring-security-web</artifactId>
 </dependency>
   <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
```



## springboot 支持

```
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-security</artifactId>
        </dependency>
          <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
```

##  spring配置  

```
application.yml
server:
  port: 8097
spring:
  profiles:
    active: dev
  mvc:
    view:
      suffix: html
mybatis:
  configuration:
    map-underscore-to-camel-case: true
  mapper-locations:
    - classpath:mapperxml/*.xml
```

```
application-dev.yml
spring:
  datasource:
    url: jdbc:mysql://192.168.1.158:3306/spsecurity?useUnicode=true&characterEncoding=utf-8&serverTimezone=Asia/Shanghai
    username: root
    password: riversky
    druid:
      initial-size: 5 #连接池初始化大小
      min-idle: 10 #最小空闲连接数
      max-active: 20 #最大连接数
      web-stat-filter:
        exclusions: "*.js,*.gif,*.jpg,*.png,*.css,*.ico,/druid/*" #不统计这些请求数据
      stat-view-servlet: #访问监控网页的登录用户名和密码
        login-username: druid
        login-password: druid
#  redis:
#    host: 192.168.1.158 # Redis服务器地址
#    database: 0 # Redis数据库索引（默认为0）
#    port: 6379 # Redis服务器连接端口
#    password:  # Redis服务器连接密码（默认为空）
#    timeout: 300ms # 连接超时时间（毫秒）
```

##  资源  

```java
@RestController
@RequestMapping("/admin/api")
public class AdminController {
    @GetMapping("hello")
    public CommonResult hello(){
        return CommonResult.success("hello admin");
    }
}
```

```java
@RestController
@RequestMapping("/app/api")
public class AppController {
    @GetMapping("hello")
    public CommonResult hello(){
        return CommonResult.success("hello app");
    }
}
```

```
@RestController
@RequestMapping("/user/api")
public class UserController {
    @GetMapping("hello")
    public CommonResult hello(){
        return CommonResult.success("hello user");
    }
}
```



## 默认实现

如果什么都不配置就会有默认的登陆验证

logcalhost:8080/login页面

以及默认的提交页面  

默认用户名user,密码启动项目时会自动生成一个

##  基本表单验证 

如果想自定义登录页面，以及自定义提交的url那么如下配置即可

自定义登陆页面

```
static/myLogin.html
<!DOCTYPE HTML>
<html>
<head>
    <title> login</title>
    <meta http-equiv="Content-Type" content="text/html;charset=utf-8" />
</head>
<body>
<div>
    <form action="login"  method="post">
        <input type="text" name="username" placeholder="username"/>
        <input type="password" name="password" placeholder="password"/>
        <input type="submit" value="Login">
    </form>
    <div>
    </div>
</div>
</body>
</html>
```



配置类需要继承WebSecurityConfigurerAdapter

```
@EnableWebSecurity
@Slf4j
@Configuration
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Override
    protected void configure(HttpSecurity http) throws Exception {
        log.debug("using default config(HttpSecurity) . If subclassed this will ");
        http.authorizeRequests()
                .antMatchers("/admin/api/**").hasRole("ADMIN")
                .antMatchers("/user/api/**").hasAuthority("ROLE_USER")
                .antMatchers("/app/api/**","/doc.html","/swagger-ui.html","/swagger-resources/**").permitAll()
                .antMatchers("/webjars/springfox-swagger-ui/**").permitAll()
                .anyRequest().authenticated()
                .and()
           .formLogin()
                .loginPage("/myLogin.html")
                .loginProcessingUrl("/login")
                .successHandler(new AuthenticationSuccessHandler() {
                    @Override
                    public void onAuthenticationSuccess(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse, Authentication authentication) throws IOException, ServletException {
                        log.info("登陆成功");
                        httpServletResponse.setContentType("application/json;charset=UTF-8");
                        PrintWriter out = httpServletResponse.getWriter();
                        out.write("{\"code\":\"0\",\"message\":\"welcome lonin\"}");
                    }
                })
                .failureHandler(new AuthenticationFailureHandler() {
                    @Override
                    public void onAuthenticationFailure(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse, AuthenticationException e) throws IOException, ServletException {
                        log.error("登陆失败");
                        httpServletResponse.setContentType("application/json;charset=UTF-8");
                        httpServletResponse.setStatus(401);
                        PrintWriter out = httpServletResponse.getWriter();
                        out.write("{\"code\":\"401\",\"message\":\""+e.getMessage()+"\"}");
                    }
                })
                .permitAll()
                .and()
                .csrf().disable();


    }



    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }
}
```

> >   权限配置config方法中指定url资源（ant风格）以及所需要的权限即可。  

> >   成功或者失败处理直接在  登陆部分中设置successHandler与failureHandler即可

#  认证授权

认证授权中主要是根据UserDetailService接口进行加载数据，它是一种用户信息管理接口，其中主要包含

![1595249098422](.\img\1595249098422.png)



![1595249317992](.\img\1595249317992.png)



## 内存认证授权支持

其实就是上面的

![1595249433261](.\img\1595249433261.png)

使用时只需要讲UserDetailsService实现类InMemoryUserDetailsMananger注入Spring容器即可

```
public class ZdUserDetailService implements UserDetailsService {
    @Autowired
    private PasswordEncoder encoder;
    private InMemoryUserDetailsManager manager = new InMemoryUserDetailsManager();
    @PostConstruct
    public void Init(){
        manager.createUser(User.withUsername("riversky").password(encoder.encode("123456")).roles("USER").build());
        manager.createUser(User.withUsername("admin").password(encoder.encode("123456")).roles("ADMIN").build());
    }

    @Override
    public UserDetails loadUserByUsername(String s) throws UsernameNotFoundException {
        return manager.loadUserByUsername(s);
    }
}
```



##  默认数据库支持实现

使用前提讲数据库按照Spring 默认进行表生成

```
use spsecurity;
DROP TABLE IF EXISTS `users`;
create table users(
    username varchar(50) not null primary key ,
    password varchar(500) not null ,
    enabled  boolean not null
);
create table authorities(
  username varchar(50) not null ,
  authority varchar(50) not null ,
  constraint fk_authorities_users foreign key(username) references authorities(username)
);
create unique index  ix_auth_username on authorities(username, authority) ;
```



```
@Service
public class ZdJdbcUserDetailService extends JdbcUserDetailsManager {
@Autowired
    private DataSource dataSource;

@PostConstruct
    public void init(){
        this.setDataSource(dataSource);
    }
}

```



## 自定义数据库实现

maven依赖

```
        <dependency>
            <groupId>org.projectlombok</groupId>
            <artifactId>lombok</artifactId>
        </dependency>
        <dependency>
            <groupId>org.springframework.boot</groupId>
            <artifactId>spring-boot-starter-web</artifactId>
        </dependency>
        <dependency>
            <groupId>org.springframework.data</groupId>
            <artifactId>spring-data-commons</artifactId>
        </dependency>
<!--        <dependency>-->
        <!--            <groupId>org.springframework.boot</groupId>-->
        <!--            <artifactId>spring-boot-starter-security</artifactId>-->
        <!--        </dependency>-->
        <dependency>
            <groupId>com.github.pagehelper</groupId>
            <artifactId>pagehelper-spring-boot-starter</artifactId>
        </dependency>
        <dependency>
            <groupId>org.springframework.security</groupId>
            <artifactId>spring-security-web</artifactId>
        </dependency>
        <dependency>
            <groupId>com.alibaba</groupId>
            <artifactId>druid-spring-boot-starter</artifactId>
        </dependency>
        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
        </dependency>
        <dependency>
            <groupId>org.springframework.security</groupId>
            <artifactId>spring-security-config</artifactId>
        </dependency>
        <dependency>
            <groupId>org.mybatis.generator</groupId>
            <artifactId>mybatis-generator-core</artifactId>
        </dependency>
        <dependency>
            <groupId>io.springfox</groupId>
            <artifactId>springfox-swagger2</artifactId>
        </dependency>
        <dependency>
            <groupId>com.github.xiaoymin</groupId>
            <artifactId>swagger-bootstrap-ui</artifactId>
        </dependency>
        <dependency>
            <groupId>cn.hutool</groupId>
            <artifactId>hutool-all</artifactId>
        </dependency>
```



```
use spsecurity;
DROP TABLE IF EXISTS `users`;
create table users(
                        id bigint(20) NOT NULL AUTO_INCREMENT PRIMARY KEY ,
                      username varchar(50) not null  ,
                      password varchar(500) not null ,
                      enabled  tinyint(4) NOT NULL  DEFAULT '1' COMMENT '用户是否可用',
                      roles text CHARACTER SET utf8 COMMENT '用户角色，多个角色用逗号隔开',
                      KEY 'username' ('username')
);
insert into users  (username,password,roles)values ('riversky','$2a$10$zGef5I3OmrX3omKspVBmweXifwRj0VJLhk/pEa9rmeIEJ9rwtrb5G','ROLE_USER');
insert into users  (username,password,roles)values ('admin','$2a$10$zGef5I3OmrX3omKspVBmweXifwRj0VJLhk/pEa9rmeIEJ9rwtrb5G','ROLE_USER,ROLE_ADMIN');
```

然后使用mybatis进行代码生成

```
MybatisGenerator.xml

<?xml version="1.0" encoding="UTF-8"?>
<!DOCTYPE generatorConfiguration
    PUBLIC "-//mybatis.org//DTD MyBatis Generator Configuration 1.0//EN"
    "http://mybatis.org/dtd/mybatis-generator-config_1_0.dtd">

<generatorConfiguration>
    <!--<classPathEntry location="/Program Files/IBM/SQLLIB/java/db2java.zip" />-->

    <context id="MySqlContext" targetRuntime="MyBatis3" defaultModelType="flat">

        <property name="beginningDelimiter" value="`"/>
        <property name="endingDelimiter" value="`"/>
        <property name="javaFileEncoding" value="UTF-8"/>
        <!-- 为模型生成序列化方法-->
        <plugin type="org.mybatis.generator.plugins.SerializablePlugin"/>
        <!-- 为生成的Java模型创建一个toString方法 -->
        <plugin type="org.mybatis.generator.plugins.ToStringPlugin"/>

        <!--生成mapper.xml时覆盖原文件-->
        <plugin type="org.mybatis.generator.plugins.UnmergeableXmlMappersPlugin" />
        <commentGenerator type="cn.riversky.securitystu.step1.CommentGenerator">
            <!-- 是否去除自动生成的注释 true：是 ： false:否 -->
            <property name="suppressAllComments" value="true"/>
            <property name="suppressDate" value="true"/>
            <property name="addRemarkComments" value="true"/>
        </commentGenerator>
        <jdbcConnection driverClass="com.mysql.jdbc.Driver"
                        connectionURL="jdbc:mysql://192.168.1.158:3306/spsecurity?useLegacyDatetimeCode=false&amp;serverTimezone=UTC&amp;nullCatalogMeansCurrent=true"
                        userId="root"
                        password="riversky">
        </jdbcConnection>


        <javaModelGenerator targetPackage="cn.riversky.securitystu.step1.domain" targetProject="demo1\src\main\java" />


        <sqlMapGenerator targetPackage="mapperxml" targetProject="demo1\src\main\resources" />

        <javaClientGenerator type="XMLMAPPER" targetPackage="cn.riversky.securitystu.step1.mapper" targetProject="demo1\src\main\java" />

        <!--生成全部表tableName设为%-->
        <table tableName="%">
            <generatedKey column="id" sqlStatement="MySql" identity="true"/>
        </table>
    </context>
</generatorConfiguration>
```

自定义注释生成

```
/**
 * 自定义的注释生成器
 * @author riversky
 * @date 2020/05/29
 **/
public class CommentGenerator extends DefaultCommentGenerator {
    private boolean addRemarkComments = false;
    private static final String EXAMPLE_SUFFIX="Example";
    private static final String API_MODEL_PROPERTY_FULL_CLASS_NAME="io.swagger.annotations.ApiModelProperty";
    /**
     * 设置用户配置的参数
     */
    @Override
    public void addConfigurationProperties(Properties properties) {
        super.addConfigurationProperties(properties);
        this.addRemarkComments = StringUtility.isTrue(properties.getProperty("addRemarkComments"));
    }

    /**
     * 给字段添加注释
     */
    @Override
    public void addFieldComment(Field field, IntrospectedTable introspectedTable,
                                IntrospectedColumn introspectedColumn) {
        String remarks = introspectedColumn.getRemarks();
        //根据参数和备注信息判断是否添加备注信息
        if(addRemarkComments&&StringUtility.stringHasValue(remarks)){
//            addFieldJavaDoc(field, remarks);
            //数据库中特殊字符需要转义
            if(remarks.contains("\"")){
                remarks = remarks.replace("\"","'");
            }
            //给model的字段添加swagger注解
            field.addJavaDocLine("@ApiModelProperty(value = \""+remarks+"\")");
        }
    }

    /**
     * 给model的字段添加注释
     */
    private void addFieldJavaDoc(Field field, String remarks) {
        //文档注释开始
        field.addJavaDocLine("/**");
        //获取数据库字段的备注信息
        String[] remarkLines = remarks.split(System.getProperty("line.separator"));
        for(String remarkLine:remarkLines){
            field.addJavaDocLine(" * "+remarkLine);
        }
        addJavadocTag(field, false);
        field.addJavaDocLine(" */");
    }

    @Override
    public void addJavaFileComment(CompilationUnit compilationUnit) {
        super.addJavaFileComment(compilationUnit);
        //只在model中添加swagger注解类的导入
        if(!compilationUnit.isJavaInterface()&&!compilationUnit.getType().getFullyQualifiedName().contains(EXAMPLE_SUFFIX)){
            compilationUnit.addImportedType(new FullyQualifiedJavaType(API_MODEL_PROPERTY_FULL_CLASS_NAME));
        }
    }
    public static void main(String[] args) throws Exception  {
        //代码生成中的警告信息
        List<String> warnings = new ArrayList<>();
        //当生成的代码重复时，覆盖原代码
        boolean overwrite = true;
        //读取我们的 MBG 配置文件
        InputStream is = CommentGenerator.class.getResourceAsStream("/MybatisGenerator.xml");
        ConfigurationParser cp = new ConfigurationParser(warnings);
        Configuration config = cp.parseConfiguration(is);
        is.close();
        DefaultShellCallback callback = new DefaultShellCallback(overwrite);
        //创建 MBG
        MyBatisGenerator myBatisGenerator = new MyBatisGenerator(config, callback, warnings);
        //执行生成代码
        myBatisGenerator.generate(null);
        //输出警告信息
        for (String warning : warnings) {
            log.info(warning);
        }
    }
}
```

```
mybatis配置
@Configuration
@EnableTransactionManagement
@MapperScan({"cn.riversky.securitystu.step1.mapper"})
public class MyBatisConfig {
}

```

```
Dto与UserDetailService实现类
@Data
public class ZdUserDetails extends Users implements UserDetails {

    @Override
    public Collection<? extends GrantedAuthority> getAuthorities() {
        return AuthorityUtils.commaSeparatedStringToAuthorityList(getRoles());
    }
    @Override
    public boolean isAccountNonExpired() {
        return true;
    }
    @Override
    public boolean isAccountNonLocked() {
        return true;
    }
    @Override
    public boolean isCredentialsNonExpired() {
        return true;
    }
    @Override
    public boolean isEnabled() {
        Byte b=1;
        return this.getEnable().equals(b);
    }
}

@Service
public class DiyJdbcUserDetailService implements UserDetailsService {

    @Autowired
    private UsersMapper usersMapper;
    @Override
    public UserDetails loadUserByUsername(String s) throws UsernameNotFoundException {
        UsersExample usersExample = new UsersExample();
        UsersExample.Criteria criteria = usersExample.createCriteria().andUsernameEqualTo(s);
        List<Users> users = usersMapper.selectByExample(usersExample);
        if(CollUtil.isEmpty(users)&&users.size()!=1){
            return null;
        }else{
            Users users1 = users.get(0);
            ZdUserDetails zdUserDetails = new ZdUserDetails();
            BeanUtils.copyProperties(users1,zdUserDetails);
            return zdUserDetails;
        }
    }
}
```



# 基本常用接口与作用

## UserDetails  

描述用户信息实体的接口

## UserDetailsService

描述用户管理（主要是查询）的接口

## Authentication  

描述一次认证请求

##  AuthentiactionProvider

定义一个认证过程  

```
/**
 * Indicates a class can process a specific
 * {@link org.springframework.security.core.Authentication} implementation.
 *
 * @author Ben Alex
 */
public interface AuthenticationProvider {
	// ~ Methods
	// ========================================================================================================

	/**
	 * Performs authentication with the same contract as
	 * {@link org.springframework.security.authentication.AuthenticationManager#authenticate(Authentication)}
	 * .
	 *
	 * @param authentication the authentication request object.
	 *
	 * @return a fully authenticated object including credentials. May return
	 * <code>null</code> if the <code>AuthenticationProvider</code> is unable to support
	 * authentication of the passed <code>Authentication</code> object. In such a case,
	 * the next <code>AuthenticationProvider</code> that supports the presented
	 * <code>Authentication</code> class will be tried.
	 *
	 * @throws AuthenticationException if authentication fails.
	 */
	Authentication authenticate(Authentication authentication)
			throws AuthenticationException;

	/**
	 * Returns <code>true</code> if this <Code>AuthenticationProvider</code> supports the
	 * indicated <Code>Authentication</code> object.
	 * <p>
	 * Returning <code>true</code> does not guarantee an
	 * <code>AuthenticationProvider</code> will be able to authenticate the presented
	 * instance of the <code>Authentication</code> class. It simply indicates it can
	 * support closer evaluation of it. An <code>AuthenticationProvider</code> can still
	 * return <code>null</code> from the {@link #authenticate(Authentication)} method to
	 * indicate another <code>AuthenticationProvider</code> should be tried.
	 * </p>
	 * <p>
	 * Selection of an <code>AuthenticationProvider</code> capable of performing
	 * authentication is conducted at runtime the <code>ProviderManager</code>.
	 * </p>
	 *
	 * @param authentication
	 *
	 * @return <code>true</code> if the implementation can more closely evaluate the
	 * <code>Authentication</code> class presented
	 */
	boolean supports(Class<?> authentication);
}
```

![1595312713237](.\img\1595312713237.png)



## ProviderManager

一次完整的认证可以包含多个AuthenticationPrivider ,所以有一个ProviderManager

![1595313517134](.\img\1595313517134.png)

> >  可以自定义认证技术AuthenticationProvider    满足特殊需求  

常见的认证技术

1.   HTTP层面的包含HTTP基本与HTTP摘要认证技术  
2. 基于LDAP的（Lightweight Directory Access protocol）轻量目录访问协议。
3. OpenID认证技术
4. OAuth认证技术
5. 系统内维护的用户名与密码认证技术  

## AbstractUserDetailsAuthenticationProvider

![1595314842557](.\img\1595314842557.png)

> >  自定义的需要继承该类，然后重写  retireveUser(用户查询) and  additionAuthenticationChencks(校验)即可。  例如Dao的一个实现就是。当然也可以直接继承DaoAuthenticationProvider，然后覆盖additionAuthenticationChencks即可。  



一个完整的认证可以包含多个AuthenticationProvider,这些AuthenticationProvider都是ProviderManager管理的，而ProviderManager是由UsernamePasswordAuthenticationFilter调用的。也就是说，所有的AuthencationProvider包含的Authentication都来源于UsernamePasswordAuthenticationFilter.  





## Filter(OncePerRequestFilter)

> >  Servlet的filter并不能保证，因此可以使用Spring-Security 的实现一次性过滤器。  

![1595311977794](.\img\1595311977794.png)

> > 实现该类后，可以在config中进行addFilterBefore（）；



标准认证源：sessionId+IP地址

![1595317099670](.\img\1595317099670.png)



##  配置小细节（默认实现）

# 常用实现模式  

## 自定义过滤器(验证增强)-优雅方式  

一般如果自定义字段或者验证机制需要3步骤  

1.   重写WebAu
2.  容器中 Web实现
3. UserDetailPasswordAuthFIlter中处理

例如demo

token支持

``` 
@Getter
@Setter
public class MyWebAuthenticationDetails extends WebAuthenticationDetails {
    private String token;
    /**
     * Records the remote address and will also set the session Id if a session already
     * exists (it won't create one).
     *
     * @param request that the authentication request was received from
     */
    public MyWebAuthenticationDetails(HttpServletRequest request) {
        super(request);
       String headerNames = request.getHeader("token");
        setToken(headerNames);
    }
}
@Service
public class MyAuthenticationDetailsSource implements AuthenticationDetailsSource<HttpServletRequest, WebAuthenticationDetails> {
    @Override
    public WebAuthenticationDetails buildDetails(HttpServletRequest context) {
        return new MyWebAuthenticationDetails(context);
    }
}
@Component
public class MyAuthenticationProvider extends DaoAuthenticationProvider {
    public MyAuthenticationProvider(UserDetailsService userDetailsService,PasswordEncoder passwordEncoder) {
        this.setUserDetailsService(userDetailsService);
        this.setPasswordEncoder(passwordEncoder);
    }
    @Autowired
    private PasswordEncoder passwordEncoder;
    @Override
    protected void additionalAuthenticationChecks(UserDetails userDetails, UsernamePasswordAuthenticationToken authentication) throws AuthenticationException {
        Object details = authentication.getDetails();
        System.out.println(details);
        super.additionalAuthenticationChecks(userDetails, authentication);
    }

}
```

```
@EnableWebSecurity(debug = true)
@Slf4j
@Configuration
public class WebSecurityConfig extends WebSecurityConfigurerAdapter {
    @Autowired
    private AuthenticationProvider authenticationProvider;
    @Override
    protected void configure(AuthenticationManagerBuilder auth) throws Exception {
        auth.authenticationProvider(authenticationProvider);
    }

    @Override
    protected void configure(HttpSecurity http) throws Exception {
        log.debug("using default config(HttpSecurity) . If subclassed this will ");
        http.authorizeRequests()
                .antMatchers("/admin/api/**").hasRole("ADMIN")
                .antMatchers("/user/api/**").hasAuthority("ROLE_USER")
                .antMatchers("/app/api/**","/doc.html","/swagger-ui.html","/swagger-resources","/swagger-resources/**").permitAll()
                .antMatchers("/**/*.js","/**/*.css","/**/*.png","/**/*.ico").permitAll()
                .antMatchers("/webjars/springfox-swagger-ui/**").permitAll()
                .anyRequest().authenticated()
                .and()
                .csrf().disable()
           .formLogin()
                .authenticationDetailsSource(authenticationDetailsSource())
                .loginPage("/myLogin.html")
                .loginProcessingUrl("/login")
                .successHandler(new AuthenticationSuccessHandler() {
                    @Override
                    public void onAuthenticationSuccess(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse, Authentication authentication) throws IOException, ServletException {
                        log.info("登陆成功");
                        httpServletResponse.setContentType("application/json;charset=UTF-8");
                        PrintWriter out = httpServletResponse.getWriter();
                        out.write("{\"code\":\"0\",\"message\":\"welcome lonin\"}");
                    }
                })
                .failureHandler(new AuthenticationFailureHandler() {
                    @Override
                    public void onAuthenticationFailure(HttpServletRequest httpServletRequest, HttpServletResponse httpServletResponse, AuthenticationException e) throws IOException, ServletException {
                        log.error("登陆失败");
                        httpServletResponse.setContentType("application/json;charset=UTF-8");
                        httpServletResponse.setStatus(401);
                        PrintWriter out = httpServletResponse.getWriter();
                        out.write("{\"code\":\"401\",\"message\":\""+e.getMessage()+"\"}");
                    }
                }).permitAll() ;
    }
    @Bean
    public PasswordEncoder passwordEncoder() {
        return new BCryptPasswordEncoder();
    }
```



##  OnceFilter-JWT 

```java
/**
 * JWT登录授权过滤器
 * @author riversky
 * @date 2020/06/08
 **/
public class JwtAuthenticationTokenFilter extends OncePerRequestFilter {
    private static final Logger LOGGER = LoggerFactory.getLogger(JwtAuthenticationTokenFilter.class);
    @Autowired
    private UserDetailsService userDetailsService;
    @Autowired
    private JwtTokenUtil jwtTokenUtil;
    @Value("${jwt.tokenHeader}")
    private String tokenHeader;
    @Value("${jwt.tokenHead}")
    private String tokenHead;

    @Override
    protected void doFilterInternal(HttpServletRequest request,
                                    HttpServletResponse response,
                                    FilterChain chain) throws ServletException, IOException {
        String authHeader = request.getHeader(this.tokenHeader);
        if (authHeader != null && authHeader.startsWith(this.tokenHead)) {
            String authToken = authHeader.substring(this.tokenHead.length());// The part after "Bearer "
            String username = jwtTokenUtil.getUserNameFromToken(authToken);
            LOGGER.info("checking username:{}", username);
            if (username != null && SecurityContextHolder.getContext().getAuthentication() == null) {
                UserDetails userDetails = this.userDetailsService.loadUserByUsername(username);
                if (jwtTokenUtil.validateToken(authToken, userDetails)) {
                    UsernamePasswordAuthenticationToken authentication = new UsernamePasswordAuthenticationToken(userDetails, null, userDetails.getAuthorities());
                    authentication.setDetails(new WebAuthenticationDetailsSource().buildDetails(request));
                    LOGGER.info("authenticated user:{}", username);
                    SecurityContextHolder.getContext().setAuthentication(authentication);
                }
            }
        }
        chain.doFilter(request, response);
    }
}

```

```
适配器配置中

 .and().addFilterBefore(jwtAuthenticationTokenFilter(), UsernamePasswordAuthenticationFilter.class);
```



##  rememberme 实现

###　需求

当页面刷新时常常会出现该问题（降低重新登陸的頻率）。　　

因此可以利用cookie中保存用戶登錄信息。

1.   散列加密方案

原理：

hashInfo=md5Hex(username+":"+expirationTime+":"+password+":"+key)

rememberCookie=base64(username+":"+expirationTime+":"+hashInfo)



配置方式

```
.rememberMe().userDetailsService(userDetailsService()).and()
```

默认是两周过期  

见AbstractRememberMeServices

并且每次表单登陆成功后，都会更新此令牌  

增加key支持

```
  .rememberMe().userDetailsService(userDetailsService()).key("bluroo").and()
```

> >  弊端依赖于客户端，不安全

2.  



##  注销实现  



##  跨域与CORS

## csrf



##  CAS 

# OAuth 

##  角色  



![1595400438243](.\img\1595400438243.png)

## 使用模式  

###  授权码模式  

功能最完整，流程最严密的一种  ，会将用户引导到授权服务器进行身份验证，验证成功后，会将授权令牌传递给客户端  

特征：授权与取验证码都在应用后端进行调用，比较安全。

如典型应用

```
https://graph.qq.com/oauth2.0/show?which=Login&display=pc&response_type=code&client_id=100270989&redirect_uri=https://passport.csdn.net/account/login?oauth_provider=QQProvider&state=test
```

需要注意其中，

1.  response_type指授权类型，为必要项，固定为code.
2. client_id 指客户端id,必要项
3. state指客户端的状态，通常在授权服务器重定向时原样返回。  
4. scope为申请的权限范围，如获取用户信息，获取用户相册等，有授权服务器抽象为具体条目。  
5. redirect_uri为授权通过后的重定向URL,授权服务器将在用户登陆完成之后重定向到类似下面的地址  

`https://passport.csdn.net/account/login?oauth_provider=QQProvider&code=xxx&state=test`

客户端拿到code之后需要向授权服务器申请访问令牌（仅可以使用一次，用完作废）.

申请令牌时也有一些关键参数，其中关键的有

```
https://graph.qq.com/oauth2.0/xxx？grant_type=authorization_code&code=xxx&...
```

1. grant_type 授权类型，授权码模式为：authorization_code
2. client_id  指客户端id;code指前面获取的授权码
3. redirect_uri指重定向URL.通过构建一个HTTP请求发起访问令牌的申请，如果成功，则会得到访问令牌，以及一些当令牌刷新时需要的参数。  

###  隐式授权模式  

隐式授权模式的客户端一般指浏览器。这就意味着访问令牌通过重定向传递到浏览器中，在通过浏览器的js代码来获取访问令牌。  

特征： 授权后会直接讲访问令牌发放到浏览器的锚点hash域`var hash=window.location.hash`

该模式与授权码模式类似，不同之处在于授权成功的重定向上，授权码模式是携带一个认证码，由客户端（三方后端通过授权码申请访问令牌）而隐式授权模式，直接讲访问令牌作为url的散列部分给浏览器  

```
http://graph.qq.com/demo/index.jsp?#access_token=FE04*******&expire_in-7776000&state=test
```

URL#号后面的部分被称为URL HASH,散列部分是专门用于指导浏览器行为的，并不会传到三方应用的后端

一般情况最好是利用浏览器的cookie存储访问令牌。  

### 密码授权模式 

客户端直接携带用户的密码向授权服务器申请令牌。  

客户端（三方）直接使用用户的信息(account password)向授权服务器所索求令牌。    

###  客户端授权模式

该模式一般由客户端提前向授权服务器申请应用公钥与私钥。当使用时，客户端直接通过这些关键信息向授权服务器申请访问令牌。





