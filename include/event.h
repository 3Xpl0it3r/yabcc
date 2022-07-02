
#include "event.bpf.h"

#include <string.h>
#include <stdlib.h>

#define MAX_EVENT_SIZE 64
struct event_kind_t {
    __u32 key;
    char *value;
};

struct event_kind_t* event_mapper[MAX_EVENT_SIZE]; 

__u32 hashCode(__u32 key) {
   return key % MAX_EVENT_SIZE;
}


void event_register(__u32 key,char* event_value) {

    struct event_kind_t *item = (struct event_kind_t*)malloc(sizeof(*item));
    item->value = (char*)malloc(strlen(event_value));
    strncpy(item->value, event_value, strlen(event_value) * sizeof(char));

   event_mapper[key] = item;
}

struct event_kind_t *get_event_item(__u32 key) {
    struct event_kind_t *item = event_mapper[key];
    return item;
}

void register_all_event(void)
{
    /*
    event_register(EVENT_TP_NAPI_GRO_RECEIVE_ENTRY, "napi_gro_receive_entry");
    event_register(EVENT_KPROBE_NETIF_RX, "kprobe/netif_rx");
    event_register(EVENT_KPROBE_NETIF_RECEIVE_SKB, "__netif_receive_skb");
    event_register(EVENT_KPROBE_TPACKET_RCV, "tpacket_rcv");
    event_register(EVENT_KPROBE_PACKET_RCV, "packet_rcv");
    event_register(EVENT_KPROBE_NAPI_GRO_RECEIVE, "napi_gro_receive_entry");
    event_register(EVENT_KPROBE_DEV_QUEUE_XMIT, "__dev_queue_xmit");
    event_register(EVENT_KPROBE_BR_HANDLE_FRAME_FINISH, "br_handle_frame_finish");
    event_register(EVENT_KPROBE_BR_NF_PRE_ROUTINE, "br_nf_pre_routing");
    event_register(EVENT_KPROBE_BR_NF_PRE_ROUTINE_FINISH, "bf_nf_pre_routing_finish");
    event_register(EVENT_KPROBE_BR_PASS_FRAME_UP, "br_nf_pass_frame_up");
    event_register(EVENT_KPROBE_BR_NETIF_RECEIVE_SKB, "br_netif_receive_skb");
    event_register(EVENT_KPROBE_BR_FORWARD, "br_forward");
    event_register(EVENT_KPROBE___BR_FOEWARD, "__br_forward");
    event_register(EVENT_KPROBE_BR_FORWARD_FINISH, "br_forward_finish");
    event_register(EVENT_KPROBE_BR_NF_FORWARD_IP, "br_nf_forward_ip");
    event_register(EVENT_KPROBE_BR_NF_FORWARD_FINISH, "bf_nf_forward_finish");
    event_register(EVENT_KPROBE_BR_NF_POST_ROUTINE, "bf_nf_post_routine");
    event_register(EVENT_KPROBE_BR_NF_DEV_QUEUE_XMIT, "br_nf_dev_queue_xmit");
    event_register(EVENT_KPROBE_IP_RCV, "ip_rcv");
    event_register(EVENT_KPROBE_IP_RCV_FINISH, "ip_rcv_finish");
    event_register(EVENT_KPROBE_IP_OUTPUT, "ip_output");
    event_register(EVENT_KPROBE_IP_FINISH_OUTPUT, "ip_finish_output");
    event_register(EVENT_KPROBE_IPT_DO_TABLE, "ipt_do_table");
    event_register(EVENT_KRET_IPT_DO_TABLE, "ret/ipt_do_table");
    event_register(EVENT_KPROBE_IP6T_DO_TABLE, "ip6t_do_table");
    event_register(EVENT_KRET_IP6T_DO_TABLE, "ret/ipv6_do_table");
    event_register(EVENT_KRET_KFREE_SKB, "ret/kfree_skb");
    */
}

void unregister_all_event(void)
{
    struct event_kind_t *item;
    for (int i = 0 ; i < MAX_EVENT_SIZE; i ++) {
        item = event_mapper[i];
        if (item != NULL) {
            if (item->value != NULL) {
                free(item->value);
                item->value = NULL;
            }
            free(item);
            item = NULL;
        }
    }
}
