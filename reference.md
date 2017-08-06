---
title: reference stuff
layout: page
published: true
---

# Reference documentation

The information contained in this section is a general reference for various subjects
Some of this is links from the Internet to technical documentation or searchable reference tools;
the rest are my own notes I've tried to organise into something useful. If you're looking for more of a step-by-step guide to something,
It can be found in [explain stuff]({% link tutorials.md %})

{% assign mydocs = site.reference | group_by: 'category' %}
{% for cat in mydocs %}
## {{cat.name | capitalize }}
{% assign items = cat.items | sort: 'order' %}
{% for item in items %}
  - [{{ item.title }}]({{ item.url }})
{% endfor %}

{% endfor %}
