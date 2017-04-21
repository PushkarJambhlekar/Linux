#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <linux/mutex.h>

struct identity {
	char name[20];
	int id;
	bool busy;
	struct list_head list;
};

//static struct identity *db_head;
static LIST_HEAD(db_head);
static struct mutex db_lock;
static struct kmem_cache *db_cache;

static void __id_add(struct identity *obj)
{
	list_add (&obj->list, &db_head);
}
static int identity_create(char *name, int id)
{
	struct identity *temp;

	if (!name) {
		pr_err("%s: name argument is null\n", __func__);
		return -EINVAL;
	}

	temp = kmem_cache_alloc(db_cache, GFP_KERNEL);
	if (!temp)
		return -ENOMEM;

	strncpy(temp->name, name, 20);
	temp->id = id;
	temp->busy = false;
	INIT_LIST_HEAD(&temp->list);

	mutex_lock (&db_lock);
	__id_add(temp);
	mutex_unlock (&db_lock);

	return 0;
}

static struct identity *identity_find(int id)
{
	struct identity *it = NULL;

	mutex_lock (&db_lock);
	list_for_each_entry (it, &db_head, list) {
		if (it->id == id)
			goto exit;
	}
	it = NULL;
exit:
	mutex_unlock (&db_lock);

	return it;
}

static void identity_destroy(int id)
{
	struct identity *id_node = identity_find(id);

	if (!id_node)
		return;

	list_del(&id_node->list);
	kmem_cache_free(db_cache, id_node);
}

static void init_list(void)
{
	struct identity *temp;

	mutex_init (&db_lock);
	db_cache = kmem_cache_create ("identity", sizeof(struct identity),
				     0, 0, NULL);
	if (identity_create("Alice", 1))
		pr_err("Failed to create identity for Alice\n");

	if (identity_create("Bob", 2))
		pr_err("Failed to create identity for Bob\n");

	if (identity_create("Dave", 3))
		pr_err("Failed to create identity for Dave\n");

	if (identity_create("Gena", 10))
		pr_err("Failed to create identity for Gena\n");


	temp = identity_find(3);
	pr_debug("id 3 = %s\n", temp->name);

	temp = identity_find(42);
	if (temp == NULL)
		pr_debug("id 42 not found\n");

	identity_destroy(2);
	identity_destroy(1);
	identity_destroy(10);
	identity_destroy(42);
	identity_destroy(3);
}
static int __init hello_init(void)
{
	init_list();
	return 0;
}

void __exit hello_exit(void)
{
	kmem_cache_destroy(db_cache);
	pr_debug ("Exiting list module\n");
}


module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("GPL");

