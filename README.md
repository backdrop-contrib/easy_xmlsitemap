Easy XML sitemap
===================================

Generates XML sitemap conforming to [Google's recommendations](https://support.google.com/webmasters/answer/2620865) 
for using "hreflang" attribute in sitemap on multilingual site and [sitemaps.org protocol](http://www.sitemaps.org/protocol.html).

Features
--------
Generated sitemap is available at *http(s)://your.domain/sitemap.xml* and include URLs for: 

- pages created by nodes;
- non-empty taxonomy terms pages;
- publicly available pages by "Views" module.

If one node is set as site's front page, direct URL to this node will be 
automatically excluded from sitemap to avoid content duplication.

URLs which you do not want include to sitemap may be excluded.

Content which presented on any of available languages can be excluded from the sitemap.

Each time sitemap re-built, backup copy of previous file state is saved as 
*public://easy_xmlsitemap/sitemap.xml.bak*

Less important and optional URLs attributes "priority" and "lastmod" are omitted in this version.

Installation
------------
If you have file "sitemap.xml" in website root directory, please remove 
or rename this file before you start module installation.

Install this module using the official Backdrop CMS instructions at 
https://backdropcms.org/guide/modules

Configuration and usage
-----------------------
Administration page is available via *Administration > Configuration > 
Search and metadata > Easy XML Sitemap* (admin/config/metadata/easy_xmlsitemap) 
and may be useful for:

- anytime (re)build XML sitemap by using button "BUILD SITEMAP NOW";
- view information when last time sitemap was generated.

Under "Advanced settings" fieldset:
- set (if you need) different default base URL used for sitemap links;
- select sitemap rebuild frequency: manually, daily (default) or any cron run;
- add exclusions for URLs you won't include in sitemap;
- add exclusions for content of languages you won't include in sitemap.

License
-------
This project is GPL v2 software. See the LICENSE.txt file in this directory for
complete text.

Current Maintainer
------------------
Vladimir (https://github.com/findlabnet/)

More information
----------------
For bug reports, feature or support requests, please use the module 
issue queue at https://github.com/backdrop-contrib/easy_xmlsitemap/issues.
