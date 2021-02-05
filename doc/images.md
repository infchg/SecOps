identified 8 Palo Alto Counters that can be monitored and sent to logs (e.g. in Matlab)
![in matlab](18n-counters2.PNG)

 Example of TCP peaks detected with these counters, some available in CLI too, but these SNMP pull let us track in our own tools.
 ![demo of TCP peaks detected](1113-fw.png)

These scripts followed 10 firewalls around America, Asia, Europe. The picture show only America traffic, tracked via SNMP a pair of palo-altos in HA.
![fw](26s-fw.png)

Althought those examples tracked millions hits to many brands and apps,
the method to track PA applies to normal traffic for few webs as well.

There is allways a small percentage ~2% of regular traffic related to NonSYN NonSession drops, randomly distributed as caused by individual user device or user isp disconections. 

However this close monitoring of Palo Alto counters let us identify precisely moments of short disruptions ocurrent in own or near-own infrastructures, for instance causedg by eBGP renegotiation after a link failure.

Attacks are also very easy to identify as in these pictures 
![](ISP-dos-alerts.png)
![demo: nonsessions PAloAlto counter during attacks](nonsess-sep17-12hrs.png)

all these complement existing Palo Alto standard summary of traffic, adding very usefull details we can explore in elastic, splunk, etc.
![Palo Alto standard summary of traffic](pa-standard.png)


 
