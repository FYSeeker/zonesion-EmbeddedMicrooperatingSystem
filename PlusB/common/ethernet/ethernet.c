#include "ethernet.h"


uip_lladdr_t EthAddr = {0};//网卡地址
uip_ipaddr_t HostIpAddr = {0};
uip_ipaddr_t GatewayIpAddr = {0};
uip_ipaddr_t NetworkMask = {0};


uint8_t tapdev_init()
{
    return etherdev_init();
}

uint16_t tapdev_read()
{
    return etherdev_read();
}

void tapdev_send(void)
{
    etherdev_send();
}

void localHostAddrInit(void)
{
    EthAddr.addr[0] = emacETHADDR0;
    EthAddr.addr[1] = emacETHADDR1;
    EthAddr.addr[2] = emacETHADDR2;
    EthAddr.addr[3] = emacETHADDR3;
    EthAddr.addr[4] = emacETHADDR4;
    EthAddr.addr[5] = emacETHADDR5;
    uip_setethaddr(EthAddr);
    
    uip_ipaddr(&HostIpAddr, 192,168,1,101);		//Host IP address
    uip_sethostaddr(&HostIpAddr);
    uip_ipaddr(&GatewayIpAddr, 192,168,1,1);		//Default Gateway
    uip_setdraddr(&GatewayIpAddr);
    uip_ipaddr(&NetworkMask, 255,255,255,0);     //Network Mask
    uip_setnetmask(&NetworkMask);
}

uint8_t TcpipOutput()
{
    uip_arp_out();
    tapdev_send();
    return 0;
}

void tcpipFuncInit(void)
{
    tcpip_set_outputfunc(TcpipOutput);
}

void uipSendPing(uip_ipaddr_t *dest_addr)
{
    static uint16_t ipid = 0;
    static uint16_t seqno = 0;

    UIP_IP_BUF->vhl = 0x45;
    UIP_IP_BUF->tos = 0;
    UIP_IP_BUF->ipoffset[0] = UIP_IP_BUF->ipoffset[1] = 0;
    ++ipid;
    UIP_IP_BUF->ipid[0] = ipid >> 8;
    UIP_IP_BUF->ipid[1] = ipid & 0xff;
    UIP_IP_BUF->proto = UIP_PROTO_ICMP;
    UIP_IP_BUF->ttl = UIP_TTL;

    uip_ipaddr_copy(&UIP_IP_BUF->destipaddr, dest_addr);
    uip_ipaddr_copy(&UIP_IP_BUF->srcipaddr, &uip_hostaddr);

    UIP_ICMP_BUF->type = ICMP_ECHO;
    UIP_ICMP_BUF->icode = 0;
    UIP_ICMP_BUF->id = 0xadad;
    UIP_ICMP_BUF->seqno = uip_htons(seqno++);

    uip_len = UIP_ICMPH_LEN + UIP_IPH_LEN + PING_DATALEN;
    UIP_IP_BUF->len[0] = (uint8_t)((uip_len) >> 8);
    UIP_IP_BUF->len[1] = (uint8_t)((uip_len) & 0x00ff);

    UIP_ICMP_BUF->icmpchksum = 0;
    UIP_ICMP_BUF->icmpchksum = ~uip_chksum((uint16_t *)&(UIP_ICMP_BUF->type),
                                           UIP_ICMPH_LEN + PING_DATALEN);

    /* Calculate IP checksum. */
    UIP_IP_BUF->ipchksum = 0;
    UIP_IP_BUF->ipchksum = ~(uip_ipchksum());

    tcpip_output();
}


PROCESS(uip_poll, "uip_poll");

PROCESS_THREAD(uip_poll, ev, data)
{
    static struct etimer arp_timer;
    static process_event_t uipPoll_event;
    
    PROCESS_BEGIN();
    
    etimer_set(&arp_timer, 100);
    while(tapdev_init())//dev init
    {
        PROCESS_WAIT_EVENT();
        if(ev == PROCESS_EVENT_TIMER)
        {
            etimer_set(&arp_timer, 100);
            LED2 = !LED2;
        }
    }
    LED2 = 1;//OFF
    
    uip_arp_init();
    localHostAddrInit();//本地主机地址初始化
    tcpipFuncInit();
    
    uipPoll_event = process_alloc_event();
    etimer_set(&arp_timer, 1000*10);
    process_post(&uip_poll,uipPoll_event,NULL);
    
    while(1)
    {
        PROCESS_WAIT_EVENT();
        if(ev == uipPoll_event)
        {
            process_post(&uip_poll,uipPoll_event,NULL);//polling event
            
            uip_len = tapdev_read();
            if(uip_len > 0)
            {
                if(BUF->type == uip_htons(UIP_ETHTYPE_IP))
                {
                    uip_arp_ipin();
                    //uip_input();
                    tcpip_input();
                    /* If the above function invocation resulted in data that
                    should be sent out on the network, the global variable
                    uip_len is set to a value > 0. */
                    if(uip_len > 0)
                    {
                        uip_arp_out();
                        tapdev_send();
                    }
                }
                else if(BUF->type == uip_htons(UIP_ETHTYPE_ARP))
                {
                    uip_arp_arpin();
                    /* If the above function invocation resulted in data that
                    should be sent out on the network, the global variable
                    uip_len is set to a value > 0. */
                    if(uip_len > 0)
                    {
                        tapdev_send();
                    }
                }
                
            }
            /* Call the ARP timer function every 10 seconds. */
            if(etimer_expired(&arp_timer))
            {
                etimer_reset(&arp_timer);
                uip_arp_timer();
            }
        }
    }
    PROCESS_END();
}



PROCESS(ethernet_process, "ethernet_process");

PROCESS_THREAD(ethernet_process, ev, data)
{
    PROCESS_BEGIN();
    
    process_start(&tcpip_process,NULL);
    process_start(&uip_poll,NULL);
    
    PROCESS_END();
}
