# 背景  
如果我们可以跟别人说：“我们在1502643933071见面，别晚了！”那么就再简单不过了。但是我们希望时间与昼夜和四季有关，于是事情就变复杂了。JDK 1.0中包含了一个java.util.Date类，但是它的大多数方法已经在JDK 1.1引入Calendar类之后被弃用了。而Calendar并不比Date好多少。它们面临的问题是：可变性：像日期和时间这样的类应该是不可变的。偏移性：Date中的年份是从1900开始的，而月份都从0开始。格式化：格式化只对Date有用，Calendar则不行。此外，它们也不是线程安全的；不能处理闰秒等。  
# 新时间Api  
第三次引入的API是成功的，并且Java 8中引入的java.time API 已经纠正了过去的缺陷，将来很长一段时间内它都会为我们服务。  
Java 8 吸收了 Joda-Time 的精华，以一个新的开始为 Java 创建优秀的 API。新的 java.time 中包含了所有关于本地日期（LocalDate）、本地时间（LocalTime）、本地日期时间（LocalDateTime）、时区（ZonedDateTime）和持续时间（Duration）的类。历史悠久的 Date 类新增了 toInstant() 方法，用于把 Date 转换成新的表示形式。这些新增的本地化时间日期 API 大大简化了日期时间和本地化的管理。  
**包结构**  
* java.time  包含值对象的基础包
* java.time.chrono  提供对不同的日历系统的访问
* java.time.format  格式化和解析时间和日期
* java.time.temporal  包含底层框架和扩展特性
* java.time.zone  包含市区支持的类

对于大多数使用者,只需要用到基础包,和format包以及temporal包,因此尽管提供了68个新的公开类型,但是大多数开发者,大概只需要用到其中的1/3  
## LocalDate ,LocalTime LocalDateTime
LocalDate、LocalTime、LocalDateTime 类是其中较重要的几个类，它们的实例是不可变的对象，分别表示使用 ISO-8601日历系统的日期、时间、日期和时间。它们提供了简单的本地日期或时间，并不包含当前的时间信息，也不包含与时区相关的信息。  
* LocalDate代表IOS格式（yyyy-MM-dd）的日期,可以存储生日、纪念日等日期。
* LocalTime表示一个时间，而不是日期。
* LocalDateTime是用来表示日期和时间的，这是一个最常用的类之一。  

注：ISO-8601日历系统是国际标准化组织制定的现代公民的日期和时间的表示法，也就是公历。  
|方法|描述|
|:--|:--|
|now() /now(ZoneId zone)|静态方法，根据当前时间创建对象/指定时区的对象|
|of()|静态方法，根据指定日期/时间创建对象|
|getDayOfMonth()/getDayOfYear()|获得月份天数(1-31) /获得年份天数(1-366)|
|getDayOfWeek()|获得星期几(返回一个 DayOfWeek 枚举值)|
|getMonth()|获得月份, 返回一个 Month 枚举值|
|getMonthValue() / getYear()|获取的月份/年|
|getHour()/getMinute()/getSecond()|获得当前对象对应的小时、分钟、秒|
|withDayOfMonth()/withDayOfYear()/ withMonth()/withYear()|将月份天数、年份天数、月份、年份修改为指定的值并返回新的对象|
|plusDays(), plusWeeks(), plusMonths(), plusYears(),plusHours()|向当前对象添加几天、几周、几个月、几年、几小时|
|minusMonths() / minusWeeks()/ minusDays()/minusYears()/minusHours()|从当前对象减去几月、几周、几天、几年、几小时|

## 瞬时：Instant  
Instant：时间线上的一个瞬时点。这可能被用来记录应用程序中的事件时间戳。    
在处理时间和日期的时候，我们通常会想到年,月,日,时,分,秒。然而，这只是时间的一个模型，是面向人类的。第二种通用模型是面向机器的，或者说是连续的。在此模型中，时间线中的一个点表示为一个很大的数，这有利于计算机处理。在UNIX中，这个数从1970年开始，以秒为的单位；同样的，在Java中，也是从1970年开始，但以毫秒为单位。  
java.time包通过值类型Instant提供机器视图，不提供处理人类意义上的时间单位。Instant表示时间线上的一点，而不需要任何上下文信息，例如，时区。概念上讲，它只是简单的表示自1970年1月1日0时0分0秒（UTC）开始的秒数。因为java.time包是基于纳秒计算的，所以Instant的精度可以达到纳秒级。   
(1 ns = 10^-9s)   1秒 = 1000毫秒 =10^6微秒=10^9纳秒  
**Api**  
|方法|描述|
|:--|:--|
|now()|静态方法,返回UTC市区的Instant类的对象
|ofEpochMilli(long epochZMilli)|静态方法,返回在1970-01-01 00 00 00 基础上指定的毫秒之后的Instant类对象|
|atOffset(ZoneOffset offset)|结合即时便宜创建一个OffsetDateTime|
|toEpochMilli()|返回毫秒时间戳|

