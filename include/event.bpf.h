#ifndef __EVENT_MAPPER_BPF_H
#define __EVENT_MAPPER_BPF_H


typedef unsigned int  __u32;

/*
 * 网络相关的Event
 */
// TP 
// for new sk_buff
#define EVENT_FEXIT_ALLOC_SKB 0x00
#define EVENT_FEXIT_BUILD_SKB 0x01
#define EVENT_TP_NAPI_GRO_RECEIVE_ENTRY 0x02
// cloned sk_buff
#define EVENT_FEXIT_SKB_CLONE 0x03
// begin of processing
#define EVENT_TP_NETIF_RECEIVE_SKB 0x04

// tc
#define EVENT_FENTRY_TCF_CLASSIFY_INGRESS 0x05
#define EVENT_FEXIT_TCF_CLASSIFY_INGRESS  0x06
#define EVENT_FENTRY_TCF_CLASSIFY       0x07
#define EVENT_FEXIT_TCF_CLASSIFY        0x08

// conntrack
#define EVENT_KPROBE_NF_CONNTRACK_IN    0x09
#define EVENT_KRET_NF_CONNTRACK_IN  0x0A

// iptabls
#define EVENT_KPROBE_IPT_DO_TABLE   0x0B
#define EVENT_KRET_IPT_DO_TABLE 0x0C
#define EVENT_KPROBE_IP6T_DO_TABLE  0x0D
#define EVENT_KRET_IP6T_DO_TABLE 0x0E

// queued to nic
#define EVENT_TP_NET_DEV_QUEUE  0x0F

// queue to socket
#define EVENT_KPROBE_TC_QUEUE_RCV  0x10
#define EVENT_KPROBE_UDP_QUEUE_RCV_SKB 0x11

#define EVENT_TP_CONSUME_SKB 0x12
#define EVENT_TP_KFREE_SKB  0x13
#define EVENT_FENTRY_KFREE_SKB 0x14


// for tplife
#define EVENT_KPROBE_NETIF_RX  0x15
#define EVENT_KPROBE_NETIF_RECEIVE_SKB  0x16
#define EVENT_KPROBE_TPACKET_RCV 0x17
#define EVENT_KPROBE_PACKET_RCV 0x18
#define EVENT_KPROBE_NAPI_GRO_RECEIVE 0x19
#define EVENT_KPROBE_DEV_QUEUE_XMIT 0x1A
// kp not exiting
#define EVENT_KPROBE_BR_HANDLE_FRAME_FINISH 0x1B
#define EVENT_KPROBE_BR_NF_PRE_ROUTINE 0x1C
#define EVENT_KPROBE_BR_NF_PRE_ROUTINE_FINISH 0x1D
#define EVENT_KPROBE_BR_PASS_FRAME_UP 0x1E
#define EVENT_KPROBE_BR_NETIF_RECEIVE_SKB 0x1F
#define EVENT_KPROBE_BR_FORWARD 0x20
#define EVENT_KPROBE___BR_FOEWARD 0x21
#define EVENT_KPROBE_BR_FORWARD_FINISH 0x22
#define EVENT_KPROBE_BR_NF_FORWARD_IP 0x23
#define EVENT_KPROBE_BR_NF_FORWARD_FINISH 0x24
#define EVENT_KPROBE_BR_NF_POST_ROUTINE 0x25
#define EVENT_KPROBE_BR_NF_DEV_QUEUE_XMIT 0x26
#define EVENT_KPROBE_IP_RCV 0x27
#define EVENT_KPROBE_IP_RCV_FINISH 0x28
#define EVENT_KPROBE_IP_OUTPUT 0x29
#define EVENT_KPROBE_IP_FINISH_OUTPUT 0x2A
#define EVENT_KRET_KFREE_SKB 0x2B



#endif