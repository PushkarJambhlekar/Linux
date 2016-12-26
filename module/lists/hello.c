#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/string.h>
#include <linux/slab.h>
struct identity {
	char name[20];
	int id;
	bool busy;
	struct list_head list;
};

static struct identity *db_list=NULL;
static struct kmem_cache *id_cache = NULL;

int identity_create(char *name, int id)
{
	struct identity *tmp = NULL;
	if(!db_list) {
		db_list = kmem_cache_alloc(id_cache, GFP_KERNEL);
		INIT_LIST_HEAD(&db_list->list);
	}

	tmp = kmem_cache_alloc(id_cache, GFP_KERNEL);
	INIT_LIST_HEAD(&tmp->list);

	strncpy(tmp->name, name, 20);
	tmp->id = id;

	list_add(&(tmp->list), &(db_list->list));
	printk("Creating Identity: name=:%s\tid:%d\n",tmp->name,tmp->id);
	return 0;
}

struct identity *identity_find(int id)
{
	struct list_head *pos = NULL;
	struct identity *tmp;
	list_for_each(pos, &db_list->list) {
		tmp = list_entry(pos, struct identity, list);
		if(tmp->id == id)
			return tmp;
	}

	return NULL;
}

void identity_destroy (int id)
{
	struct list_head *itr,*q;
	struct identity *tmp;
	list_for_each_safe(itr,q,&db_list->list) {
		tmp = list_entry(itr, struct identity, list);
		if (tmp->id == id)
		{
			list_del(itr);
			kmem_cache_free(id_cache, tmp);
		}
	}
}

static int __init hello_init(void)
{
    struct identity *temp;
    printk("Hello World\n");

    id_cache = kmem_cache_create("identity", sizeof(struct identity), 0, 0, NULL);
	identity_create("Pushkar",1);
	identity_create("Bob", 2);
	identity_create("Dave", 3);
	identity_create("Gena", 10);

	temp = identity_find(3);
	printk("id 3 = %s\n", temp->name);

	temp = identity_find(42);

	if (temp == NULL)
		printk("id 42 not found\n");

	identity_destroy(2);
	identity_destroy(1);
	identity_destroy(10);
	identity_destroy(42);
	identity_destroy(3);
    return 0;
}

void __exit hello_exit(void)
{
	if(id_cache)
		kmem_cache_destroy(id_cache);
    printk( "Goodbye world!\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");

