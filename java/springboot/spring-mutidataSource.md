# 多数据源的方案  

## 多库方式  
### 场景
项目中需要谅解多个数据库进行操作
### 实现
1. 禁用springboot 的DataSourceAutoConfiguration,因为它会读取application.properties文件的spring.datasource.*属性并自动配置单数据源。在@SpringBootApplication注解中添加exclude属性即可：    
```
@SpringBootApplication(exclude = {
  DataSourceAutoConfiguration.class
})
```
2. 配置文件
```
# titan库
spring.datasource.titan-master.url=jdbc:mysql://X.X.X.X:port/titan?characterEncoding=UTF-8
spring.datasource.titan-master.username=
spring.datasource.titan-master.password=
spring.datasource.titan-master.driver-class-name=com.mysql.jdbc.Driver
# 连接池配置
# 省略
# 其它库
spring.datasource.db2.url=jdbc:mysql://X.X.X.X:port/titan2?characterEncoding=UTF-8
spring.datasource.db2.username=
spring.datasource.db2.password=
spring.datasource.db2.driver-class-name=com.mysql.jdbc.Driver
```
3. 手动提供数据源
```
@Configuration
public class DataSourceConfig {
 @Bean(name = "titanMasterDS")
 @ConfigurationProperties(prefix = "spring.datasource.titan-master") // application.properteis中对应属性的前缀
 public DataSource dataSource1() {
  return DataSourceBuilder.create().build();
 }
 @Bean(name = "ds2")
 @ConfigurationProperties(prefix = "spring.datasource.db2") // application.properteis中对应属性的前缀
 public DataSource dataSource2() {
  return DataSourceBuilder.create().build();
 }
}
```
4. Mybatis的配置(写两个配置,分别mapper与sqlSessionFactory的)
```
@Configuration
@MapperScan(basePackages = {"titan.mapper"}, sqlSessionFactoryRef = "sqlSessionFactory1")
public class MybatisDbAConfig {
 @Autowired
 @Qualifier("titanMasterDS")
 private DataSource ds1;
 @Bean
 public SqlSessionFactory sqlSessionFactory1() throws Exception {
  SqlSessionFactoryBean factoryBean = new SqlSessionFactoryBean();
  factoryBean.setDataSource(ds1); // 使用titan数据源, 连接titan库
  return factoryBean.getObject();
 }
 @Bean
 public SqlSessionTemplate sqlSessionTemplate1() throws Exception {
  SqlSessionTemplate template = new SqlSessionTemplate(sqlSessionFactory1()); // 使用上面配置的Factory
  return template;
 }
}
```
```
@Configuration
@MapperScan(basePackages = {"other.mapper"}, sqlSessionFactoryRef = "sqlSessionFactory2")
public class MybatisDbBConfig {
 @Autowired
 @Qualifier("ds2")
 private DataSource ds2;
 @Bean
 public SqlSessionFactory sqlSessionFactory2() throws Exception {
  SqlSessionFactoryBean factoryBean = new SqlSessionFactoryBean();
  factoryBean.setDataSource(ds2);
  return factoryBean.getObject();
 }
 @Bean
 public SqlSessionTemplate sqlSessionTemplate2() throws Exception {
  SqlSessionTemplate template = new SqlSessionTemplate(sqlSessionFactory2());
  return template;
 }
}
```
>> 需要注意,此时两个不同的Mapper会自动的找属于自己的库(当然也可以进行多个数据库的任意配置)
## 动态数据源  
使用动态数据源的初衷，是能在应用层做到读写分离，即在程序代码中控制不同的查询方法去连接不同的库。除了这种方法以外，数据库中间件也是个不错的选择，它的优点是数据库集群对应用来说只暴露为单库，不需要切换数据源的代码逻辑.   
我们通过自定义注解 + AOP的方式实现数据源动态切换。  
1. 首先定义一个ContextHolder, 用于保存当前线程使用的数据源名：  
```
public class DataSourceContextHolder {
 public static final Logger log = LoggerFactory.getLogger(DataSourceContextHolder.class);
 /**
  * 默认数据源
  */
 public static final String DEFAULT_DS = "titan-master";
 private static final ThreadLocal<String> contextHolder = new ThreadLocal<>();
 // 设置数据源名
 public static void setDB(String dbType) {
  log.debug("切换到{}数据源", dbType);
  contextHolder.set(dbType);
 }
 // 获取数据源名
 public static String getDB() {
  return (contextHolder.get());
 }
 // 清除数据源名
 public static void clearDB() {
  contextHolder.remove();
 }
}
```
2. 自定义一个javax.sql.DataSource接口的实现，这里只需要继承Spring为我们预先实现好的父类AbstractRoutingDataSource即可  
```
public class DynamicDataSource extends AbstractRoutingDataSource {
 private static final Logger log = LoggerFactory.getLogger(DynamicDataSource.class);
 @Override
 protected Object determineCurrentLookupKey() {
  log.debug("数据源为{}", DataSourceContextHolder.getDB());
  return DataSourceContextHolder.getDB();
 }
}
```
3. 创建动态数据源：  
```
/**
  * 动态数据源: 通过AOP在不同数据源之间动态切换
  * @return
  */
 @Bean(name = "dynamicDS1")
 public DataSource dataSource() {
  DynamicDataSource dynamicDataSource = new DynamicDataSource();
  // 默认数据源
  dynamicDataSource.setDefaultTargetDataSource(dataSource1());
  // 配置多数据源
  Map<Object, Object> dsMap = new HashMap(5);
  dsMap.put("titan-master", dataSource1());
  dsMap.put("ds2", dataSource2());
  dynamicDataSource.setTargetDataSources(dsMap);
  return dynamicDataSource;
 }
```
4. Aop注解实现数据源的选择
自定义注解  
```
@Retention(RetentionPolicy.RUNTIME)
@Target({
  ElementType.METHOD
})
public @interface DS {
 String value() default "titan-master";
}
```
编写AOP切面  
```
@Aspect
@Component
public class DynamicDataSourceAspect {
 @Before("@annotation(DS)")
 public void beforeSwitchDS(JoinPoint point){
  //获得当前访问的class
  Class<?> className = point.getTarget().getClass();
  //获得访问的方法名
  String methodName = point.getSignature().getName();
  //得到方法的参数的类型
  Class[] argClass = ((MethodSignature)point.getSignature()).getParameterTypes();
  String dataSource = DataSourceContextHolder.DEFAULT_DS;
  try {
   // 得到访问的方法对象
   Method method = className.getMethod(methodName, argClass);
   // 判断是否存在@DS注解
   if (method.isAnnotationPresent(DS.class)) {
    DS annotation = method.getAnnotation(DS.class);
    // 取出注解中的数据源名
    dataSource = annotation.value();
   }
  } catch (Exception e) {
   e.printStackTrace();
  }
  // 切换数据源
  DataSourceContextHolder.setDB(dataSource);
 }
 @After("@annotation(DS)")
 public void afterSwitchDS(JoinPoint point){
  DataSourceContextHolder.clearDB();
 }
}
```

5. 使用
```
@Autowired
private UserAModelMapper userAMapper;
@DS("titan-master")
public String ds1() {
 return userAMapper.selectByPrimaryKey(1).getName();
}
@DS("ds2")
public String ds2() {
 return userAMapper.selectByPrimaryKey(1).getName();
}
```
说白了就是对AOP的一种使用(通过切面来获取注解,然后根据注解的value来判断使用哪个数据源)