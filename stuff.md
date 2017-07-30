---
layout: page
title: Infodump
published: true
---

# Useful information (for someone, probably)

These are snippets of information that I've collected over the years which needed a place to live outside my
Chrome bookmarks.

First, because a number of these pages are not link dumps, but actual
guides or documentation relating to tools or programs I use regularly; information that often falls out
of my head unless I write it down somewhere.

Second, because I always forget that my bookmarks are there.

Third, because you can't see my bookmarks (unless you steal my laptop, I suppose), so I can't share the information.

Anyhow. Here's the list.

{% assign mydocs = site.docs | group_by: 'category' %}
{% for cat in mydocs %}
## {{cat.name | capitalize }}
{% assign items = cat.items | sort: 'order' %}
{% for item in items %}
  - [{{ item.title }}]({{ item.url }})
{% endfor %}

{% endfor %}
