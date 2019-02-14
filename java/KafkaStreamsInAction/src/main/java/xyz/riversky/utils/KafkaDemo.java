package xyz.riversky.utils;

import java.util.Arrays;
import java.util.List;

public class KafkaDemo {
    public   static void test(String key,int numberOfPartitions){
        int patition =key.hashCode()%numberOfPartitions;
    }
    public static void main(String[] args) {
    }
}
