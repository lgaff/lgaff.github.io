---
title: stuff others know
layout: page
published: true
---

## Other places on the Internet that are useful

These are snippets of information that I've collected over the years which needed a place to live outside my
Chrome bookmarks because I often forget they exist, and because others can't use them from there (unless you steal my laptop, I suppose)

Anyhow. Here's the list.

{% assign mydocs = site.links | group_by: 'category' %}
{% for cat in mydocs %}
## {{cat.name | capitalize }}
{% assign items = cat.items | sort: 'order' %}
{% for item in items %}
  - [{{ item.title }}]({{ item.url }})
{% endfor %}

{% endfor %}
