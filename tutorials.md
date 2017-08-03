---
layout: page
title: Things explained
published: true
---

### Lindsay explains things for Lindsay

Sometimes, I can't find an effective tutorial on the Internet. So, I write myself
one. Past me explains things in dumb-person English so that future me, a
rather forgetful individual, does not have to figure it out again.

{% assign mydocs = site.tutorials | group_by: 'category' %}
{% for cat in mydocs %}
## {{cat.name | capitalize }}
{% assign items = cat.items | sort: 'order' %}
{% for item in items %}
  - [{{ item.title }}]({{ item.url }})
{% endfor %}

{% endfor %}
