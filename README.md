Easy XML sitemap
===================================

Simple module for build a XML sitemap following to 
[Google's recommendations](https://support.google.com/webmasters/answer/2620865) 
for using "hreflang" attribute in sitemap of multilingual site.

Features
--------
Sitemap file will be accessible on URL *http(s)://your.domain/sitemap.xml* 
and automatically include URLs for: 

- pages created by nodes
- non-empty taxonomy terms pages
- public available pages by "Views" module

If some node is set as site's front page, URL of this node will be 
automatically excluded from sitemap to avoid content duplication.

For URLs which you do not want include to sitemap, exclusions may be added.

Each time sitemap re-built, backup copy of previous file state is saved as 
public://easy_xmlsitemap/sitemap.xml.bak

Optional and less important URLs attributes "priority" and "lastmod" 
are omitted in this version.

Installation
------------
If you have file "sitemap.xml" in website root directory, please remove 
or rename this file before you start module installation.

Install this module using the official Backdrop CMS instructions at 
https://backdropcms.org/guide/modules

Configuration and usage
-----------------------
Administration page is available via *Administration > Configuration > 
Search and metadata > Easy XML Sitemap* (admin/config/search/easy_xmlsitemap) 
and may be useful for:

- build XML sitemap by using button "BUILD SITEMAP NOW" (before first time build 
you will get error 404 from "/sitemap.xml)
- get information about last time sitemap build

under "SETTINGS" fieldset:
- set (if you need) different default base URL used for sitemap links
- select sitemap rebuild frequency: manually, daily (default) or any cron run
- add exclusions for URLs you won't include in sitemap (see description on the form).

License
-------

This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

Current Maintainer
------------------

Vladimir (https://github.com/findlabnet/)

