# Palo Alto Watch

 
**Palo Alto Watch** is a series of  infos and scripts for deep FireWall Investigations in [Splunk] or Elastic,

this brings many new details to the existing charts of the [standard] Palo Alto tool.


 

When you need to investigate specific details of what is going on the PA parameters help.

Several SNMP OIDs are rarelly documented but able to track Palo Alto traffic in detail, 

  simple scripts can collect among many FWs and feed logs to Elastic or Splunk for plots.

 This splunk query shows peaks in TCP

while a specific website received from 500

 ![Image of Yaktocat](doc/.png)

### Notes

a
:

splunk
: ![splunk image](doc/1113-fw.png)

standard
: [standard PA image[

[splunk]: #notes "image below"

[standard]: #notes "image below"  

b
:


### PA standards

Since PAN-OS v7.0.0, the following counters could also be accessed through Palo Alto Networks private MIBs:
 
- panGlobalCountersDOSCounters
- panGlobalCountersDropCounters
- panGlobalCountersIPFragmentationCounters
- panGlobalCountersTCPState
 
while  CLI command to extract Flow counters with a DoS aspect:
> show counter global filter category flow aspect dos


 
### OLDER <2015

#### Beluga Information-Change coding language  
 
graphical flows coded in beluga graphical language. 
examples querying Google App Enginge infchg site are shown in beluga-

currently the application was renamed in the Google Compute preview App
the google cloud URLs  are no longer reacheable, Since the Beluga service was moved to other cloud servers, 
  - backlog:  the urls to be updated with the correct servers apps on GC & AWS

