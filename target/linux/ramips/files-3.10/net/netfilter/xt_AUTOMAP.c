/* x_tables module for setting the IPv4/IPv6 DSCP field, Version 1.8
 *
 * (C) 2002 by Harald Welte <laforge@netfilter.org>
 * based on ipt_FTOS.c (C) 2000 by Matthew G. Marsh <mgm@paktronix.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * See RFC2474 for a description of the DSCP field within the IP Header.
 *
 * xt_DSCP.c,v 1.8 2002/08/06 18:41:57 laforge Exp
*/

#include <linux/module.h>
#include <linux/skbuff.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <net/dsfield.h>
#include <linux/if_vlan.h>

#include <linux/netfilter/x_tables.h>
#include <linux/netfilter/xt_AUTOMAP.h>
#include <linux/netfilter/xt_DSCP.h>
#include <net/dsfield.h>

#include <linux/version.h>

MODULE_LICENSE("GPL");
MODULE_ALIAS("ipt_AUTOMAP");
MODULE_ALIAS("ip6t_AUTOMAP");
#if 0
static int getVlanPrioAndIpHeader(struct sk_buff *skb, unsigned char *prio, struct iphdr **iph){
	unsigned short TCI;
	unsigned short id;	/* VLAN ID, given from frame TCI */
	 /* Need to recalculate IP header checksum after altering TOS byte */
	const struct vlan_hdr *fp;
	struct vlan_hdr _frame;
	struct iphdr *ih = NULL;

	/* get ip header */
	ih = NULL;
	ih = ip_hdr(skb);

	*iph = ih;

	/* check VLAN header is parsed or not ? */
	if(ntohs(((struct vlan_hdr *)(skb->vlan_header))->h_vlan_encapsulated_proto) == 0){

		/* tagged packet */
		if(skb->protocol == ETH_P_8021Q) {

             fp = skb_header_pointer(skb, 0, sizeof(_frame), &_frame);
             if (fp == NULL)
                return -1;

          /* Tag Control Information (TCI) consists of the following elements:
	              * - User_priority. The user_priority field is three bits in length,
	              * 	interpreted as a binary number.
	              * - Canonical Format Indicator (CFI). The Canonical Format Indicator
	              *	 (CFI) is a single bit flag value. Currently ignored.
	              * - VLAN Identifier (VID). The VID is encoded as
	              * 	an unsigned binary number.
	            */
             TCI = ntohs(fp->h_vlan_TCI);
             id = TCI & VLAN_VID_MASK;
             *prio = (TCI >> 13) & 0x7;

		}
		else { /* untagged packet */
			TCI = 0;
			id = 0;
			/* Packet with no VLAN tag will be sent to default queue just like 1p value is 1 */
			*prio = 1;
		}

    }
	else{
         /* for new broadcom vlan device */
         TCI = ((struct vlan_hdr *)(skb->vlan_header))->h_vlan_TCI;
         id = TCI & VLAN_VID_MASK;
         *prio = (TCI >> 13) & 0x7;
    }

	return 0;
}
#endif

//static unsigned int target(struct sk_buff **pskb, const struct xt_tgchk_param *par)
static unsigned int AUTOMAP_target_v4(struct sk_buff *skb, const struct xt_action_param *par)
{
	const struct xt_automap_target_info *aminfo = par->targinfo;
	const struct vlan_hdr *fp;
	struct vlan_hdr _frame;
	struct iphdr *iph = NULL;
	unsigned char prio = 0;
	unsigned char dscpPrecedence = 0;
	unsigned short TCI;
	unsigned short id;

	/* get ip header */
#if LINUX_VERSION_CODE >= KERNEL_VERSION(3,11,0)
	if (skb->protocol == __constant_htons(ETH_P_IP))
		iph = (struct iphdr *)skb_network_header(skb);
    else if (skb->protocol == __constant_htons(ETH_P_8021Q)) {
        if (*(unsigned short *)(skb_network_header(skb) + VLAN_HLEN - 2) == __constant_htons(ETH_P_IP))
			iph = (struct iphdr *)(skb_network_header(skb) + VLAN_HLEN);
    }
#else
	if (skb->protocol == __constant_htons(ETH_P_IP))
		iph = (struct iphdr *)(skb->network_header);
    else if (skb->protocol == __constant_htons(ETH_P_8021Q)) {
        if (*(unsigned short *)(skb->network_header + VLAN_HLEN - 2) == __constant_htons(ETH_P_IP))
			iph = (struct iphdr *)(skb->network_header + VLAN_HLEN);
    }
#endif
	
	switch(aminfo->type){
		case AUTOMAP_TYPE_8021P:
			prio = ((skb)->vlan_tci>>13)&0x7;
			/* mark priority queue */
			skb->mark |= vlan8021pToPriorityQueue[prio];

			/* lookup upstream 8021p to DSCP value table */
			//dscp = vlan8021pToDSCP[prio];

			/* mark DSCP value */
			//if (!skb_make_writable(skb, sizeof(struct iphdr)))
	        //                return NF_DROP;

	        //ipv4_change_dsfield(ip_hdr(skb), (__u8)(~XT_DSCP_MASK), dscp << XT_DSCP_SHIFT);

			break;
		case AUTOMAP_TYPE_DSCP:
			
			if(iph==NULL)
				skb->mark|=0x0;
			else {
				/* get dscp precedence */
				dscpPrecedence = ((iph->tos)>>5)&0x7;

				/* mark value for priority queue */
				skb->mark |= dscpPrecedenceToPriorityQueue[dscpPrecedence];
			}
			break;
		case AUTOMAP_TYPE_PKTLEN:
			if(iph==NULL)
				skb->mark|=0x0;
			else {
				if(iph->tot_len > 1100){
					skb->mark|=vlan8021pToPriorityQueue[1]; /* queue prio 4 */
				}else if(iph->tot_len < 250){
					skb->mark|=vlan8021pToPriorityQueue[6]; /* queue prio 2 */
				}else{  /*250~1100*/
					skb->mark|=vlan8021pToPriorityQueue[3]; /* queue prio 3 */
				}
			}
			break;
		default:
			break;
	}
	
	return XT_CONTINUE;
}


static int AUTOMAP_checkentry_v4(const struct xt_tgchk_param *par)
{
	return 0;
}

static struct xt_target xt_auto_target __read_mostly = {

	.name		= "AUTOMAP",
	.revision   = 0,
	.family		= NFPROTO_IPV4,
	.checkentry	= AUTOMAP_checkentry_v4,
	.target		= AUTOMAP_target_v4,
	.targetsize	= sizeof(struct xt_automap_target_info),
	.table		= "mangle",
	.me		= THIS_MODULE,

};

static int __init xt_automap_target_init(void)
{
	//return xt_register_targets(xt_auto_target, ARRAY_SIZE(xt_auto_target));
	return xt_register_target(&xt_auto_target);
}

static void __exit xt_automap_target_fini(void)
{
	//xt_unregister_targets(xt_auto_target, ARRAY_SIZE(xt_auto_target));
	xt_unregister_target(&xt_auto_target);
}

module_init(xt_automap_target_init);
module_exit(xt_automap_target_fini);
