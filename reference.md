---
layout: page
title: Useful stuff
published: true
---

## Reference documentation

The information contained in this section is a general reference for various subjects. If you're looking for more of a step-by-step guide to something,
It can be found in [Things explained]({% link tutorials.md %})

{% assign mydocs = site.tutorials | group_by: 'category' %}
{% for cat in mydocs %}
## {{cat.name | capitalize }}
{% assign items = cat.items | sort: 'order' %}
{% for item in items %}
  - [{{ item.title }}]({{ item.url }})
{% endfor %}

{% endfor %}