>> 时间戳是指格林威治时间1970-01-01 00 00 00(北京1970-01-01 08 00 00)至今的总秒数

# 格式化与解析
java.time.format.DateTimeFormatter 类：该类提供了三种格式化方法  
*	预定义的标准格式。如：ISO_LOCAL_DATE_TIME;ISO_LOCAL_DATE;ISO_LOCAL_TIME
*	本地化相关的格式。如：ofLocalizedDateTime(FormatStyle.LONG)
*	自定义的格式。如：ofPattern(“yyyy-MM-dd hh:mm:ss”)

常用API
|方法|描述|
|:--|:--|
|ofPattern(String pattern)|静态方法，返回一个指定字符串格式的DateTimeFormatter |
|format(TemporalAccessor t)|格式化一个日期、时间，返回字符串|
|parse(CharSequence text)|将指定格式的字符序列解析为一个日期、时间|

#  其他API
*	ZoneId：该类中包含了所有的时区信息，一个时区的ID，如 Europe/Paris
*	ZonedDateTime：一个在ISO-8601日历系统时区的日期时间，如 2007-12-
03T10:15:30+01:00 Europe/Paris。(其中每个时区都对应着ID，地区ID都为“{区域}/{城市}”的格式，例如：Asia/Shanghai等)  
*	Clock：使用时区提供对当前即时、日期和时间的访问的时钟。
*	持续时间：Duration，用于计算两个“时间”间隔
*	日期间隔：Period，用于计算两个“日期”间隔
*	TemporalAdjuster : 时间校正器。有时我们可能需要获取例如：将日期调整到“下一个工作日”等操作。
*	TemporalAdjusters : 该类通过静态方法(firstDayOfXxx()/lastDayOfXxx()/nextXxx())提供了大量的常用 TemporalAdjuster 的实现。

demo
```
@Test
public void test() {
    //ZoneId:类中包含了所有的时区信息
    // ZoneId的getAvailableZoneIds():获取所有的
    Set<String> zoneIds = ZoneId.getAvailableZoneIds();
    for (String s : zoneIds) {
        System.out.println(s);
    }
    // ZoneId的of():获取指定时区的时间
    LocalDateTime localDateTime = LocalDateTime.now(ZoneId.of("Asia/Tokyo"));
    System.out.println(localDateTime);
    //ZonedDateTime:带时区的日期时间
    // ZonedDateTime的now():获取本时区的ZonedDateTime对象
    ZonedDateTime zonedDateTime = ZonedDateTime.now();
    System.out.println(zonedDateTime);
    // ZonedDateTime的now(ZoneId id):获取指定时区的ZonedDateTime对象
    ZonedDateTime zonedDateTime1 = ZonedDateTime.now(ZoneId.of("Asia/Tokyo"));
    System.out.println(zonedDateTime1);
}
@Test
public void test1() {
    //时间间隔
    LocalTime localTime = LocalTime.now();
    LocalTime localTime1 = LocalTime.of(15, 23, 32);
    Duration between = Duration.between(localTime1, localTime);
    System.out.println(between);
    System.out.println(between.getSeconds());
    System.out.println(between.getNano());
    LocalDateTime localDateTime = LocalDateTime.of(2016, 6, 12, 15, 23, 32);
    LocalDateTime localDateTime1 = LocalDateTime.of(2017, 6, 12, 15, 23, 32);
    Duration between1 = Duration.between(localDateTime1, localDateTime);
    System.out.println(between1.toDays());
}
@Test
public void test2() {
    //Date间隔
    LocalDate now = LocalDate.now();
    LocalDate of = LocalDate.of(2028, 3, 18);
    Period between = Period.between(now, of);
    System.out.println(between);
    System.out.println(between.getYears());
    System.out.println(between.getMonths());
    System.out.println(between.getDays());
    Period period = between.withYears(2);
    System.out.println(period);
}
@Test
public void test3() {
    TemporalAdjuster next = TemporalAdjusters.next(DayOfWeek.SUNDAY);
    LocalDateTime with = LocalDateTime.now().with(next);
    System.out.println(with);
    //获取下一个工作日是哪天
    LocalDate with1 = LocalDate.now().with(temporal -> {
        LocalDate date = (LocalDate) temporal;
        switch (date.getDayOfWeek()) {
            case FRIDAY:
                return date.plusDays(3);
            case SATURDAY:
                return date.plusDays(2);
            default:
                return date.plusDays(1);
        }
    });
    System.out.println("下个工作日:"+with1);
}
```
# 旧API转换

