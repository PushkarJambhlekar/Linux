#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/netfilter.h>
#include <linux/netfilter_ipv4.h>

static struct nf_hook_ops nf_in;
static struct ts_config *config;

#define SEARCH_TEXT		"test"
#define SEARCH_TEXT_LEN		4

unsigned int hook_nf_in(void *priv,
			struct sk_buff *skb,
			const struct nf_hook_state *st)
{
	int pos;
	struct ts_state state;

	memset(&state, 0, sizeof(state));
	for(pos = skb_find_text(skb, 0, INT_MAX, config);
	    pos!= UINT_MAX;
	    pos = textsearch_next(config,&state))
	    	pr_debug("%s: Eudyptula ID found at 0x%x location\n",__func__, pos);

	return NF_ACCEPT;
}

static void init_nf(void)
{

	config = textsearch_prepare("kmp", SEARCH_TEXT, SEARCH_TEXT_LEN, GFP_KERNEL,
				  TS_AUTOLOAD);

	nf_in.hook	= hook_nf_in;
	nf_in.hooknum	= NF_INET_LOCAL_IN;
	nf_in.pf	= NFPROTO_IPV4;
	nf_in.priority	= NF_IP_PRI_FIRST;

	nf_register_hook(&nf_in);
}

static void exit_nf(void)
{
	nf_unregister_hook(&nf_in);
	textsearch_destroy(config);
}
static int __init hello_init(void)
{
	init_nf();
	printk("Hello World\n");
	return 0;
}

void __exit hello_exit(void)
{
	exit_nf();
	printk( "Goodbye world!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");

