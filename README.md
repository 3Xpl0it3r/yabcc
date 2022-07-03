# yabcc
rewrite bcc/tools with libbpf  to support co-re

#### Usage
```bash
git clone https://github.com/3Xpl0it3r/yabcc.git
cd yabcc
# midify Makefile path of libbpf header, 

make

l0calh0st@l0calh0st:~/yabcc$ sudo ./bcc --help
Usage: bcc [OPTION...] [iotop|cachestat]

 common
  -i, --interval=Int         interval

 CacheState
  -T, --timestamp            print the timestamp

 iotop
      --sort=Str             sort by [io|byte|cost]

  -?, --help                 Give this help list
      --usage                Give a short usage message
  -V, --version              Print program version

Mandatory or optional arguments to long options are also mandatory or optional
for any corresponding short options.

Report bugs to shouc.wang@hotmail.com.
```

#### TODO List

- [x] biotop
- [x] cachestat
- [] argdist
- [] bashreadline
- [] bindsnoop
- [] biolatency
- [] biolatpcts
- [] biopattern
- [] biosnoop
- [] bitesize
- [] bpflist
- [] btrfsdist
- [] btrfsslower
- [] cachetop
- [] capable
- [] compactsnoop
- [] cpudist
- [] cpuunclaimed
- [] criticalstat
- [] dbslower
- [] dbstat
- [] dcsnoop
- [] dcstat
- [] deadlock
- [] dirtop
- [] drsnoop
- [] execsnoop
- [] exitsnoop
- [] ext4dist
- [] ext4slower
- [] filelife
- [] fileslower
- [] filetop
- [] funccount
- [] funcinterval
- [] funclatency
- [] funcslower
- [] gethostlatency
- [] hardirqs
- [] inject
- [] killsnoop
- [] klockstat
- [] kvmexit
- [] llcstat
- [] mdflush
- [] memleak
- [] mountsnoop
- [] mysqld_qslower
- [] netqtop
- [] nfsdist
- [] nfsslower
- [] offcputime
- [] offwaketime
- [] oomkill
- [] opensnoop
- [] pidpersec
- [] profile
- [] readahead
- [] runqlat
- [] runqlen
- [] runqslower
- [] shmsnoop
- [] slabratetop
- [] sofdsnoop
- [] softirqs
- [] solisten
- [] sslsniff
- [] stackcount
- [] statsnoop
- [] swapin
- [] syncsnoop
- [] syscount
- [] tcpaccept
- [] tcpcong
- [] tcpconnect
- [] tcpconnlat
- [] tcpdrop
- [] tcplife
- [] tcpretrans
- [] tcprtt
- [] tcpstates
- [] tcpsubnet
- [] tcpsynbl
- [] tcptop
- [] tcptracer
- [] threadsnoop
- [] tplist
- [] trace
- [] ttysnoop
- [] vfscount
- [] vfsstat
- [] virtiostat
- [] wakeuptime
- [] xfsdist
- [] xfsslower
- [] zfsdist
- [] zfsslower

