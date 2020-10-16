# fake_darknet_ros

必要パッケージ

[darknet_ros](https://github.com/leggedrobotics/darknet_ros)

### Usage

~~~
# config/yolo_result.txt

# 1番目の検出結果
Class1,probability1
Class2,probability2
...
---
# 2番目の検出結果
Class1,probability1
Class2,probability2
...
---
...
~~~

~~~
human,0.8
pen,0.5
---
yakiniku,1.0
---
~~~

~~~
$ roslaunch fake_darknet_ros fake_darknet_ros.launch
>> 1
１番目の検出結果をパブリッシュ
>> 2
2番目の検出結果をパブリッシュ
~~~

