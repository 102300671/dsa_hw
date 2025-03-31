---
layout: home
title: "欢迎来到我的数据结构作业站点"
---

## 这是我的数据结构作业

欢迎访问我的数据结构作业站点。在这里，你可以找到我的数据结构作业和其他相关内容。
源代码 ：[C](https://github.com/102300671/102300671DS-HW.github.io/tree/main/c)/[C++](https://github.com/102300671/102300671DS-HW.github.io/tree/main/cpp)

{% for post in site.posts %}
{% assign file_components = post.path | split: '/' | last | split: '.' | first | split: '-' %}
{% assign year = file_components[0] %}
{% assign month = file_components[1] %}
{% assign day = file_components[2] %}
<p>{{ year }}-{{ month }}-{{ day }}</p>
<p><a href="{{site.baseurl}}{{ post.url }}">{{ post.title }}</a></p>
{% endfor %}