|类|To遗留类|From遗留类|
|:--|:--|:--|
|java.time.Instant与java.util.Date|Date.from(instant)|date.toInstant()|
|java.time.Instant与java.sql.Timestamp|Timestamp.from(instant)|timestamp.toInstant()|
|java.time.ZonedDateTime 与java.util.GregorianCalendar|GregorianCalendar.from(zonedDateTime)|cal.toZonedDateTime |
|java.time.LocalDate与java.sql.Time|Date.valueOf(localDate) |date.toLocalDate() |
|java.time.LocalTime 与java.sql.Time|Date.valueOf(localDate) |date.toLocalTime() |
|java.time.LocalDateTime 与java.sql.Timestamp|Timestamp.valueOf(localDateTime) |timestamp.toLocalDateTime() |
|java.time.ZonedId与java.util.TimeZone|Timezone.getTimeZone(id) |timeZone.toZoneId() |
|java.time.format.DateTimeFormatter与java.text.DateFormat|formatter.toFormat() |无|

# 综合Demo
```
/**
 * @author riversky
 * @date 2020/04/07
 **/
public class Demo1 {
    public static void main(String[] args) {
//      tes1();
//        tes2();
//        tes3();
//        tes4();
//        tes5();
//        test6();
//        tes7();
        tes8();
    }
    /**
     * now 与of的基本使用
     */
    public static void tes1() {
        var now=Instant.now();
        System.out.println(now);
        LocalDate now1 = LocalDate.now();
        System.out.println(now1);
        LocalTime now2 = LocalTime.now();
        System.out.println(now2);
        LocalDateTime now3 = LocalDateTime.now();
        System.out.println(now3);
        ZonedDateTime now4 = ZonedDateTime.now();
        System.out.println(now4);

        Instant instant = Instant.ofEpochMilli(System.currentTimeMillis());
        System.out.println(instant);

        LocalDate of = LocalDate.of(2020, Month.APRIL, 7);
        System.out.println(of);
    }

    /**
     * 时区的使用
     */
    public static void tes2() {
        LocalDateTime now = LocalDateTime.now();
        ZonedDateTime zonedDateTime = now.atZone(ZoneId.systemDefault());
        System.out.println(zonedDateTime);

    }

    /**
     * 时间加减的使用
     */
    public static void tes3() {
        LocalDateTime now = LocalDateTime.now();
        LocalDateTime plus = now.plus(1, ChronoUnit.HOURS);
        System.out.println(plus);
    }

    /**
     * ChronoUtit的基于with的修改
     */
    public static void tes4() {
        LocalDateTime now = LocalDateTime.now();
        LocalDateTime with = now.with(ChronoField.SECOND_OF_MINUTE, 2);
        System.out.println(with);

    }
    /**
     * with 修改与调节器
     */
    public static void tes5() {
        LocalDateTime now = LocalDateTime.now();
        LocalDateTime with = now.with(TemporalAdjusters.firstDayOfNextYear());
        System.out.println(with);
    }

    /**
     * between
     */
    public static void test6(){
        LocalDateTime now = LocalDateTime.now();
        LocalDateTime plus = now.plus(3, ChronoUnit.HOURS);
        long seconds = Duration.between(now, plus).getSeconds();
        System.out.println(seconds);
    }

    /**
     * 转换
     */
    public static void tes7(){
        var date = new java.util.Date();
        Instant instant = date.toInstant();
        ZonedDateTime zonedDateTime = instant.atZone(ZoneId.systemDefault());
        LocalDate localDate = zonedDateTime.toLocalDate();
        System.out.println(localDate);

        Date date1 = new Date(System.currentTimeMillis());
        LocalDate localDate1 = date1.toLocalDate();
        System.out.println(localDate1);
    }
    /**
     * 格式化
     */
    public static void tes8(){
        LocalDateTime parse = LocalDateTime.parse("2020-04-07A11:18:02.156", DateTimeFormatter.ofPattern("yyyy-MM-dd'A'HH:mm:ss.SSS"));
        System.out.println(parse);
        String format = parse.format(DateTimeFormatter.ofPattern("yyyy'@'MM:dd HH:mm:ss"));
        System.out.println(format);
    }
}
```
